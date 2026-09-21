/*******************************************************************************
  Input / Output Port COnfiguration Routine source File

  File Name:
    port_config.c

  Summary:
    This file includes subroutine for initializing GPIO pins as analog/digital,
    input or output etc. Also to PPS functionality to Remap-able input or output 
    pins

  Description:
    Definitions in the file are for dsPIC33CDV(L)256MC506 Motor Control 
    Development board from Microchip
 
*******************************************************************************/
/*******************************************************************************
* Copyright (c) 2026 released Microchip Technology Inc.  All rights reserved.
*
* SOFTWARE LICENSE AGREEMENT:
* 
© [2026] Microchip Technology Inc. and its subsidiaries.
 
    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS "AS IS." 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <xc.h>
#include "port_config.h"
#include "userparms.h"

static void configureGateDriverFault(void);
// *****************************************************************************
/* Function:
    SetupGPIOPorts()

  Summary:
    Routine to set-up GPIO ports

  Description:
    Function initializes GPIO pins for input or output ports,analog/digital pins,
    remap the peripheral functions to desires RPx pins.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */

void SetupGPIOPorts(void)
{
    // Reset all PORTx register (all inputs)
    #ifdef TRISA
        TRISA = 0xFFFF;
        LATA  = 0x0000;
    #endif
    #ifdef ANSELA
        ANSELA = 0x0000;
    #endif

    #ifdef TRISB
        TRISB = 0xFFFF;
        LATB  = 0x0000;
    #endif
    #ifdef ANSELB
        ANSELB = 0x0000;
    #endif

    #ifdef TRISC
        TRISC = 0xFFFF;
        LATC  = 0x0000;
    #endif
    #ifdef ANSELC
        ANSELC = 0x0000;
    #endif

    #ifdef TRISD
        TRISD = 0xFFFF;
        LATD  = 0x0000;
    #endif
    #ifdef ANSELD
        ANSELD = 0x0000;
    #endif

    #ifdef TRISE
        TRISE = 0xFFFF;
        LATE  = 0x0000;
    #endif
    #ifdef ANSELE
        ANSELE = 0x0000;
    #endif

    MapGPIOHWFunction();

    return;
}
// *****************************************************************************
/* Function:
    Map_GPIO_HW_Function()

  Summary:
    Routine to setup GPIO pin used as input/output analog/digital etc

  Description:
    Function initializes GPIO pins as input or output port pins,analog/digital 
    pins,remap the peripheral functions to desires RPx pins.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */

