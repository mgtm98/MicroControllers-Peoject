#include "KeyPad.h"

char key_pad [4][4] = {{'1','2','3','A'}, 
											 {'4','5','6','B'},
											 {'7','8','9','C'},
											 {'*','0','#','D'}};

											 
											 
void Keypad_init(void){
	// Initialization of column pins as Digital Input pins
	GPIO_initPin(KEYPAD_COL,PIN4, GPIO_CONF_DI);
	GPIO_initPin(KEYPAD_COL,PIN5, GPIO_CONF_DI);
	GPIO_initPin(KEYPAD_COL,PIN6, GPIO_CONF_DI);
	GPIO_initPin(KEYPAD_COL,PIN7, GPIO_CONF_DI);
	GPIO_setPUR(KEYPAD_COL,PIN4, HIGH);
	GPIO_setPUR(KEYPAD_COL,PIN5, HIGH);
	GPIO_setPUR(KEYPAD_COL,PIN6, HIGH);
	GPIO_setPUR(KEYPAD_COL,PIN7, HIGH);
	
	// Initialization of column pins as Digital Output pins
	GPIO_initPin(KEYPAD_ROW,PIN4, GPIO_CONF_DO);
	GPIO_initPin(KEYPAD_ROW,PIN5, GPIO_CONF_DO);
	GPIO_initPin(KEYPAD_ROW,PIN6, GPIO_CONF_DO);
	GPIO_initPin(KEYPAD_ROW,PIN7, GPIO_CONF_DO);
	GPIO_setPUR(KEYPAD_ROW, PIN4, HIGH);
	GPIO_setPUR(KEYPAD_ROW, PIN5, HIGH);
	GPIO_setPUR(KEYPAD_ROW, PIN6, HIGH);
	GPIO_setPUR(KEYPAD_ROW, PIN7, HIGH);
}

char keypad_getkey(void){
		
		int  col;
		col= GPIO_readPort(KEYPAD_COL);
		GPIO_setPort(KEYPAD_ROW,LOW);					
		
		if(col & 0xF0){
				return KEYPAD_NOKEY;
		}
		while(1){
	
				// 1st row has zero
				GPIO_setPin(KEYPAD_ROW,PIN4, HIGH); 
				col = GPIO_readPort(KEYPAD_COL) & 0xF0;
				if (col == 0xE0){
					return key_pad [0][0];
				}else if (col == 0xD0){
					return key_pad [0][1];
				}else if(col == 0xB0){
					return key_pad [0][2];
				}else if (col == 0x70){
					return key_pad [0][3];
				}
				
				// 2nd row has zero
				GPIO_setPin(KEYPAD_ROW,PIN5, HIGH); 
				col = GPIO_readPort(KEYPAD_COL) & 0xF0;
				if (col == 0xE0){
					return key_pad [1][0];
				}else if (col == 0xD0){
					return key_pad [1][1];
				}else if(col == 0xB0){
					return key_pad [1][2];
				}else if (col == 0x70){
					return key_pad [1][3];
				}
				
				// 3rd row has zero
				GPIO_setPin(KEYPAD_ROW,PIN6, HIGH); 
				col = GPIO_readPort(KEYPAD_COL) & 0xF0;
				if (col == 0xE0){
					return key_pad [2][0];
				}else if (col == 0xD0){
					return key_pad [2][1];
				}else if(col == 0xB0){
					return key_pad [2][2];
				}else if (col == 0x70){
					return key_pad [2][3];
				}
				
				// 4th row has zero
				GPIO_setPin(KEYPAD_ROW,PIN4, HIGH); 
				col = GPIO_readPort(KEYPAD_COL) & 0xF0;
				if (col == 0xE0){
					return key_pad [3][0];
				}else if (col == 0xD0){
					return key_pad [3][1];
				}else if(col == 0xB0){
					return key_pad [3][2];
				}else if (col == 0x70){
					return key_pad [3][3];
				}						
	   }
}
