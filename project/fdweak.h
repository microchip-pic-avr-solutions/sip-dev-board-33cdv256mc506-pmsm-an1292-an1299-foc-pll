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
#ifndef __FDWEAK_H
#define __FDWEAK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
    
/* Field weakening Parameter data type

  Description:
    This structure will host parameters related to field weakening function.
 */
typedef struct
{
    /* d-current reference */
    int16_t qIdRef;
    /* Flux weakening on speed -*/
    int16_t qFwOnSpeed;
    /* Lookup tables index */
    int16_t qIndex;
    /* Curve for magnetizing current variation with speed */
    int16_t qFwCurve[18];
    /* Curve for InvKfi constant InvKfi = Omega/BEMF variation with speed */
    int16_t qInvKFiCurve[18];
    /* Curve for Ls variation with speed */
    int16_t qLsCurve[18];    
} FDWEAK_PARM_T;

extern FDWEAK_PARM_T fdWeakParm;

void InitFWParams();
int16_t FieldWeakening( int16_t qMotorSpeed );

#ifdef __cplusplus
}
#endif

#endif /* __FDWEAK_H */
