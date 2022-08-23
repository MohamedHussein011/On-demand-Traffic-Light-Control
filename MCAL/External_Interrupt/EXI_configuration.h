/*
 * Name: Mohamed Hussein 
 * Layer: MCAL
 * Version: V1.0 - 28/10/2021
 * Driver: External Interrupts
 */
 

#ifndef _EXI_CONFIGURATION_H
#define _EXI_CONFIGURATION_H

/******************************************************************************
* !comment : Select Interrupt Sense Control option:  		 	               *
*           1: LOW_LEVEL                                                     *
*           2: ON_CHANGE                                                     *
            3: FALLING_EDGE                                                     *
            4: RISING_EDGE                                         			*
******************************************************************************/
 
#define INT0_SENSE     FALLING_EDGE
#define INT1_SENSE     FALLING_EDGE
#define INT2_SENSE     FALLING_EDGE

 
 
#endif 
