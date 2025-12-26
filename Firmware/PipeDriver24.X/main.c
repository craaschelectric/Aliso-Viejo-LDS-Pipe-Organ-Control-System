/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F46K42
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

uint8_t KeyArray[64];
uint8_t StopArray[64];
uint16_t KeyTestArray[4];
uint8_t ReceiveBuffer[17];
uint8_t TempBuffer;
uint8_t TempData1;
uint8_t TempData2;
uint8_t ByteCount;
bool CommandInProcess=false;
bool CTS=true;
bool Mine=false;
bool Gate;
bool ANDGate;
bool NANDGate;
bool CouplerFlag;
uint8_t EEBase;
signed int i;
signed int j;
uint8_t StartArray;
int DeliveryAddress;

uint16_t BoardAddress = 0x1E;
uint8_t ValidBlocks=0;
uint16_t ValiditySignal=0;
uint8_t BlockConfig[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
int StartBit[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
int EndBit[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
signed char Offset[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
uint16_t GateBit[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
bool NoGate[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
uint16_t ANDBit[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
uint16_t NANDBit[32]={0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
uint32_t OutputArray=0;
bool OutputArrayPending=false;
bool Locked=false;


/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    PORTA=0;
    PORTB=PORTB&0xF0;
    PORTC=PORTC&0xF0;
    PORTD=0;
    PIPE25_SetLow();
    

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    UART1_Initialize();
    UART2_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_Initialize();
    INTCON0bits.GIEL = 1;

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    
    
    ValiditySignal=(uint16_t) ((DATAEE_ReadByte(6)<<8) | (DATAEE_ReadByte(7)));
    if (ValiditySignal==0x5A96){
        BoardAddress=(uint16_t)(DATAEE_ReadByte(0)<<8 | DATAEE_ReadByte(1));
        ValidBlocks=DATAEE_ReadByte(2);
        for (i=1; i<=ValidBlocks; i++){
            BlockConfig[i-1]= DATAEE_ReadByte((uint16_t) (i*8));
            StartBit[i-1]= (int) DATAEE_ReadByte((uint16_t) (i*8+1));
            EndBit[i-1]=(int) DATAEE_ReadByte((uint16_t) (i*8+2));
            Offset[i-1]= (signed char) DATAEE_ReadByte((uint16_t) (i*8+3));
            GateBit[i-1]=(uint16_t) DATAEE_ReadByte((uint16_t) (i*8+4));
            ANDBit[i-1]=(uint16_t) DATAEE_ReadByte((uint16_t) (i*8+5));
            NANDBit[i-1]= (uint16_t) DATAEE_ReadByte((uint16_t) (i*8+6));
            if ((BlockConfig[i-1]&0x1)==1) StartBit[i-1]=0x100 | StartBit[i-1];
            if ((BlockConfig[i-1]&0b10)==0b10) EndBit[i-1]=0x100 | EndBit[i-1];
            if ((BlockConfig[i-1]&0b100)==0b100) GateBit[i-1]=0x100 | GateBit[i-1];
            if ((BlockConfig[i-1]&0b1000)==0b1000) ANDBit[i-1]=0x100 | ANDBit[i-1];
            if ((BlockConfig[i-1]&0b10000)==0b10000) NANDBit[i-1]=0x100 | NANDBit[i-1];
            if ((BlockConfig[i-1]&0b100000)==0b100000) NoGate[i-1]=true;
            
        }
    }

    while (1)
    {
        // DataStructure
        // Keyboard and Stop arrays are 16 long long words (512 bits).  
        // EERPOM configuration.  PIC18F46K42 has 1K of EEPROM, 4K data RAM
        //      0= Board Address MSB
        //      1= Board Address LSB
        //      2= Number of valid blocks (Up to 32)
        //      6= Validity signal for EEPROM, if EEPROM is valid, =0x5A
        //      7= Validity signal for EEPROM, if EEPROM is valid, =0x96
        //   Configuration blocks (n start at 1)
        //      8n+0 = Block Config
        //          Bit 0 = bit 9 of Start field
        //          Bit 1 = bit 9 of End field
        //          Bit 2 = bit 9 of Gate field
        //          Bit 3 = bit 9 of And field
        //          Bit 4 = bit 9 of Nand field
        //          Bit 5 = No gates - Replicate start to end
        //          Bit 7 = 1=Coupler 0=Stop
        //      8n+1 = Start bit - 512 bit number of the Keyboard bit to start 
        // the pipe drivers. This always maps to PIPE01
        //      8n+2 = End bit - 512 bit number of the Keyboard bit to end 
        // the pipe drivers
        //      8n+3 = 256 bit Offset from keyboard
        //      8n+4 = Gate bit - 512 bit number of the Stop bit to gate on. 
        // This reflects the stop in question
        //      8n+5 = AND gate - 512 bit number of the Stop bit to AND with 
        // the gate bit. Used when the Coupler bit =1
        //      8n+6 = NAND gate - 512 bit number of the Stop bit to NAND with 
        // the gate.  Used for Unison Off.
        //      Activation formula is 
        //          if (keyboardbit+offset) is between Start and End. So 
        // start loop (x) at (Start+offset to End+offset)
        //              Drive bit[x]=KeyboardBit[start+offset+x]&(Gate[n]&
        // ((!Coupler&!NAND)|(Coupler&AND))
        //      Calculation is done on 0xCn/0xDn commands
        
        
        
        
        
        // Receive from UART1 
        // command 0xAn. SysConfigure n=number of bytes (0-15, 0 on read).  
        //      Byte order following: BoardMSB // BoardLSB // Address(bit 7=0 
        //      for write, 1 for read) Start Address= aaaa aaa0 // n bytes of data (if Write)
        //              If it isn't mine, CTS=false for me until 0xFE.
        // command 0xBn. MIDI CC command, n=channel. Byte order following: 
        //      Controller number (0-0x7F), Value (0-0x7F)
        // command 0b110r aaaa. r:0=StopData, 1=KeyData. aaaa=address of long 
        //      long.  Byte order following: 4 bytes of data, MSB first in time.
        // command 0xFD = Lock EEPROM from being written until next powerup.
        // command 0xFE = ACK/CTS.  Hold serial output until ACK if the EERPOM 
        //  0xAn command isn't mine. Host process [Send An array]
        //  [Receive En array][Send 0xFE]
        // command 0xFF = Reset
        //
        // TODO - Stop 0,0 is now always on by default,  Need to have default off to FF FF
        
        if (UART1_is_rx_ready()){
            TempBuffer=UART1_Read();
        }
// 0xAn EEPROM sys configure
        //  Note, new version the address assumes a 0 on the end to address 256 bytes of EEPROM for 32 blocks.  
        //  Format is 0xAn MSBBoardAddress LSBBoardAddress raaa aaaa (bytes).  Start Address= aaaa aaa0. read if r=1. 
        if ((TempBuffer&0xF0)==0xA0){
            while (!UART1_is_rx_ready()){}
            TempData1=UART1_Read();
            while (!UART1_is_rx_ready()){}
            TempData2=UART1_Read();
            if ((TempData1<<8|TempData2)==BoardAddress) Mine= true; else Mine=false;
            while (!UART1_is_rx_ready()){}
            EEBase=UART1_Read();
            ByteCount=TempBuffer&0x0F;
            if (Mine){
                if ((TempBuffer&0x0F)>0 && (EEBase&0x80)==0){//write
                    for (i=1; i <= (ByteCount&0x7F); i++){
                        while (!UART1_is_rx_ready()){}
                        TempData1=UART1_Read();
                        ReceiveBuffer[i]=TempData1;
                    }
                    if(Locked==false){
                        for (i=1; i <= (ByteCount&0x7F); i++){
                            DATAEE_WriteByte((uint16_t) ((EEBase<<1)+i-1),ReceiveBuffer[i]);
                        }
                    }
                    
                    BoardAddress=(uint16_t)(DATAEE_ReadByte(0)<<8 | DATAEE_ReadByte(1));
                    ValidBlocks=DATAEE_ReadByte(2);
                    for (i=1; i<=ValidBlocks; i++){
                        BlockConfig[i-1]= DATAEE_ReadByte((uint16_t) (i*8));
                        StartBit[i-1]= (int) DATAEE_ReadByte((uint16_t) (i*8+1));
                        EndBit[i-1]=(int) DATAEE_ReadByte((uint16_t) (i*8+2));
                        Offset[i-1]= (signed char) DATAEE_ReadByte((uint16_t) (i*8+3));
                        GateBit[i-1]=(uint16_t) DATAEE_ReadByte((uint16_t) (i*8+4));
                        ANDBit[i-1]=(uint16_t) DATAEE_ReadByte((uint16_t) (i*8+5));
                        NANDBit[i-1]= (uint16_t) DATAEE_ReadByte((uint16_t) (i*8+6));
                        if ((BlockConfig[i-1]&0x1)==1) StartBit[i-1]=0x100 | StartBit[i-1];
                        if ((BlockConfig[i-1]&0b10)==0b10) EndBit[i-1]=0x100 | EndBit[i-1];
                        if ((BlockConfig[i-1]&0b100)==0b100) GateBit[i-1]=0x100 | GateBit[i-1];
                        if ((BlockConfig[i-1]&0b1000)==0b1000) ANDBit[i-1]=0x100 | ANDBit[i-1];
                        if ((BlockConfig[i-1]&0b10000)==0b10000) NANDBit[i-1]=0x100 | NANDBit[i-1];
                        
                    }
                    

                }//write
                
//                if (CTS && (TempBuffer&0x0F)>0 && (EEBase&0x80)==0x80){//read
                  if (CTS && (TempBuffer&0x0F)>0){//read, ack
                //  On read, we send an En command back to the host through UART1
                      if(BoardAddress==0){
                          BoardAddress=(uint16_t) (DATAEE_ReadByte(0)<<8)|DATAEE_ReadByte(1);
                      }
                        while (!UART1_is_tx_ready()){}
                        UART1_Write(0xE0|ByteCount);
                        while (!UART1_is_tx_ready()){}
                        UART1_Write((uint8_t)((BoardAddress&0xFF00)>>8));
                        while (!UART1_is_tx_ready()){}
                        UART1_Write((uint8_t) (BoardAddress&0xFF)>>8);
                        while (!UART1_is_tx_ready()){}
                        UART1_Write((uint8_t) ((EEBase<<1)));
                        for (i=0;i<=ByteCount-1;i++){
                            while (!UART1_is_tx_ready()){}
                            UART1_Write((uint8_t) DATAEE_ReadByte((uint16_t) ((EEBase<<1)+i)));
                        }
                        
                    
                }//read    
                    
            }//mine
            else//not mine
            {
                if ((TempBuffer&0x0F)>0 && (EEBase&0x80)==0){//write
                    for (i=1; i <= (ByteCount&0x7F); i++){
                        while (!UART1_is_rx_ready()){}
                        TempData1=UART1_Read();
                        ReceiveBuffer[i]=TempData1;
                    }
                }
                
            }
            
            Mine=false;
        }//A0
        
// Bn CC command
        
        if ((TempBuffer&0xF0)==0xB0){
            while (!UART1_is_rx_ready()){}
            TempData1=UART1_Read();
            while (!UART1_is_rx_ready()){}
            TempData2=UART1_Read();
            // Insert pedal control here.  It may be a different code load.
            
        }

// 0b110r nnnn - Write Array
        if ((TempBuffer&0xE0)==0xC0){
            LEDOUT_SetHigh();
            for (i=3; i>=0; i--){
                while (!UART1_is_rx_ready()){}
                DeliveryAddress=(TempBuffer&0x0F)<<2;
                DeliveryAddress=DeliveryAddress+i;
                TempData1=UART1_Read();
                if ((TempBuffer&0x10)==0x10){// key data
                    KeyArray[DeliveryAddress]=TempData1;
                }
                else {// stop data
                    StopArray[DeliveryAddress]=TempData1;
                }
                
            }// for i
    		OutputArray=0;
            OutputArrayPending=true;

            for (i=0; i<=(ValidBlocks-1); i++){
                StartArray=(uint8_t) StartBit[i]>>3;
                if((BlockConfig[i]&0x1)>0) StartArray=StartArray|0x20;
                
                
                
        //              Drive bit[x]=KeyboardBit[start+offset+x]&(Gate[n]&((!Coupler&!NAND)|(Coupler&AND))
                Gate=     ((StopArray[GateBit[i]>>3] & 1<<(GateBit[i]&7)  )>0);
                ANDGate=  ((StopArray[ANDBit[i] >>3] & 1<<(ANDBit[i] &7)  )>0);
                NANDGate= ((StopArray[NANDBit[i]>>3] & 1<<(NANDBit[i]&7)  )>0);
                CouplerFlag = ((BlockConfig[i]&0x80)==0x80);
                KeyTestArray[0]=(uint16_t) ((KeyArray[StartArray+1]<<8) | (KeyArray[StartArray]))>>(StartBit[i]&0x7);
                KeyTestArray[1]=(uint16_t) ((KeyArray[StartArray+2]<<8) | (KeyArray[StartArray+1]))>>(StartBit[i]&0x7);
                KeyTestArray[2]=(uint16_t) ((KeyArray[StartArray+3]<<8) | (KeyArray[StartArray+2]))>>(StartBit[i]&0x7);
                KeyTestArray[3]=(uint16_t) ((KeyArray[StartArray+4]<<8) | (KeyArray[StartArray+3]))>>(StartBit[i]&0x7);
                int EndBitVal=EndBit[i];
//                if((BlockConfig[i]&0x1)>0) EndBitVal=EndBitVal|0x100;
                int StartBitVal=StartBit[i];
//                if((BlockConfig[i]&0x2)>0) StartBitVal=StartBitVal|0x100;
 
                
                if ( 
                        (!NoGate[i] && Gate && Offset[i]==0 && ( (!CouplerFlag&&!NANDGate) || ( CouplerFlag&&ANDGate ) ))
                        ||(NoGate[i] && Offset[i]==0)
                        
                        ){
                    OutputArrayPending=true;
                    if (                               (KeyTestArray[0]&0b00000001)>0) OutputArray=OutputArray|1;
                    if ( (EndBitVal-StartBitVal)>=1 && (KeyTestArray[0]&0b00000010)>0) OutputArray=OutputArray|2;
                    if ( (EndBitVal-StartBitVal)>=2 && (KeyTestArray[0]&0b00000100)>0) OutputArray=OutputArray|4;
                    if ( (EndBitVal-StartBitVal)>=3 && (KeyTestArray[0]&0b00001000)>0) OutputArray=OutputArray|8;
                    if ( (EndBitVal-StartBitVal)>=4 && (KeyTestArray[0]&0b00010000)>0) OutputArray=OutputArray|0x10;
                    if ( (EndBitVal-StartBitVal)>=5 && (KeyTestArray[0]&0b00100000)>0) OutputArray=OutputArray|0x20;
                    if ( (EndBitVal-StartBitVal)>=6 && (KeyTestArray[0]&0b01000000)>0) OutputArray=OutputArray|0x40;
                    if ( (EndBitVal-StartBitVal)>=7 && (KeyTestArray[0]&0b10000000)>0) OutputArray=OutputArray|0x80;
                    if ( (EndBitVal-StartBitVal)>=8 && (KeyTestArray[1]&0b00000001)>0) OutputArray=OutputArray|0x100;
                    if ( (EndBitVal-StartBitVal)>=9 &&  (KeyTestArray[1]&0b00000010)>0) OutputArray=OutputArray|0x200;
                    if ( (EndBitVal-StartBitVal)>=10 && (KeyTestArray[1]&0b00000100)>0) OutputArray=OutputArray|0x400;
                    if ( (EndBitVal-StartBitVal)>=11 && (KeyTestArray[1]&0b00001000)>0) OutputArray=OutputArray|0x800;
                    if ( (EndBitVal-StartBitVal)>=12 && (KeyTestArray[1]&0b00010000)>0) OutputArray=OutputArray|0x1000;
                    if ( (EndBitVal-StartBitVal)>=13 && (KeyTestArray[1]&0b00100000)>0) OutputArray=OutputArray|0x2000;
                    if ( (EndBitVal-StartBitVal)>=14 && (KeyTestArray[1]&0b01000000)>0) OutputArray=OutputArray|0x4000;
                    if ( (EndBitVal-StartBitVal)>=15 && (KeyTestArray[1]&0b10000000)>0) OutputArray=OutputArray|0x8000;
                    if ( (EndBitVal-StartBitVal)>=16 && (KeyTestArray[2]&0b00000001)>0) OutputArray=OutputArray|0x10000;
                    if ( (EndBitVal-StartBitVal)>=17 && (KeyTestArray[2]&0b00000010)>0) OutputArray=OutputArray|0x20000;
                    if ( (EndBitVal-StartBitVal)>=18 && (KeyTestArray[2]&0b00000100)>0) OutputArray=OutputArray|0x40000;
                    if ( (EndBitVal-StartBitVal)>=19 && (KeyTestArray[2]&0b00001000)>0) OutputArray=OutputArray|0x80000;
                    if ( (EndBitVal-StartBitVal)>=20 && (KeyTestArray[2]&0b00010000)>0) OutputArray=OutputArray|0x100000;
                    if ( (EndBitVal-StartBitVal)>=21 && (KeyTestArray[2]&0b00100000)>0) OutputArray=OutputArray|0x200000;
                    if ( (EndBitVal-StartBitVal)>=22 && (KeyTestArray[2]&0b01000000)>0) OutputArray=OutputArray|0x400000;
                    if ( (EndBitVal-StartBitVal)>=23 && (KeyTestArray[2]&0b10000000)>0) OutputArray=OutputArray|0x800000;
                    if ( (EndBitVal-StartBitVal)>=24 && (KeyTestArray[3]&0b00000001)>0) OutputArray=OutputArray|0x1000000;
                    
                }//Gate No offset
                
                
                if ( 
                        (!NoGate[i]&&Gate && Offset[i]>0 && ( (!CouplerFlag&&!NANDGate) || ( CouplerFlag&&ANDGate ) ))   
                        ||(NoGate[i]&&Offset[i]>0)
                        
                        ){
                    OutputArrayPending=true;
                    if (                               (KeyTestArray[0]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)1<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=1 && (KeyTestArray[0]&0b00000010)>0) OutputArray=OutputArray|((uint32_t)2<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=2 && (KeyTestArray[0]&0b00000100)>0) OutputArray=OutputArray|((uint32_t)4<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=3 && (KeyTestArray[0]&0b00001000)>0) OutputArray=OutputArray|((uint32_t)8<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=4 && (KeyTestArray[0]&0b00010000)>0) OutputArray=OutputArray|((uint32_t)0x10<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=5 && (KeyTestArray[0]&0b00100000)>0) OutputArray=OutputArray|((uint32_t)0x20<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=6 && (KeyTestArray[0]&0b01000000)>0) OutputArray=OutputArray|((uint32_t)0x40<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=7 && (KeyTestArray[0]&0b10000000)>0) OutputArray=OutputArray|((uint32_t)0x80<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=8 && (KeyTestArray[1]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)0x100<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=9 &&  (KeyTestArray[1]&0b00000010)>0) OutputArray=OutputArray|((uint32_t)0x200<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=10 && (KeyTestArray[1]&0b00000100)>0) OutputArray=OutputArray|((uint32_t)0x400<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=11 && (KeyTestArray[1]&0b00001000)>0) OutputArray=OutputArray|((uint32_t)0x800<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=12 && (KeyTestArray[1]&0b00010000)>0) OutputArray=OutputArray|((uint32_t)0x1000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=13 && (KeyTestArray[1]&0b00100000)>0) OutputArray=OutputArray|((uint32_t)0x2000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=14 && (KeyTestArray[1]&0b01000000)>0) OutputArray=OutputArray|((uint32_t)0x4000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=15 && (KeyTestArray[1]&0b10000000)>0) OutputArray=OutputArray|((uint32_t)0x8000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=16 && (KeyTestArray[2]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)0x10000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=17 && (KeyTestArray[2]&0b00000010)>0) OutputArray=OutputArray|((uint32_t)0x20000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=18 && (KeyTestArray[2]&0b00000100)>0) OutputArray=OutputArray|((uint32_t)0x40000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=19 && (KeyTestArray[2]&0b00001000)>0) OutputArray=OutputArray|((uint32_t)0x80000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=20 && (KeyTestArray[2]&0b00010000)>0) OutputArray=OutputArray|((uint32_t)0x100000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=21 && (KeyTestArray[2]&0b00100000)>0) OutputArray=OutputArray|((uint32_t)0x200000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=22 && (KeyTestArray[2]&0b01000000)>0) OutputArray=OutputArray|((uint32_t)0x400000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=23 && (KeyTestArray[2]&0b10000000)>0) OutputArray=OutputArray|((uint32_t)0x800000<<Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=24 && (KeyTestArray[3]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)0x1000000<<Offset[i]);
					
                    
                    
                }//Gate Offset>0
                
                
                
                if ( 
                        (!NoGate[i]&&Gate && Offset[i]<0 && ( (!CouplerFlag&&!NANDGate) || ( CouplerFlag&&ANDGate ) ) )  
                        ||(NoGate[i]&&Offset[i]<0)
                        
                        ){
                    OutputArrayPending=true;
                    if (                               (KeyTestArray[0]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)1>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=1 && (KeyTestArray[0]&0b00000010)>0) OutputArray=OutputArray|((uint32_t)2>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=2 && (KeyTestArray[0]&0b00000100)>0) OutputArray=OutputArray|((uint32_t)4>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=3 && (KeyTestArray[0]&0b00001000)>0) OutputArray=OutputArray|((uint32_t)8>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=4 && (KeyTestArray[0]&0b00010000)>0) OutputArray=OutputArray|((uint32_t)0x10>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=5 && (KeyTestArray[0]&0b00100000)>0) OutputArray=OutputArray|((uint32_t)0x20>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=6 && (KeyTestArray[0]&0b01000000)>0) OutputArray=OutputArray|((uint32_t)0x40>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=7 && (KeyTestArray[0]&0b10000000)>0) OutputArray=OutputArray|((uint32_t)0x80>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=8 && (KeyTestArray[1]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)0x100>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=9 &&  (KeyTestArray[1]&0b00000010)>0) OutputArray=OutputArray|((uint32_t)0x200>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=10 && (KeyTestArray[1]&0b00000100)>0) OutputArray=OutputArray|((uint32_t)0x400>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=11 && (KeyTestArray[1]&0b00001000)>0) OutputArray=OutputArray|((uint32_t)0x800>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=12 && (KeyTestArray[1]&0b00010000)>0) OutputArray=OutputArray|((uint32_t)0x1000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=13 && (KeyTestArray[1]&0b00100000)>0) OutputArray=OutputArray|((uint32_t)0x2000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=14 && (KeyTestArray[1]&0b01000000)>0) OutputArray=OutputArray|((uint32_t)0x4000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=15 && (KeyTestArray[1]&0b10000000)>0) OutputArray=OutputArray|((uint32_t)0x8000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=16 && (KeyTestArray[2]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)0x10000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=17 && (KeyTestArray[2]&0b00000010)>0) OutputArray=OutputArray|((uint32_t)0x20000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=18 && (KeyTestArray[2]&0b00000100)>0) OutputArray=OutputArray|((uint32_t)0x40000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=19 && (KeyTestArray[2]&0b00001000)>0) OutputArray=OutputArray|((uint32_t)0x80000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=20 && (KeyTestArray[2]&0b00010000)>0) OutputArray=OutputArray|((uint32_t)0x100000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=21 && (KeyTestArray[2]&0b00100000)>0) OutputArray=OutputArray|((uint32_t)0x200000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=22 && (KeyTestArray[2]&0b01000000)>0) OutputArray=OutputArray|((uint32_t)0x400000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=23 && (KeyTestArray[2]&0b10000000)>0) OutputArray=OutputArray|((uint32_t)0x800000>>Offset[i]);
                    if ( (EndBitVal-StartBitVal)>=24 && (KeyTestArray[3]&0b00000001)>0) OutputArray=OutputArray|((uint32_t)0x1000000>>Offset[i]);
					
					
/*
                    if (                               (KeyTestArray[0]&0b00000001)>0) PIPE01_SetHigh(); else PIPE01_SetLow();
                    if ( (EndBitVal-StartBitVal)>=1 && (KeyTestArray[0]&0b00000010)>0) PIPE02_SetHigh(); else PIPE02_SetLow();
                    if ( (EndBitVal-StartBitVal)>=2 && (KeyTestArray[0]&0b00000100)>0) PIPE03_SetHigh(); else PIPE03_SetLow();
                    if ( (EndBitVal-StartBitVal)>=3 && (KeyTestArray[0]&0b00001000)>0) PIPE04_SetHigh(); else PIPE04_SetLow();
                    if ( (EndBitVal-StartBitVal)>=4 && (KeyTestArray[0]&0b00010000)>0) PIPE05_SetHigh(); else PIPE05_SetLow();
                    if ( (EndBitVal-StartBitVal)>=5 && (KeyTestArray[0]&0b00100000)>0) PIPE06_SetHigh(); else PIPE06_SetLow();
                    if ( (EndBitVal-StartBitVal)>=6 && (KeyTestArray[0]&0b01000000)>0) PIPE07_SetHigh(); else PIPE07_SetLow();
                    if ( (EndBitVal-StartBitVal)>=7 && (KeyTestArray[0]&0b10000000)>0) PIPE08_SetHigh(); else PIPE08_SetLow();
                    if ( (EndBitVal-StartBitVal)>=8 && (KeyTestArray[1]&0b00000001)>0) PIPE09_SetHigh(); else PIPE09_SetLow();
                    if ( (EndBitVal-StartBitVal)>=9 &&  (KeyTestArray[1]&0b00000010)>0) PIPE10_SetHigh(); else PIPE10_SetLow();
                    if ( (EndBitVal-StartBitVal)>=10 && (KeyTestArray[1]&0b00000100)>0) PIPE11_SetHigh(); else PIPE11_SetLow();
                    if ( (EndBitVal-StartBitVal)>=11 && (KeyTestArray[1]&0b00001000)>0) PIPE12_SetHigh(); else PIPE12_SetLow();
                    if ( (EndBitVal-StartBitVal)>=12 && (KeyTestArray[1]&0b00010000)>0) PIPE13_SetHigh(); else PIPE13_SetLow();
                    if ( (EndBitVal-StartBitVal)>=13 && (KeyTestArray[1]&0b00100000)>0) PIPE14_SetHigh(); else PIPE14_SetLow();
                    if ( (EndBitVal-StartBitVal)>=14 && (KeyTestArray[1]&0b01000000)>0) PIPE15_SetHigh(); else PIPE15_SetLow();
                    if ( (EndBitVal-StartBitVal)>=15 && (KeyTestArray[1]&0b10000000)>0) PIPE16_SetHigh(); else PIPE16_SetLow();
                    if ( (EndBitVal-StartBitVal)>=16 && (KeyTestArray[2]&0b00000001)>0) PIPE17_SetHigh(); else PIPE17_SetLow();
                    if ( (EndBitVal-StartBitVal)>=17 && (KeyTestArray[2]&0b00000010)>0) PIPE18_SetHigh(); else PIPE18_SetLow();
                    if ( (EndBitVal-StartBitVal)>=18 && (KeyTestArray[2]&0b00000100)>0) PIPE19_SetHigh(); else PIPE19_SetLow();
                    if ( (EndBitVal-StartBitVal)>=19 && (KeyTestArray[2]&0b00001000)>0) PIPE20_SetHigh(); else PIPE20_SetLow();
                    if ( (EndBitVal-StartBitVal)>=20 && (KeyTestArray[2]&0b00010000)>0) PIPE21_SetHigh(); else PIPE21_SetLow();
                    if ( (EndBitVal-StartBitVal)>=21 && (KeyTestArray[2]&0b00100000)>0) PIPE22_SetHigh(); else PIPE22_SetLow();
                    if ( (EndBitVal-StartBitVal)>=22 && (KeyTestArray[2]&0b01000000)>0) PIPE23_SetHigh(); else PIPE23_SetLow();
                    if ( (EndBitVal-StartBitVal)>=23 && (KeyTestArray[2]&0b10000000)>0) PIPE24_SetHigh(); else PIPE24_SetLow();
                    if ( (EndBitVal-StartBitVal)>=24 && (KeyTestArray[3]&0b00000001)>0) PIPE25_SetHigh(); else PIPE25_SetLow();

*/   
                }//Gate Offset<0

            }//i
            if (OutputArrayPending){
                uint32_t OutputToPort=0;
                    PORTA=(int) OutputArray&0xFF;
                    OutputToPort=(OutputArray>>8);
					PORTB=(PORTB &0xF0) | ((int)OutputToPort&0x0F);
                    OutputToPort=(OutputArray>>12);
					PORTC=(PORTC &0xF0) | ((int)OutputToPort&0x0F);
                    OutputToPort=(OutputArray>>16);
					PORTD=((int)OutputToPort&0xFF);
					if ((OutputArray&0x1000000) == 0x1000000) PIPE25_SetHigh(); else PIPE25_SetLow();
// Special case rework for Aliso 8 Principal 25-48, Pipe25 on Pipe13 (board 0x0A)
//					if ((OutputArray&0x001000) == 0x001000) PIPE25_SetHigh(); else PIPE25_SetLow();
			}		

            LEDOUT_SetLow();
        }//0b110r nnnn

        
// 0xFn - System stuff        
        if (TempBuffer==0xFF) RESET();
        if (TempBuffer==0xFE) CTS=true;
        if (TempBuffer==0xFD) Locked=true;

        CLRWDT();
        
        // Receive from UART2/Send to UART1 Tx
        // Data received from upstream is passed to UART1 Tx
        // If I'm addressed, assemble EEPROM data and send
        if (UART2_is_rx_ready()){
            TempBuffer=UART2_Read();
            while (!UART1_is_tx_ready()){}
            UART1_Write(TempBuffer);

        }
        
        
        TempBuffer=0;

        // Add your application code
    }// while 1


}
/**
 End of File
*/