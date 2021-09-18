/*
File Name:TIMER_program
Author:DohaOsama
Date:19/9/2021
Description:TIMER Driver 
version 1.1
*/
#include "../../LIB/STD_TYPES.h"//library  contains all datatypes needed in this program
#include "../../LIB/BIT_MATH.h"//library contains clear and set and get and toggle bit it will be used in this program 
#include "TIMER_interface.h"//it is a header file that contain functions prototypes and some definitions and it will be very important to the user
#include "TIMER_private.h"//it is a header file that contains information very important in the program but it is not important for the user
#include "TIMER_config.h"//it is a header file that make the TIMER_program to be flexible for all users

static void (*TIMER_pvINT0Fuction)(void)=NULL_POINTER;

void TIMER_voidPreBuiltConfiguration (u8 Copy_u8PreBuildConfiguration)
{
	switch(Copy_u8PreBuildConfiguration)
	{
		case Normal  :
		CLEAR_BIT(TIMER_TCCR0,TCCR0_WGM01);
		CLEAR_BIT(TIMER_TCCR0,TCCR0_WGM00);
		SET_BIT(TIMER_TIMSK,TIMSK_OCIE0);
		break;
		case PWMPhase :
		CLEAR_BIT(TIMER_TCCR0,TCCR0_WGM01);
		SET_BIT(TIMER_TCCR0,TCCR0_WGM00);
		SET_BIT(TIMER_TIMSK,TIMSK_TOIE0);
		break;
		case CTC :
		CLEAR_BIT(TIMER_TCCR0,TCCR0_WGM00);
		SET_BIT(TIMER_TCCR0,TCCR0_WGM01);
		SET_BIT(TIMER_TIMSK,TIMSK_OCIE0);
		break;
		case FastPWM :
		SET_BIT(TIMER_TCCR0,TCCR0_WGM00);
		SET_BIT(TIMER_TCCR0,TCCR0_WGM01);
		SET_BIT(TIMER_TIMSK,TIMSK_OCIE0);
		break;
	}
		#if CompareOUT==NormalPort
		CLEAR_BIT(TIMER_TCCR0,TCCR0_COM00);
		CLEAR_BIT(TIMER_TCCR0,TCCR0_COM01);
		#elif CompareOUT==ToggleOc0
		SET_BIT(TIMER_TCCR0,TCCR0_COM00);
		CLEAR_BIT(TIMER_TCCR0,TCCR0_COM01);
		#elif CompareOUT==ClearOC0
		CLEAR_BIT(TIMER_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER_TCCR0,TCCR0_COM01);
		#elif CompareOUT==SetOC0
		CLEAR_BIT(TIMER_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER_TCCR0,TCCR0_COM01);
		#endif
		//set the prescaler 
	    CLEAR_BIT(TIMER_TCCR0,TCCR0_CS00);
		SET_BIT(TIMER_TCCR0,TCCR0_CS01);
		CLEAR_BIT(TIMER_TCCR0,TCCR0_CS02);
	
}
 void TIMER_voidInt0SetCallBack(void(*Copy_pvNotificationFunction))
{
	TIMER_pvINT0Fuction=Copy_pvNotificationFunction;
}
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(TIMER_pvINT0Fuction!=NULL_POINTER)
	{
		TIMER_pvINT0Fuction();
	}
}
 
void TIMER0_VoidSetCompareValue(u8 Copy_u8CompareValue)
{
	
	TIMER_OCR0=Copy_u8CompareValue;
}
s32 TIMER_s32Mapping(u32 Local_u8INPUTMin,u32 Local_u32INPUTMax,u32 Local_u32OUTPUTMin,u32 Loacl_u32OUTPUTMax,u32 Local_u32INPUTValue)
{
	s32 Local_u32OUTPUTValue;
	Local_u32OUTPUTValue=(((Loacl_u32OUTPUTMax-Local_u32OUTPUTMin)/(Local_u32INPUTMax- Local_u8INPUTMin))*( Local_u32INPUTValue- Local_u8INPUTMin))-Local_u32OUTPUTMin;
	return Local_u32OUTPUTValue;
}
//timer1

//void INT0_Initiat(void)//PreBuilt Configuration


void TIMER1_VoidFastModeInitiat(void)
{
#if TIMER1_MODE==MODES_Normal
	CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10); 

	CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
	
	CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);

	CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);

	CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_WGM12); 

	CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);
	
	CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS10); 

	SET_BIT(TIMER1_TCCR1B,TCCR1B_CS11);

	CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS12); 

#elif TIMER1_MODE== MODES_FastPWM
	CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10); 

	SET_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
	
	CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0); 

	SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);

	SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM12); 

	SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);
	
	CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS10); 

	SET_BIT(TIMER1_TCCR1B,TCCR1B_CS11);

	CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS12); 
#endif
}

void TIMER1_VoidSetMode(u8 Copy_u8TIMER1MODE)
{
	switch(Copy_u8TIMER1MODE)
	{
		case MODES_Normal:
		CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10); 

		CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
	
		CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);

		CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);

		CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_WGM12); 

		CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);
	
		CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS10); 

		SET_BIT(TIMER1_TCCR1B,TCCR1B_CS11);

		CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS12); 
		break;
		case MODES_FastPWM:
		CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10); 

		SET_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
	
		CLEAR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0); 

		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);

		SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM12); 

		SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);
	
		CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS10); 

		SET_BIT(TIMER1_TCCR1B,TCCR1B_CS11);

		CLEAR_BIT(TIMER1_TCCR1B,TCCR1B_CS12); 
		break;
		
	}


}
void TIMER1_VoidSetCompareValue(u16 Copy_u16CompareValue)
{
	TIMER1_OCR1A=Copy_u16CompareValue;
}
void TIMER1_VoidTopValue(u16 Copy_u16TopValue)
{
	TIMER1_ICR1=Copy_u16TopValue;
}
	