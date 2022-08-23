/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 01/10/2021
 * Driver: DIO - Digital Input Output
 */

#ifndef _DIO_CONFIGURATION_H
#define _DIO_CONFIGURATION_H

/******************************************************************************
 * !comment : Select Direction for PORTA option:  		    	                 *
 *           1: 0                  -----> INPUT                               *
 *           2: 1                  -----> OUTPUT                              *
 ******************************************************************************/
#define PORTA_PIN0_DIR                1
#define PORTA_PIN1_DIR                1
#define PORTA_PIN2_DIR                1
#define PORTA_PIN3_DIR                0
#define PORTA_PIN4_DIR                0
#define PORTA_PIN5_DIR                0
#define PORTA_PIN6_DIR                0
#define PORTA_PIN7_DIR                0

/******************************************************************************
 * !comment : Select Direction for PORTB option:  		    	                 *
 *           1: 0                  -----> INPUT                               *
 *           2: 1                  -----> OUTPUT                              *
 ******************************************************************************/
#define PORTB_PIN0_DIR                1
#define PORTB_PIN1_DIR                1
#define PORTB_PIN2_DIR                1
#define PORTB_PIN3_DIR                0
#define PORTB_PIN4_DIR                0
#define PORTB_PIN5_DIR                0
#define PORTB_PIN6_DIR                0
#define PORTB_PIN7_DIR                0

/******************************************************************************
 * !comment : Select Direction for PORTC option:  		    	                 *
 *           1: 0                  -----> INPUT                               *
 *           2: 1                  -----> OUTPUT                              *
 ******************************************************************************/
#define PORTC_PIN0_DIR                0
#define PORTC_PIN1_DIR                0
#define PORTC_PIN2_DIR                0
#define PORTC_PIN3_DIR                0
#define PORTC_PIN4_DIR                0
#define PORTC_PIN5_DIR                0
#define PORTC_PIN6_DIR                0
#define PORTC_PIN7_DIR                0

/******************************************************************************
 * !comment : Select Direction for PORTD option:  		    	                 *
 *           1: 0                  -----> INPUT                               *
 *           2: 1                  -----> OUTPUT                              *
 ******************************************************************************/
#define PORTD_PIN0_DIR                0
#define PORTD_PIN1_DIR                0
#define PORTD_PIN2_DIR                0
#define PORTD_PIN3_DIR                0
#define PORTD_PIN4_DIR                0
#define PORTD_PIN5_DIR                0
#define PORTD_PIN6_DIR                0
#define PORTD_PIN7_DIR                0

/******************************************************************************
 * !comment : Select Initial Value for every PIN for PORTA option:             *
 *           1: 0                  -----> LOW or Floating                      *
 *           2: 1                  -----> HIGH or PULLED-UP                    *
 ******************************************************************************/
#define PORTA_PIN0_INITIAL_VALUE                1
#define PORTA_PIN1_INITIAL_VALUE                0
#define PORTA_PIN2_INITIAL_VALUE                0
#define PORTA_PIN3_INITIAL_VALUE                0
#define PORTA_PIN4_INITIAL_VALUE                0
#define PORTA_PIN5_INITIAL_VALUE                0
#define PORTA_PIN6_INITIAL_VALUE                0
#define PORTA_PIN7_INITIAL_VALUE                0

/******************************************************************************
 * !comment : Select Initial Value for every PIN for PORTB option:             *
 *           1: 0                  -----> LOW or Floating                      *
 *           2: 1                  -----> HIGH or PULLED-UP                    *
 ******************************************************************************/
#define PORTB_PIN0_INITIAL_VALUE                0
#define PORTB_PIN1_INITIAL_VALUE                0
#define PORTB_PIN2_INITIAL_VALUE                0
#define PORTB_PIN3_INITIAL_VALUE                0
#define PORTB_PIN4_INITIAL_VALUE                0
#define PORTB_PIN5_INITIAL_VALUE                0
#define PORTB_PIN6_INITIAL_VALUE                0
#define PORTB_PIN7_INITIAL_VALUE                0

/******************************************************************************
 * !comment : Select Initial Value for every PIN for PORTC option:             *
 *           1: 0                  -----> LOW or Floating                      *
 *           2: 1                  -----> HIGH or PULLED-UP                    *
 ******************************************************************************/
#define PORTC_PIN0_INITIAL_VALUE                0
#define PORTC_PIN1_INITIAL_VALUE                0
#define PORTC_PIN2_INITIAL_VALUE                0
#define PORTC_PIN3_INITIAL_VALUE                0
#define PORTC_PIN4_INITIAL_VALUE                0
#define PORTC_PIN5_INITIAL_VALUE                0
#define PORTC_PIN6_INITIAL_VALUE                0
#define PORTC_PIN7_INITIAL_VALUE                0

/******************************************************************************
 * !comment : Select Initial Value for every PIN for PORTD option:             *
 *           1: 0                  -----> LOW or Floating                      *
 *           2: 1                  -----> HIGH or PULLED-UP                    *
 ******************************************************************************/
#define PORTD_PIN0_INITIAL_VALUE                0
#define PORTD_PIN1_INITIAL_VALUE                0
#define PORTD_PIN2_INITIAL_VALUE                1
#define PORTD_PIN3_INITIAL_VALUE                0
#define PORTD_PIN4_INITIAL_VALUE                0
#define PORTD_PIN5_INITIAL_VALUE                0
#define PORTD_PIN6_INITIAL_VALUE                0
#define PORTD_PIN7_INITIAL_VALUE                0



#endif /* DIO_CONFIGURATION_H_ */