void MapGPIOHWFunction(void)
{
    
    /* ANALOG SIGNALS */

    // Configure Port pins for Motor Current Sensing
    
#ifdef INTERNAL_OPAMP_CONFIG
    
    /** IA connected to OA1 **/
    /* IA- : Pin #16 - OA1IN-/AN16/RA1 */
    ANSELAbits.ANSELA1 = 1;
    TRISAbits.TRISA1 = 1;
  
    /* IA+ : Pin #17 - OA1IN+/AN9/RA2 */
    ANSELAbits.ANSELA2 = 1;
    TRISAbits.TRISA2 = 1;

    /* IA out : Pin #15 - OA1IN+/AN9/RA2 */
    ANSELAbits.ANSELA0 = 1;
    TRISAbits.TRISA0 = 0;
    
    /** IBUS connected to OA2 **/
    /* IBUS- : Pin #33 - PGD2/OA2IN-/AN8/RP35/RB3 */
    ANSELBbits.ANSELB3 = 1;
    TRISBbits.TRISB3 = 1;
    
    /* IBUS+ : Pin #34 - PGC2/OA2IN+/AN17/RP36/RB4 */ 
    ANSELBbits.ANSELB4 = 1;
    TRISBbits.TRISB4 = 1;

    /* IBUS out : Pin #32 - OA2OUT/AN1/CMP1D/CMP2D/RP34/INT0/RB2 */
    ANSELBbits.ANSELB2 = 1;
    TRISBbits.TRISB2 = 0;
    
    /** IB connected to OA3 **/
    /* IB- : Pin #22 - OA3IN-/AN13/CMP1B/ISRC0/RP49/RC1 */
    ANSELCbits.ANSELC1 = 1;
    TRISCbits.TRISC1 = 1;
    
    /* IB+ : Pin #23 - OA3IN+/AN14/ISRC1/RP50/RC2 */ 
    ANSELCbits.ANSELC2 = 1;
    TRISCbits.TRISC2 = 1;
    
    /* IB out : Pin #19 - OA3OUT/AN4/IBIAS3/RA4 */
    ANSELAbits.ANSELA4 = 1;
    TRISAbits.TRISA4 = 0;
    
    //Op-Amp Configuration
    AMPCON1Hbits.NCHDIS1 = 0;    //Wide input range for Op Amp #1
    AMPCON1Lbits.AMPEN1 = 1;     //Enables Op Amp #1
    
    AMPCON1Hbits.NCHDIS2 = 0;    //Wide input range for Op Amp #2
    AMPCON1Lbits.AMPEN2 = 1;     //Enables Op Amp #2
    
    AMPCON1Hbits.NCHDIS3 = 0;    //Wide input range for Op Amp #3
    AMPCON1Lbits.AMPEN3 = 1;     //Enables Op Amp #3
    
    AMPCON1Lbits.AMPON = 1;      //Enables op amp modules if their respective AMPENx bits are also asserted
 
#else
    /* IA out : Pin #15 - OA1IN+/AN9/RA2 */
    ANSELAbits.ANSELA0 = 1;
    TRISAbits.TRISA0 = 1;
    
    /* IBUS out : Pin #32 - OA2OUT/AN1/CMP1D/CMP2D/RP34/INT0/RB2 */
    ANSELBbits.ANSELB2 = 1;
    TRISBbits.TRISB2 = 1;
    
    /* IB out : Pin #19 - OA3OUT/AN4/IBIAS3/RA4 */
    ANSELAbits.ANSELA4 = 1;
    TRISAbits.TRISA4 = 1;
#endif
    
    /* Potentiometer input - used as Speed Reference */
    /* POT : Pin #27  AN15/CMP2A/IBIAS2/RP51/RC3*/
    ANSELCbits.ANSELC3 = 1;
    TRISCbits.TRISC3 = 1;  

    /* DC Bus Voltage Signal */
    /* VBUS : Pin #14 - AN12/RP48/RC0*/
    ANSELCbits.ANSELC0 = 1;
    TRISCbits.TRISC0 = 1;   

    /* Digital SIGNALS */   
    // DIGITAL INPUT/OUTPUT PINS

    /* Inverter Control - PWM Outputs - These pins are internally connected
     to the gate driver MCP8021
     * PWM1L : Pin #02  - RP47/PWM1L/RB15
     * PWM1H : Pin #01  - RP46/PWM1H/RB14
     * PWM2L : Pin #64  - RP45/PWM2L/RB13
     * PWM2H : Pin #63  - TDI/RP44/PWM2H/RB12
     * PWM3L : Pin #62  - TCK/RP43/PWM3L/RB11
     * PWM3H : Pin #61  - TMS/RP42/PWM3H/RB10     */
    TRISBbits.TRISB15 = 0 ;          
    TRISBbits.TRISB14 = 0 ;         
    TRISBbits.TRISB13 = 0 ;          
    TRISBbits.TRISB12 = 0 ;           
    TRISBbits.TRISB11 = 0 ;          
    TRISBbits.TRISB10 = 0 ;         
    
    /* Debug LEDs */
    /* LED1 : Pin #29 - OSCO/CLKO/AN6/RP33/RB1 */
    TRISBbits.TRISB1 = 0; 
    /* LED2 : Pin #24 - AN19/IBIAS1/RP54/RC6 */ 
    TRISCbits.TRISC6 = 0;           

    /* Push button Switches */
    /* SW1 : Pin #37 - RP72/SDO2/PCI19/RD8 */
    TRISDbits.TRISD8 = 1;           
    /* SW2 :  Pin #13 - ANN0/RP77/RD13 */
    TRISDbits.TRISD13 = 1; 
	
	/** Diagnostic Interface
        Re-map UART Channels to the device pins connected to the following 
        pins on the Motor Control Development Board.
        DEBUG_RX : Pin #30 -  AN18/ISRC3/RP74/RD10 (Input)
        DEBUG_TX : Pin #31 -  AN7/ISRC2/RP55/RC7 (Output)   */
    _U1RXR = 74;
    _RP55R = 0b000001;
    
    /* Gate Driver MCP8021 Pins 
       These pins are internally connected to the gate driver
       DE2 : Pin #3 - RP60/RC12  
       OE  : Pin #4 - RP61/RC13  
       Fault : Pin #59 - RP65/PWM4H/RD1 */
    /* Configuring DE2 Pin with UART2 */
     _U2RXR = 60;
     _RP60R = 3;
     _CNPUC12 = 1;
     /* Configuring OE pin */
    TRISCbits.TRISC13 = 0;
    /* Configuring Fault pin */
     configureGateDriverFault();
     
}
void configureGateDriverFault(void)
{
    uint16_t bufferPortD;
  
    TRISDbits.TRISD1 = 1;
   _CNPUD1 = 1;
   
    CNCOND = 0;
/*  ON: Change Notification (CN) Control for PORTx On bit
    1 = CN is enabled
    0 = CN is disabled   */
    CNCONDbits.ON = 1;
/*    CNSTYLE: Change Notification Style Selection bit
    1 = Edge style (detects edge transitions, bits are used for a CNE)
    0 = Mismatch style (detects change from last port read event)       */    
    CNCONDbits.CNSTYLE = 1;
     
    CNEN0D = 0;
    CNEN0Dbits.CNEN0D1 = 0;
    CNEN1D = 0;
    CNEN1Dbits.CNEN1D1 = 1;
    
    bufferPortD = PORTD;
    _CNDIF = 0;
    _CNDIE = 1;
    _CNDIP = 7;
     
}
