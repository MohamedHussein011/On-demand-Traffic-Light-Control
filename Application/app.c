/*
 * app.c
 *
 *  Created on: 19/08/2022
 *      Author: Mohamed Hussein
 */

#include "../Library/BIT_MATH.h"
#include "../Library/STD_TYPE.h"

#include "../MCAL/External_interrupt/EXI_interface.h"
#include "../MCAL/Global_interrupt/GIE_interface.h"
#include "../MCAL/Timer/Timer_interface.h"
#include "../MCAL/DIO/DIO_interface.h"

#include "../ECUAL/LED/LED_interface.h"
#include "../ECUAL/Button/Button_interface.h"

#include "app.h"

#define PRESSED         0         /*Button is pressed*/
#define NOT_PRESSED     1         /*Button is Not pressed*/
#define True                1
#define False               0

/*Flag to Deactivate pedestrian's Red LED or Not*/
static uint8_t PedestrianRedLEDoff_Flag = False;
/*Global Counter for Normal mode (Car's LEDs) to count every Timer1 Interrupt making delay*/
static uint8_t u8GlobalCounter = 0;
/*Global Counter for pedestrian mode to count every Timer0 Interrupt making delay*/
static uint16_t u16GlobalCounterPedestrian = 0;
/*Global Counter for Button interrupt to make sure it's pressed once but short not long press or more than a press*/
static uint8_t u8InterruptCounterPedestrian = 0;

/*Variables to hold the state of Car's Red and green LEDs & Pedestrian's Green LED if the button is pressed*/
uint8_t u8Car_RedLED = 0;
uint8_t u8Car_GreenLED = 0;
uint8_t u8Pedestrian_GreenLED = 0;
uint8_t u8Button_state = 0;

/*Normal Mode function for Car's LEDs*/
void NormalMode(void);
/*Pedestrian Mode function to check when the button is pressed*/
void PedestrianMode(void);
/*function to take action based on the state by which the button is pressed*/
void PedestrianState(void);

void app_Start(void)
{
	/*Initialize every pin state i used, Car's Green LED is on*/
	vPORT_Init();

	/*CallBack function for Normal Mode to change patterns every five seconds*/
	u8Timer1_ComASetCallBack(NormalMode);
	/*CallBack function for Pedestrian Mode if the button is pressed*/
	u8EXI_INT0SetCallBack(PedestrianMode);

	/*Initialize Timer0 & Timer1 & External interrupt 0*/
	vTimer0_Initprebuild();
	vTimer1_Initprebuild();
	vEXI_InitINT0();

	/*Enable Global Interrupt*/
	vGlobalInterrupt_Enable();
}

void NormalMode(void)
{
	u8GlobalCounter++;
	/*Car's Green LED is now off & Yellow LED starts blinking for five seconds*/
	if(u8GlobalCounter == 5)
	{
		u8LED_OFF(DIO_PORTA,DIO_PIN0);
		u8LED_Toggle(DIO_PORTA,DIO_PIN1);
	}else if(u8GlobalCounter >= 6 && u8GlobalCounter <= 9)
	{
		u8LED_Toggle(DIO_PORTA,DIO_PIN1);
	}else if(u8GlobalCounter == 10)     /*Car's Red LED is now on for 5 seconds & Yellow LED is off */
	{
		u8LED_OFF(DIO_PORTA,DIO_PIN1);
		u8LED_ON(DIO_PORTA,DIO_PIN2);
	}else if(u8GlobalCounter == 15)    /*Car's Red LED is now off & Yellow LED starts blinking for five seconds*/
	{
		u8LED_OFF(DIO_PORTA,DIO_PIN2);
		u8LED_Toggle(DIO_PORTA,DIO_PIN1);

	}else if(u8GlobalCounter >= 16 && u8GlobalCounter <= 19)
	{
		u8LED_Toggle(DIO_PORTA,DIO_PIN1);
	}else if(u8GlobalCounter == 20)      /*Repeat the operation: Car's Green LED is now on*/
	{
		u8LED_OFF(DIO_PORTA,DIO_PIN1);
		u8LED_ON(DIO_PORTA,DIO_PIN0);
		u8GlobalCounter = 0;
	}

}

