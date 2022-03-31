/*
 * pwm_init.c
 *
 *  Created on: 2019-02-01
 *      Author: Sani Patel
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

void pwm_init(void)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;  // Disable the clock input to epwm module
    EDIS;

    EPwm1Regs.TBCTL.all = 0 ;   // reset all bits in TBCTL

      EPwm1Regs.ETSEL.bit.INTEN = 1;
      EPwm1Regs.ETSEL.bit.INTSEL = 2;
       EPwm1Regs.ETSEL.bit.SOCAEN = 1;
       EPwm1Regs.ETSEL.bit.SOCASEL = 6;

      EPwm1Regs.ETPS.bit.SOCAPRD = 1;
      EPwm1Regs.ETPS.bit.INTPRD = 1;


    EPwm1Regs.TBCTL.bit.CLKDIV = 0x00;  //We set the CLKDIV to value of 00 because we want the timebase clock to be as fast as possible
    EPwm1Regs.TBCTL.bit.CTRMODE = 0x00; //We set the CTRMODE to value of 00 because we were specified to use the count up mode
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 0x01; //We set the SYNCOSEL to value of 01 because this sets the CTR to zero
    EPwm1Regs.TBCTL.bit.PHSEN = 0x00; //We set the PHSEN to value of 00 because we do not want to load the time base counter from the time base phase register
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0x00; //We set the HSPCLKDIV to 00 so we do not scale the clock
    EPwm1Regs.TBCTL.bit.PRDLD = 0x00; //We set the PRDLD to 00 so the period register is loaded from the shadow register

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0x00; //This sets the operating mode for CMPB Register to shadow mode
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0x00; //This sets the operating mode for CMPA Register to shadow mode

    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0x00; //This sets that A loads at CTR equal to 0
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 0x00; //This sets that B loads at CTR equal to 0

    EPwm1Regs.TBPHS.all = 0; //This makes it so that we are not synchronizing multiple modules

    EPwm1Regs.DBCTL.bit.IN_MODE = 0x00; //This is set to 00 because EPWM1A is the source for the rising and falling edge
    EPwm1Regs.DBCTL.bit.POLSEL = 0x02; //This is set to 02 for active high complimentary mode
    EPwm1Regs.DBCTL.bit.OUT_MODE = 0x03; //This is set to 03 for dead band to be enable for both rising and falling edge

    EPwm1Regs.AQCTLA.bit.ZRO = 0x02; //This is set to 02 because it forces EPWM1A to output high when counter is zero
    EPwm1Regs.AQCTLA.bit.CAU = 0x01; //This is set to 01 because it forces the output to be low when the counter equals active CMPA

    EPwm1Regs.TBPRD = PWM_NUMCLK; // Period = 5000 TBCLK counts - global variable
    EPwm1Regs.CMPA.half.CMPA = PWM_DRATIO; // Duty ratio = 2500 for 50% - global variable
    //EPwm1Regs.CMPA.half.CMPA = 0;

    EPwm1Regs.DBFED = Dead_band; // FED = 105 TBCLKs initially - global variable
    EPwm1Regs.DBRED = Dead_band; // RED = 105 TBCLKs initially - global variable

    // Enable clocks for PWM modules
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}
