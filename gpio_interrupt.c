#include "gpio.h"

void (*callbackTable[6][8])();

void    GPIO_initInterrupt(GPIO_Type *gpio, Pin pin, InterruptEvent ev, void (*callback)(void)){
	gpio->IS &= ~(pin);
    switch(ev){
        case BOTH:
            gpio->IBE |= pin;
            break;
    case FALLING:
            gpio->IBE &= ~(pin);
            gpio->IEV &= ~(pin);
            break;
    case RISING:
            gpio->IBE &= ~(pin);
            gpio->IEV |= pin;
            break;
    }
	gpio->ICR |= (pin);
	gpio->IM  |= (pin);
		
	switch((int)gpio){
		case (int)GPIOA:	NVIC_EN0 |= (1 << 0); callbackTable[0][Log(pin)] = callback; break;
		case (int)GPIOB:  NVIC_EN0 |= (1 << 1); callbackTable[1][Log(pin)] = callback; break;
		case (int)GPIOC:	NVIC_EN0 |= (1 << 2); callbackTable[2][Log(pin)] = callback; break;
		case (int)GPIOD:	NVIC_EN0 |= (1 << 3); callbackTable[3][Log(pin)] = callback; break;
		case (int)GPIOE:	NVIC_EN0 |= (1 << 4);	callbackTable[4][Log(pin)] = callback; break;
		case (int)GPIOF:  NVIC_EN0 |= (1 << 30); callbackTable[5][Log(pin)] = callback; break;
	}
}

void GPIO_interruptHandler(GPIO_Type *gpio, uint8_t portNumber){
	if(gpio->MIS == PIN0){
		gpio->ICR |= PIN0;
		callbackTable[portNumber][0]();
	}else if(gpio->MIS == PIN1){
		gpio->ICR |= PIN1;
		callbackTable[portNumber][1]();
	}else if(gpio->MIS == PIN2){
		gpio->ICR |= PIN2;
		callbackTable[portNumber][2]();
	}else if(gpio->MIS == PIN3){
		gpio->ICR |= PIN3;
		callbackTable[portNumber][3]();
	}else if(gpio->MIS == PIN4){
		gpio->ICR |= PIN4;
		callbackTable[portNumber][4]();
	}else if(gpio->MIS == PIN5){
		gpio->ICR |= PIN5;
		callbackTable[portNumber][5]();
	}else if(gpio->MIS == PIN6){
		gpio->ICR |= PIN6;
		callbackTable[portNumber][6]();
	}else if(gpio->MIS == PIN7){
		gpio->ICR |= PIN7;
		callbackTable[portNumber][7]();
	}
}

void GPIOA_Handler(){
	GPIO_interruptHandler(GPIOA, 0);
}

void GPIOB_Handler(){
	GPIO_interruptHandler(GPIOB, 1);
}

void GPIOC_Handler(){
	GPIO_interruptHandler(GPIOC, 2);
}

void GPIOD_Handler(){
	GPIO_interruptHandler(GPIOD, 3);
}

void GPIOE_Handler(){
	GPIO_interruptHandler(GPIOE, 4);
}

void GPIOF_Handler(){
	GPIO_interruptHandler(GPIOF,5);
}
