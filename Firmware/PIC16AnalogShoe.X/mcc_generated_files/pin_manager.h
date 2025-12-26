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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15325
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

// get/set RA0 procedures
#define RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RA0_GetValue()              PORTAbits.RA0
#define RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RA0_SetPullup()             do { WPUAbits.WPUA0 = 1; } while(0)
#define RA0_ResetPullup()           do { WPUAbits.WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()         do { ANSELAbits.ANSA0 = 1; } while(0)
#define RA0_SetDigitalMode()        do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set Stage7 aliases
#define Stage7_TRIS                 TRISAbits.TRISA4
#define Stage7_LAT                  LATAbits.LATA4
#define Stage7_PORT                 PORTAbits.RA4
#define Stage7_WPU                  WPUAbits.WPUA4
#define Stage7_OD                   ODCONAbits.ODCA4
#define Stage7_ANS                  ANSELAbits.ANSA4
#define Stage7_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Stage7_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Stage7_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Stage7_GetValue()           PORTAbits.RA4
#define Stage7_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Stage7_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define Stage7_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define Stage7_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define Stage7_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define Stage7_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define Stage7_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define Stage7_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set Stage6 aliases
#define Stage6_TRIS                 TRISAbits.TRISA5
#define Stage6_LAT                  LATAbits.LATA5
#define Stage6_PORT                 PORTAbits.RA5
#define Stage6_WPU                  WPUAbits.WPUA5
#define Stage6_OD                   ODCONAbits.ODCA5
#define Stage6_ANS                  ANSELAbits.ANSA5
#define Stage6_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define Stage6_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define Stage6_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define Stage6_GetValue()           PORTAbits.RA5
#define Stage6_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define Stage6_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define Stage6_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define Stage6_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define Stage6_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define Stage6_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define Stage6_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define Stage6_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set Stage0 aliases
#define Stage0_TRIS                 TRISCbits.TRISC0
#define Stage0_LAT                  LATCbits.LATC0
#define Stage0_PORT                 PORTCbits.RC0
#define Stage0_WPU                  WPUCbits.WPUC0
#define Stage0_OD                   ODCONCbits.ODCC0
#define Stage0_ANS                  ANSELCbits.ANSC0
#define Stage0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Stage0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Stage0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Stage0_GetValue()           PORTCbits.RC0
#define Stage0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Stage0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define Stage0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define Stage0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define Stage0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define Stage0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define Stage0_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define Stage0_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set Stage1 aliases
#define Stage1_TRIS                 TRISCbits.TRISC1
#define Stage1_LAT                  LATCbits.LATC1
#define Stage1_PORT                 PORTCbits.RC1
#define Stage1_WPU                  WPUCbits.WPUC1
#define Stage1_OD                   ODCONCbits.ODCC1
#define Stage1_ANS                  ANSELCbits.ANSC1
#define Stage1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Stage1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Stage1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Stage1_GetValue()           PORTCbits.RC1
#define Stage1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Stage1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Stage1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Stage1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Stage1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define Stage1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define Stage1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define Stage1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set Stage2 aliases
#define Stage2_TRIS                 TRISCbits.TRISC2
#define Stage2_LAT                  LATCbits.LATC2
#define Stage2_PORT                 PORTCbits.RC2
#define Stage2_WPU                  WPUCbits.WPUC2
#define Stage2_OD                   ODCONCbits.ODCC2
#define Stage2_ANS                  ANSELCbits.ANSC2
#define Stage2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define Stage2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define Stage2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define Stage2_GetValue()           PORTCbits.RC2
#define Stage2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define Stage2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define Stage2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define Stage2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define Stage2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define Stage2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define Stage2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define Stage2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set Stage3 aliases
#define Stage3_TRIS                 TRISCbits.TRISC3
#define Stage3_LAT                  LATCbits.LATC3
#define Stage3_PORT                 PORTCbits.RC3
#define Stage3_WPU                  WPUCbits.WPUC3
#define Stage3_OD                   ODCONCbits.ODCC3
#define Stage3_ANS                  ANSELCbits.ANSC3
#define Stage3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define Stage3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define Stage3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define Stage3_GetValue()           PORTCbits.RC3
#define Stage3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define Stage3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define Stage3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define Stage3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define Stage3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define Stage3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define Stage3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define Stage3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set Stage4 aliases
#define Stage4_TRIS                 TRISCbits.TRISC4
#define Stage4_LAT                  LATCbits.LATC4
#define Stage4_PORT                 PORTCbits.RC4
#define Stage4_WPU                  WPUCbits.WPUC4
#define Stage4_OD                   ODCONCbits.ODCC4
#define Stage4_ANS                  ANSELCbits.ANSC4
#define Stage4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define Stage4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define Stage4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define Stage4_GetValue()           PORTCbits.RC4
#define Stage4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define Stage4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define Stage4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define Stage4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define Stage4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define Stage4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define Stage4_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define Stage4_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set Stage5 aliases
#define Stage5_TRIS                 TRISCbits.TRISC5
#define Stage5_LAT                  LATCbits.LATC5
#define Stage5_PORT                 PORTCbits.RC5
#define Stage5_WPU                  WPUCbits.WPUC5
#define Stage5_OD                   ODCONCbits.ODCC5
#define Stage5_ANS                  ANSELCbits.ANSC5
#define Stage5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define Stage5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define Stage5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define Stage5_GetValue()           PORTCbits.RC5
#define Stage5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define Stage5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define Stage5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define Stage5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define Stage5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define Stage5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define Stage5_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define Stage5_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

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