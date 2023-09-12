/*
 * LCD_interface.h
 *
 * Created: 06-Sep-23 6:41:56 PM
 *  Author: SEIF EL-DIN SOLTAN 
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


	
/*	for four bit mode	*/



#define LCD_CmndBit0                          0
#define LCD_CmndBit1                          1
#define LCD_CmndBit2                          2
#define LCD_CmndBit3                          3



void LCD_init                                 (void);
void LCD_sendComnd                            (u8 cmnd);
void LCD_sendChar                             (u8 Character_Data);
void LCD_SendString                           (u8 *String_Data);
void LCD_ClearDesplay                         (void);
void LCD_GOTO_LOCATION                        (u8 X_Location, u8 Y_Location);
void LCD_SendNumber                           (u16 Number);
void LCD_SendNumberToLocation                 (u16 Number,u8 X_Location, u8 Y_Location);

void LCD_init_8bit                            (void);
void LCD_sendComnd_8BIT                       (u8 cmnd);
void LCD_sendChar_8BIT                        (u8 Character_Data);
void LCD_SendString_8BIT                      (u8 *String_Data);
void LCD_ClearDesplay_8BIT                    (void);
void LCD_GOTO_LOCATION_8BIT                   (u8 X_Location, u8 Y_Location);
void LCD_SendNumber_8BIT                      (u16 Number);
void LCD_SendNumberToLocation_8BIT            (u16 Number,u8 X_Location, u8 Y_Location);
#endif /* LCD_INTERFACE_H_ */