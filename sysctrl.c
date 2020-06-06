#include "sysctrl.h"

void SYSCTRL_initGPIO(GPIO_SYSCTRL gpioCTL){
		SYSCTL->RCGCGPIO |= gpioCTL;
//		while(!(SYSCTL->PRGPIO & gpioCTL));
}

void SYSCTRL_initUART(UART_SYSCTRL uartCTL){
		SYSCTL->RCGCUART |= uartCTL;
//		while(!(SYSCTL->PRUART & uartCTL));
}