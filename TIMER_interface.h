/*File Name:TIMER_interface
Author:DohaOsama
Date:19/9/2021 
version 1.1
*/
#ifndef TIMER_INTERFACE

#define TIMER_INTERFACE

#define Normal  0

#define PWMPhase 1//phase correct mode

#define CTC  	2

#define FastPWM 3

#define MODES_Normal 0

#define MODES_FastPWM 14
void TIMER_voidPreBuiltConfiguration (u8 Copy_u8PreBuildConfiguration);

void TIMER_VoidSetCallBack(void(* Copy_NotificationFunc)(void));

void TIMER0_VoidSetCompareValue(u8 Copy_u8CompareValue);

s32 TIMER_s32Mapping(u32 Local_u8INPUTMin,u32 Local_u32INPUTMax,u32 Local_u32OUTPUTMin,u32 Loacl_u32OUTPUTMax,u32 Local_u32INPUTValue);

void TIMER1_VoidFastModeInitiat(void);

void TIMER1_VoidSetMode(u8 Copy_u8TIMER1MODE);

void TIMER1_VoidSetCompareValue(u16 Copy_u16CompareValue);

void TIMER1_VoidTopValue(u16 Copy_u16TopValue);


#endif