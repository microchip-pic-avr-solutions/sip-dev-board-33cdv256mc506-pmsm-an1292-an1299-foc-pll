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
#ifndef __BOARD_SERVICE_H
#define __BOARD_SERVICE_H

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>
#include "motor_control_noinline.h"
#include "hardware_access_functions.h"
#include "pwm.h"
#ifdef __cplusplus  // Provide C++ Compatability
    extern "C" {
#endif
/** 
 * System States 
 * SYSTEM_INITIALISATION
 * SYSTEM_RUNNING
 */
typedef enum tagSYSTEM_STATE
{ 
    SYSTEM_INITIALIZATION = 0,      /* System Initialization Stage */
    SYSTEM_READY = 1,               /* System is Ready */
    SYSTEM_ERROR = 2,               /* System error */
     
}SYSTEM_STATE;

/* Button Scanning State

  Description:
    This structure will host parameters required by Button scan routine.
 */
typedef enum tagBUTTON_STATE
{
    BUTTON_NOT_PRESSED = 0, // wait for button to be pressed
    BUTTON_PRESSED = 1, // button was pressed, check if short press / long press
    BUTTON_DEBOUNCE = 2
} BUTTON_STATE;
    
// *****************************************************************************
/* Button data type

  Description:
    This structure will host parameters required by Button scan routine.
 */
typedef struct
{
   BUTTON_STATE state;
   uint16_t debounceCount;
   bool logicState;
   bool status;
} BUTTON_T;

// <editor-fold defaultstate="expanded" desc="DEFINITIONS/CONSTANTS ">
/* Heart beat LED - specify in no.of milli second */
#define HEART_BEAT_LED_mSec     250
/* Rate at which board service i executed**/
/* Specify the board service tick in milli second */
#define BOARD_SERVICE_TICK_mSec 1
/* Button De-bounce in milli Seconds */
#define BUTTON_DEBOUNCE_mSec    30

/* Board service tick count is incremented in every Timer 1 interrupt */
#define BOARD_SERVICE_TICK_COUNT    (BOARD_SERVICE_TICK_mSec*1000/LOOPTIME_MICROSEC)
/* Heart beat LED count is incremented in every Timer 1 interrupt */
#define HEART_BEAT_LED_COUNT        (HEART_BEAT_LED_mSec/BOARD_SERVICE_TICK_mSec)
/* Button De-bounce count is incremented at every board service function call */
#define BUTTON_DEBOUNCE_COUNT       (BUTTON_DEBOUNCE_mSec/BOARD_SERVICE_TICK_mSec)

void InitPeripherals(void);
void DisablePWMOutputs(void);
void EnablePWMOutputs(void);
void ClearPWMPCIFault(void);
void BoardServiceInit(void);
void BoardServiceStepIsr(void);
void BoardService(void);
bool IsPressed_Button1(void);
bool IsPressed_Button2(void);
void PWMDutyCycleSetDualEdge(MC_DUTYCYCLEOUT_T *,MC_DUTYCYCLEOUT_T *);
void PWMDutyCycleSet(MC_DUTYCYCLEOUT_T *);
void pwmDutyCycleLimitCheck(MC_DUTYCYCLEOUT_T *,uint16_t,uint16_t);


extern volatile uint16_t systemState;
extern volatile uint16_t runtimeState;
#ifdef __cplusplus
}
#endif

#endif /* __BOARD_SERVICE_H */
