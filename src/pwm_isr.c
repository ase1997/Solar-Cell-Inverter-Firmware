/*
 * pwm.isr.c
 *
 *  Created on: Apr 3, 2019
 *      Author: sanip
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#include "project.h"
#include "main.h"

#include "gpio_init.h"
#include "pwm_init.h"
#include "math.h"
#include "adc_init.h"
#include "adc_isr.h"
#include "pwm_isr.h"
#include "xint_isr.h"


extern Uint16 sync_count;
extern Uint16 adcInt_count;
extern Uint16 pwmInt_count;
extern float32 angle;
extern Uint16 state_variable;
extern float32 d_t;
extern float32 m_t;
extern Uint32 delta_angle;
extern float32 pwm_cmpa;
extern Uint16 xInt3Location;




interrupt void pwm_isr(void)
{
    //EALLOW;


    xInt3Location = PieCtrlRegs.PIEIER12.all;

    IER = 0x0800;

    EINT;

    if(state_variable == 2){
            pwmInt_count++;

            angle = pwmInt_count *(Two_Pi/Pwm_Freq)*60;
            d_t = 0.5 + (m_t*sin(angle));

            pwm_cmpa = 4999 * d_t;


            EPwm1Regs.CMPA.half.CMPA = pwm_cmpa;

            }

    EPwm1Regs.ETCLR.bit.INT = 1; //clear etflg bit

    DINT; //step 4

    PieCtrlRegs.PIEIER12.all = xInt3Location;
    IER = 0x0805;


     PieCtrlRegs.PIEACK.bit.ACK3 = 1; //Step 5


   // EDIS;

}


