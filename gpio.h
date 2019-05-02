
#ifndef GPIO_H
#define GPIO_H

// System clock register
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))

// GPIO register definitions
	
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_DR8_R        (*((volatile unsigned long *)0x40005508))

#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
	
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DATA_PIN2    (*((volatile unsigned long *)0x40024010))

#endif /* GPIO_H */
