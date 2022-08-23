/*
 * Name: Mohamed Hussein 
 * Layer: MCAL
 * Version: V1.0 - 15/10/2021
 * Driver: External Interrupts
 */


/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/Interrupts.h"

/* 3. MCAL Files */
#include "EXI_registers.h"
#include "EXI_private.h"
#include "EXI_configuration.h"
#include "EXI_interface.h"

/*Global pointer to function*/
void (*EXI_INT0CallBack) (void)  = NULL;
void (*EXI_INT1CallBack) (void)  = NULL;
void (*EXI_INT2CallBack) (void)  = NULL;


/* Functions Definitions */
/*initialize External Interrupt 0 with configuration you choose
 * Input: void
 * return: void
 */
void vEXI_InitINT0(void)     /* PD2 */
{
	/* Set Configuration to generate interrput */
#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR, ISC00);
	CLR_BIT(MCUCR, ISC01);
#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR, ISC00);
	CLR_BIT(MCUCR, ISC01);
#elif INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR, ISC00);
	SET_BIT(MCUCR, ISC01);
#elif INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR, ISC00);
	SET_BIT(MCUCR, ISC01);
#else
#error "wrong INT0_SENSE configuration option"
#endif

	/* Set External Interrput 0 Enable */
	SET_BIT(GICR, INT0);

}

void vEXI_InitINT1 (void)     /* PD3 */
{
	/* Set Configuration to generate interrput */
#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR, ISC10);
	CLR_BIT(MCUCR, ISC11);
#elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR, ISC10);
	CLR_BIT(MCUCR, ISC11);
#elif INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR, ISC10);
	SET_BIT(MCUCR, ISC11);
#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR, ISC10);
	SET_BIT(MCUCR, ISC11);
#else
#error "wrong INT1_SENSE configuration option"
#endif

	/* Set External Interrput 1 Enable */
	SET_BIT(GICR, INT1);

}

void vEXI_InitINT2(void)    /* PB2 */
{
	/* Set Configuration to generate interrput */
#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,ISC2);
#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,ISC2);
#else
#error "wrong INT2_SENSE configuration option"
#endif

	/* Set External Interrput 2 Enable */
	SET_BIT(GICR, INT2);
}

/*CallBack function for External Interrupt 0
 * Input: pointer to function that you need to operate at ISR
 * return: Error State uint8_t type
 */
uint8_t u8EXI_INT0SetCallBack (void (*pvFunction_t) (void) )
{
	uint8_t u8Local_Error = OK;

	if(pvFunction_t != NULL)
	{
		EXI_INT0CallBack = pvFunction_t;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}
uint8_t u8EXI_INT1SetCallBack (void (*pvFunction_t) (void) )
{
	uint8_t u8Local_Error = OK;

	if(pvFunction_t != NULL)
	{
		EXI_INT1CallBack = pvFunction_t;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;

}
uint8_t u8EXI_INT2SetCallBack (void (*pvFunction_t) (void) )
{
	uint8_t u8Local_Error = OK;

	if(pvFunction_t != NULL)
	{
		EXI_INT2CallBack = pvFunction_t;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;

}

/******************************************************************************
 * !comment  :  ISR Function EXI.  							 			      *
 ******************************************************************************/
/*INT0*/
ISR(EXT_INT0)
{
	EXI_INT0CallBack();
}

/*INT1*/
ISR(EXT_INT1)
{
	EXI_INT1CallBack();
}

/*INT2*/
ISR(EXT_INT2)
{
	EXI_INT2CallBack();
}
