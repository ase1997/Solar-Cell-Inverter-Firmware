/*
 * adc_init.c
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

void adc_init(void)
{

    EALLOW;

    InitAdc();


    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;





    EDIS;

}



