/*
 * KEYPAD_program.c
 *
 * Created: 08-Sep-23 8:55:08 AM
 *  Author: SEIF EL-DIN SOLTAN
 */ 
#include "BIT_MATH.h"
#include "STD_TYPE.h"

#include "DIO_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"


void KEYPAD_init(void)
{
	DIO_SetPinDirection(KEYPAD_ROW0_PORT,KEYPAD_ROW0_PIN,DIO_PORT_INPUT);
	DIO_SetPinDirection(KEYPAD_ROW1_PORT,KEYPAD_ROW1_PIN,DIO_PORT_INPUT);	
	DIO_SetPinDirection(KEYPAD_ROW2_PORT,KEYPAD_ROW2_PIN,DIO_PORT_INPUT);	
	DIO_SetPinDirection(KEYPAD_ROW3_PORT,KEYPAD_ROW3_PIN,DIO_PORT_INPUT);	
	
	DIO_SetPinDirection(KEYPAD_COL0_PORT,KEYPAD_COL0_PIN,DIO_PORT_OUTPUT);	
	DIO_SetPinDirection(KEYPAD_COL1_PORT,KEYPAD_COL1_PIN,DIO_PORT_OUTPUT);	
	DIO_SetPinDirection(KEYPAD_COL2_PORT,KEYPAD_COL2_PIN,DIO_PORT_OUTPUT);	
	DIO_SetPinDirection(KEYPAD_COL3_PORT,KEYPAD_COL3_PIN,DIO_PORT_OUTPUT);	
	
	DIO_SetPinDirection(KEYPAD_COL0_PORT,KEYPAD_COL0_PIN,DIO_PIN_HIGH);
	DIO_SetPinDirection(KEYPAD_COL1_PORT,KEYPAD_COL1_PIN,DIO_PIN_HIGH);
	DIO_SetPinDirection(KEYPAD_COL2_PORT,KEYPAD_COL2_PIN,DIO_PIN_HIGH);
	DIO_SetPinDirection(KEYPAD_COL3_PORT,KEYPAD_COL3_PIN,DIO_PIN_HIGH);
	
	DIO_activePinInPullUpResistance(KEYPAD_ROW0_PORT,KEYPAD_ROW0_PIN);
	DIO_activePinInPullUpResistance(KEYPAD_ROW1_PORT,KEYPAD_ROW1_PIN);
	DIO_activePinInPullUpResistance(KEYPAD_ROW2_PORT,KEYPAD_ROW2_PIN);
	DIO_activePinInPullUpResistance(KEYPAD_ROW3_PORT,KEYPAD_ROW3_PIN);
}


void KEYPAD_GetValue(u8* ReturnedValue)  //try switch 
{
	if (ReturnedValue != NULL)
	{
		*ReturnedValue=KEYPAD_NOT_PRESSED;
		
		u8 RowsCounter,ColumnsCounter ;
		
		u8 ColumnsPort[4]={KEYPAD_COL0_PORT,KEYPAD_COL1_PORT,KEYPAD_COL2_PORT,KEYPAD_COL3_PORT};
		u8 ColumnsPins[4]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN};
	
		u8 RowsPort[4]={KEYPAD_ROW0_PORT,KEYPAD_ROW1_PORT,KEYPAD_ROW2_PORT,KEYPAD_ROW3_PORT};
     	u8 RowsPins[4]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN};
        
		u8 PinValue,PinFlag=0;
		
		u8 KEYPAD_Caracters [4][4] = KEYPAD_PATTERN;
										  
		for(ColumnsCounter=0;ColumnsCounter<4;ColumnsCounter++)
		{
			//Activate Each Column 
			DIO_SetPinValue(ColumnsPort[ColumnsCounter],ColumnsPins[ColumnsCounter],DIO_PIN_LOW);
			for (RowsCounter=0;RowsCounter<4;RowsCounter++)
			{
				//Read Rows 
				DIO_ReadValue(RowsPort[RowsCounter],RowsPins[RowsCounter],&PinValue);
				if (KEYPAD_PRESSED == PinValue)
				{
					while (KEYPAD_PRESSED == PinValue)
					{
						//block keypad to take one value for one pressed 
						DIO_ReadValue(RowsPort[RowsCounter],RowsPins[RowsCounter],&PinValue);
					}
					*ReturnedValue = KEYPAD_Caracters[RowsCounter][ColumnsCounter];
					PinFlag=1;
					break;
				}
			}
			
			if (1 ==PinFlag)
			{
				break;
			}
			//Deactivate Current Column 
			DIO_SetPinValue(ColumnsPort[ColumnsCounter],ColumnsPins[ColumnsCounter],DIO_PIN_HIGH);
		}
	} 
	else
	{
		//do nothing
	}	
}
