/*
 * KEYPAD_config.h
 *
 * Created: 08-Sep-23 8:53:34 AM
 *  Author: SEIF EL-DIN SOLTAN
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


#define KEYPAD_ROW0_PORT         DIO_PORTC
#define KEYPAD_ROW0_PIN          DIO_PIN4

#define KEYPAD_ROW1_PORT         DIO_PORTC
#define KEYPAD_ROW1_PIN          DIO_PIN5

#define KEYPAD_ROW2_PORT         DIO_PORTC
#define KEYPAD_ROW2_PIN          DIO_PIN6

#define KEYPAD_ROW3_PORT         DIO_PORTC
#define KEYPAD_ROW3_PIN          DIO_PIN7

#define KEYPAD_COL0_PORT         DIO_PORTC
#define KEYPAD_COL0_PIN          DIO_PIN0

#define KEYPAD_COL1_PORT         DIO_PORTC
#define KEYPAD_COL1_PIN          DIO_PIN1

#define KEYPAD_COL2_PORT         DIO_PORTC
#define KEYPAD_COL2_PIN          DIO_PIN2

#define KEYPAD_COL3_PORT         DIO_PORTC
#define KEYPAD_COL3_PIN          DIO_PIN3



#define KEYPAD_PATTERN     { {7,8,9,'/'},      \
                             {4,5,6,'*'},      \
                             {1,2,3,'-'},      \
                             {'#',0,'=','+'}   \
	                      }
						  

	                					  


#endif /* KEYPAD_CONFIG_H_ */