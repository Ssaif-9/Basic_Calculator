/*
 * CALCULATOR.c
 *
 * Created: 10-Sep-23 3:47:53 PM
 *  Author: SEIF EL-DIN SULTAN OSMAN 
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

#include "STD_TYPE.h"
#include "BIT_MATH.h"

#include "DIO_private.h"
#include "DIO_interface.h"
#include "DIO_config.h"

#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"

#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"

void ADD(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result);
void SUB(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result);
void MUL(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result);
void DIV(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result);


int main(void)
{
	u8 Operator,Equal;
	u32 FirstNum , SecondNum ;
	u32 Result;
	u32 FirstNumArr[4],SecondNumArr[4];
	u32 KeypadValue;
	
	u8 FirstNumFlag,OperatorFlag,SecondNumFlag,EqualFlag = 0 ;
	
	LCD_init();
	KEYPAD_init();
	
	LCD_GOTO_LOCATION(5,1);
	LCD_SendString("WELCOME!");
	LCD_sendComnd(LCD_GO_TO_2ND_LINE);
	LCD_SendString(" +-/*CALCOLATOR ");
	_delay_ms(1000);
	LCD_ClearDesplay();
	LCD_sendComnd(LCD_GO_TO_2ND_LINE);
	LCD_GOTO_LOCATION(5,2);
	LCD_SendString("# Reset");
	LCD_sendComnd(LCD_GO_TO_1ND_LINE);
	while(1)
	{
		KEYPAD_GetValue(&KeypadValue);
		if (KEYPAD_NOT_PRESSED != KeypadValue )
		{
			if (KeypadValue != '+' && KeypadValue != '-' && KeypadValue != '*' && KeypadValue != '/' && KeypadValue != '=' && KeypadValue != '#' && FirstNumFlag != 4 &&  OperatorFlag == 0 &&  SecondNumFlag == 0 && EqualFlag == 0  )
			{
				 FirstNum=KeypadValue;
				 FirstNumArr[FirstNumFlag]=FirstNum;
				 FirstNumFlag++ ;
				 LCD_SendIntegarNumber(KeypadValue);
			}
			
			 if( (KeypadValue == '+' || KeypadValue == '-' || KeypadValue == '*'|| KeypadValue == '/' ) && (FirstNumFlag != 0  && OperatorFlag == 0  && SecondNumFlag == 0 && EqualFlag == 0)  )
			 {
			 	 Operator = KeypadValue;
			 	 OperatorFlag = 1 ;
			 	 LCD_sendChar(KeypadValue);
			 }
			
			 if (KeypadValue != '+' && KeypadValue != '-' && KeypadValue != '*' && KeypadValue != '/' && KeypadValue != '='  && KeypadValue != '#' && FirstNumFlag != 0 && OperatorFlag == 1 && SecondNumFlag != 4 && EqualFlag == 0 )
			 {
				 SecondNum=KeypadValue;
				 SecondNumArr[SecondNumFlag]=SecondNum;
				 SecondNumFlag++ ;
				 LCD_SendIntegarNumber(KeypadValue);
			 }
			
			 if (KeypadValue == '=' && FirstNumFlag != 0 && OperatorFlag == 1  && SecondNumFlag != 0 && EqualFlag == 0)
			 {
				 Equal=KeypadValue;
				 EqualFlag = 1 ;
				 LCD_sendChar(KeypadValue);
				 switch(Operator)
				 {
				 	 case '+' :
				 	 ADD(FirstNumArr,SecondNumArr,FirstNumFlag,SecondNumFlag,&Result);
				 	 break;
				 	 case '-' :
				 	 SUB(FirstNumArr,SecondNumArr,FirstNumFlag,SecondNumFlag,&Result);
				 	 break;
				 	 case '*' :
				 	 MUL(FirstNumArr,SecondNumArr,FirstNumFlag,SecondNumFlag,&Result);
				 	 break;
				 	 case '/' :
				 	 DIV(FirstNumArr,SecondNumArr,FirstNumFlag,SecondNumFlag,&Result);
				 	 break;
				 }
			 }
			if (KeypadValue == '#')
			 {
				 if (FirstNumFlag != 0 && OperatorFlag == 1  && SecondNumFlag != 0 && EqualFlag == 1)
				 {
					 LCD_ClearDesplay();
					 LCD_sendComnd(LCD_GO_TO_2ND_LINE);
					 LCD_GOTO_LOCATION(5,2);
					 LCD_SendString("# Reset");
					 LCD_sendComnd(LCD_GO_TO_1ND_LINE);
					 FirstNumFlag=SecondNumFlag=OperatorFlag=EqualFlag=0;
				 }
				 if (FirstNumFlag != 0 && OperatorFlag == 1  && SecondNumFlag != 0 && EqualFlag == 0 )
				 {
					 //Clear Last Location by shift left and send 'space' 
				 }					 
			 }
		}	
	}
}




void ADD(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result)
{
	u8 Index;
	u32 NUM1=FirstNumArr[0];
	u32 NUM2=SecondNumArr[0];
	
	for(Index=1;Index<FirstNumFlag;Index++)
	{
		NUM1 = NUM1*10 +FirstNumArr[Index];
	}
	
	for(Index=1;Index<SecondNumFlag;Index++)
	{
		NUM2 = NUM2*10 +SecondNumArr[Index];
	}
	
	
	*Result = (NUM1 + NUM2) ;
	LCD_SendIntegarNumber(*Result);
}

void SUB(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result)
{
	u8 Index;
	u32 NUM1=FirstNumArr[0];
	u32 NUM2=SecondNumArr[0];
	
	for(Index=1;Index<FirstNumFlag;Index++)
	{
		NUM1 = NUM1*10 +FirstNumArr[Index];
	}
	
	for(Index=1;Index<SecondNumFlag;Index++)
	{
		NUM2 = NUM2*10 +SecondNumArr[Index];
	}
	
	if(NUM2 > NUM1)
	{
		*Result = (NUM2 - NUM1) ;
		LCD_sendChar('-');
		LCD_SendIntegarNumber(*Result);
	}
	else
	{
		*Result = (NUM1 - NUM2) ;
		LCD_SendIntegarNumber(*Result);
	}
}

void MUL(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result)
{
	u8 Index;
	u32 NUM1=FirstNumArr[0];
	u32 NUM2=SecondNumArr[0];
	
	for(Index=1;Index<FirstNumFlag;Index++)
	{
		NUM1 = NUM1*10 +FirstNumArr[Index];
	}
	
	for(Index=1;Index<SecondNumFlag;Index++)
	{
		NUM2 = NUM2*10 +SecondNumArr[Index];
	}
	*Result = (NUM1 * NUM2) ;
	LCD_SendIntegarNumber(*Result);
}

void DIV(u32 FirstNumArr[], u32 SecondNumArr[],u8 FirstNumFlag,u8 SecondNumFlag, u32* Result)
{
	u8 Index;
	u32 NUM1=FirstNumArr[0];
	u32 NUM2=SecondNumArr[0];
	
	for(Index=1;Index<FirstNumFlag;Index++)
	{
		NUM1 = NUM1*10 +FirstNumArr[Index];
	}
	for(Index=1;Index<SecondNumFlag;Index++)
	{
		NUM2 = NUM2*10 +SecondNumArr[Index];
	}
	
	if (0 == NUM2)
	{
		LCD_ClearDesplay();
		LCD_SendString("Division ERROR/0");
		LCD_sendComnd(LCD_GO_TO_2ND_LINE);
		LCD_GOTO_LOCATION(5,2);
		LCD_SendString("# Reset");
	}	
	else
	{
		*Result = (NUM1 / NUM2) ;
		LCD_SendIntegarNumber(*Result);
	}
}
