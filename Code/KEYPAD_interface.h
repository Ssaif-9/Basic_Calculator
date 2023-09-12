/*
 * KEYPAD_interface.h
 *
 * Created: 08-Sep-23 8:53:54 AM
 *  Author: SEIF EL-DIN SOLTAN
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define KEYPAD_PRESSED                  0
#define KEYPAD_NOT_PRESSED              0xff 

void KEYPAD_init                       (void);
void KEYPAD_GetValue                   (u8* ReturnedValue);



#endif /* KEYPAD_INTERFACE_H_ */