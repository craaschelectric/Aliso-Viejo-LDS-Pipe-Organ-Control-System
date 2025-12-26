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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F46K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB 	          :  MPLAB X 5.40	
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

// get/set PIPE01 aliases
#define PIPE01_TRIS                 TRISAbits.TRISA0
#define PIPE01_LAT                  LATAbits.LATA0
#define PIPE01_PORT                 PORTAbits.RA0
#define PIPE01_WPU                  WPUAbits.WPUA0
#define PIPE01_OD                   ODCONAbits.ODCA0
#define PIPE01_ANS                  ANSELAbits.ANSELA0
#define PIPE01_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define PIPE01_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define PIPE01_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define PIPE01_GetValue()           PORTAbits.RA0
#define PIPE01_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define PIPE01_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define PIPE01_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define PIPE01_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define PIPE01_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define PIPE01_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define PIPE01_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define PIPE01_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set PIPE02 aliases
#define PIPE02_TRIS                 TRISAbits.TRISA1
#define PIPE02_LAT                  LATAbits.LATA1
#define PIPE02_PORT                 PORTAbits.RA1
#define PIPE02_WPU                  WPUAbits.WPUA1
#define PIPE02_OD                   ODCONAbits.ODCA1
#define PIPE02_ANS                  ANSELAbits.ANSELA1
#define PIPE02_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define PIPE02_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define PIPE02_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define PIPE02_GetValue()           PORTAbits.RA1
#define PIPE02_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define PIPE02_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define PIPE02_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define PIPE02_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define PIPE02_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define PIPE02_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define PIPE02_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define PIPE02_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set PIPE03 aliases
#define PIPE03_TRIS                 TRISAbits.TRISA2
#define PIPE03_LAT                  LATAbits.LATA2
#define PIPE03_PORT                 PORTAbits.RA2
#define PIPE03_WPU                  WPUAbits.WPUA2
#define PIPE03_OD                   ODCONAbits.ODCA2
#define PIPE03_ANS                  ANSELAbits.ANSELA2
#define PIPE03_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define PIPE03_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define PIPE03_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define PIPE03_GetValue()           PORTAbits.RA2
#define PIPE03_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define PIPE03_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define PIPE03_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define PIPE03_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define PIPE03_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define PIPE03_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define PIPE03_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define PIPE03_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set PIPE04 aliases
#define PIPE04_TRIS                 TRISAbits.TRISA3
#define PIPE04_LAT                  LATAbits.LATA3
#define PIPE04_PORT                 PORTAbits.RA3
#define PIPE04_WPU                  WPUAbits.WPUA3
#define PIPE04_OD                   ODCONAbits.ODCA3
#define PIPE04_ANS                  ANSELAbits.ANSELA3
#define PIPE04_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define PIPE04_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define PIPE04_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define PIPE04_GetValue()           PORTAbits.RA3
#define PIPE04_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define PIPE04_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define PIPE04_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define PIPE04_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define PIPE04_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define PIPE04_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define PIPE04_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define PIPE04_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set PIPE05 aliases
#define PIPE05_TRIS                 TRISAbits.TRISA4
#define PIPE05_LAT                  LATAbits.LATA4
#define PIPE05_PORT                 PORTAbits.RA4
#define PIPE05_WPU                  WPUAbits.WPUA4
#define PIPE05_OD                   ODCONAbits.ODCA4
#define PIPE05_ANS                  ANSELAbits.ANSELA4
#define PIPE05_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define PIPE05_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define PIPE05_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define PIPE05_GetValue()           PORTAbits.RA4
#define PIPE05_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define PIPE05_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define PIPE05_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define PIPE05_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define PIPE05_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define PIPE05_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define PIPE05_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define PIPE05_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set PIPE06 aliases
#define PIPE06_TRIS                 TRISAbits.TRISA5
#define PIPE06_LAT                  LATAbits.LATA5
#define PIPE06_PORT                 PORTAbits.RA5
#define PIPE06_WPU                  WPUAbits.WPUA5
#define PIPE06_OD                   ODCONAbits.ODCA5
#define PIPE06_ANS                  ANSELAbits.ANSELA5
#define PIPE06_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define PIPE06_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define PIPE06_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define PIPE06_GetValue()           PORTAbits.RA5
#define PIPE06_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define PIPE06_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define PIPE06_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define PIPE06_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define PIPE06_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define PIPE06_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define PIPE06_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define PIPE06_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set PIPE07 aliases
#define PIPE07_TRIS                 TRISAbits.TRISA6
#define PIPE07_LAT                  LATAbits.LATA6
#define PIPE07_PORT                 PORTAbits.RA6
#define PIPE07_WPU                  WPUAbits.WPUA6
#define PIPE07_OD                   ODCONAbits.ODCA6
#define PIPE07_ANS                  ANSELAbits.ANSELA6
#define PIPE07_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define PIPE07_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define PIPE07_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define PIPE07_GetValue()           PORTAbits.RA6
#define PIPE07_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define PIPE07_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define PIPE07_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define PIPE07_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define PIPE07_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define PIPE07_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define PIPE07_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define PIPE07_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set PIPE08 aliases
#define PIPE08_TRIS                 TRISAbits.TRISA7
#define PIPE08_LAT                  LATAbits.LATA7
#define PIPE08_PORT                 PORTAbits.RA7
#define PIPE08_WPU                  WPUAbits.WPUA7
#define PIPE08_OD                   ODCONAbits.ODCA7
#define PIPE08_ANS                  ANSELAbits.ANSELA7
#define PIPE08_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define PIPE08_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define PIPE08_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define PIPE08_GetValue()           PORTAbits.RA7
#define PIPE08_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define PIPE08_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define PIPE08_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define PIPE08_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define PIPE08_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define PIPE08_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define PIPE08_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define PIPE08_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set PIPE09 aliases
#define PIPE09_TRIS                 TRISBbits.TRISB0
#define PIPE09_LAT                  LATBbits.LATB0
#define PIPE09_PORT                 PORTBbits.RB0
#define PIPE09_WPU                  WPUBbits.WPUB0
#define PIPE09_OD                   ODCONBbits.ODCB0
#define PIPE09_ANS                  ANSELBbits.ANSELB0
#define PIPE09_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define PIPE09_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define PIPE09_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define PIPE09_GetValue()           PORTBbits.RB0
#define PIPE09_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define PIPE09_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define PIPE09_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define PIPE09_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define PIPE09_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define PIPE09_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define PIPE09_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define PIPE09_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set PIPE10 aliases
#define PIPE10_TRIS                 TRISBbits.TRISB1
#define PIPE10_LAT                  LATBbits.LATB1
#define PIPE10_PORT                 PORTBbits.RB1
#define PIPE10_WPU                  WPUBbits.WPUB1
#define PIPE10_OD                   ODCONBbits.ODCB1
#define PIPE10_ANS                  ANSELBbits.ANSELB1
#define PIPE10_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define PIPE10_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define PIPE10_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define PIPE10_GetValue()           PORTBbits.RB1
#define PIPE10_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define PIPE10_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define PIPE10_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define PIPE10_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define PIPE10_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define PIPE10_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define PIPE10_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define PIPE10_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set PIPE11 aliases
#define PIPE11_TRIS                 TRISBbits.TRISB2
#define PIPE11_LAT                  LATBbits.LATB2
#define PIPE11_PORT                 PORTBbits.RB2
#define PIPE11_WPU                  WPUBbits.WPUB2
#define PIPE11_OD                   ODCONBbits.ODCB2
#define PIPE11_ANS                  ANSELBbits.ANSELB2
#define PIPE11_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define PIPE11_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define PIPE11_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define PIPE11_GetValue()           PORTBbits.RB2
#define PIPE11_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define PIPE11_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define PIPE11_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define PIPE11_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define PIPE11_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define PIPE11_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define PIPE11_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define PIPE11_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set PIPE12 aliases
#define PIPE12_TRIS                 TRISBbits.TRISB3
#define PIPE12_LAT                  LATBbits.LATB3
#define PIPE12_PORT                 PORTBbits.RB3
#define PIPE12_WPU                  WPUBbits.WPUB3
#define PIPE12_OD                   ODCONBbits.ODCB3
#define PIPE12_ANS                  ANSELBbits.ANSELB3
#define PIPE12_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define PIPE12_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define PIPE12_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define PIPE12_GetValue()           PORTBbits.RB3
#define PIPE12_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define PIPE12_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define PIPE12_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define PIPE12_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define PIPE12_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define PIPE12_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define PIPE12_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define PIPE12_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSELB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set PIPE13 aliases
#define PIPE13_TRIS                 TRISCbits.TRISC0
#define PIPE13_LAT                  LATCbits.LATC0
#define PIPE13_PORT                 PORTCbits.RC0
#define PIPE13_WPU                  WPUCbits.WPUC0
#define PIPE13_OD                   ODCONCbits.ODCC0
#define PIPE13_ANS                  ANSELCbits.ANSELC0
#define PIPE13_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define PIPE13_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define PIPE13_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define PIPE13_GetValue()           PORTCbits.RC0
#define PIPE13_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define PIPE13_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define PIPE13_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define PIPE13_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define PIPE13_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define PIPE13_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define PIPE13_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define PIPE13_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set PIPE14 aliases
#define PIPE14_TRIS                 TRISCbits.TRISC1
#define PIPE14_LAT                  LATCbits.LATC1
#define PIPE14_PORT                 PORTCbits.RC1
#define PIPE14_WPU                  WPUCbits.WPUC1
#define PIPE14_OD                   ODCONCbits.ODCC1
#define PIPE14_ANS                  ANSELCbits.ANSELC1
#define PIPE14_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define PIPE14_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define PIPE14_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define PIPE14_GetValue()           PORTCbits.RC1
#define PIPE14_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define PIPE14_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define PIPE14_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define PIPE14_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define PIPE14_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define PIPE14_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define PIPE14_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define PIPE14_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set PIPE15 aliases
#define PIPE15_TRIS                 TRISCbits.TRISC2
#define PIPE15_LAT                  LATCbits.LATC2
#define PIPE15_PORT                 PORTCbits.RC2
#define PIPE15_WPU                  WPUCbits.WPUC2
#define PIPE15_OD                   ODCONCbits.ODCC2
#define PIPE15_ANS                  ANSELCbits.ANSELC2
#define PIPE15_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define PIPE15_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define PIPE15_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define PIPE15_GetValue()           PORTCbits.RC2
#define PIPE15_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define PIPE15_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define PIPE15_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define PIPE15_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define PIPE15_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define PIPE15_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define PIPE15_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define PIPE15_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set PIPE16 aliases
#define PIPE16_TRIS                 TRISCbits.TRISC3
#define PIPE16_LAT                  LATCbits.LATC3
#define PIPE16_PORT                 PORTCbits.RC3
#define PIPE16_WPU                  WPUCbits.WPUC3
#define PIPE16_OD                   ODCONCbits.ODCC3
#define PIPE16_ANS                  ANSELCbits.ANSELC3
#define PIPE16_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define PIPE16_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define PIPE16_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define PIPE16_GetValue()           PORTCbits.RC3
#define PIPE16_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define PIPE16_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define PIPE16_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define PIPE16_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define PIPE16_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define PIPE16_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define PIPE16_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define PIPE16_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set PIPE17 aliases
#define PIPE17_TRIS                 TRISDbits.TRISD0
#define PIPE17_LAT                  LATDbits.LATD0
#define PIPE17_PORT                 PORTDbits.RD0
#define PIPE17_WPU                  WPUDbits.WPUD0
#define PIPE17_OD                   ODCONDbits.ODCD0
#define PIPE17_ANS                  ANSELDbits.ANSELD0
#define PIPE17_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define PIPE17_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define PIPE17_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define PIPE17_GetValue()           PORTDbits.RD0
#define PIPE17_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define PIPE17_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define PIPE17_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define PIPE17_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define PIPE17_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define PIPE17_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define PIPE17_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define PIPE17_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set PIPE18 aliases
#define PIPE18_TRIS                 TRISDbits.TRISD1
#define PIPE18_LAT                  LATDbits.LATD1
#define PIPE18_PORT                 PORTDbits.RD1
#define PIPE18_WPU                  WPUDbits.WPUD1
#define PIPE18_OD                   ODCONDbits.ODCD1
#define PIPE18_ANS                  ANSELDbits.ANSELD1
#define PIPE18_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define PIPE18_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define PIPE18_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define PIPE18_GetValue()           PORTDbits.RD1
#define PIPE18_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define PIPE18_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define PIPE18_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define PIPE18_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define PIPE18_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define PIPE18_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define PIPE18_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define PIPE18_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set PIPE19 aliases
#define PIPE19_TRIS                 TRISDbits.TRISD2
#define PIPE19_LAT                  LATDbits.LATD2
#define PIPE19_PORT                 PORTDbits.RD2
#define PIPE19_WPU                  WPUDbits.WPUD2
#define PIPE19_OD                   ODCONDbits.ODCD2
#define PIPE19_ANS                  ANSELDbits.ANSELD2
#define PIPE19_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define PIPE19_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define PIPE19_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define PIPE19_GetValue()           PORTDbits.RD2
#define PIPE19_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define PIPE19_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define PIPE19_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define PIPE19_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define PIPE19_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define PIPE19_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define PIPE19_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define PIPE19_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set PIPE20 aliases
#define PIPE20_TRIS                 TRISDbits.TRISD3
#define PIPE20_LAT                  LATDbits.LATD3
#define PIPE20_PORT                 PORTDbits.RD3
#define PIPE20_WPU                  WPUDbits.WPUD3
#define PIPE20_OD                   ODCONDbits.ODCD3
#define PIPE20_ANS                  ANSELDbits.ANSELD3
#define PIPE20_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define PIPE20_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define PIPE20_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define PIPE20_GetValue()           PORTDbits.RD3
#define PIPE20_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define PIPE20_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define PIPE20_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define PIPE20_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define PIPE20_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define PIPE20_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define PIPE20_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define PIPE20_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set PIPE21 aliases
#define PIPE21_TRIS                 TRISDbits.TRISD4
#define PIPE21_LAT                  LATDbits.LATD4
#define PIPE21_PORT                 PORTDbits.RD4
#define PIPE21_WPU                  WPUDbits.WPUD4
#define PIPE21_OD                   ODCONDbits.ODCD4
#define PIPE21_ANS                  ANSELDbits.ANSELD4
#define PIPE21_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define PIPE21_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define PIPE21_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define PIPE21_GetValue()           PORTDbits.RD4
#define PIPE21_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define PIPE21_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define PIPE21_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define PIPE21_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define PIPE21_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define PIPE21_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define PIPE21_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define PIPE21_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set PIPE22 aliases
#define PIPE22_TRIS                 TRISDbits.TRISD5
#define PIPE22_LAT                  LATDbits.LATD5
#define PIPE22_PORT                 PORTDbits.RD5
#define PIPE22_WPU                  WPUDbits.WPUD5
#define PIPE22_OD                   ODCONDbits.ODCD5
#define PIPE22_ANS                  ANSELDbits.ANSELD5
#define PIPE22_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define PIPE22_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define PIPE22_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define PIPE22_GetValue()           PORTDbits.RD5
#define PIPE22_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define PIPE22_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define PIPE22_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define PIPE22_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define PIPE22_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define PIPE22_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define PIPE22_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define PIPE22_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set PIPE23 aliases
#define PIPE23_TRIS                 TRISDbits.TRISD6
#define PIPE23_LAT                  LATDbits.LATD6
#define PIPE23_PORT                 PORTDbits.RD6
#define PIPE23_WPU                  WPUDbits.WPUD6
#define PIPE23_OD                   ODCONDbits.ODCD6
#define PIPE23_ANS                  ANSELDbits.ANSELD6
#define PIPE23_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define PIPE23_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define PIPE23_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define PIPE23_GetValue()           PORTDbits.RD6
#define PIPE23_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define PIPE23_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define PIPE23_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define PIPE23_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define PIPE23_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define PIPE23_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define PIPE23_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define PIPE23_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set PIPE24 aliases
#define PIPE24_TRIS                 TRISDbits.TRISD7
#define PIPE24_LAT                  LATDbits.LATD7
#define PIPE24_PORT                 PORTDbits.RD7
#define PIPE24_WPU                  WPUDbits.WPUD7
#define PIPE24_OD                   ODCONDbits.ODCD7
#define PIPE24_ANS                  ANSELDbits.ANSELD7
#define PIPE24_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define PIPE24_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define PIPE24_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define PIPE24_GetValue()           PORTDbits.RD7
#define PIPE24_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define PIPE24_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define PIPE24_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define PIPE24_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define PIPE24_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define PIPE24_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define PIPE24_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define PIPE24_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set LEDOUT aliases
#define LEDOUT_TRIS                 TRISEbits.TRISE0
#define LEDOUT_LAT                  LATEbits.LATE0
#define LEDOUT_PORT                 PORTEbits.RE0
#define LEDOUT_WPU                  WPUEbits.WPUE0
#define LEDOUT_OD                   ODCONEbits.ODCE0
#define LEDOUT_ANS                  ANSELEbits.ANSELE0
#define LEDOUT_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LEDOUT_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LEDOUT_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LEDOUT_GetValue()           PORTEbits.RE0
#define LEDOUT_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LEDOUT_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LEDOUT_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LEDOUT_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LEDOUT_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LEDOUT_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LEDOUT_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LEDOUT_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set PIPE25 aliases
#define PIPE25_TRIS                 TRISEbits.TRISE2
#define PIPE25_LAT                  LATEbits.LATE2
#define PIPE25_PORT                 PORTEbits.RE2
#define PIPE25_WPU                  WPUEbits.WPUE2
#define PIPE25_OD                   ODCONEbits.ODCE2
#define PIPE25_ANS                  ANSELEbits.ANSELE2
#define PIPE25_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define PIPE25_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define PIPE25_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define PIPE25_GetValue()           PORTEbits.RE2
#define PIPE25_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define PIPE25_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define PIPE25_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define PIPE25_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define PIPE25_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define PIPE25_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define PIPE25_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define PIPE25_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

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