/*
 * LCD_program.c
 *
 * Created: 06-Sep-23 6:41:33 PM
 *  Author: SEIF EL-DIN SOLTAN 
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/*	UTILES_LIB	*/
#include "STD_TYPE.h"
#include "BIT_MATH.h"
/*	MCAL	*/
#include "DIO_interface.h"
#include "DIO_private.h"
/*	HAL	*/
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


void LCD_init(void)
{
	//SET PIN AS OUTPUT
	DIO_SetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_OUTPUT);
	
	
	 DIO_SetPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	 DIO_SetPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	 DIO_SetPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	 DIO_SetPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
	 	 
		
	_delay_ms(35);
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	private_WriteHalfPort(LCD_COMMAND_FOR_FOUR_BIT_MODE);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	LCD_sendComnd(LCD_FUNCTION_SET);
	_delay_us(45);
	
	LCD_sendComnd(LCD_DISPLAY_ON_OFF_CONTROL);
	_delay_us(45);
	
	LCD_sendComnd(LCD_DESPLAY_CLEAR);
	_delay_ms(2);
	
	LCD_sendComnd(LCD_ENTRY_MODE_SET);
	_delay_us(45);

}

void LCD_sendComnd(u8 Cmnd)
{
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	private_WriteHalfPort(Cmnd>>4);                                    //PORTA_REG= (PORTA_REG & 0x0f) | (Cmnd & 0xf0) 
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	private_WriteHalfPort(Cmnd);                                      //PORTA_REG= (PORTA_REG & 0x0f) | ((Cmnd & 0xf0) <<4)
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}


void LCD_sendChar(u8 Character_Data)
{
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	private_WriteHalfPort(Character_Data>>4);                        //PORTA_REG= (PORTA_REG & 0x0f) | (Character_Data & 0xf0) 
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	private_WriteHalfPort(Character_Data);                         //PORTA_REG= (PORTA_REG & 0x0f) | ((Character_Data & 0xf0) <<4)
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}

void LCD_SendString (u8 *String_Data)
{
	while((*String_Data)!='\0')
	{
		LCD_sendChar(*String_Data);
		String_Data++;
	}
}


void LCD_ClearDesplay()
{
	LCD_sendComnd (LCD_DESPLAY_CLEAR);		
	_delay_ms(2);
	LCD_sendComnd (LCD_Cursor_At_Home_position);		
}

void LCD_GOTO_LOCATION(u8 X_Location, u8 Y_Location)
{
	u8 FirstLocation[] = {0x80, 0xC0, 0x94, 0xD4};
	LCD_sendComnd(FirstLocation[Y_Location-1] + X_Location-1);
	_delay_us(1000);
}

void LCD_SendIntegarNumber(u16 IntegerNumber)
{
	u16 NumberString[16];
	snprintf(NumberString,17,"%d",IntegerNumber);    
	LCD_SendString(NumberString);
}


void LCD_SendNumberToLocation(u16 Number,u8 X_Location, u8 Y_Location)
{
	LCD_GOTO_LOCATION(X_Location,Y_Location);
	LCD_SendIntegarNumber(Number);
}

void LCD_SendFloatNumber(f32 FloatNumber)
{
	u16 NumberString[16];
	snprintf(NumberString,17,"%f",FloatNumber);
	LCD_SendString(NumberString);
}

void LCD_VidDataShiftLeft()
{
	LCD_sendComnd(LCD_SHIFTLEFT);
}

void LCD_VidDataShiftRight()
{
	LCD_sendComnd(LCD_SHIFTRIGHT);
}


void private_WriteHalfPort (u8 Value)
{
	(DIO_PIN_LOW==GET_BIT(Value,LCD_CmndBit0)) ? (DIO_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_LOW)) : (DIO_SetPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_HIGH));
	(DIO_PIN_LOW==GET_BIT(Value,LCD_CmndBit1)) ? (DIO_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_LOW)) : (DIO_SetPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_HIGH));
	(DIO_PIN_LOW==GET_BIT(Value,LCD_CmndBit2)) ? (DIO_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_LOW)) : (DIO_SetPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_HIGH));
	(DIO_PIN_LOW==GET_BIT(Value,LCD_CmndBit3)) ? (DIO_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_LOW)) : (DIO_SetPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_HIGH));
}


/***************************************************************************************************************************************************************/
/*8_BIT*/


void LCD_init_8bit(void)
{
	//SET PIN AS OUTPUT
	DIO_SetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_SetPinDirection(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_OUTPUT);
	
	DIO_setPortDirection(LCD_PORT,DIO_PORT_OUTPUT);
	
	_delay_ms(35);
//     DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
//     DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	LCD_sendComnd_8BIT(LCD_FUNCTION_SET_8BIT);
	_delay_us(45);
	
	LCD_sendComnd_8BIT(LCD_DISPLAY_ON_OFF_CONTROL_8BIT);
	_delay_us(45);
	
	LCD_sendComnd_8BIT(LCD_DESPLAY_CLEAR_8BIT);
	_delay_ms(2);
	
	LCD_sendComnd_8BIT(LCD_ENTRY_MODE_SET_8BIT);
	_delay_us(45);

}



void LCD_sendComnd_8BIT(u8 Cmnd)
{
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	DIO_setPortValue(LCD_PORT,Cmnd);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}

void LCD_sendChar_8BIT(u8 Character_Data)
{
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	DIO_setPortValue(LCD_PORT,Character_Data);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
}

void LCD_SendString_8BIT (u8 *String_Data)
{
	while((*String_Data)!='\0')
	{
		LCD_sendChar_8BIT(*String_Data);
		String_Data++;
	}
}

void LCD_ClearDesplay_8BIT ()
{
	LCD_sendComnd_8BIT (LCD_DESPLAY_CLEAR);
	_delay_ms(2);
	LCD_sendComnd_8BIT (LCD_Cursor_At_Home_position);
}

void LCD_GOTO_LOCATION_8BIT(u8 X_Location, u8 Y_Location)
{
	u8 FirstLocation[] = {0x80, 0xC0, 0x94, 0xD4};
	LCD_sendComnd_8BIT(FirstLocation[Y_Location-1] + X_Location-1);
	_delay_us(1000);
}

void LCD_SendIntegarNumber_8BIT(u16 IntegerNumber)
{
	u16 NumberString[16];
	snprintf(NumberString,17,"%d",IntegerNumber);
	LCD_SendString_8BIT(NumberString);
}


void LCD_SendNumberToLocation_8BIT(u16 Number,u8 X_Location, u8 Y_Location)
{
	LCD_GOTO_LOCATION(X_Location,Y_Location);
	LCD_SendIntegarNumber_8BIT(Number);
}

void LCD_SendFloatNumber_8BIT(f32 FloatNumber)
{
	u16 NumberString[16];
	snprintf(NumberString,17,"%f",FloatNumber);
	LCD_SendString_8BIT(NumberString);
}