

/* Console controller - stops only
*  This structure accepts and reports MIDI messages. All vagaries relating to LED vs SAM are taken care of by microprocessors local to the LED or SAM.
*
* The stop action interface is a 10 pin multi-drop bus. The pinout is as follows:
*1- PeriphOut  2- MasterOut
*3-VCC   4-nRESET
*5-GND   6-SYNC_LOAD
*7-CLK   8-GND
*9-SAMPWR  10-SAMPWR
*PERIPHOUT - Output from peripheral to master. Pulled up hard (470 ohm). Peripheral uses open collector driver to indicate a 0, no drive or drive and release to indicate a 1. Multiple peripherals share this output.
*MASTEROUT - Output from master to peripheral. Always drive from master (SAMMidiProc
*SYNC/LOAD- A high to low transition indicates to every to reset counters. The next clock after Sync/Load goes to 0 is  the start of the read.write chain. Clock must be low on SYNC.
*CLOCK – Peripherals and master change data on rising edge, read data on falling edge. This clock will be no faster than 100KHz, high will be at least 5ms, low at least 5ms. Peripheral should respond within 3ms.

* There are 256 data bit slots. Bit 0 (least significant bit) is on the closest clock to the SYNC signal.
*
* This software instance provides the same timing on two different chains. The results are reported on different MIDI channels.
* The MIDI notes are spread across 2 channels.  So for chain 1, it's MIDIChannel and MIDIChannel+1;  For chain 2, it's MIDIChannel+2 and MIDIChannel+3
*
* The key action is an 8 pin daisy-chain interface.  It drives a shift register chain. There are 2 separate interfaces., each capable of 256 keys (4 manuals, or 3 manuals and pedal will fit in one interface).
* Pinout of the 8 pin interface is
* 1 – Input to shift chain (SER) 	2- Output from shift chain (nQH)
* 3 – VCC (3.3V)      				4- nRST (SRCLR)
* 5 – GND     						6 – LOAD (RCLK and G/OutputEnable)
* 7 – CLK (SRCLK)     				8 – GND
* Operation of the signals is governed by the component used: 74HC597 serial shift register, parallel input, serial output.
* The key channel 1 is MIDIChannel+4 and MIDIChannel+5
* The key channel 2 is MIDIChannel+6 and MIDIChannel+7
* 
* 
* This implementation in order to reduce latentcy limits the SAM to 64 slots per chain.  The keyboards do 2 clocks per slot (it's not a software controlled shift register)
* 
*/


 /* General CA inputs are 
  *   G.C.
  *   Stop sense lines
  * Combination inputs are
  *   SET
  *   MEM+
  *   MEM-
  *   Crescendo
  *   Prev
  *   Next
  * 
  * SD card format is as follows
  * File names for each memory is Allnnnmm.mem.  Leading 0's.  l=expansion nnn=memory level, mmm=piston number.  In hex.
  * The bit fields are loaded for the piston pressed when pressed. 
  * A prefix is for this revision which has 256 bit (16 word) stop fields.  It uses only SAMCHAIN1 (index 0)
  * All pistons can do anything.
  * Effect masks are in ROM
  * 
  * 
  * CRESCENDO
  * Current implementation has one level of Crescendo.
  * 
  * Crescendo is XCnnmmmm.CRE  nn=crescendo number, mmmm=stage number.  The field is accessed from the SD card as the crescendo pedal is changed and applied to the stops
  * Crescendo is silent, so while in crescendo state, the crescendo routine sends midi note on and note off without updating Current or Previons state
  * Pressing a piston or pulling a stop does change the stops 
  * When in crescendo state, MIDI Ins should be ignored
  * 
  * Setting crescendo = Press "SET" while crescendo is not in the OFF state
  * The display shows "CRESC: <LEVEL>" on the second line, starting at 0.  At this state, we are in the "CrescendoSet" state
  * Set up the stops and press SET. The level advances to the next, and sets the stops as in that stage.  Press SET and go through 31 stages.
  * use "Next" and "Prev" to go to next or previous level
  * use "GCancel" to exit the CrescendoSet state.
  * 
  */

#include <MIDI.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,16,2);
#include <TimerOne.h>
#include <SD.h>
#include <SPI.h>
#define PIPESERIAL Serial3

File pistonFile;
const int chipSelect=BUILTIN_SDCARD;

const int VersionNumberMajor=0;
const int VersionNumberMinor=4;
// 0.4 - adds transposer, auto pedal, sfz
// remap MIDI channels
int LEDStatus=22;
int MIDIChannel=8; //Must be 8 or less. Stored at EEPROM address 1.  EEPROM 0 validates write.  If 0xA5 then the EEPROM address is good.  EEPROM 2 stores PWM value. Flags stored EEPROM 3.
int TranslatedMIDIChannel=0;
int TranslatedNoteNumber=0;
const int NoteBase=0;
const int ConsoleOn=17;
const int ChamberOn=23;
bool PowerIsOn=true;
bool PrevLoopPowerButton=false;
int PrevLowestGtNote=33;

//HARDWARE CONFIG - For rev B board
//Input chain
const int SAMSense[2]={6,1};//Input from peripherals
const int SAMRst[2]={12,4};// Active low, pulled high
const int SAMSync[2]={10,2};// high to low resets for everyone
const int SAMCLK[2]={11,3};// 100KHz or less. clock high and then change data.  Read data after clock low.
const int SAMDrive[2]={5,0};//Output from this master
const int BitsSupportedPerChain=64;

const int KeyOut[2]={25,36};
const int KeyIn[2]={24,35};
const int KeyRst[2]={29,39};
const int KeyLoad[2]={26,21};
const int KeyCLK[2]={28,20};
const int LCDAddress=0x27;
const int SAMDelay=10; //in loops, has to match microcontroller, not less than 3. 
//TODO - Could reduce this if in UC latch output on 256th clock. 
//TODO - Check if it needs to move to 12 due to change in frame time.
int SAMDelayCount=0;
bool SAMFlag=false;

int TransposeOffset=0;
bool TransposeAdj=false;
int TransposeButton=0x2FA;


int test = 0;
const int LEDPin = 13; 
const unsigned long bitTime=120;// in microseconds 120
//const int frameTime=31000;// in microseconds 31000
//const int frameTime=7750; // frame time is divided by 4 for 64 slots
const int frameTime=21000; // frame time is divided by 4 for 64 slots

// Analog
bool EnableAnalog=true;
const int SwitchInputs[]={A17,A17,A0,A1,A2,A3}; //choir, cresc, swell = 0 1 2
bool EnableSwitchExpression=false;
const int numAnalogChannels=1;
const int PedalCCValue[]={0x7,0x10, 0x11, 0x12, 0x13};
int PedalCurrentState[]={0,0,0,0,0};
int PedalAnalogChannel[]={A17,A17,A0,A1,A2,A3};
int AnalogReadChannel=0;
const int numBars=0;
const int AnalogChannelSegments[]={11,11,11,10,10};
const int AnalogMin=0x4f;
const int AnalogDivisor=3;// number of shifts to the right (divs/2) to determine number of stages. 
int PedAveraging[8][5]={
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}
};
int PedAvgCtr=0;
int AllSwells=0x0094; //if not FFFF, indicates control bit number which is the all swells to swell control, and if on, same data is sent on AllSwellsChannel. 0-03FF  //TODO should be 0x3xx something
int AllSwellsChannel=2; 
bool AllSwellsChanged=false;
bool AllSwellsEnabled[]={false,false,true,false};
float BarValueF=0;
float ValueMax[]={1,0.8,1,1};
int BarAddress[]={2,1,0,3};

// End Analog



char LCDData[2][16]={{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
String myString="";
unsigned char LoopCounter=0;
bool LoopDone=false;
int keystate=0;
int EEValue;
bool HighConfigOn;
bool LowConfigOn;
bool ConfigState=false;
bool PowerUpGC=false;


// CA constants and variables
const bool SAMChainsSupported=1; // For this implementation, we will only support one chain of 255 (SAM Chain 1 = index 0)
const int NextButton[4] = {0x400,0x400,0x400,0x400};  // this is the bit number in the scan chain, 0-3FF as with pistons
const int PrevButton[4] = {0x400,0x400,0x400,0x400};
const int Reversible[8] = {0x28F,0x299,0x298,0x400, 0x400,0x400,0x400,0x400};
const int ReversibleControlled[8]={12,11,46,0x400, 0x400,0x400,0x400,0x400};
const int GCButton = 0x297;
const int SetButton=0x29A;
const int PowerButton=0x400;
const int MemLevelJump=30;

const int AutoPedal=0x0E; 
const int PedalStart=0x2C0;
const int GtStart=0x3C0;


bool SetState=false;
bool SetEdgeState=false;
bool GCState=false;
bool PistonChangedFlag=false;
bool SpecialPistonState=false;
bool PrevNextPiston=false;
int PrevProcIndex=0;
int PrevProcBit=0;
int PrevProcArray=0;
const int MemPlusButton = 0x2FB;
const int MemMinusButton = 0x2F9;
const int MemPlusButton2 = 0;
const int MemMinusButton2 = 0;
int CurrentPistonNumber= 0;//used with prev/next 
const int MaxPistonNumber= 9;//used with prev/next
int CurrentMemoryNumber= 0;//used with prev/next
String tTempString="0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
int ProcIndex=0;
int ProcBit=0;
int ProcArray=0;
int PressedPiston=0;
bool NewPistonSet=false;
const int NumGenerals=9;
const int SFZPiston=0x290;
bool SFZState=false;
const int SFZPin=0x30;
const int CrescPin=0x38;
const unsigned int SFZArray[4]={0xBFFE,0xAFF7,0xFFDF,0};//This corresponds to CurrentState[0][3..0]



// specifies input number (0-FE)  which is the sense line. 0xFF means not enabled. Look at PreviousState/CurrentState. First nibble is word number, starting at 0 on the Right. Second nibble is bit number
// ChangedState MSW first: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0100 0000   In this example, it is 0x19
// ChangedState MSW first: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 4000 0000 0000   In this example, it is 0x2E.  This value goes in the 

//40 pistons - define which input controls each (0-3FF), 400 = not used. Third nibble is which chain 2=KCH1, 3=KCH2, 0=SAMCH1, 1=SAMCH2  

// as below the PistonName, the lines here are General 1-14, Pedal 1-6, GT 1-6, SW 1-6, CH 1-6, Something else 1-2
const int Piston[40]={
  0x281,0x282,0x283,0x284,
  0x285,0x286,0x287,0x288,
  0x400,0x400,0x400,0x400,
  0x400,0x400,
  
  0x2EC,0x2ED,0x2EE,0x2EF,0x2F0,0x400,
  
  0x291,0x292,0x293,0x294,0x295,0x296,
  
  0x289,0x28A,0x28B,0x28C,0x28D,0x28E,
  
  0x400,0x400,0x400,0x400,0x400,0x400,
  
  0x400,0x400
};
const int SequencerPistonList[20]={0,1,2,3, 4,5,6,7, 8,0,0,0, 0,0,0,0, 0,0,0,0};  // This is an index into Generals 1-xx, xx<=20, It tells what number in the Piston[] list the general is. 
const char PistonName[40][6]={
  {"GEN01"},
  {"GEN02"},
  {"GEN03"},
  {"GEN04"},
  {"GEN05"},
  {"GEN06"},
  {"GEN07"},
  {"GEN08"},
  {"GEN09"},
  {"GEN10"},
  {"GEN11"},
  {"GEN12"},
  {"GEN13"},
  {"GEN14"},
  
  {"PED01"},
  {"PED02"},
  {"PED03"},
  {"PED04"},
  {"PED05"},
  {"PED06"},
  

  {"GT1  "},
  {"GT2  "},
  {"GT3  "},
  {"GT4  "},
  {"GT5  "},
  {"GT6  "},

  {"SW1  "},
  {"SW2  "},
  {"SW3  "},
  {"SW4  "},
  {"SW5  "},
  {"SW6  "},

  {"CH1  "},
  {"CH2  "},
  {"CH3  "},
  {"CH4  "},
  {"CH5  "},
  {"CH6  "},
  
  {"SP1  "},
  {"SP2  "}

};
// This array is 256 entries, one for each SAM sense line. For this implementation, only the SAMCHAIN1 is supported (256 SAM inputs).
// const uint8_t Sense[256]={ 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
const unsigned int GCMask[16] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
//A 0 here will cancel the corresponding SAMCHAIN1 bit. A 1 will leave it alone
// view these as a 256 bit number, LSB on the right.  Code handles the translation.

// Sense bit mask. Intended for the use of Divisionals, etc, to determine what sense lines are enabled for each piston.
// 1 in the field means the sense is active for that Piston - Corresponds to ChangedState:. First index corresponds to Piston[] assignment,second to ChangedState word
// BitMask[PistonNumber][ChangedStateWord]
// Second number is number of columns (entries in each vector).
// First number is the piston number
// The entry in the vector corresponds to the ChangedState: SAM matrix.  
// view these as a 256 bit number, LSB on the right.  Code handles the translation.
const unsigned int BitMask [40][16] = {
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General1
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General2
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General3
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General4
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General5
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General6
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General7
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0x0,0xFFFF,0xFFFF,0xFFFE},  //e.g. Piston[0] Sense mask, General8

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},// Gen 9
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},// Gen 10
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},// Gen 11
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},// Gen 12
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // Gen 13
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // Gen 14

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0x7FE}, // Pedal 1
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0x7FE}, // Pedal 2
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0x7FE}, // Pedal 3
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0x7FE}, // Pedal 4
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0x7FE}, // Pedal 5
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0xFFF,0,0}, // Gt 1
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0xFFF,0,0}, // Gt 2
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0xFFF,0,0}, // Gt 3
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0xFFF,0,0}, // Gt 4
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0xFFF,0,0}, // Gt 5
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0xFFF,0,0}, // Gt 6

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0xFFFE,0}, //Sw1
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0xFFFE,0}, //Sw2
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0xFFFE,0}, //Sw3
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0xFFFE,0}, //Sw4
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0xFFFE,0}, //Sw5
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0xFFFE,0}, //Sw6

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // CH 1
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // CH 2
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // CH 3
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // CH 4
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // CH 5
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // CH 6

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}

};



