/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 23/10/2021
 *
 */
 
#ifndef _TIMER_INTERFACE_H
#define _TIMER_INTERFACE_H


typedef enum {
	NormalTimermode,
	PWM_phasecorrectmode,
	CTCmode,
	Fast_PWMmode,
}EN_TimerMode_t;

typedef enum {
	NormalTimer1mode,
	CTC_OCR1A_TOPmode,
	CTC_ICR1_TOPmode,
	Fast_PWM_ICR1mode,
	Fast_PWM_OCR1Amode
}EN_Timer1Mode_t;

typedef enum {
	Timer_Stop,
	Timer_Noprescaler,
	Timer_prescaler8,
	Timer_prescaler64,
	Timer_prescaler256,
	Timer_prescaler1024
}EN_TimerPrescaler_t;

typedef enum {
	Timer2_Stop,
	Timer2_Noprescaler,
	Timer2_prescaler8,
	Timer2_prescaler32,
	Timer2_prescaler64,
	Timer2_prescaler128,
	Timer2_prescaler256,
	Timer2_prescaler1024,
}EN_Timer2Prescaler_t;

/*Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.*/
#define SET_AT_TOP_CLEAR_AT_COMPARE			1       /*Non Inverted mode --> duty cycle = comp value / 2^n*/

/*Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting*/
#define CLEAR_AT_TOP_SET_AT_COMPARE			2       /*Inverted mode --> duty cycle = 1 - (comp value / 2^n)*/
#define NORMAL_OPERATION                    3
#define TOGGLE                              4   //OC0 in normal mode

#define CHANNEL_A              0
#define CHANNEL_B              1

#define ICU_RISING_EDGE            0
#define ICU_FALLING_EDGE           1


/****************************************Timer initialize**************************************************/
void vTimer0_Initprebuild (void);           /*prebuild function*/
uint8_t vTimer0_Initpostbuild (EN_TimerMode_t ENcopy_mode, EN_TimerPrescaler_t ENcopy_prescaler);        /*postbuild function*/

void vTimer1_Initprebuild (void);
uint8_t vTimer1_Initpostbuild (EN_Timer1Mode_t ENcopy_mode, EN_TimerPrescaler_t ENcopy_prescaler);

void vTimer2_Initprebuild (void);
void vTimer2_Initpostbuild (EN_TimerMode_t ENcopy_mode, EN_Timer2Prescaler_t ENcopy_prescaler);

/****************************************Timer0 Post Configurations****************************************/
uint8_t u8Timer0_OVSetCallBack(void (*pvcopy_CallBackFunction) (void));
uint8_t u8Timer0_CTCSetCallBack(void (*pvcopy_CallBackFunction) (void));
uint8_t u8Timer0_SetOverFlowPreload(uint8_t u8copy_Value);
void vTimer0_SetCompMatchValue(uint8_t u8copy_Value);
void vTimer0_DisableOverFlowInterrupt(void);
void vTimer0_EnableCOverFlowInterrupt(void);
void vTimer0_DisableCompareMatchInterrupt(void);
void vTimer0_EnableCompareMatchInterrupt(void);
uint8_t  u8Timer0_SetCompareMatchMode(uint8_t u8Copy_Mode);
/**********************************************************************************************************/

/****************************************Timer1 Post Configurations****************************************/
uint8_t u8Timer1_OVSetCallBack(void   (*pvcopy_CallBackFunction) (void));
uint8_t u8Timer1_ComBSetCallBack(void (*pvcopy_CallBackFunction) (void));
uint8_t u8Timer1_ComASetCallBack(void (*pvcopy_CallBackFunction) (void));
uint8_t u8Timer1_CESetCallBack(void   (*pvcopy_CallBackFunction) (void));
uint8_t  u8Timer1_SetCompareMatchMode(uint8_t u8copy_ChannelID, uint8_t u8Copy_Mode);
uint8_t u8Timer1_SetCompValue(uint8_t u8Copy_Channel, uint16_t u16Copy_Value);
void vTimer1_DisableCompareMatchInterrupt(uint8_t u8copy_ChannelID);
void vTimer1_EnableCompareMatchInterrupt (uint8_t u8copy_ChannelID);
void vTimer1_DisableOverFlowInterrupt(void);
void vTimer1_EnableOverFlowInterrupt(void);
uint8_t u8Timer1_SetOverFlowPreload(uint16_t u16Copy_TCNT1);
void vTimer1_SetICRValue(uint16_t u16Copy_ICR);
void vTimer1_ICUInit(void);
void vTimer1_ICUResetTimer(void);
uint16_t  u16Timer1_ICUGetTimerRead(void);
void vTimer1_ICUSetEdge(uint8_t u8copy_EdgeId);
void vTimer1_ICUDeInit(void);
void vTimer1_DisableICUInterrupt(void);
void vTimer1_EnableCICUInterrupt(void);
/**********************************************************************************************************/

/****************************************Timer2 Post Configurations****************************************/
uint8_t u8Timer2_OVSetCallBack(void (*pvcopy_CallBackFunction) (void));
uint8_t u8Timer2_CTCSetCallBack(void (*pvcopy_CallBackFunction) (void));
void vTimer2_SetOverFlowPreload(uint8_t u8copy_Value);
void vTimer2_SetCompMatchValue(uint8_t u8copy_Value);
void vTimer2_DisableOverFlowInterrupt(void);
void vTimer2_EnableOverFlowInterrupt(void);
void vTimer2_DisableCompareMatchInterrupt(void);
void vTimer2_EnableCompareMatchInterrupt(void);
uint8_t  u8Timer2_SetCompareMatchMode(uint8_t u8Copy_Mode);
/**********************************************************************************************************/

#endif 
