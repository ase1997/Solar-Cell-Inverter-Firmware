/*
 * gpio_init.c
 *
 *  Created on: 2018-05-29
 *      Author: John Troxler
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

void gpio_init(void)
{
    EALLOW;
    //
    // PWM GPIO Config

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;

        GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
       GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;
     GpioDataRegs.GPADAT.bit.GPIO2 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;

    //need IER call for each interrupt
     IER |= M_INT12;
      IER |= M_INT1;
      IER |= M_INT3;

    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;
     PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;

     PieVectTable.XINT3 = &xint_isr;
      PieVectTable.ADCINT = &adc_isr;
      PieVectTable.EPWM1_INT = &pwm_isr;

       XIntruptRegs.XINT3CR.bit.ENABLE = 1;
       XIntruptRegs.XINT3CR.bit.POLARITY = 1;

     GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;
     GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;
     GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 2;
     GpioCtrlRegs.GPBCTRL.bit.QUALPRD0 = 6;
     GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 1;


    //need to enable each interrupt in pieier



    EDIS;
}