void PedestrianMode(void)
{
	u8InterruptCounterPedestrian++;

	u8DIO_ReadPinVal(DIO_PORTA,DIO_PIN2, &u8Car_RedLED);
	u8DIO_ReadPinVal(DIO_PORTA,DIO_PIN0, &u8Car_GreenLED);
	u8DIO_ReadPinVal(DIO_PORTB,DIO_PIN0, &u8Pedestrian_GreenLED);
	u8Button_Readvalue(DIO_PORTD,DIO_PIN2, &u8Button_state);

	if(u8Car_RedLED && u8InterruptCounterPedestrian <= 1)      /*if button is pressed when Car's Red LED is on*/
	{
		/*Car's Red LED is on for five seconds & pedestrian's Green LED is on too*/
		u8LED_ON(DIO_PORTB,DIO_PIN0);
		u8Timer1_SetCompValue(CHANNEL_A, 31250);  /*Re-initialize Timer1*/
		u8Timer1_SetOverFlowPreload(0);      /*Re-initialize Timer1*/
		u8GlobalCounter = 10;  /*to off car's Red LED after five seconds*/
		u8LED_ON(DIO_PORTA,DIO_PIN2);
		u8Timer0_OVSetCallBack(PedestrianState);
		u8Timer0_SetOverFlowPreload(124);     /*start timer0 to count with preload 124 to count for five seconds */
		vTimer0_EnableCOverFlowInterrupt();   /*every second takes 31 overFlows */
		PedestrianRedLEDoff_Flag = True;   /*to stop timer0 interrupt after the 5 seconds of Red LED is on*/
		u8InterruptCounterPedestrian = 0;
	}
	else if(u8Car_GreenLED && u8InterruptCounterPedestrian <= 1)    /*if button is pressed when Car's Green LED is on*/
	{
		/*pedestrian's Red LED is on for five seconds & Car's Green LED is on too*/
		u8LED_ON(DIO_PORTB,DIO_PIN2);
		u8Timer1_SetCompValue(CHANNEL_A, 31250);    /*Re-initialize Timer1*/
		u8Timer1_SetOverFlowPreload(0);      /*Re-initialize Timer1*/
		u8GlobalCounter = 0;    /*to off car's Green LED after five seconds*/
		u16GlobalCounterPedestrian = 306;   /*to off pedestrian's Red LED after five seconds*/
		u8Timer0_OVSetCallBack(PedestrianState);
		u8Timer0_SetOverFlowPreload(124);
		vTimer0_EnableCOverFlowInterrupt();
		PedestrianRedLEDoff_Flag = False;  /*to not stop timer0 interrupt after the 5 seconds of Red LED is on*/
		u8InterruptCounterPedestrian = 0;
	}
	else if(u8Car_RedLED && u8Pedestrian_GreenLED)   /*if the cars red light is on and pedestrian green light is on, nothing to be done */
	{
		/*Do nothing*/
	}
	else if(u8GlobalCounter >= 5 && u8GlobalCounter < 10 && u8InterruptCounterPedestrian <= 1)    /*if button is pressed when Car's Yellow LED is blinking*/
	{
		/*pedestrian's Red LED is on for five seconds & Car's Yellow LED is blinking*/
		u8LED_ON(DIO_PORTB,DIO_PIN2);
		u8LED_Toggle(DIO_PORTA,DIO_PIN1);
		u8Timer1_SetCompValue(CHANNEL_A, 31250);    /*Re-initialize Timer1*/
		u8Timer1_SetOverFlowPreload(0);      /*Re-initialize Timer1*/
		u8GlobalCounter = 4;    /*to Toggle car's Yellow LED for five seconds*/
		u16GlobalCounterPedestrian = 428;     /*to pedestrian's car's Yellow LED for five seconds*/
		u8Timer0_OVSetCallBack(PedestrianState);
		u8Timer0_SetOverFlowPreload(124);
		vTimer0_EnableCOverFlowInterrupt();
		PedestrianRedLEDoff_Flag = False;     /*to not stop timer0 interrupt after the 5 seconds of Red LED is on*/
		u8InterruptCounterPedestrian = 0;
	}
	else if(u8GlobalCounter >= 15 && u8GlobalCounter < 20 && u8InterruptCounterPedestrian <= 1)    /*if button is pressed when Car's Yellow LED is blinking*/
	{
		/*pedestrian's Red LED is on for five seconds & Car's Yellow LED is blinking*/
		u8LED_ON(DIO_PORTB,DIO_PIN2);
		u8LED_Toggle(DIO_PORTA,DIO_PIN1);
		u8Timer1_SetCompValue(CHANNEL_A, 31250);      /*Re-initialize Timer1*/
		u8Timer1_SetOverFlowPreload(0);      /*Re-initialize Timer1*/
		u8GlobalCounter = 4;       /*to Toggle car's Yellow LED for five seconds*/
		u16GlobalCounterPedestrian = 428;    /*to pedestrian's car's Yellow LED for five seconds*/
		u8Timer0_OVSetCallBack(PedestrianState);
		u8Timer0_SetOverFlowPreload(124);   /*Re-initialize Timer0*/
		vTimer0_EnableCOverFlowInterrupt();
		PedestrianRedLEDoff_Flag = False;       /*to not stop timer0 interrupt after the 5 seconds of Red LED is on*/
		u8InterruptCounterPedestrian = 0;
	}

	u8InterruptCounterPedestrian = 0;
}