// Scanning constants and variables

// The system supports 2 chains for SAMs and 2 chains for keys. Chains 0 and 1 are SAM chains (10 pin), and chains 2 and 3 are key chains (8 pin).
// In this implementation we will only implement one SAM chain (0) and one key chain (2).
unsigned int CurrentState[4][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  }; //each scan chain is 256 bits, 4 unsigned chars per scan chain. Even high byte, odd low byte
uint32_t PipeOutState[2][8]={
  {0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}
  }; //each scan chain is 256 bits, 4 unsigned chars per scan chain. Even high byte, odd low byte
uint32_t PipeOutPrevious[2][8]={
  {0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}
  }; //each scan chain is 256 bits, 4 unsigned chars per scan chain. Even high byte, odd low byte
uint32_t PipeOutMask[2][8]={
  {0,0xFFFFFFFF,0,0,0,0,0},{0x1FFFFFFF,0xFFFFFFFF,0x1FFFFFFF,0xFFFFFFFF,0,0,0,0}
  }; //each scan chain is 256 bits, 4 unsigned chars per scan chain. Even high byte, odd low byte
unsigned int PreviousState[4][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
} ; //each scan chain is 64 bits, 4 unsigned chars per scan chain. Even high byte, odd low byte. 4 chains supported
unsigned int PendingMIDIOn[4][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}; // if a bit is set here, then the switch changed state
unsigned int PendingMIDIOff[4][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}; // if a bit is set here, then the switch changed state
bool ChangedFlag=false;
bool InternalChangedFlag=false;
unsigned int t32temp=0;
unsigned int OutputArray[4][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
int BitCounter[]={0,0,0,0};
int WordCounter[]={0,0,0,0};

// CRESCENDO constants and variables
bool CrescendoState=false;
bool CrescendoSetState=false;
int CrescendoPedalChannel=0; //Matches analog channel
int CrescendoCurrentLevel=0; //read from crescendo pedal
int CrescendoPrevLevel=0;
const bool CrescendoEnabled=true;
int CrescendoNumber=0; // Allowances for multiple crescendos 
// Stops are on 0&1, CurrentState reflects actual state of stops, CrescendoCurrentState is from Memory.  Or them together to send out
unsigned int CrescendoPreviousState[2][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
unsigned int CrescendoCurrentState[2][16]={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};




// Misc. System variables
bool EnablePowerupLED=false;
const bool PCMessageEnabled=false;
bool PCMessageReceived=false;
const int PCMessageChannel = 1;
const int PCMessageNote=0x1;
int PCMessageLEDPort=6;
int PCMessageShutdownSwitch=5;
bool PCMessageShutdownSwitchPrevState=1;
bool PCMessageCurrentState=1; 
int SendNoteValue=0;


///////////////////////////Setup///////////////////////////

void setup() {
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
  Serial.begin(115200);
  PIPESERIAL.begin(38400,SERIAL_8N1);
  Wire.begin();
  pinMode(LEDPin,OUTPUT);
  digitalWrite(LEDPin,HIGH);

//  PIPESERIAL.print("HelloWorld");
  Serial.print("Version: ");Serial.print(VersionNumberMajor,DEC);Serial.print(".");Serial.print(VersionNumberMinor,DEC);

  Serial.println("Setup LCD...");
//  initLCD();
  lcd.init();
  lcd.noBacklight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BallantyneOrgans");
  lcd.print(VersionNumberMajor,DEC);
  lcd.print(".");
  lcd.print(VersionNumberMinor,DEC);
  lcd.setCursor(0,1);
  lcd.print(" Aliso LDS: OFF ");  

  pinMode(ConsoleOn,OUTPUT);
  digitalWrite(ConsoleOn,LOW);
//    digitalWrite(ConsoleOn,HIGH);
  
  pinMode(ChamberOn,OUTPUT);
  digitalWrite(ChamberOn,LOW);
//  digitalWrite(ChamberOn,HIGH);
  
  PIPESERIAL.write((byte) 0xFD);//Lock pipe drivers

  
  Serial.println("Setup scan chains...");
  for (int i=0;i<=1;i++){
    pinMode(SAMSense[i],INPUT_PULLUP);
    pinMode(SAMRst[i],INPUT_PULLUP);
    pinMode(SAMSync[i],OUTPUT);
    digitalWrite(SAMSync[i],LOW);
    pinMode(SAMCLK[i],OUTPUT);
    digitalWrite(SAMCLK[i],LOW);
    pinMode(SAMDrive[i],OUTPUT);
    digitalWrite(SAMDrive[i],LOW);
    
    pinMode(KeyIn[i],INPUT_PULLUP);
    pinMode(KeyOut[i],OUTPUT);
    digitalWrite(KeyOut[i],HIGH);
    pinMode(KeyRst[i],OUTPUT);
    digitalWrite(KeyRst[i],HIGH);
    delay(1);
    digitalWrite(KeyRst[i],LOW);
    delay(1);
    digitalWrite(KeyRst[i],HIGH);
    pinMode(KeyLoad[i],OUTPUT);
    digitalWrite(KeyLoad[i],HIGH);
    pinMode(KeyCLK[i],OUTPUT);
    digitalWrite(KeyCLK[i],LOW);
 
  }// for i

  Serial.println("Setup Expression...");

  if (EnableSwitchExpression){
    for (int i=0;i<=5;i++){
      pinMode(SwitchInputs[i],INPUT_PULLUP);
    }
    Serial.println("Switch pullups set");
    int j=0;
    for (int i=0; i<=5;i++){
      if (digitalRead(SwitchInputs[i])==0) j+=0x10;
    }
    PedalCurrentState[0]=j;
  }//switch expression

//  mcp.begin();
  Serial.println("Setup Expression1..");
  if(numBars>1){
    for(int j=0;j<numBars;j++){
      for (int i=0;i<=AnalogChannelSegments[j];i++){
		  barOut(BarAddress[j],i);
      Serial.print("barout");Serial.print(BarAddress[j]);Serial.print(",");Serial.println(i);
        delay(30);
      }
    }// j - initialize bars
  }// if initialize bars
  Serial.println("Setup Expression2..");


  if (EnableAnalog){
    for (int i=0;i<numAnalogChannels;i++){
      pinMode(PedalAnalogChannel[i],INPUT);
//      pinMode(PedalAnalogChannel[i],INPUT_PULLUP);
      PedalCurrentState[i]=0;
      int l=analogRead(PedalAnalogChannel[i]);
      int j=l>>AnalogDivisor;
        if (PedalCurrentState[i]>=j){
          for (int k=PedalCurrentState[i]-1; k>=j; k--){
            usbMIDI.sendControlChange(PedalCCValue[i],k,MIDIChannel);
            Serial.print("AnalogValueDOWN Channel ");
            Serial.print(i);
            Serial.print(" POT value:");
            Serial.print(j);
            Serial.print(" CCValue:");
            Serial.println(k);
          }//for
        }//if
        else{
          for (int k=PedalCurrentState[i]+1; k<=j; k++){
            usbMIDI.sendControlChange(PedalCCValue[i],k,MIDIChannel);
            Serial.print("AnalogValueUP Channel ");
            Serial.print(i);
            Serial.print(" POT value:");
            Serial.print(j);
            Serial.print(" CCValue:");
            Serial.println(k);
          }
        }//else
        PedalCurrentState[i]=j;
        Serial.print("Current State ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(PedalCurrentState[i]);
        barOut(BarAddress[i],0);
        BarValueF=(((float) l/(float) 0x3FF)/ValueMax[i]);
        if (BarValueF>=0.98) barOut(BarAddress[i],AnalogChannelSegments[i]);
        else barOut(BarAddress[i],(int) (BarValueF*((float) AnalogChannelSegments[i])));
        
    }//  for i, each analog channel
  }
    Serial.println("Setup Expression3..");

    Serial.println("Setup Database..");
    for (int i=0; i<=3; i++){
      for (int j=0; j<=15; j++){
        CurrentState[i][j]=0;
        PreviousState[i][j]=0;
        PendingMIDIOff[i][j]=0xFFFF;
        PendingMIDIOn[i][j]=0;
      }
    }


/* PCMessage setup  
  pinMode(PCMessageLEDPort,OUTPUT);
  pinMode(PCMessageShutdownSwitch,INPUT_PULLUP);
*/
  pinMode(LEDStatus,OUTPUT);
  digitalWrite(LEDStatus,HIGH);


  
  Serial.println("Setup SD...");
    if (!SD.begin(chipSelect)) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }


  Serial.println("End Setup...");
  Serial.print("Version..");
  Serial.print(VersionNumberMajor,DEC);
  Serial.print(".");
  Serial.println(VersionNumberMinor,DEC);
  Timer1.initialize(frameTime); // 10ms loop time
  Timer1.attachInterrupt(restartLoop);
  Timer1.start();

//wait for HW message here. Default is A0 01 for channel 1 note 1


if(PCMessageEnabled){
  while (!PCMessageReceived){
  lcd.setCursor(0,0);
  lcd.print("Loading.........");
  if(usbMIDI.read()) {
        if((usbMIDI.getType()==0xA0)&&(usbMIDI.getChannel()==PCMessageChannel)&&(usbMIDI.getData1()==PCMessageNote)) PCMessageReceived=true;
        else {Serial.print("Type: ");Serial.print(usbMIDI.getType(),HEX);Serial.print(" CH:");Serial.print(usbMIDI.getChannel(),DEC);Serial.print(" Note:");Serial.println(usbMIDI.getData1(),DEC);}   
    }; //Look for Aftertouch (Ax) on or off on our channel
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print(".........Loading");    
  delay(1000);
  }
}

  Serial.println("PC Message Received");
//  lcd.clear();
//  PrintLCDMemory();

//////This block permenantly enables power up on power up
PowerIsOn=true;
digitalWrite(ConsoleOn,HIGH);
digitalWrite(ChamberOn,HIGH);
/////////


if(PowerIsOn){
  digitalWrite(ConsoleOn,HIGH);
  digitalWrite(ChamberOn,HIGH);
  lcd.clear();
  lcd.backlight();
  PrintLCDMemory();
  Serial.println("PowerUpWait");
  delay(1000);// Wait for power to come on and drivers to boot
  // We set the current state of these two bits to inactive so that there is a change and the pipe drivers register it
  //Send out current state of shoe enable "Stop" [0][3],0
  bitSet(CurrentState[0][3],0);
  int j=0;
  int i=1;
  Serial.print("Startup initial setup"); Serial.print("CMD:");Serial.print((byte) (0xC0 | ((j&0x03)<<3) | (i&0x07)) ,HEX);Serial.print("||");
  PIPESERIAL.write(byte (0xC0 | ((j&0x03)<<3) | (i&0x07)) );
      for (int k=(i*2+1); k>=i*2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[j][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.

        PIPESERIAL.write(byte ((CurrentState[j][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
      }//m
        
      }//k
      Serial.println("");
  // Send out current state of Trem enable "Key" [3][11],15
  j=3;
  i=5;
  Serial.print("Startup initial setup"); Serial.print("CMD:");Serial.print((byte) (0xC0 | ((j&0x03)<<3) | (i&0x07)) ,HEX);Serial.print("||");
  PIPESERIAL.write(byte (0xC0 | ((j&0x03)<<3) | (i&0x07)) );
      for (int k=(i*2+1); k>=i*2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[j][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.

        PIPESERIAL.write(byte ((CurrentState[j][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
      }//m
        
      }//k
      Serial.println("");
  
  // Enable a general cancel
  PowerUpGC=true;
  LoopCounter=0;
  
}//Start up with power on


}//setup


///////////////////////////////////main////////////////////////////

void loop() {
  LoopCounter++;
  digitalWrite(LEDStatus,bitRead(LoopCounter,4));
  digitalWrite(LEDPin,bitRead(LoopCounter,2));
  
//  Serial.print(".");
//  if(LoopCounter==0) Serial.print(".");

////////////////////// SCAN DATA IN  //////////////////////////////////////////

// Start of sequence strobe

for (int i=0; i<=1; i++){
  digitalWrite(SAMSync[i],HIGH);
  digitalWrite(KeyLoad[i],LOW);
}
delayMicroseconds(bitTime+bitTime);
for (int i=0;i<=1;i++){
  digitalWrite(SAMSync[i],LOW);
  digitalWrite(KeyLoad[i],HIGH);
}
delayMicroseconds(bitTime+bitTime);

if (SAMDelayCount<=0xFC) SAMDelayCount++; 

if(SAMDelayCount<=SAMDelay) {Serial.print("SAM Delay ");Serial.print(SAMDelayCount,DEC);Serial.print("001 LoopCount:");Serial.println(LoopCounter,DEC);}
else {
  while(usbMIDI.read()) {}; //Look for note on or off on our channel
  for (int j=0;j<=3;j++){
    for (int i=15;i>=0;i--){
      if(PendingMIDIOn[j][i]!=0){
          Serial.print("PendingMIDIOn[");Serial.print(j,DEC);Serial.print("][");Serial.print(i,DEC);Serial.print("]: ");Serial.print(PendingMIDIOn[j][i],HEX);Serial.print(" LoopCount:");Serial.println(LoopCounter,DEC);
          SAMDelayCount=0;
      }
      if(PendingMIDIOff[j][i]!=0xFFFF){
          Serial.print("PendingMIDIOff[");Serial.print(j,DEC);Serial.print("][");Serial.print(i,DEC);Serial.print("]: ");Serial.print(PendingMIDIOff[j][i],HEX);Serial.print(" LoopCount:");Serial.println(LoopCounter,DEC);
          SAMDelayCount=0;
      }
      CurrentState[j][i]=CurrentState[j][i]&(PendingMIDIOff[j][i]);
      PendingMIDIOff[j][i]=0xFFFF;
      CurrentState[j][i]=CurrentState[j][i]|(PendingMIDIOn[j][i]);
      PendingMIDIOn[j][i]=0;
      }//i
  }//j
}//else sam delay


// TODO - There's a boundry condition where at 0,0,0, when set, the SAMState leaks over into bits 14 and 15 of Keyout (CurrentState[2][0] = C000) when CurrentState[0][0] = 1.






ChangedFlag=false;
// The loop will output the current state to the SAMDrive, and input the peripheral state from the SAMSense and KeyIn lines 
// Change data (outputs) on rising edge, read data (inputs) on the falling edge.

for (int i=0;i<BitsSupportedPerChain;i++){
  unsigned long Currenttime=micros();
  while(micros()>=(0xFFFFFFFF-(bitTime+10))){}// If there's less than 30us left on the timer, we'll wait for the timer rollover. This prevents from having to do rollover edge conditions

  int q=BitsSupportedPerChain-i-1; // supporting 4 clocks per keyboard chain per clock per SAM chain.  Each key channel is 256 in for each SAM channel of 64. With this we support 8 keyboards and 128 SAM inputs.
  // We could halve the latency by going down to 32/4 keyboards and using 2 channels.

  for (int j=0;j<=1;j++){
    digitalWrite(SAMDrive[j],bitRead(CurrentState[j][i>>4],(i&0xF)));// SAMs on 0 and 1
    digitalWrite(SAMCLK[j],HIGH);
    bitWrite(CurrentState[j+2][((q*4+4)-1)>>4],(q*4+4-1)&0xF,!digitalRead(KeyIn[j]));//Negative logic, a 1 on the peripheral is inactive, 0 is active. Keys on 2&3
    digitalWrite(KeyCLK[j],HIGH);
    }//j
    delayMicroseconds(1);
	for (int k=1;k<=3;k++){
		// do extra keyboard clock in.  Supports 4 clocks
		digitalWrite(KeyCLK[0],LOW);
		digitalWrite(KeyCLK[1],LOW);
		delayMicroseconds(1);
		for (int j=0;j<=1;j++){
			bitWrite(CurrentState[j+2][(q*4+(4-k)-1)>>4],(q*4+(4-k)-1)&0xF,!digitalRead(KeyIn[j]));//Negative logic, a 1 on the peripheral is inactive, 0 is active
			digitalWrite(KeyCLK[j],HIGH);
			}//j
		delayMicroseconds(1);
	}//k
  
  if (((bitTime/2)-7)>0)delayMicroseconds((bitTime/2)-7);

  for (int j=0;j<=1;j++){
    digitalWrite(SAMCLK[j],LOW);
    digitalWrite(KeyCLK[j],LOW);
    if(!PistonChangedFlag){
    bitWrite(CurrentState[j][i>>4],i&0xF,LOW);
    if (digitalRead(SAMSense[j])==LOW) bitWrite(CurrentState[j][i>>4],i&0xF,HIGH);
    }//
  }//j
    

  
  while((micros()-Currenttime)<bitTime){}
}//i


//////////////////We set stop 15/14 always in order to enable shoes
bitSet(CurrentState[0][3],0);
bitSet(PreviousState[0][3],0);
/////////////////
// WORKAROUND - disable 4' Trumpet stop on SW for cipher
//bitClear(CurrentState[0][1],0x0B);
//bitClear(CurrentState[0][0],0x0D);//sw ped 4
// WORKAROUND - disable automatic pedal
//bitClear(CurrentState[0][0],0x0E);//Automatic Pedal




/*///////Test stop setup goes here
bitSet(CurrentState[0][0],9);//16 trombone pedal
bitSet(CurrentState[0][1],5);//Sw Nachthorn
bitSet(CurrentState[0][2],3);//Gt Flute Ouverte
bitSet(CurrentState[0][2],13);//SwGt16
bitSet(CurrentState[0][0],14);//AutoPedal
//
bitSet(CurrentState[0][2],1);//Gt 8' Octave
CurrentState[0][0]=0xFFFF;
CurrentState[0][1]=0xFFFF;
CurrentState[0][2]=0xFFFF;

if((LoopCounter&0x0FF)==0) bitClear(CurrentState[0][2],1);
if((LoopCounter&0xF)==0) test=1; else test=test<<1;
int valuein=test;
//if(bitRead(LoopCounter,15)==6) valuein=0xFFFF-LoopCounter;
CurrentState[3][12]=valuein;
CurrentState[3][13]=valuein;
CurrentState[3][14]=valuein;
CurrentState[3][15]=valuein;
//
 PreviousState[3][12]=!LoopCounter;
PreviousState[3][13]=!LoopCounter;
PreviousState[3][14]=!LoopCounter;
PreviousState[3][15]=!LoopCounter;

/*/



/*/ Power On/Off routine


bool PowerButtonPressed=false;
if ((bitRead(CurrentState[PowerButton>>8][(PowerButton&0xF0)>>4],PowerButton-(PowerButton>>4)*16)==1)){
  PowerButtonPressed=true;
}
if (PowerButtonPressed&&!PrevLoopPowerButton){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Release Button");
  lcd.setCursor(0,1);
  if (PowerIsOn) lcd.print(" to Power Off  "); else lcd.print(" to Power On   ");
}
if(PrevLoopPowerButton&&!PowerButtonPressed){
if(PowerIsOn){
  digitalWrite(ConsoleOn,LOW);
  digitalWrite(ChamberOn,LOW);
  lcd.clear();
  lcd.noBacklight();
  lcd.setCursor(0,0);
  lcd.print("BallantyneOrgans");
  lcd.print(VersionNumberMajor,DEC);
  lcd.print(".");
  lcd.print(VersionNumberMinor,DEC);
  lcd.setCursor(0,1);
  lcd.print(" Aliso LDS: OFF ");  
}
if(!PowerIsOn){
  digitalWrite(ConsoleOn,HIGH);
  digitalWrite(ChamberOn,HIGH);
  lcd.clear();
  lcd.backlight();
  PrintLCDMemory();
  Serial.println("PowerUpWait");
  delay(1000);// Wait for power to come on and drivers to boot
  // We set the current state of these two bits to inactive so that there is a change and the pipe drivers register it
  //Send out current state of shoe enable "Stop" [1][15],15
  int j=1;
  int i=7;
  Serial.print("Startup initial setup"); Serial.print("CMD:");Serial.print((byte) (0xC0 | ((j&0x03)<<3) | (i&0x07)) ,HEX);Serial.print("||");
  PIPESERIAL.write(byte (0xC0 | ((j&0x03)<<3) | (i&0x07)) );
      for (int k=(i*2+1); k>=i*2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[j][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.

        PIPESERIAL.write(byte ((CurrentState[j][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
      }//m
        
      }//k
      Serial.println("");
  // Send out current state of Trem enable "Key" [3][11],15
  j=3;
  i=5;
  Serial.print("Startup initial setup"); Serial.print("CMD:");Serial.print((byte) (0xC0 | ((j&0x03)<<3) | (i&0x07)) ,HEX);Serial.print("||");
  PIPESERIAL.write(byte (0xC0 | ((j&0x03)<<3) | (i&0x07)) );
      for (int k=(i*2+1); k>=i*2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[j][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.

        PIPESERIAL.write(byte ((CurrentState[j][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
      }//m
        
      }//k
      Serial.println("");
  // Enable a general cancel
  PowerUpGC=true;
  LoopCounter=0;
  
}
PowerIsOn=!PowerIsOn;
}
PrevLoopPowerButton=PowerButtonPressed;
*///End Power Button Routine

/*//TEST, display status immediatly post scan

bool testChangedFlag=false;
for (int i=0;i<=15;i++){
  for (int j=0;j<=3;j++){
    if(CurrentState[j][i]!=PreviousState[j][i])
      testChangedFlag=true;
  }//j
}//i

if (testChangedFlag){
  Serial.print("Immediate Post Scan Changed LoopCount: ");Serial.println(LoopCounter,DEC);
  for (int j=0;j<=3;j++){
    Serial.print("PreviousState[");
    Serial.print(j);
    Serial.print("]:  ");
    for (int i=15;i>=0;i--){
      Serial.print(PreviousState[j][i],HEX);
      Serial.print(" ");
      }//i
    Serial.println(" ");
  }//j
  for (int j=0;j<=3;j++){
    Serial.print("CurrentState[");
    Serial.print(j);
    Serial.print("]:  ");
    for (int i=15;i>=0;i--){
      Serial.print(CurrentState[j][i],HEX);
      Serial.print(" ");
      }//i
    Serial.println(" ");
  }//j
}//changed
*/

/////Simple Auto Pedal Routine (Duplicate lowest Gt note in Pedal)
if ((bitRead(CurrentState[AutoPedal>>8][(AutoPedal&0xF0)>>4],AutoPedal-(AutoPedal>>4)*16)==1)){
  bool LowestNoteFound=false;
      int ai=0;
      while(ai<=31&&!LowestNoteFound)
      {
        if(bitRead(CurrentState[(GtStart&0xF00)>>8][((GtStart&0xF0)>>4)+(ai>>4)],ai&0xF)==1  || bitRead(CurrentState[(PedalStart&0xF00)>>8][((PedalStart&0xF0)>>4)+(ai>>4)],ai&0xF)==1 ){
          LowestNoteFound=true;
          bitSet(CurrentState[(PedalStart&0xF00)>>8][((PedalStart&0xF0)>>4)+(ai>>4)],ai&0xF);
        }//if
        ai++;
      }//while

}
// End Simple Auto pedal. TODO only play it if there is a new note (don't go up to the held note)


/*///////////////Auto Pedal Routine
if ((bitRead(CurrentState[AutoPedal>>8][(AutoPedal&0xF0)>>4],AutoPedal-(AutoPedal>>4)*16)==1)){
  unsigned long AutoCurrent= ((unsigned long)(CurrentState[(GtStart&0xF00)>>8][((GtStart&0xF0)>>4)+1]<<16) | (unsigned long)(CurrentState[(GtStart&0xF00)>>8][(GtStart&0xF0)>>4]));
  unsigned long AutoPrev=   ((unsigned long)(PreviousState[(GtStart&0xF00)>>8][((GtStart&0xF0)>>4)+1]<<16) | (unsigned long)(PreviousState[(GtStart&0xF00)>>8][(GtStart&0xF0)>>4]));
  unsigned long AutoPedalState= ((unsigned long)(CurrentState[(PedalStart&0xF00)>>8][((PedalStart&0xF0)>>4)+1]<<16) | (unsigned long)(CurrentState[(PedalStart&0xF00)>>8][(PedalStart&0xF0)>>4]));
  unsigned long AutoAND=0xFFFFFFFF;
  unsigned long AutoOR=0;
  int FindLowestGtNote=33;
  if ((AutoCurrent^AutoPrev)!=0){
		if(AutoCurrent>=1){
			for(int ai=0;ai<=31;ai++)
			{
				if(bitRead((AutoCurrent^AutoPrev),ai)==1){
					if(bitRead(AutoCurrent,ai)==1) {
						FindLowestGtNote=ai;
					}
					if(bitRead(AutoCurrent,ai)==0) bitClear(AutoAND,ai);
				}//bit changed
				
			}//ai
			if(FindLowestGtNote<=32&&PrevLowestGtNote>FindLowestGtNote) {bitSet(AutoOR,FindLowestGtNote); PrevLowestGtNote=FindLowestGtNote;} else bitSet(AutoOR,PrevLowestGtNote);
      if(FindLowestGtNote>32) PrevLowestGtNote=33;
			CurrentState[(PedalStart&0xF00)>>8][((PedalStart&0xF0)>>4)+1]=(int) (   ( (CurrentState[(PedalStart&0xF00)>>8][((PedalStart&0xF0)>>4)+1] & (AutoAND>>16)) | (AutoOR>>16) )| AutoPedalState);    
			CurrentState[(PedalStart&0xF00)>>8][(PedalStart&0xF0)>>4]=(int) (( (CurrentState[(PedalStart&0xF00)>>8][(PedalStart&0xF0)>>4] & (AutoAND&0xFFFF)) | (AutoOR&0xFFFF)) |AutoPedalState );    
			Serial.print("AutoCurrent: ");Serial.println(AutoCurrent,HEX);
			Serial.print(" AutoPrev: ");Serial.print(AutoPrev,HEX);
			Serial.print(" AutoPedal: ");Serial.println(AutoPedal,HEX);
			Serial.print("AutoAND: ");Serial.print(AutoAND,HEX);
			Serial.print(" AutoOR: ");Serial.print(AutoOR,HEX);
      Serial.println(" LowestNote:");Serial.println(FindLowestGtNote,DEC);
			
			
		}//if there's a GT note in the lower 32 playing
		
  }//new note pressed in GT bottom 32.
//  else
//  {
//    if(PrevLowestGtNote>32){
//      CurrentState[(PedalStart&0xF00)>>8][(PedalStart&0xF0)>>4]=0;
//      CurrentState[(PedalStart&0xF00)>>8][((PedalStart&0xF0)>>4)+1]=0;
//    }
//  }// hold previous state
  
  
}// if autopedal stop on

/*///////////////EndAuto Pedal Routine


////////////////////////// END SCAN DATA IN ///////////////////////////




if (PowerIsOn){
//


//////////////////////////////////// ANALOG CHANNELS ///////////////////////////////////////////////////////

/* Switch Expression
if (EnableSwitchExpression){
  int i=0;
  int j=0;
  for (int k=0; k<=5;k++){
    //debug
    pinMode(SwitchInputs[i],INPUT_PULLUP);
  //!debug
    if (digitalRead(SwitchInputs[k])==0) {j+=0x10; Serial.print("Switch number: ");Serial.println(k);}
  }
  if (j!=PedalCurrentState[i])
    {
      if (PedalCurrentState[i]>=j)
      {
        for (int k=PedalCurrentState[i]-1; k>=j; k--)
        {
          usbMIDI.sendControlChange(PedalCCValue[i],k,MIDIChannel);
    Serial.print("SwitchValue");
    Serial.println(j,HEX);
        }
      }
      else
      {
        for (int k=PedalCurrentState[i]+1; k<=j; k++)
        {
          usbMIDI.sendControlChange(PedalCCValue[i],k,MIDIChannel);
    Serial.print("SwitchValue");
    Serial.println(j);
        }
      }
      PedalCurrentState[i]=j;
      Serial.print("Current State ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(PedalCurrentState[i]);
    }
} //switch expression
*/




///////////////////////// Scan analog channels /////////////////////////////


  if (EnableAnalog){
    for (int i=0;i<numAnalogChannels;i++){
      AnalogReadChannel=i;
      if ((bitRead(CurrentState[AllSwells>>8][(AllSwells&0xF0)>>4],AllSwells-(AllSwells>>4)*16)==1)&&AllSwellsEnabled[i]) AnalogReadChannel=AllSwellsChannel;
      int l=(analogRead(PedalAnalogChannel[AnalogReadChannel]));
      if (l<=AnalogMin) l=0; else l=l-AnalogMin;
      int j=(l>>AnalogDivisor);
//      if(j<=4) j=0; else j=j-4;
      if (j!=PedalCurrentState[i]){
        if (PedalCurrentState[i]>=j){
          for (int k=PedalCurrentState[i]-1; k>=j; k--){
            usbMIDI.sendControlChange(PedalCCValue[i],k,MIDIChannel);
            Serial.println("--EXPRESSION--");
            Serial.print("Pedal# ");
            Serial.print(i);
            Serial.print(" AnalogValueDOWN  ");
            Serial.print(j);
            Serial.print(" CCValue:");
            Serial.print(k);
            Serial.print("  Raw l value:");
            Serial.println(l,HEX);
          }//for
        }//if
        else{
          for (int k=PedalCurrentState[i]+1; k<=j; k++){
            usbMIDI.sendControlChange(PedalCCValue[i],k,MIDIChannel);
            Serial.println("--EXPRESSION--");
            Serial.print("Pedal# ");
            Serial.print(i);
            Serial.print(" AnalogValueUP  ");
            Serial.print(j);
            Serial.print(" CCValue:");
            Serial.print(k);
            Serial.print("  Raw l value:");
            Serial.println(l,HEX);
          }
        }//else
        PedalCurrentState[i]=j;
        Serial.print("Current State Pedal#");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(PedalCurrentState[i]);

        BarValueF=(((float) l/(float) 0x3FF)/ValueMax[i]);
        if (BarValueF>=0.98) barOut(BarAddress[i],AnalogChannelSegments[i]);
        else {
        barOut(BarAddress[i],(int) (BarValueF*((float) AnalogChannelSegments[i])));
        Serial.print("BarValue: ");
        Serial.print(BarValueF);
        Serial.println((int) BarValueF,DEC);
        Serial.print("BarValueint: ");
        Serial.print((int) (BarValueF*((float) AnalogChannelSegments[i])));
        }
      }// if j!=
    }//  for i, each analog channel
  }
////////////////////////////////analog channel/


/// Transposer


if ((TransposeButton<0x400)&((bitRead(CurrentState[TransposeButton>>8][(TransposeButton&0xF0)>>4],TransposeButton-(TransposeButton>>4)*16)==1)&&(bitRead(PreviousState[TransposeButton>>8][(TransposeButton&0xF0)>>4],TransposeButton-(TransposeButton>>4)*16)==0))) {
    Serial.println("TransposerSet");lcd.setCursor(13,1);lcd.print("TRN");
} 

if ((TransposeButton<0x400)&(bitRead(CurrentState[TransposeButton>>8][(TransposeButton&0xF0)>>4],TransposeButton-(TransposeButton>>4)*16)==1)) TransposeAdj=true; else TransposeAdj=false; 
if ((TransposeButton<0x400)&((bitRead(CurrentState[TransposeButton>>8][(TransposeButton&0xF0)>>4],TransposeButton-(TransposeButton>>4)*16)==0)&&(bitRead(PreviousState[TransposeButton>>8][(TransposeButton&0xF0)>>4],TransposeButton-(TransposeButton>>4)*16)==1))) {
    Serial.println("TransposerReleaseSetState");lcd.setCursor(13,1);lcd.print("   ");
} 

if ((SFZPiston<0x400)&((bitRead(CurrentState[SFZPiston>>8][(SFZPiston&0xF0)>>4],SFZPiston-(SFZPiston>>4)*16)==1)&&(bitRead(PreviousState[SFZPiston>>8][(SFZPiston&0xF0)>>4],SFZPiston-(SFZPiston>>4)*16)==0))) {
  SFZState=!SFZState;
  ///todo - sfz stuff
  
  
  
  if (SFZState){
    Serial.println("SFZ State");lcd.setCursor(13,1);lcd.print("SFZ");
    bitSet(CurrentState[SFZPin>>8][(SFZPin&0xF0)>>4],SFZPin-(SFZPin>>4)*16);
    //TODO send to indicator
	  // Send SFZ Stop Array to PIPESERIAL.  Array is 64 bytes, 4 16s
	  for(int i=0;i<=1;i++){
		  Serial.print("SFZPipeOut Regular CMD, Stops Low (1-32):"); 
		Serial.print(byte (0xC0|i),HEX);Serial.print(":");
		PIPESERIAL.write(byte (0xC0|i));
		for (int k=1; k>=0; k--){
			for (int m=1; m>=0; m--){
				Serial.print(byte ((SFZArray[k+i*2]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
				PIPESERIAL.write(byte ((SFZArray[k+i*2]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
			}//m
		}//k
	  }//i
	  Serial.println("");
	// Set SFZ pin
  }
  if (!SFZState){
	  // Send CurrentState Stop Array to PIPESERIAL
	  for(int i=0;i<=1;i++){
		  Serial.print("PipeOut SFZ Return CMD, Stops:"); 
		Serial.print(byte (0xC0|i),HEX);Serial.print(":");
    bitClear(CurrentState[SFZPin>>8][(SFZPin&0xF0)>>4],SFZPin-(SFZPin>>4)*16);
		PIPESERIAL.write(byte (0xC0|i));
		for (int k=1; k>=0; k--){
			for (int m=1; m>=0; m--){
				Serial.print(byte ((CurrentState[0][k+(i<<1)]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
				PIPESERIAL.write(byte ((CurrentState[0][k+(i<<1)]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
				}//m
		}//k
	  }//i
    Serial.println("SFZ State OFF");lcd.setCursor(13,1);lcd.print("   ");
	// Clear SFZ pin
  }
  
} 





//////////////////////////////  COMBINATION ACTION MEMORY  ///////////////SFZ///////////////////////////

SpecialPistonState=false;   
PistonChangedFlag=false;

for (int j=0;j<=3;j++) for (int i=0;i<=15;i++) OutputArray[j][i]=0;
// if changed and mem+==0, memorylevel++ to 255
if ((bitRead(CurrentState[SetButton>>8][(SetButton&0xF0)>>4],SetButton-(SetButton>>4)*16)==1)) {SetState=true;Serial.println("set");lcd.setCursor(13,1);lcd.print("SET");} 
else SetState=false; ///Note: SET is level, not edge sensitive
if (
  ((bitRead(CurrentState[MemPlusButton>>8][(MemPlusButton&0xF0)>>4],MemPlusButton-(MemPlusButton>>4)*16)==1)&&(bitRead(PreviousState[MemPlusButton>>8][(MemPlusButton&0xF0)>>4],MemPlusButton-(MemPlusButton>>4)*16)==0))
  |(bitRead(CurrentState[MemPlusButton2>>8][(MemPlusButton2&0xF0)>>4],MemPlusButton2-(MemPlusButton2>>4)*16)==1)&&(bitRead(PreviousState[MemPlusButton2>>8][(MemPlusButton2&0xF0)>>4],MemPlusButton2-(MemPlusButton2>>4)*16)==0)

){
  Serial.println("Mem plus button");
  if(!CrescendoSetState&&!SetState&&!TransposeAdj)
  {
  if (CurrentMemoryNumber<=0xFFE) {
    CurrentMemoryNumber++;
    // Write current memory number to LCD
  PrintLCDMemory();
    }
  SpecialPistonState=true;
  }
  
  if(!CrescendoSetState&&SetState&&!TransposeAdj)
  {
  int CheckMemoryLevel=0xFFE;
  if (CurrentMemoryNumber<=(CheckMemoryLevel - MemLevelJump)) {
    CurrentMemoryNumber=CurrentMemoryNumber+MemLevelJump;
    // Write current memory number to LCD
  PrintLCDMemory();
    }
  SpecialPistonState=true;
  }
  
  if (CrescendoCurrentLevel<=31&&CrescendoSetState&&!TransposeAdj) {
  Serial.println("Cresc Mem Plus button");
    CrescendoCurrentLevel++;
    Serial.print("Mem plus new crescendo level ");Serial.println(CrescendoCurrentLevel,DEC);
    // Write current memory number to LCD
    lcd.setCursor(0,1);
      lcd.print("CrescLevel: ");
        if (CrescendoCurrentLevel<=9) lcd.print("0");
      lcd.print(CrescendoCurrentLevel,DEC);
    }

  if (TransposeAdj){
    if (TransposeOffset<6){
      TransposeOffset++;
      lcd.setCursor(0,1);
      lcd.print("Trans: ");
      if(TransposeOffset>0) lcd.print("+");
      lcd.print(TransposeOffset,DEC);
      if (TransposeOffset==0){
        lcd.setCursor(0,1);
        lcd.print("           ");
      }
    }
    
  }//transposeadj


}
// if changed and mem-==0, memorylevel-- to 0
if (
  ((bitRead(CurrentState[MemMinusButton>>8][(MemMinusButton&0xF0)>>4],MemMinusButton-(MemMinusButton>>4)*16)==1)&&(bitRead(PreviousState[MemMinusButton>>8][(MemMinusButton&0xF0)>>4],MemMinusButton-(MemMinusButton>>4)*16)==0))
  |(bitRead(CurrentState[MemMinusButton2>>8][(MemMinusButton2&0xF0)>>4],MemMinusButton2-(MemMinusButton2>>4)*16)==1)&&(bitRead(PreviousState[MemMinusButton2>>8][(MemMinusButton2&0xF0)>>4],MemMinusButton2-(MemMinusButton2>>4)*16)==0)

)
{
  Serial.println("Mem Minus button");
  
  
  if(!CrescendoSetState&&!SetState&&!TransposeAdj){
    if (CurrentMemoryNumber>=1) {
	    CurrentMemoryNumber--;
	    // Write current memory number to LCD
      PrintLCDMemory();
    }
    SpecialPistonState=true;
    }
  if(!CrescendoSetState&&SetState&&!TransposeAdj){
    if (CurrentMemoryNumber>=MemLevelJump) {
      CurrentMemoryNumber=CurrentMemoryNumber-MemLevelJump;
      // Write current memory number to LCD
      PrintLCDMemory();
    }
    SpecialPistonState=true;
    }



    
  if (CrescendoCurrentLevel>=2&&CrescendoSetState&&!TransposeAdj) {
  Serial.println("Cresc Mem Minus button");
      CrescendoCurrentLevel--;
      // Write current memory number to LCD
        lcd.setCursor(0,1);
        lcd.print("CrescLevel: ");
        if (CrescendoCurrentLevel<=9) lcd.print(" ");
        lcd.print(CrescendoCurrentLevel,DEC);
    }
  if (TransposeAdj){
    if (TransposeOffset>-6){
      TransposeOffset--;
      lcd.setCursor(0,1);
      lcd.print("Trans: ");
      if(TransposeOffset>0) lcd.print("+");
       lcd.print(TransposeOffset,DEC);
      if (TransposeOffset==0){
        lcd.setCursor(0,1);
        lcd.print("          ");
      }
    }
    
  }//transposeadj
  
}//memminus
  
// check for set
if ((bitRead(CurrentState[SetButton>>8][(SetButton&0xF0)>>4],SetButton-(SetButton>>4)*16)==1)) {SetState=true;Serial.println("set");lcd.setCursor(13,1);lcd.print("SET");} 
else SetState=false; ///Note: SET is level, not edge sensitive
if (
  !(SetButton==0x400)
  &&
  (bitRead(CurrentState[SetButton>>8][(SetButton&0xF0)>>4],SetButton-(SetButton>>4)*16)==0)
  &&
  (bitRead(PreviousState[SetButton>>8][(SetButton&0xF0)>>4],SetButton-(SetButton>>4)*16)==1)
  ) 
  {lcd.setCursor(13,1);lcd.print("   ");
  SetEdgeState=true;
  Serial.println("Set edge");
  }
  else
  SetEdgeState=false; 

// check for GCButton
if ((bitRead(CurrentState[GCButton>>8][(GCButton&0xF0)>>4],GCButton-(GCButton>>4)*16)==1)||
  (PowerUpGC&&LoopCounter==(SAMDelay+5))) {
    Serial.println("GC ON TEST");
  GCState=true;
  SpecialPistonState=true;
  if(!PowerUpGC) {Serial.println("GC");lcd.setCursor(13,1);lcd.print("GC ");}
  PistonChangedFlag=true;
  PowerUpGC=false;
  TransposeOffset=0;
  TransposeAdj=false;
  lcd.setCursor(0,1);
  lcd.print("          ");
  SFZState=false;
  //TODO clear SFZ indicator
}
else GCState=false; ///Note: GC is level, not edge sensitive
if ((bitRead(CurrentState[GCButton>>8][(GCButton&0xF0)>>4],GCButton-(GCButton>>4)*16)==0)&&(bitRead(PreviousState[GCButton>>8][(GCButton&0xF0)>>4],GCButton-(GCButton>>4)*16)==1)) {lcd.setCursor(13,1);lcd.print("   ");Serial.println("GC Off");} 



// check for previous and next.  If previous or next, then set the appropriate Current State bit corresponding to virtually pressed button
for (int i=0;i<=3;i++){
  if(NextButton[i]!=0x400){
    
    ProcIndex=(NextButton[i]>>4)&0xF;
    ProcBit=NextButton[i]-(NextButton[i]>>4)*16;
    ProcArray=(NextButton[i]&0xF00)>>8;
    if ((bitRead(PreviousState[ProcArray][ProcIndex],ProcBit)==0)&&(bitRead(CurrentState[ProcArray][ProcIndex],ProcBit)==1)){
      CurrentPistonNumber++;
      Serial.print("NextButton.............");
		  if (CurrentMemoryNumber<=0xFFE&&CurrentPistonNumber==MaxPistonNumber) {
        CurrentMemoryNumber++;
        CurrentPistonNumber=0;
		  }
      else{
        if(CurrentPistonNumber==MaxPistonNumber-1&&CurrentMemoryNumber==0xFFF){
          CurrentPistonNumber--;}  
      }

      // we know what memory and what piston we are on now.  Now set the bit based on CurrentPistonNumber in OutputArray
      PistonChangedFlag=true;
      ProcIndex=(Piston[SequencerPistonList[CurrentPistonNumber]]>>4)&0xF;
      ProcBit=Piston[SequencerPistonList[CurrentPistonNumber]]-(Piston[SequencerPistonList[CurrentPistonNumber]]>>4)*16;
      ProcArray=(Piston[SequencerPistonList[CurrentPistonNumber]]&0xF00)>>8;
//      bitSet(OutputArray[ProcArray][ProcIndex],ProcBit);
      PrevNextPiston=true;
      bitSet(CurrentState[ProcArray][ProcIndex],ProcBit);
      bitClear(PreviousState[ProcArray][ProcIndex],ProcBit);
      PrevProcArray=ProcArray;
      PrevProcIndex=ProcIndex;
      PrevProcBit=ProcBit;
      // Write current memory number to LCD
        PrintLCDMemory();
        lcd.setCursor(0,1);
        for(int k=0;k<=4;k++){
        lcd.print(PistonName[CurrentPistonNumber][k]);
        Serial.print(PistonName[SequencerPistonList[CurrentPistonNumber]][k]);
        }// for k
        Serial.println("");
    }// if button pushed
  }//!next 400
  
  if(PrevButton[i]!=0x400){
    ProcIndex=(PrevButton[i]>>4)&0xF;
    ProcBit=PrevButton[i]-(PrevButton[i]>>4)*16;
    ProcArray=(PrevButton[i]&0xF00)>>8;
    if ((bitRead(PreviousState[ProcArray][ProcIndex],ProcBit)==0)&&(bitRead(CurrentState[ProcArray][ProcIndex],ProcBit)==1)){
      CurrentPistonNumber--;
//      SpecialPistonState=true;
      if (CurrentMemoryNumber>=1&&CurrentPistonNumber==-1) {
        CurrentMemoryNumber--;
        CurrentPistonNumber=(MaxPistonNumber-1);
        // Write current memory number to LCD
      }// if bitread
      else{
        if(CurrentPistonNumber==-1&&CurrentMemoryNumber==0){
          CurrentPistonNumber=0;         
        }
      }
      // we know what memory and what piston we are on now.  Now set the bit based on CurrentPistonNumber in OutputArray
      PistonChangedFlag=true;
      ProcIndex=(Piston[SequencerPistonList[CurrentPistonNumber]]>>4)&0xF;
      ProcBit=Piston[SequencerPistonList[CurrentPistonNumber]]-(Piston[SequencerPistonList[CurrentPistonNumber]]>>4)*16;
      ProcArray=(Piston[SequencerPistonList[CurrentPistonNumber]]&0xF00)>>8;
//      bitSet(OutputArray[ProcArray][ProcIndex],ProcBit);
      PrevNextPiston=true;
      bitSet(CurrentState[ProcArray][ProcIndex],ProcBit);
      bitClear(PreviousState[ProcArray][ProcIndex],ProcBit);
      PrevProcArray=ProcArray;
      PrevProcIndex=ProcIndex;
      PrevProcBit=ProcBit;
        Serial.print("PrevButton.............");
        PrintLCDMemory();
        lcd.setCursor(0,1);
        for(int k=0;k<=4;k++){
        lcd.print(PistonName[CurrentPistonNumber][k]);
        Serial.print(PistonName[SequencerPistonList[CurrentPistonNumber]][k]);
        }// for k
        Serial.println("");

    }
  }//!prev 400

	}//next i, next and previous buttons
	
	


if (!SpecialPistonState&&!CrescendoSetState){
	
for (int i=0;i<=39;i++){
  if (Piston[i]!=0x400){
    ProcIndex=(Piston[i]>>4)&0xF;
    ProcBit=Piston[i]-(Piston[i]>>4)*16;
    ProcArray=(Piston[i]&0xF00)>>8;
    if ((bitRead(PreviousState[ProcArray][ProcIndex],ProcBit)==0)&&(bitRead(CurrentState[ProcArray][ProcIndex],ProcBit)==1)){
      // generate filename
      Serial.print("pushed Piston ");Serial.println(i);
      if (i<NumGenerals) CurrentPistonNumber=i;
      PistonChangedFlag=true;
      PressedPiston=i;
      lcd.setCursor(0,1);
      for(int k=0;k<=4;k++){
        lcd.print(PistonName[i][k]);
      }
      String PistonFilename = "A00";//A for piston, 00 reserved.  
      if (CurrentMemoryNumber<=0xFF) PistonFilename=PistonFilename+"0";//support 0xFFF memories (8192)
      if (CurrentMemoryNumber<=0xF) PistonFilename=PistonFilename+"0";
      PistonFilename=PistonFilename+String(CurrentMemoryNumber,HEX);
	  Serial.print("Memory Level: ");Serial.println(CurrentMemoryNumber,HEX);

// Write current memory number to LCD
  PrintLCDMemory();
  
      if (i<=0xF) PistonFilename=PistonFilename+"0";
      PistonFilename=PistonFilename+String(i,HEX);
      Serial.print("PistonFilename: ");
      Serial.println(PistonFilename);

//At this point we have the piston filename , regardless of the SET.

      
      // Create file if it doesn't exist
      if (!SD.exists(PistonFilename.c_str())){
        Serial.print("Create File "); Serial.println(PistonFilename);
        pistonFile=SD.open(PistonFilename.c_str(),FILE_WRITE);
        pistonFile.close();
        pistonFile=SD.open(PistonFilename.c_str(),FILE_WRITE);
        pistonFile.print("0000000000000000000000000000000000000000000000000000000000000000");// Format is 256 bits, or 64 nibbles (characters - bits per). For the implementation, we will only support 256 SAMs
        pistonFile.close();
      }

      if (SetState){
        SD.remove(PistonFilename.c_str());
    		pistonFile=SD.open(PistonFilename.c_str(),FILE_WRITE);
        pistonFile.close();
        pistonFile=SD.open(PistonFilename.c_str(),FILE_WRITE);

        for (int j=15;j>=0;j--){
            Serial.print("BuildOutputArray " );Serial.print(i);Serial.println(j);printint16(CurrentState[0][j]);Serial.print("&");printint16(BitMask[i][15-j]);Serial.println("");
            OutputArray[0][j]=(CurrentState[0][j])&(BitMask[i][15-j]);//Stores 0's, which are active, as 1's. Note that we only support chain 0, which is SAMCHAIN1.
            PistonChangedFlag=true;
            switch (OutputArray[0][j]){
              case 0:
                pistonFile.print("0000");Serial.print("0000");
                break;
              case 1 ... 0xF:
                pistonFile.print("000");pistonFile.print(OutputArray[0][j],HEX);Serial.print("000");Serial.print(OutputArray[0][j],HEX);
                break;
              case 0x10 ... 0xFF:
                pistonFile.print("00");pistonFile.print(OutputArray[0][j],HEX);Serial.print("00");Serial.print(OutputArray[0][j],HEX);
                break;
              case 0x100 ... 0xFFF:
                pistonFile.print("0");pistonFile.print(OutputArray[0][j],HEX);Serial.print("0");Serial.print(OutputArray[0][j],HEX);
                break;
              case 0x1000 ... 0xFFFF:
                pistonFile.print(OutputArray[0][j],HEX);Serial.print(OutputArray[0][j],HEX);
                break;
            }
            
            
        }
         Serial.print("002 LoopCount: ");Serial.println(LoopCounter,DEC);
        Serial.print("Set Piston[");Serial.print(i,DEC);Serial.print("]: ");for(int testi=0;testi<=7;testi++) printint16(OutputArray[0][7-testi]);Serial.println("");
        NewPistonSet=true;Serial.print("New Piston Set=true");
        
       } //SetStatus
       else // not set status
       {
    			pistonFile=SD.open(PistonFilename.c_str());

		// read file, convert HEX to numbers and write to tTempArray[].  Build OutputArray[], which gets applied to CurrentState after it's written to PreviousState so that changes get applied on next cycle
          tTempString="";
          while (pistonFile.available()) {
            switch (pistonFile.read()){
            case 48:
              tTempString=tTempString+"0";
              break;
            case 49:
              tTempString=tTempString+"1";
              break;
            case 50:
              tTempString=tTempString+"2";
              break;
            case 51:
              tTempString=tTempString+"3";
              break;
            case 52:
              tTempString=tTempString+"4";
              break;
            case 53:
              tTempString=tTempString+"5";
              break;
            case 54:
              tTempString=tTempString+"6";
              break;
            case 55:
              tTempString=tTempString+"7";
              break;
            case 56:
              tTempString=tTempString+"8";
              break;
            case 57:
              tTempString=tTempString+"9";
              break;
            case 65:
              tTempString=tTempString+"A";
              break;
            case 66:
              tTempString=tTempString+"B";
              break;
            case 67:
              tTempString=tTempString+"C";
              break;
            case 68:
              tTempString=tTempString+"D";
              break;
            case 69:
              tTempString=tTempString+"E";
              break;
            case 70:
              tTempString=tTempString+"F";
              break;
          }//switch
//          Serial.println(tTempString);
          }//while file
          Serial.print("String Read from ");Serial.print(pistonFile);Serial.print(": ");Serial.println(tTempString);
          for (int j=15;j>=0;j--){
			Serial.print("j=");Serial.print(j);Serial.print("::");
            OutputArray[0][j]=t16Stringtoint(tTempString.substring(j*4,j*4+4));//Set the CurrentState of SAMCHAIN1, after PREVIOUS state is reset.
            Serial.print("OutputArray[0][");Serial.print(j,DEC);Serial.print("]: ");Serial.println(OutputArray[0][j],HEX);
          }

            
            
	   } //Not Set Status    
            
        pistonFile.close();

        
        
      }//if piston changed
    }//if piston !=0
  }//for i
  
  if (PrevNextPiston){
      PrevNextPiston=false;
      bitClear(CurrentState[PrevProcArray][PrevProcIndex],PrevProcBit);
      bitClear(PreviousState[PrevProcArray][PrevProcIndex],PrevProcBit);
  }
  
}//!GCstate && !SetState

////////////////////////////////// END COMBINATION ACTION


// Check for Reversibles
for (int i=0;i<=7;i++){
  if ((bitRead(CurrentState[Reversible[i]>>8][(Reversible[i]&0xF0)>>4],Reversible[i]-(Reversible[i]>>4)*16)==1)&&(bitRead(PreviousState[Reversible[i]>>8][(Reversible[i]&0xF0)>>4],Reversible[i]-(Reversible[i]>>4)*16)==0)) {
      if(bitRead(CurrentState[ReversibleControlled[i]>>8][(ReversibleControlled[i]&0xF0)>>4],ReversibleControlled[i]-(ReversibleControlled[i]>>4)*16)==1)
        bitClear(CurrentState[ReversibleControlled[i]>>8][(ReversibleControlled[i]&0xF0)>>4],ReversibleControlled[i]-(ReversibleControlled[i]>>4)*16);
      else
        bitSet(CurrentState[ReversibleControlled[i]>>8][(ReversibleControlled[i]&0xF0)>>4],ReversibleControlled[i]-(ReversibleControlled[i]>>4)*16);     
    } 
}

// Send out stops.  
if(!SFZState&&!CrescendoState&&(CurrentState[0][0]!=PreviousState[0][0]||CurrentState[0][1]!=PreviousState[0][1])){
      Serial.print("PipeOut Regular CMD, Stops Low (1-32):"); 
      Serial.print(byte (0xC0),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC0));
      for (int k=1; k>=0; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[0][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        PIPESERIAL.write(byte ((CurrentState[0][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        }//m
      }//k
      Serial.println("");
}


if(!SFZState&&!CrescendoState&&(CurrentState[0][2]!=PreviousState[0][2]||CurrentState[0][3]!=PreviousState[0][3])){
      Serial.print("PipeOut Regular CMD, Stops high (32-63):"); 
      Serial.print(byte (0xC1),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC1));
      for (int k=3; k>=2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[0][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        PIPESERIAL.write(byte ((CurrentState[0][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        }//m
      }//k
      Serial.println("");
}

// END Send out stops


///////////////////////////// Crescendo //////////////////////////////////////////////////
int cj=PedalCurrentState[CrescendoPedalChannel];
if (cj<=2) cj=0;


////////////// Enter crescendo state if pedal is off the peg
if (!CrescendoState&&cj>=1&&CrescendoEnabled&&!CrescendoSetState){
  Serial.print("Entering Crescendo state");
  CrescendoCurrentLevel=cj;
  CrescendoState=true;
  bitSet(CurrentState[CrescPin>>8][(CrescPin&0xF0)>>4],CrescPin-(CrescPin>>4)*16); // Turn on indicator
  Serial.print(" Cresc pin current state:[");Serial.print((CrescPin>>8),HEX);Serial.print("][");Serial.print((CrescPin&0xF0)>>4,HEX);Serial.print("]"); Serial.println(CurrentState[CrescPin>>8][(CrescPin&0xF0)>>4],HEX);
  lcd.setCursor(0,1);
  lcd.print("CrescLevel: ");
  if (CrescendoCurrentLevel<=9) lcd.print(" ");
  lcd.print(CrescendoCurrentLevel,DEC);
  for(int i=0;i<=15;i++){
	CrescendoCurrentState[0][i]=0;
	CrescendoCurrentState[1][i]=0;
	CrescendoPreviousState[0][i]=0;
	CrescendoPreviousState[1][i]=0; 
  }
}//Enter Crescendo


/////////////// Exit crescendo state if pedal is on 0
if (CrescendoState&&cj==0){
  Serial.print("Exiting Crescendo state");
  CrescendoState=false;
  bitClear(CurrentState[CrescPin>>8][(CrescPin&0xF0)>>4],CrescPin-(CrescPin>>4)*16); // Turn off indicator
  Serial.print(" Cresc pin current state:[");Serial.print((CrescPin>>8),HEX);Serial.print("][");Serial.print((CrescPin&0xF0)>>4,HEX);Serial.print("]"); Serial.println(CurrentState[CrescPin>>8][(CrescPin&0xF0)>>4],HEX);

  lcd.clear();
  PrintLCDMemory();
// Send 0's for all current crescendo state 1's 




	for (int i=0;i<=255;i++){
	//	for (int j=0;j<=1;j++){  // on this implementation, only 255 (actually 48) stops supported, on [0]
		int j=0;
		int currentstateflag=(bitRead(CurrentState[j][i>>4],i&0xF)); // end state should be Current state with no Crescendo left overs.
		int previousstateflag=bitRead(CrescendoCurrentState[j][i>>4],i&0xF);
		if(currentstateflag!=previousstateflag){
			int MIDICHOut=MIDIChannel+2*j;
			if (bitRead(i,7)==HIGH) MIDICHOut++;
			int NoteNumber=NoteBase+(i&0x7F);
// Remap MIDI IO.  SW= channel 15, 0-0x3C.  GT=Channel 15,0x40-0x5C. Ped=Channel 13, 0x40-5F. Stops=Channel 0, 00-0x3F
// Map to SW= Channel 1, 0x24=0x26, GT=channel 0 0x24-0x61, PED=Channel 2, 0x24-0x33. Stops=Channel 15, 0x00=0x3F.
			MIDIOutTranslate(MIDICHOut,NoteNumber);
			MIDICHOut=TranslatedMIDIChannel;
			NoteNumber=TranslatedNoteNumber;
      
			if (currentstateflag) {usbMIDI.sendNoteOn(NoteNumber,0x7F,MIDICHOut);Serial.print("CRESCENDO EXIT Send Note ON:");} 
			else  {usbMIDI.sendNoteOff(NoteNumber,0x7F,MIDICHOut);Serial.print("CRESCENDO EXIT Send Note OFF:");}
			Serial.print(NoteNumber,DEC);
			Serial.print(" CH:");
			Serial.println(MIDICHOut,DEC);
		}//if changed
//    bitWrite(CrescendoPreviousState[j][i>>4],i&0xF,currentstateflag);
//		}//j
	}//i
  ///////////// Send out pre cresc stop status to pipes
	if(!SFZState){
      Serial.print("PipeOut ExitCresc, Stops Low (1-32):"); 
      Serial.print(byte (0xC0),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC0));
      for (int k=1; k>=0; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[0][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        PIPESERIAL.write(byte ((CurrentState[0][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        }//m
      }//k
      Serial.println("");


      Serial.print("PipeOut ExitCresc, Stops high (32-63):"); 
      Serial.print(byte (0xC1),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC1));
      for (int k=3; k>=2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte ((CurrentState[0][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        PIPESERIAL.write(byte ((CurrentState[0][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        }//m
      }//k
      Serial.println("");
	}
      
}// Exit Crescendo


//////////////// While in Crescendo state
if (CrescendoState&&CrescendoEnabled){
  if(cj!=CrescendoCurrentLevel){
    CrescendoCurrentLevel=cj;
    
    // Read crescendo data from SD card
      String PistonFilename = "XC0000";//XC for Crescendo, 00 reserved for crescendo number, for now 00 for first 2 digits of 4 levels. 
      if ((CrescendoCurrentLevel-2)<=0xF) PistonFilename=PistonFilename+"0"; //Support FF levels
      PistonFilename=PistonFilename+String((CrescendoCurrentLevel-2),HEX);
      Serial.print("Cresc Level: ");Serial.println((CrescendoCurrentLevel-2),HEX);
      Serial.print("cj: ");Serial.print(cj,HEX);

// Write current level to LCD
      lcd.setCursor(0,1);
      lcd.print("CrescLevel: ");
      if ((CrescendoCurrentLevel-2)<=9) lcd.print(" ");
      lcd.print((CrescendoCurrentLevel-2),DEC);

      Serial.print("PistonFilename: ");
      Serial.println(PistonFilename);

      if (SD.exists(PistonFilename.c_str())){
          pistonFile=SD.open(PistonFilename.c_str(),FILE_READ);

    // read file, convert HEX to numbers and write to tTempArray[].  Build OutputArray[], which gets applied to CurrentState after it's written to PreviousState so that changes get applied on next cycle
          tTempString="";
          while (pistonFile.available()) {
            switch (pistonFile.read()){
            case 48:
              tTempString=tTempString+"0";
              break;
            case 49:
              tTempString=tTempString+"1";
              break;
            case 50:
              tTempString=tTempString+"2";
              break;
            case 51:
              tTempString=tTempString+"3";
              break;
            case 52:
              tTempString=tTempString+"4";
              break;
            case 53:
              tTempString=tTempString+"5";
              break;
            case 54:
              tTempString=tTempString+"6";
              break;
            case 55:
              tTempString=tTempString+"7";
              break;
            case 56:
              tTempString=tTempString+"8";
              break;
            case 57:
              tTempString=tTempString+"9";
              break;
            case 65:
              tTempString=tTempString+"A";
              break;
            case 66:
              tTempString=tTempString+"B";
              break;
            case 67:
              tTempString=tTempString+"C";
              break;
            case 68:
              tTempString=tTempString+"D";
              break;
            case 69:
              tTempString=tTempString+"E";
              break;
            case 70:
              tTempString=tTempString+"F";
              break;
			}//switch
          }//while file
          Serial.print("String Read from ");Serial.print(pistonFile);Serial.print(": ");Serial.print(tTempString);
          for (int j=15;j>=0;j--){
            Serial.print("j=");Serial.print(j);Serial.print("::");
            OutputArray[0][15-j]=t16Stringtoint(tTempString.substring(j*4,j*4+4));//Set the CurrentState of SAMCHAIN1, after PREVIOUS state is reset.
            Serial.print("OutputArray[0][");Serial.print(j,DEC);Serial.print("]: ");Serial.println(OutputArray[0][j],HEX);
			CrescendoCurrentState[0][j]=OutputArray[0][j];

      //WORKAROUND - mask 4'tpt and 4' sw to ped
// WORKAROUND - disable 4' Trumpet stop on SW for cipher
bitClear(CrescendoCurrentState[0][1],0x0B);
bitClear(CrescendoCurrentState[0][0],0x0D);//sw ped 4
// WORKAROUND
      
      //
      

          }
          pistonFile.close();
      } // File exists


// if changes, send notes on and off.  Current state has been dealt with before.  We only handle Crescendo changes
bool CrescChanged=false;

for (int i=0;i<=255;i++){
  int j=0; // only 256 stops supported with this code, on SAMCHAIN1, CurrentState[0][i]. We can reduce i max to 63 to speed this for most applications
  
  
    int currentstateflag=bitRead(CrescendoCurrentState[j][i>>4],i&0xF);
    int previousstateflag=bitRead(CrescendoPreviousState[j][i>>4],i&0xF);
    if(currentstateflag!=previousstateflag){ // no need to send MIDI out for crescendo
      CrescChanged=true;
    }//if changed
    bitWrite(CrescendoPreviousState[j][i>>4],i&0xF,currentstateflag);
  }//i, crescendo changes check
  
  
  if (CrescChanged&&!SFZState){

      Serial.print("PipeOut CrescChanged, Stops Low (1-32):"); 
      Serial.print(byte (0xC0),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC0));
      for (int k=1; k>=0; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          ,HEX );Serial.print(":");// sends out only crescendo changed stops ored with stops on
        PIPESERIAL.write(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          );
        }//m
      }//k
      Serial.println("");


      Serial.print("PipeOut CrescChanged, Stops high (32-63):"); 
      Serial.print(byte (0xC1),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC1));
      for (int k=3; k>=2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          ,HEX );Serial.print(":");// sends out only crescendo changed stops ored with stops on
        PIPESERIAL.write(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          );
        }//m
      }//k
      Serial.println("");




      }// if crescendo changed
      CrescChanged=false;
    

  }//if CurrentCrescendo Level changed
  if((CurrentState[0][0]!=PreviousState[0][0]||CurrentState[0][1]!=PreviousState[0][1])){
      Serial.print("PipeOut Cresc manual stop change CMD, Stops Low (1-32):"); 
      Serial.print(byte (0xC0),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC0));
      for (int k=1; k>=0; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          ,HEX );Serial.print(":");// sends out only crescendo changed stops ored with stops on
        PIPESERIAL.write(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          );        
		  }//m
      }//k
      Serial.println("");
	}// In crescendo, stops changes lower


if((CurrentState[0][2]!=PreviousState[0][2]||CurrentState[0][3]!=PreviousState[0][3])){
      Serial.print("PipeOut Cresc manual stop change CMD, Stops high (32-63):"); 
      Serial.print(byte (0xC1),HEX);Serial.print(":");
      PIPESERIAL.write(byte (0xC1));
      for (int k=3; k>=2; k--){
        for (int m=1; m>=0; m--){
        Serial.print(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          ,HEX );Serial.print(":");// sends out only crescendo changed stops ored with stops on
        PIPESERIAL.write(byte (
          ((CrescendoCurrentState[0][k]>>(m*8))&0xFF)
          |
          ((CurrentState[0][k]>>(m*8))&0xFF))
          );        
		  }//m
      }//k
      Serial.println("");
	}// In crescendo, stops changes upper

  
}//if CrescendoState



////////////////// Crescendo set state (Deleted, see other versions for code)



 
    
//////////////////////////PCSwitch

  PCMessageCurrentState=digitalRead(PCMessageShutdownSwitch);   
  if (PCMessageCurrentState!=PCMessageShutdownSwitchPrevState){
    if (PCMessageCurrentState==0) usbMIDI.sendNoteOn(PCMessageNote,0x7F,PCMessageChannel); else usbMIDI.sendNoteOff(PCMessageNote,0x7F,PCMessageChannel);
    PCMessageShutdownSwitchPrevState=PCMessageCurrentState;
  }

  if(EnablePowerupLED){
    if(!PCMessageReceived)
      digitalWrite(PCMessageLEDPort,bitRead(LoopCounter,6));
    else
      digitalWrite(PCMessageLEDPort,1);
  
    
  }








//////////////////////////// Send out if changed, Previous=Changed //////////////////////////////////



/*for (int i=0;i<=7;i++){
  for (int j=0;j<=3;j++){
    if((CurrentState[j][i*2]!=PreviousState[j][i*2])  ||  (CurrentState[j][i*2+1]!=PreviousState[j][i*2+1]))
	{

		ChangedFlag=true;
		
		if(
		(j==3)// keyboard 1&2
		||(j==2&&i==6) //Pedalboard
		||(j==0&&i<=1) //stop action  
		)
    
		
		{
			Serial.print("PipeOut Regular CMD:"); 
			Serial.print(byte (0xC0 | ((j&0x03)<<3) | (i&0x07)),HEX);Serial.print(":");
			PIPESERIAL.write(byte (0xC0 | ((j&0x03)<<3) | (i&0x07)) );
			for (int k=(i*2+1); k>=i*2; k--){
        
				for (int m=1; m>=0; m--){
				Serial.print(byte ((CurrentState[j][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.

				PIPESERIAL.write(byte ((CurrentState[j][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
			}//m
        
			}//k
		Serial.println("");
		}// if keyboard or pedalboard or stopaction
	
    }// if changed
	
  }//j
}//i
*/


for (int i=0;i<=7;i++){
  for (int j=0;j<=3;j++){
    if((CurrentState[j][i*2]!=PreviousState[j][i*2])  ||  (CurrentState[j][i*2+1]!=PreviousState[j][i*2+1]))
    {
    ChangedFlag=true;
    }//if changed
  }//j
}//i  





//Keyboard processing, 392-511 = [3][8-15], pipe block command DC - DF

for (int k=4;k<=7;k++){
  PipeOutState[1][k]=(CurrentState[3][(k<<1)+1]<<16) | (CurrentState[3][k<<1]);
}



for (int k=0;k<=1;k++){
  
  if(TransposeOffset>0) {
    uint32_t LowHold=PipeOutState[1][4+k*2]; 
    PipeOutState[1][4+k*2]=PipeOutState[1][4+k*2]<<TransposeOffset;
    PipeOutState[1][4+k*2+1]=PipeOutState[1][4+k*2+1]<<TransposeOffset;
    PipeOutState[1][4+k*2+1]=PipeOutState[1][4+k*2+1]|((LowHold>>(32-TransposeOffset))&(0xFFFFFFFF>>(32-TransposeOffset)));

  }
  if(TransposeOffset<0) {
    uint32_t HighHold=PipeOutState[1][4+k*2+1]; 
    PipeOutState[1][4+k*2]=PipeOutState[1][4+k*2]>>(-TransposeOffset);
    PipeOutState[1][4+k*2+1]=PipeOutState[1][4+k*2+1]>>(-TransposeOffset);
    PipeOutState[1][4+k*2]=PipeOutState[1][4+k*2]|((HighHold<<(32+TransposeOffset))&(0xFFFFFFFF<<(32+TransposeOffset)));
  }
}//k



for (int k=4;k<=7;k++){
if(PipeOutState[1][k]!=PipeOutPrevious[1][k])
  {
    PipeOutPrevious[1][k]=PipeOutState[1][k];
    Serial.print("PipeOut Regular CMD, Keyboards:"); 
    Serial.print(byte (0xD8 | ((byte) k)),HEX);Serial.print(":");
    PIPESERIAL.write(byte (0xD8 | ((byte) k)));
    for (int m=3; m>=0; m--){
        Serial.print(byte ((PipeOutState[1][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        PIPESERIAL.write(byte ((PipeOutState[1][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
    }//m
    Serial.println("");
  }//if
}//k  

////////////// END send out keyboards


// Pedal (192-223 = 16 bit [2][12,13] 32 bit [0][6], pipe block command D6
int k=6;
PipeOutState[0][k]=(CurrentState[2][(k<<1)+1]<<16) | (CurrentState[2][k<<1]);
if(TransposeOffset>0) PipeOutState[0][k]=PipeOutState[0][k]<<TransposeOffset; else PipeOutState[0][k]=PipeOutState[0][k]>>(-TransposeOffset);
if(PipeOutState[0][k]!=PipeOutPrevious[0][k])
  {
    PipeOutPrevious[0][k]=PipeOutState[0][k];
    Serial.print("PipeOut Regular CMD, Pedal:"); 
    Serial.print(byte (0xD0 | ((byte) k)),HEX);Serial.print(":");
    PIPESERIAL.write(byte (0xD0 | ((byte) k)));
    for (int m=3; m>=0; m--){
        Serial.print( byte ((PipeOutState[0][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        PIPESERIAL.write( byte ((PipeOutState[0][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
    }//m
    Serial.println("");
  }
  
//
// shoes - on 2E0-2E9, using upper 8.  Pipe block command D7
k=7;
PipeOutState[0][k]=(CurrentState[2][(k<<1)+1]<<16) | (CurrentState[2][k<<1]);
if((PipeOutState[0][k]!=PipeOutPrevious[0][k])&&!CrescendoState)
  {
    PipeOutPrevious[0][k]=PipeOutState[0][k];
    Serial.print("PipeOut Regular CMD, Shoe:"); 
    Serial.print(byte (0xD0 | ((byte) k)),HEX);Serial.print(":");
    PIPESERIAL.write(byte (0xD0 | ((byte) k)));
    uint32_t PipeTemp=PipeOutPrevious[0][k]<<8;
    for (int m=3; m>=0; m--){
        Serial.print( byte ((PipeOutState[0][k]>>(m*8))&0xFF),HEX );Serial.print(":");// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
        PIPESERIAL.write( byte ((PipeOutState[0][k]>>(m*8))&0xFF) );// sends out both changed stops and changed keys to pipe drivers.  TODO - do the same with Crescendo on stops.
    }//m
    Serial.println("");

  }
//
// End send out keys and shoes





// Send any MIDI out, set previousstate to current state.

if (ChangedFlag){
  Serial.print("changedflag 003 LoopCount: ");Serial.println(LoopCounter,DEC);
  for (int j=0;j<=3;j++){
    Serial.print("Post Process Changed Flag- PreviousState[");
    Serial.print(j);
    Serial.print("]:  ");
    for (int i=15;i>=0;i--){
      Serial.print(i,HEX);Serial.print(":");
      Serial.print(PreviousState[j][i],HEX);
      Serial.print(" ");
      }//i
    Serial.println(" ");
  }//j
  for (int j=0;j<=3;j++){
    Serial.print("Post Process Changed Flag- CurrentState[");
    Serial.print(j);
    Serial.print("]:  ");
    for (int i=15;i>=0;i--){
      Serial.print(i,HEX);Serial.print(":");
      Serial.print(CurrentState[j][i],HEX);
      Serial.print(" ");
      }//i
    Serial.println(" ");
  }//j
for (int i=0;i<=255;i++){
  for (int j=0;j<=3;j++){
    int currentstateflag=bitRead(CurrentState[j][i>>4],i&0xF);
    int previousstateflag=bitRead(PreviousState[j][i>>4],i&0xF);
    if(currentstateflag!=previousstateflag){
            Serial.print("i ");Serial.print(i,HEX);Serial.print("   j ");Serial.println(j,HEX);

      if(j<=1) SAMDelayCount=0;
      int MIDICHOut=MIDIChannel+2*j;
      if (bitRead(i,7)==HIGH) MIDICHOut++;
      int NoteNumber=NoteBase+(i&0x7F);
// Remap MIDI IO.  SW= channel 15, 0-0x3C.  GT=Channel 15,0x40-0x5C. Ped=Channel 13, 0x40-5F. Stops Channel 0, 0x00-0x3F
// Map to SW= Channel 1, 0x24=0x26, GT=channel 0 0x24-0x61, PED=Channel 2, 0x24-0x33, Stops Channel 15, 00-0x3F   
      Serial.print("RAW ");Serial.print(NoteNumber,HEX);
      Serial.print(" CH:");
      Serial.println(MIDICHOut,DEC);
      MIDIOutTranslate(MIDICHOut,NoteNumber);
      MIDICHOut=TranslatedMIDIChannel;
      NoteNumber=TranslatedNoteNumber;
         
      if (currentstateflag) {usbMIDI.sendNoteOn(NoteNumber,0x7F,MIDICHOut);Serial.print("CHANGED Send Note ON:");} 
      else  {usbMIDI.sendNoteOff(NoteNumber,0x7F,MIDICHOut);;Serial.print("CHANGED Send Note OFF:");}
      Serial.print("Xlate ");Serial.print(NoteNumber,HEX);
      Serial.print(" CH:");
      Serial.println(MIDICHOut,DEC);
    }
//try
//    if(SAMDelayCount>SAMDelay) bitWrite(PreviousState[j][i>>4],i&0xF,currentstateflag);
// end try      
    bitWrite(PreviousState[j][i>>4],i&0xF,currentstateflag);
  }//j
}//i



}//ChangedFlag


if (PistonChangedFlag){
// TODO why is this here??  for (int i=1;i<=3;i++) for (int j=0;j<=15;j++) CurrentState[i][j]=CurrentState[i][j]|OutputArray[i][j];
    for (int i=0;i<=15;i++){
      if (GCState) {CurrentState[0][i]=CurrentState[0][i]&GCMask[15-i];Serial.print("CurrentState cleared by GC");}
      else {
        if(NewPistonSet==false){
          Serial.print("Not New PistonSet");
        CurrentState[0][i]=CurrentState[0][i]&(~BitMask[PressedPiston][15-i]);
        CurrentState[0][i]=CurrentState[0][i]|OutputArray[0][15-i];//// 15-i


        }
        else
        {
          Serial.print("New piston set");
        }
        
      }
      
    }//i
    NewPistonSet=false;
  Serial.println("PISTON Pressed post process");
  Serial.print("004 LoopCount: ");Serial.println(LoopCounter,DEC);
  for (int j=0;j<=3;j++){
    Serial.print("PISTON MSW first CurrentState[");
    Serial.print(j);
    Serial.print("]:  ");
    for (int i=15;i>=0;i--){
      Serial.print(i,DEC);
      Serial.print(":");
      Serial.print(CurrentState[j][i],HEX);
      Serial.print("  ");
      }//i
    Serial.println(" ");
  }//j
  for (int j=0;j<=3;j++){
    Serial.print("PISTON MSW first PreviousState[");
    Serial.print(j);
    Serial.print("]:  ");
    for (int i=15;i>=0;i--){
      Serial.print(i,DEC);
      Serial.print(":");
      Serial.print(PreviousState[j][i],HEX);
      Serial.print("  ");
      }//i
    Serial.println(" ");
  }//j
  }//PistonChangedFlag


}//if power is on.




//////////////////////////// Wait for loop interrupt ////////////////////////
  LoopDone=true;
//  Serial.print(micros());
  while(IsLoopDone()){
    delay(1); //why adding this in makes it work is beyond me.
    }
    LoopDone=true;
  
}// loop()

//////////////////////////////////////////////////////////////////// FUNCTIONS ///////////////////////////////

void printint16(unsigned int printvalue){
  if (printvalue<0xF) {Serial.print("000");Serial.print(printvalue,HEX);Serial.print(" ");return;}
  if (printvalue<0xFF) {Serial.print("00");Serial.print(printvalue,HEX);Serial.print(" ");return;}
  if (printvalue<0xFFF) {Serial.print("0");Serial.print(printvalue,HEX);Serial.print(" ");return;}
  Serial.print(printvalue,HEX); Serial.print(" ");
  return;
  
}

void PrintLCDMemory(){
      lcd.setCursor(0,0);
      lcd.print("Memory: ");
        if (CurrentMemoryNumber<=999) lcd.print("0");
        if (CurrentMemoryNumber<=99) lcd.print("0");
        if (CurrentMemoryNumber<=9) lcd.print("0");
      lcd.print(CurrentMemoryNumber,DEC);

}

void barOut(int address,int numsegments){

/*  int sendval=0x200;
  if (numsegments==0) {
    barSetup(address,0);
    return;
  }
  if (numsegments==1) 
    barSetup(address,0x200);
  else{
    for (int i=0;i<(numsegments-1);i++){
      sendval=(sendval>>1)|0x200;
    }
    barSetup(address,sendval);
  }*/
}

void barSetup(int address, int GPValue){
//  I2CWrite(address+0x20,0x15,0);// IOCON=0, Bank 0. Reset state is bank 0
  I2CWrite(address+0x20,0x0,0);// IODIRA=0, all outputs
  Serial.print("I2Cwrite(");Serial.print(address+0x20,HEX);Serial.print(",");Serial.print(0x0);Serial.print(",");Serial.println(0);
  I2CWrite(address+0x20,0x1,0xFC);// IODIRB=FC, low 2 bits outputs
  Serial.print("I2Cwrite(");Serial.print(address+0x20,HEX);Serial.print(",");Serial.print(0x1);Serial.print(",");Serial.println(0xfc,HEX);
  I2CWrite(address+0x20,0x12,GPValue&0xFF);// GPIOA
  Serial.print("I2Cwrite(");Serial.print(address+0x20,HEX);Serial.print(",");Serial.print(0x12,HEX);Serial.print(",");Serial.println(GPValue&0xFF,HEX);
  I2CWrite(address+0x20,0x13,GPValue>>8);// GPIO Bank0 = 0xFC -> Bits 0 and 1 outputs
  Serial.print("I2Cwrite(");Serial.print(address+0x20,HEX);Serial.print(",");Serial.print(0x12,HEX);Serial.print(",");Serial.println(GPValue>>8,HEX);
}

void I2CWrite(int I2CAddress, int RegAddress, int Data){
  Wire.beginTransmission(I2CAddress);
  Wire.write(RegAddress); // IOCON
  Wire.write(Data); //IOCON=0
  Wire.endTransmission();
}


/*
void barOut(int address,int numsegments){
  if (numsegments==0) {
  for (int i=0;i<=9;i++) mcp.digitalWrite(i+address*8,LOW);
    return;
  }
  for (int i=0;i<numsegments;i++) mcp.digitalWrite(i+address*8,HIGH);   
  for (int i=numsegments;i<=numsegments;i++) mcp.digitalWrite(i+address*8,LOW);
}
*/

unsigned int t16Stringtoint(String inString){
  unsigned int ReturnValue=0;
  unsigned int AddValue=0;
  Serial.print("inString = ");Serial.println(inString);
  for (int qi=0; qi<=3; qi++){
    switch (inString.charAt(qi)){
      case '0':
        AddValue=0;
        break;
      case '1':
        AddValue=1;
        break;
      case '2':
        AddValue=2;
        break;
      case '3':
        AddValue=3;
        break;
      case '4':
        AddValue=4;
        break;
      case '5':
        AddValue=5;
        break;
      case '6':
        AddValue=6;
        break;
      case '7':
        AddValue=7;
        break;
      case '8':
        AddValue=8;
        break;
      case '9':
        AddValue=9;
        break;
      case 'A':
        AddValue=10;
        break;
      case 'B':
        AddValue=11;
        break;
      case 'C':
        AddValue=12;
        break;
      case 'D':
        AddValue=13;
        break;
      case 'E':
        AddValue=14;
        break;
      case 'F':
        AddValue=15;
        break;
        
    }//switch
    AddValue=AddValue<<(4*(3-qi));
    ReturnValue=ReturnValue|AddValue;
//    Serial.print(inString.charAt(qi));Serial.print(" ");Serial.print(qi);Serial.print(" "); Serial.println(ReturnValue,HEX);    
  }//for
  return ReturnValue;
}//function



void restartLoop(){
  LoopDone=false;
//  Serial.println(millis());
//  Serial.print("TimerDone ");
//  Serial.println(LoopDone);
}

bool IsLoopDone(){
  return LoopDone;
}



// Remap MIDI IO.  SW= channel 15, 0-0x3C.  GT=Channel 15,0x40-0x5C. Ped=Channel 13, 0x40-5F
// Map to SW= Channel 1, 0x24=0x26, GT=channel 0 0x24-0x61, PED=Channel 2, 0x24-0x33
  
void myNoteOff(byte channel, byte note, byte velocity)
{
  Serial.print("External Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  MIDIInTranslate(channel,note);
  
//  if((channel>=MIDIChannel)&&(channel<=(MIDIChannel+3)))
  if((channel>=0)&&(channel<=(2)))
  {
    Serial.print("Message for me...LoopCount: ");
  channel=TranslatedMIDIChannel;
  note=TranslatedNoteNumber;
  Serial.print("External Note Off translated, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
    Serial.println(LoopCounter,DEC);
    int index=(channel-MIDIChannel)/2;
    int wordno=0;
    if(bitRead((channel-MIDIChannel),0)==HIGH) wordno=0x08;
    wordno=wordno+(note>>4);
    int bitno=note&0x0F;
    bitClear(PendingMIDIOff[index][wordno],bitno);

   }

}

void myNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("ExternalNote On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  Serial.print("Base MIDI Channel: ");
  Serial.println(MIDIChannel,HEX);
  
//  if((channel>=MIDIChannel)&&(channel<=(MIDIChannel+7)))
  if((channel>=0)&&(channel<=(2)))
  {
  channel=TranslatedMIDIChannel;
  note=TranslatedNoteNumber;
  Serial.print("External Note On translated, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
    Serial.print("Message for me...LoopCount: ");
    Serial.println(LoopCounter,DEC);
    int index=(channel-MIDIChannel)/2;
    int wordno=0;
    if(bitRead((channel-MIDIChannel),0)==HIGH) wordno=0x08;
    wordno=wordno+(note>>4);
    int bitno=note&0x0F;
    bitSet(PendingMIDIOn[index][wordno],bitno);
    Serial.print("REceive Routine PendingMIDIOn[");Serial.print(index,DEC);Serial.print("][");Serial.print(wordno,DEC);Serial.print("]: ");Serial.print(PendingMIDIOn[index][wordno],HEX);Serial.print(" LoopCount:");Serial.println(LoopCounter,DEC);

  }
  if(channel==PCMessageChannel){
    if (note==PCMessageNote) {PCMessageReceived=true;}  
  }
}


// Remap MIDI IO.  SW= channel 15, 0-0x3C.  GT=Channel 15,0x40-0x5C. Ped=Channel 13, 0x40-5F. Stops=Channel 0, 00-0x3F
// Map to SW= Channel 1, 0x24=0x26, GT=channel 0 0x24-0x61, PED=Channel 2, 0x24-0x33. Stops=Channel 8, 0x00=0x3F.
 
void MIDIOutTranslate(int channel, int note){
  bool Found=false;
  if(channel==15){
    if(note<=0x3F){
      TranslatedMIDIChannel=1;
      TranslatedNoteNumber=note+0x24;
      Found=true;
    }
    if(note>=0x40&&note<=0x7F){
      TranslatedMIDIChannel=0;
      TranslatedNoteNumber=(note&0x3F)+0x24;
      Found=true;
    }
    if(note>=0x80&&note<=0xBF){
      TranslatedMIDIChannel=3;
      TranslatedNoteNumber=note&0x7F;
      Found=true;
    }
    if(note>=0xC0&&note<=0xFF){
      TranslatedMIDIChannel=3;
      TranslatedNoteNumber=note&0x7F;
      Found=true;
    }
  }

  if(channel==13){
    if(note<=0x3F){
      TranslatedMIDIChannel=9;
      TranslatedNoteNumber=note;
      Found=true;
    }
    if(note>=0x40&&note<=0x7F){
      TranslatedMIDIChannel=2;
      TranslatedNoteNumber=(note&0x3F)+0x24;
      Found=true;
    }
    if(note>=0x80&&note<=0xFF){
      TranslatedMIDIChannel=10;
      TranslatedNoteNumber=note&0x7F;
      Found=true;
    }
  }
  
  if (!Found){
    TranslatedMIDIChannel=14;
    TranslatedNoteNumber=0x7F;
  }
  
}


void MIDIInTranslate(int channel, int note){
  bool Found=false;
  if(channel==1&&note>=0x24){
    TranslatedMIDIChannel=15;
    TranslatedNoteNumber=note-0x24;
      Found=true;
  }
  if(channel==0&&note>=0x24){
    TranslatedMIDIChannel=15;
    TranslatedNoteNumber=note-0x24+0x40;
      Found=true;
  }
  if(channel==3){
    TranslatedMIDIChannel=15;
    TranslatedNoteNumber=note+0x80;
      Found=true;
  }
  if(channel==9){
    TranslatedMIDIChannel=13;
    TranslatedNoteNumber=note;
      Found=true;
  }
  if(channel==10){
    TranslatedMIDIChannel=15;
    TranslatedNoteNumber=note+0x80;
      Found=true;
  }
  if(channel==2&&note<=67&&note>=36){
    TranslatedMIDIChannel=13;
    TranslatedNoteNumber=note-0x24+0x40;
      Found=true;
  }
  
  if (!Found){
    TranslatedMIDIChannel=9;
    TranslatedNoteNumber=0x3F;
  }
    
}
 
