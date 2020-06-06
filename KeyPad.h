#include "comman.h"
#include "gpio.h"

#define KEYPAD_COL			  GPIOC
#define KEYPAD_ROW  			GPIOE
#define KEYPAD_NOKEY			'x'

void Keypad_init(void);
char keypad_getkey(void);