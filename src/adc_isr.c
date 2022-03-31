/*
 * adc_isr.c
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
extern Uint32 angle;
extern Uint16 state_variable;

extern float32 adc0;
extern float32 adc0real;
extern float32 adc1;
extern float32 adc_sum;
extern float32 adc_avg;


interrupt void adc_isr(void)
{

    EALLOW;

    adc0 = AdcMirror.ADCRESULT0;

    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;

    adcInt_count++;

    adc0real = (0.00073 *adc0)-(7/1368);
    adc_sum = adc_sum + adc0real;
    adc_avg = (adc_sum)/(adcInt_count);


    PieCtrlRegs.PIEACK.bit.ACK1 = 1;



    EDIS;

}