void PedestrianState(void)
{
	u16GlobalCounterPedestrian++;

	/*pedestrian's Green LED is now off & Yellow LED starts blinking for five seconds*/
	if(u16GlobalCounterPedestrian == 153)
	{
		u8LED_OFF(DIO_PORTB,DIO_PIN0);
		u8LED_Toggle(DIO_PORTB,DIO_PIN1);
	}else if(u16GlobalCounterPedestrian == 184 || u16GlobalCounterPedestrian == 214 || u16GlobalCounterPedestrian == 245 || u16GlobalCounterPedestrian == 275)
	{
		u8LED_Toggle(DIO_PORTB,DIO_PIN1);
	}else if(u16GlobalCounterPedestrian == 306)      /*pedestrian's Red LED is now on for 5 seconds & Yellow LED is off */
	{
		u8LED_OFF(DIO_PORTB,DIO_PIN1);
		u8LED_ON(DIO_PORTB,DIO_PIN2);
	}else if(u16GlobalCounterPedestrian == 458)   /*pedestrian's Red LED is now off & Yellow LED starts blinking for five seconds*/
	{
		u8LED_OFF(DIO_PORTB,DIO_PIN2);
		if(PedestrianRedLEDoff_Flag)
		{
			u16GlobalCounterPedestrian = 0;        /*Reset the counter and Disable the interrupt*/
			vTimer0_DisableOverFlowInterrupt();
		}else
			u8LED_Toggle(DIO_PORTB,DIO_PIN1);
	}else if(u16GlobalCounterPedestrian == 489 || u16GlobalCounterPedestrian == 519 || u16GlobalCounterPedestrian == 550 || u16GlobalCounterPedestrian == 580)
	{
		u8LED_Toggle(DIO_PORTB,DIO_PIN1);
	}else if(u16GlobalCounterPedestrian == 611)   /*pedestrian's Green LED is now on for 5 seconds & Yellow LED is off */
	{
		u8LED_OFF(DIO_PORTB,DIO_PIN1);
		u8LED_ON(DIO_PORTB,DIO_PIN0);
	}else if(u16GlobalCounterPedestrian == 763)     /*pedestrian's Green LED is now off & Red LED is now on for 5 seconds*/
	{
		u8LED_OFF(DIO_PORTB,DIO_PIN0);
		u8LED_ON(DIO_PORTB,DIO_PIN2);
	}else if(u16GlobalCounterPedestrian == 916)       /*pedestrian's Red LED is now off*/
	{
		u8LED_OFF(DIO_PORTB,DIO_PIN2);
		u16GlobalCounterPedestrian = 0;        /*Reset the counter and Disable the interrupt*/
		vTimer0_DisableOverFlowInterrupt();
	}
}
