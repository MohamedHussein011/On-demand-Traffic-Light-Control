/*
 * Name: Mohamed Hussein
 * Layer: ECUAL
 * Version: V1.0 - 15/10/2021
 *
 */

#ifndef _BUTTON_INTERFACE_H
#define _BUTTON_INTERFACE_H


/* Fucntions Prototype */

uint8_t u8Button_Init(EN_PORT_t PortId, EN_PIN_t PinId);
uint8_t u8Button_Readvalue (EN_PORT_t PortId, EN_PIN_t PinId, uint8_t *u8Copy_Value);

#endif
