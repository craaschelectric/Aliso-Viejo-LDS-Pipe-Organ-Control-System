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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F15375
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

extern uint8_t BaseAddress;
extern uint8_t CurrentSAMState;
extern uint8_t ClockCount;
extern int CurrentStateSync;
extern int CurrentStateCLK;
extern uint16_t NewSAMState;
extern uint16_t PrevSAMState;
extern uint8_t FireOffSAMs;
extern uint8_t FireOnSAMs;
//uint8_t BitChangedFiring=0;
extern int i;
extern uint8_t mask;
extern uint16_t temp;
extern int SAMsFiring;
extern int SAMsNeedFiring;
extern uint8_t MessageCount;
extern uint8_t SAMorLED;
extern uint8_t SAMFireTime;
extern uint8_t BaseAddressMask;

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    PORTA=0;
    PORTC=0;
    NewSAMState=0;
    
/*    //test
    for (i=0;i<=2;i++){
        PORTA=0xFF;
        LED_SetHigh();
        __delay_ms(50);
        PORTA=0;
        LED_SetLow();

        __delay_ms(300);
        PORTC=0xFF;
        LED_SetHigh();
        __delay_ms(50);
        PORTC=0;
        LED_SetLow();
        
        __delay_ms(600);
        
        
        
    }
*/
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        if(CurrentStateSync==0&&SYNC_PORT==1) //sync rising edge
        {
            PERIPHOUT_SetDigitalInput(); //if it's not mine, better not drive the bus.
            ClockCount=-1;
            MessageCount++;
            CurrentStateSync=1;
            if(NewSAMState^PrevSAMState>0 && SAMFireTime>10){
            
                    PORTA=(uint8_t) NewSAMState&0xFF;
                    PORTC=(uint8_t) NewSAMState>>8;
                    LED_SetHigh();
                    PrevSAMState=NewSAMState;
                    SAMFireTime=0;
            }
            if(SAMFireTime<=10) SAMFireTime++;

        }//sync rising edge
        if (SYNC_PORT==0) CurrentStateSync=0;        // Add your application code
    }
}
/**
 End of File
*/