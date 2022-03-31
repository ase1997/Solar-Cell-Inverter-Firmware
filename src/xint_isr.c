/*
 * xint_isr.c
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
#include "pwm_init.h"

extern Uint16 state_variable;
extern Uint16 sync_count;
extern Uint16 xint_count;
extern Uint16 adcInt_count;
extern Uint16 pwmInt_count;
extern float32 angle;
extern float32 d_t;
extern float32 m_t;
extern Uint32 adc_sum, adc_avg;
extern Uint32 pwm_cmpa;


interrupt void xint_isr(void)
{
    EALLOW;

    EPwm1Regs.TBCTL.bit.SWFSYNC = 1;
/*
    if(temp == 0){
        temp = 1;
        GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    }else if(temp == 1){
        temp =0;
        GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
    }
*/

    switch(state_variable) {
    case 0: sync_count = 0;
            state_variable = 1;
            break;
    case 1: sync_count++;
            if(sync_count >= 20){
                sync_count = 0;
                state_variable = 2;
            }
            break;
    case 2: angle = 0;
            pwmInt_count = 0;
            adc_sum = 0;
            adc_avg = 0;
            adcInt_count = 0;
            break;
    default:
        sync_count = 100;

    }

    PieCtrlRegs.PIEACK.bit.ACK12 = 1;

    EDIS;
}


