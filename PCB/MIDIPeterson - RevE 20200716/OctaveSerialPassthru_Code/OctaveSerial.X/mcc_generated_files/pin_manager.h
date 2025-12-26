/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18344
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set Pin2 aliases
#define Pin2_TRIS                 TRISAbits.TRISA2
#define Pin2_LAT                  LATAbits.LATA2
#define Pin2_PORT                 PORTAbits.RA2
#define Pin2_WPU                  WPUAbits.WPUA2
#define Pin2_OD                   ODCONAbits.ODCA2
#define Pin2_ANS                  ANSELAbits.ANSA2
#define Pin2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Pin2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Pin2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Pin2_GetValue()           PORTAbits.RA2
#define Pin2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Pin2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Pin2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define Pin2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define Pin2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define Pin2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define Pin2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Pin2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set Pin1 aliases
#define Pin1_TRIS                 TRISAbits.TRISA4
#define Pin1_LAT                  LATAbits.LATA4
#define Pin1_PORT                 PORTAbits.RA4
#define Pin1_WPU                  WPUAbits.WPUA4
#define Pin1_OD                   ODCONAbits.ODCA4
#define Pin1_ANS                  ANSELAbits.ANSA4
#define Pin1_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Pin1_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Pin1_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Pin1_GetValue()           PORTAbits.RA4
#define Pin1_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Pin1_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define Pin1_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define Pin1_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define Pin1_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define Pin1_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define Pin1_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define Pin1_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set Pin0 aliases
#define Pin0_TRIS                 TRISAbits.TRISA5
#define Pin0_LAT                  LATAbits.LATA5
#define Pin0_PORT                 PORTAbits.RA5
#define Pin0_WPU                  WPUAbits.WPUA5
#define Pin0_OD                   ODCONAbits.ODCA5
#define Pin0_ANS                  ANSELAbits.ANSA5
#define Pin0_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define Pin0_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define Pin0_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define Pin0_GetValue()           PORTAbits.RA5
#define Pin0_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define Pin0_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define Pin0_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define Pin0_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define Pin0_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define Pin0_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define Pin0_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define Pin0_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set Pin10 aliases
#define Pin10_TRIS                 TRISBbits.TRISB4
#define Pin10_LAT                  LATBbits.LATB4
#define Pin10_PORT                 PORTBbits.RB4
#define Pin10_WPU                  WPUBbits.WPUB4
#define Pin10_OD                   ODCONBbits.ODCB4
#define Pin10_ANS                  ANSELBbits.ANSB4
#define Pin10_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define Pin10_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define Pin10_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define Pin10_GetValue()           PORTBbits.RB4
#define Pin10_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define Pin10_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define Pin10_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define Pin10_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define Pin10_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define Pin10_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define Pin10_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define Pin10_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set Pin12 aliases
#define Pin12_TRIS                 TRISBbits.TRISB6
#define Pin12_LAT                  LATBbits.LATB6
#define Pin12_PORT                 PORTBbits.RB6
#define Pin12_WPU                  WPUBbits.WPUB6
#define Pin12_OD                   ODCONBbits.ODCB6
#define Pin12_ANS                  ANSELBbits.ANSB6
#define Pin12_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define Pin12_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define Pin12_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define Pin12_GetValue()           PORTBbits.RB6
#define Pin12_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define Pin12_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define Pin12_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define Pin12_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define Pin12_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define Pin12_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define Pin12_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define Pin12_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set Pin4 aliases
#define Pin4_TRIS                 TRISCbits.TRISC0
#define Pin4_LAT                  LATCbits.LATC0
#define Pin4_PORT                 PORTCbits.RC0
#define Pin4_WPU                  WPUCbits.WPUC0
#define Pin4_OD                   ODCONCbits.ODCC0
#define Pin4_ANS                  ANSELCbits.ANSC0
#define Pin4_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Pin4_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Pin4_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Pin4_GetValue()           PORTCbits.RC0
#define Pin4_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Pin4_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define Pin4_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define Pin4_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define Pin4_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define Pin4_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define Pin4_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define Pin4_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set Pin6 aliases
#define Pin6_TRIS                 TRISCbits.TRISC1
#define Pin6_LAT                  LATCbits.LATC1
#define Pin6_PORT                 PORTCbits.RC1
#define Pin6_WPU                  WPUCbits.WPUC1
#define Pin6_OD                   ODCONCbits.ODCC1
#define Pin6_ANS                  ANSELCbits.ANSC1
#define Pin6_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Pin6_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Pin6_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Pin6_GetValue()           PORTCbits.RC1
#define Pin6_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Pin6_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Pin6_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Pin6_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Pin6_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define Pin6_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define Pin6_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define Pin6_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set Pin8 aliases
#define Pin8_TRIS                 TRISCbits.TRISC2
#define Pin8_LAT                  LATCbits.LATC2
#define Pin8_PORT                 PORTCbits.RC2
#define Pin8_WPU                  WPUCbits.WPUC2
#define Pin8_OD                   ODCONCbits.ODCC2
#define Pin8_ANS                  ANSELCbits.ANSC2
#define Pin8_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define Pin8_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define Pin8_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define Pin8_GetValue()           PORTCbits.RC2
#define Pin8_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define Pin8_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define Pin8_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define Pin8_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define Pin8_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define Pin8_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define Pin8_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define Pin8_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set Pin7 aliases
#define Pin7_TRIS                 TRISCbits.TRISC3
#define Pin7_LAT                  LATCbits.LATC3
#define Pin7_PORT                 PORTCbits.RC3
#define Pin7_WPU                  WPUCbits.WPUC3
#define Pin7_OD                   ODCONCbits.ODCC3
#define Pin7_ANS                  ANSELCbits.ANSC3
#define Pin7_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define Pin7_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define Pin7_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define Pin7_GetValue()           PORTCbits.RC3
#define Pin7_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define Pin7_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define Pin7_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define Pin7_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define Pin7_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define Pin7_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define Pin7_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define Pin7_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set Pin5 aliases
#define Pin5_TRIS                 TRISCbits.TRISC4
#define Pin5_LAT                  LATCbits.LATC4
#define Pin5_PORT                 PORTCbits.RC4
#define Pin5_WPU                  WPUCbits.WPUC4
#define Pin5_OD                   ODCONCbits.ODCC4
#define Pin5_ANS                  ANSELCbits.ANSC4
#define Pin5_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define Pin5_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define Pin5_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define Pin5_GetValue()           PORTCbits.RC4
#define Pin5_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define Pin5_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define Pin5_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define Pin5_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define Pin5_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define Pin5_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define Pin5_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define Pin5_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set Pin3 aliases
#define Pin3_TRIS                 TRISCbits.TRISC5
#define Pin3_LAT                  LATCbits.LATC5
#define Pin3_PORT                 PORTCbits.RC5
#define Pin3_WPU                  WPUCbits.WPUC5
#define Pin3_OD                   ODCONCbits.ODCC5
#define Pin3_ANS                  ANSELCbits.ANSC5
#define Pin3_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define Pin3_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define Pin3_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define Pin3_GetValue()           PORTCbits.RC5
#define Pin3_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define Pin3_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define Pin3_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define Pin3_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define Pin3_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define Pin3_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define Pin3_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define Pin3_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set Pin9 aliases
#define Pin9_TRIS                 TRISCbits.TRISC6
#define Pin9_LAT                  LATCbits.LATC6
#define Pin9_PORT                 PORTCbits.RC6
#define Pin9_WPU                  WPUCbits.WPUC6
#define Pin9_OD                   ODCONCbits.ODCC6
#define Pin9_ANS                  ANSELCbits.ANSC6
#define Pin9_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define Pin9_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define Pin9_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define Pin9_GetValue()           PORTCbits.RC6
#define Pin9_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define Pin9_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define Pin9_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define Pin9_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define Pin9_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define Pin9_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define Pin9_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define Pin9_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set Pin11 aliases
#define Pin11_TRIS                 TRISCbits.TRISC7
#define Pin11_LAT                  LATCbits.LATC7
#define Pin11_PORT                 PORTCbits.RC7
#define Pin11_WPU                  WPUCbits.WPUC7
#define Pin11_OD                   ODCONCbits.ODCC7
#define Pin11_ANS                  ANSELCbits.ANSC7
#define Pin11_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define Pin11_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define Pin11_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define Pin11_GetValue()           PORTCbits.RC7
#define Pin11_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define Pin11_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define Pin11_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define Pin11_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define Pin11_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define Pin11_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define Pin11_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define Pin11_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/