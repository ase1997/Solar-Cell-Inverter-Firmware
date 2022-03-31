/*
 * project.h
 *
 *  Created on: 2018-05-29
 *      Author: John Troxler
 */

#ifndef INCLUDE_PROJECT_H_
#define INCLUDE_PROJECT_H_


/* ============================ CONTEXT SWITCHES ============================ */

/* ============================= GLOBAL DEFINES ============================= */
#define PWM_TBPRD   4999             // Example global variable
#define PWM_DBRED   70 //rising
#define PWM_DBFED   70 //falling
#define PWM_CMPA 0 // duty cycle
#define PWM_NUMCLK   5000
#define PWM_DRATIO   2500

#define State_Ini 0
#define State_Vali 1
#define State_Run 2

#define Dead_band 105
#define Two_Pi 6.283
#define Pwm_Freq 1000 //Hz
#define more




#endif /* INCLUDE_PROJECT_H_ */
