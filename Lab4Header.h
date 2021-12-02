/*
*Alamjit Choat
* 1962902
* 08/10/2020
* Header file for Lab 4.
*/

#ifndef __HEADER4_H__
#define __HEADER4_H__

///////////////////////LCD GPIO_INIT///////////////////////////////
#define RCGCGPIO                (*((volatile uint32_t *)0x400FE608))

#define GPIODIR_D               (*((volatile uint32_t *)0x4005B400))
#define GPIODIR_K               (*((volatile uint32_t *)0x40061400))
#define GPIODIR_M               (*((volatile uint32_t *)0x40063400))
#define GPIODIR_N               (*((volatile uint32_t *)0x40064400))
#define GPIODIR_P               (*((volatile uint32_t *)0x40065400)) 
#define GPIODIR_Q               (*((volatile uint32_t *)0x40066400)) 

#define GPIODEN_D               (*((volatile uint32_t *)0x4005B51C))
#define GPIODEN_K               (*((volatile uint32_t *)0x4006151C))
#define GPIODEN_M               (*((volatile uint32_t *)0x4006351C)) 
#define GPIODEN_N               (*((volatile uint32_t *)0x4006451C))
#define GPIODEN_P               (*((volatile uint32_t *)0x4006551C)) 
#define GPIODEN_Q               (*((volatile uint32_t *)0x4006651C))

#define GPIOAFSEL_D             (*((volatile uint32_t *)0x4005B420)) 
#define GPIOAFSEL_K             (*((volatile uint32_t *)0x40061420)) 
#define GPIOAFSEL_M             (*((volatile uint32_t *)0x40063420)) 
#define GPIOAFSEL_N             (*((volatile uint32_t *)0x40064420)) 
#define GPIOAFSEL_P             (*((volatile uint32_t *)0x40065420)) 
#define GPIOAFSEL_Q             (*((volatile uint32_t *)0x40066420)) 

/////////////////////// SWITCHES ///////////////////////////////////
#define GPIODIR_J               (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J               (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J               (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J              (*((volatile uint32_t *)0x400603FC))

// ***************** ADC REGISTERS ****************** //
#define RCGCADC                 (*(volatile uint32_t *) 0x400FE638)
#define RCGCGPIO                (*((volatile uint32_t *)0x400FE608))
#define ADCACTSS                (*(volatile uint32_t *) 0x40038000)
#define PLLFREQ0                (*(volatile uint32_t *) 0x400FE160)
#define ADCCC                   (*(volatile uint32_t *) 0x40038FC8)
#define ADCEMUX                 (*(volatile uint32_t *) 0x40038014)
#define ADCSSMUX3               (*(volatile uint32_t *) 0x400380A0)
#define ADCSSCTL3               (*(volatile uint32_t *) 0x400380A4)
#define ADCPSSI                 (*(volatile uint32_t *) 0x40038028)
#define ADCSSFIFO3              (*(volatile uint32_t *) 0x400380A8)
#define ADCRIS                  (*(volatile uint32_t *) 0x40038004)
#define ADCISC                  (*(volatile uint32_t *) 0x4003800C)
#define ADCSSTSH3               (*((volatile uint32_t *)0x400380BC)) 

// ***************** TIMER ************************************** //
#define RCGCTIMER               (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0               (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0               (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0              (*((volatile uint32_t *)0x40030004))
#define GPTMRIS_0               (*((volatile uint32_t *)0x4003001C))
#define GPTMTAILR_0             (*((volatile uint32_t *)0x40030028)) 
#define GPTMICR_0               (*((volatile uint32_t *)0x40030024)) 
#define GPTMIMR_0               (*((volatile uint32_t *)0x40030018)) 
#define ISE_E0                  (*((volatile uint32_t *)0xE000E100)) 

///////////////////// METHODS ///////////////////////////////////////
void init_switches(void);
void init_ADC(void);
void initTimer(void);

#endif //__HEADER4_H__