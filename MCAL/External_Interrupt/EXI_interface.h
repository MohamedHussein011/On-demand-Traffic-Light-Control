/*
 * Name: Mohamed Hussein 
 * Layer: MCAL
 * Version: V1.0 - 15/10/2021
 * Driver: External Interrupts
 */
 
 
#ifndef _EXI_INTERFACE_H
#define _EXI_INTERFACE_H


/* Fucntions Prototype */
void vEXI_InitINT0(void);    /* PD2 */
void vEXI_InitINT1(void);    /* PD3 */
void vEXI_InitINT2(void);    /* PB2 */

/* Call Back Functions for ISR*/
uint8_t u8EXI_INT0SetCallBack (void (*pvFunction_t) (void));
uint8_t u8EXI_INT1SetCallBack (void (*pvFunction_t) (void));
uint8_t u8EXI_INT2SetCallBack (void (*pvFunction_t) (void));

#endif 
