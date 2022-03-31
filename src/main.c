/*
 * main.c Lab 3
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



volatile Uint16 sync_count = 0;
volatile Uint16 adcInt_count = 0;
volatile Uint16 pwmInt_count = 0;
volatile Uint16 xInt_count = 0;

volatile float32 angle = 0, delta_angle = 0;
volatile Uint16 state_variable = 0;
volatile float32 adc0;
volatile float32 adc0real;
volatile float32 adc1;

volatile float32 adc_avg = 0, adc_C_avg = 0;
volatile Uint32 adc_sum = 0, adc_C_sum = 0;
volatile float32 pwm_cmpa = 2500;
volatile Uint16 xInt3Location;


volatile float32 d_t = 0;
volatile float32 m_t = 0.25;
volatile float32 adc0;
volatile float32 adc1;
volatile float32 adc0real, adc1real;

/******************************* Local #defines *******************************/

/******************************* Local typedefs *******************************/

/************************* Local function prototypes **************************/

/********************* Code sections to be copied to RAM **********************/

/****************************** Local structures ******************************/

/************************ Global variable definitions *************************/

void main(void)
{
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks

InitSysCtrl();

#ifdef FLASH_LINK
    // Copy time critical code and Flash setup code to RAM
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    InitFlash();
#endif

    // Set the High-Speed Peripheral Clock Prescaler (HISPCP) such that HSPCLK = 25 MHz
    // HSPCLK = SYSCLKOUT/(HISPCP x 2)
    EALLOW;
#if CPU_FRQ_150MHZ

    SysCtrlRegs.HISPCP.all = 3;
#else
    SysCtrlRegs.HISPCP.all = 2;
#endif

    EDIS;

    // Step 2. Initalize GPIO:
    gpio_init();

    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    InitPieVectTable();

    EALLOW;



    // Step 4. Initialize all the Device Peripherals:
    pwm_init();
   adc_init();


    // Step 5. User specific code, enable interrupts:



    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM


    EDIS;
    while (1)
    {
        asm(" NOP");
    }

}
