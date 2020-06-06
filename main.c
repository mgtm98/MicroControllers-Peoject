#include "comman.h"
#include "gpio.h"
#include "sysctrl.h"
#include "uart.h"
#include "keypad.h"

#define STATUS1 								'a'
#define STATUS2 								'b'
#define STATUS3 								'c'
#define COMMAND_STATUS_CHANGED	'd'
#define COMMAND_CONFIRMATION		'e'
#define SELENOID								BLUE_LED

int main(){
		
	SYSCTRL_initGPIO(SYSCTRL_GPIOF);						// provide clk to PORTF
	GPIO_initPort(GPIOF, GPIO_CONF_DO);					// initialize PORTF as Digital Output port

	SYSCTRL_initUART(SYSCTRL_UART0);						// provide clk to UART0
	UART_Init(UART0, UART_BAUD_115200);					// initalize UART0 with bauderate 115200

	UART_sendString(UART0, "GET ROOM NUMBER\n");  // Get room number
	while(!UART_available(UART0));							// wait till room number is sent
	uint8_t roomNumber = UART_readChar(UART0);	// read room number (is sent as a byte number)

	UART_sendString(UART0, "GET ROOM STATUS\n");  // Get room status
	while(!UART_available(UART0));								// wait till room ststus is sent
	uint8_t status = UART_readChar(UART0);				// read room status (is sent as a byte number)

	//Keypad_init();

	while(1){
		if(status == STATUS1){
			// NOTHING TO DO
		}else if(status == STATUS2){
			char password [6];															
			char index = 0;
			while(1){
				char c = keypad_getkey();										// get keys pressed from keypad
				if(c == KEYPAD_NOKEY) continue;							// if no key pressed wait
				password[index] = c;												// stores keys in password arr
				index ++;
				if(index == 6) break;												// if 6 keys are pressed then that's the password
				}
				UART_sendString(UART0, "PASSWORD IS ");					// checking the password from the main system
				UART_sendString(UART0, password);
				while(!UART_available(UART0));									// wait till response is ready
				char confirm = UART_readChar(UART0);						// response is ready
				if(confirm == COMMAND_CONFIRMATION)
				GPIO_setPin(GPIOF, SELENOID, HIGH);
			}else if(status == STATUS3){
				GPIO_setPin(GPIOF, SELENOID, HIGH);							// Status 3 always open the door
			}
			if(UART_available(UART0)){
				uint8_t command = UART_readChar(UART0);					// if there is a command from the main system read it
				if(command == COMMAND_STATUS_CHANGED){				
				while(!UART_available(UART0));							// wait till room number is sent
					status = UART_readChar(UART0);							// read room status (is sent as a byte number)
				}
			}
		}
}
