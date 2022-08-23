/*
 * Name: Mohamed Hussein
 * Layer: ECUAL
 * Version: V1.0 - 15/10/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"

/* 3. MCAL Files */
#include "../../MCAL/DIO/DIO_interface.h"

/* 4. ECUAL Files */
#include "Button_interface.h"

/* Functions Definitions */
uint8_t u8Button_Init(EN_PORT_t PortId, EN_PIN_t PinId)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7)
	{
		u8DIO_PinDir (PortId, PinId, DIO_INPUT);
		u8DIO_PinVal (PortId, PinId, DIO_HIGH);
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

/*Read Button Pin current state
 * Input: takes Port name & Pin number & pointer that points to a variable you want to save value in it
 * return: Error State
 */
uint8_t u8Button_Readvalue (EN_PORT_t PortId, EN_PIN_t PinId, uint8_t *u8Copy_Value)
{
	uint8_t u8Local_Error = OK;

	if(PortId <= DIO_PORTD && PinId <= DIO_PIN7 && u8Copy_Value != NULL)
	{
		u8DIO_ReadPinVal(PortId, PinId, u8Copy_Value);;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
