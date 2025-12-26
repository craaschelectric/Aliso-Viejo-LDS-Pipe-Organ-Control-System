/**
  Generated Interrupt Manager Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.c

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F15375
        Driver Version    :  2.03
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above or later
        MPLAB 	          :  MPLAB X 5.20
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

#include "interrupt_manager.h"
#include "mcc.h"
extern uint8_t BaseAddress;
extern uint8_t CurrentSAMState;
extern uint8_t ClockCount;
extern int CurrentStateSync;
extern int CurrentStateCLK;
extern uint8_t NewSAMState;
extern uint8_t FireOffSAMs;
extern uint8_t FireOnSAMs;
//uint8_t BitChangedFiring=0;
extern int i;
extern uint8_t mask;
extern uint8_t temp;
extern int SAMsFiring;
extern int SAMsNeedFiring;
extern uint8_t MessageCount;
extern uint8_t SAMorLED;
extern uint8_t SAMFireTime;
extern uint8_t BaseAddressMask;
#define bitset(var,bitno) ((var) |= 1UL <<(bitno))
#define bitclr(var,bitno) ((var) &= ~(1UL<<(bitno)))

void  INTERRUPT_Initialize (void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
//    INTCONbits.IPEN = 0;
}

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.IOCIE == 1 && PIR0bits.IOCIF == 1)
    {
        PIN_MANAGER_IOC();
        if (CLK_PORT==1)// CLK Rising Edge - put data on periphout
        {
            ClockCount++;
            if((ClockCount&BaseAddressMask)==BaseAddress)
            {
                temp=~PORTD;
//                if (SAMsFiring==1) temp=~CurrentSAMState; else temp=PORTD;
                temp=temp>>((ClockCount&~BaseAddressMask));
                if ((temp&0x1)==1)// Negative common, negative logic. 0==ON. But a 1 output drive is inactive, 0 is active. So duplicate state.
                    {
                        PERIPHOUT_SetDigitalOutput();
                        PERIPHOUT_SetHigh();
                        __delay_us(1); // Open drain driver, drive high to help the bus
                        PERIPHOUT_SetDigitalInput();
                    }
                    else
                    {
                        PERIPHOUT_SetLow();
                        PERIPHOUT_SetDigitalOutput();
                    }   
            }
            if((ClockCount&BaseAddressMask)!=BaseAddress)
            {
                PERIPHOUT_SetDigitalInput(); //if it's not mine, better not drive the bus.
            }
            
        }//end rising edge
        if (CLK_PORT==0)// Falling edge read data on masterout
        {
            if((ClockCount&BaseAddressMask)==BaseAddress)
            {
                mask=(ClockCount&~BaseAddressMask);
//                if((BitChangedFiring&(1<<mask))==0){// this preserves new changes coming in during the firing
                    bitclr(NewSAMState,mask);
                    if(MASTEROUT_PORT==1) 
                    {bitset(NewSAMState,mask);}
//                }
//                if (SAMsFiring&&((CurrentSAMState^NewSAMState)&(1<<mask))) bitset(BitChangedFiring,mask);
            }
            
        }// end falling edge
        if (SAMsFiring==1 && MessageCount>SAMFireTime)
        {
            PORTA=PORTA & SAMorLED;
            PORTC=PORTC & SAMorLED;
            SAMsFiring=0;
            MessageCount=0;
            SAMsNeedFiring=0;
//            BitChangedFiring=0;
            LED_SetLow();
        }
    }
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/

