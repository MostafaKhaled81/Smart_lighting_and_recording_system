

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TIMER_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint32 TIMER0_Number_OVRflows_g = 0;
uint32 TIMER0_Init_Value_g = 0;
uint32 TIMER2_Number_OVRflows_g = 0;
uint32 TIMER2_Init_Value_g = 0;
uint16 Timer0_INT_CNT = 0;
uint16 Timer2_INT_CNT = 0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void TIMER_Init(void)
* \Description     : Timers initialization
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void TIMER_Init(void)
{
	uint8 MCU_CLK_us = 16000000 / 1000000 ;
	
	/** Timer0 Operation Mode **/
	 CLR_BIT(TCCR0 , 3);
	 CLR_BIT(TCCR0 , 6);
	 
	 /*enable_int TIMER0*/
	  SET_BIT(TIMSK,0);
		  
	uint8 Timer0Tick_Time_us = TIMER0_PRESCALER / MCU_CLK_us ;
	
	uint32 Time0_ms = TIMER0_COUNTED_mS;
	uint32 Timer0Total_Ticks = (Time0_ms*1000) / Timer0Tick_Time_us;
	TIMER0_Number_OVRflows_g = Timer0Total_Ticks / 256 ;
	TIMER0_Init_Value_g = 256 -( Timer0Total_Ticks % 256) ;
	
	if( Timer0Total_Ticks % 256 != 0)
	{
		 TIMER0_Number_OVRflows_g++;
	}
	/** Timer2 Operation Mode **/
	 CLR_BIT(TCCR2 , 3);
	 CLR_BIT(TCCR2 , 6);
	
	/*enable_int TIMER2*/
	 SET_BIT(TIMSK,6);
	
	uint8 Timer2Tick_Time_us = TIMER2_PRESCALER / MCU_CLK_us ;
	
	uint32 Time2_ms = TIMER2_COUNTED_mS;
	uint32 Timer2Total_Ticks = (Time2_ms*1000) / Timer2Tick_Time_us;
	TIMER2_Number_OVRflows_g = Timer2Total_Ticks / 256 ;
	TIMER2_Init_Value_g = 256 -( Timer2Total_Ticks % 256) ;
	
	 if( Timer2Total_Ticks % 256 != 0)
	 {
	   TIMER2_Number_OVRflows_g++;
	 }
}

/******************************************************************************
* \Syntax          : void TIMER0_on(void)
* \Description     : Set the prescaller and enable timer0
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TIMER0_on(void)
{
	Timer0_INT_CNT = 0;
	
	TCNT0 = TIMER0_Init_Value_g ;
	
	/*TIMER0_PRESCALER == CLK_SRC_PRESCALING_1024*/
	TCCR0 |= 0X05;
}

/******************************************************************************
* \Syntax          : void TIMER0_off(void)
* \Description     : Disable Timer 0 by set the prescaller =0
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TIMER0_off(void)
{
	/*TIMER0_PRESCALER == 0*/
	TCCR0 |= 0X00;
}

/******************************************************************************
* \Syntax          : void TIMER2_on(void)
* \Description     : Set the prescaller and enable timer2
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TIMER2_on(void)
{
	Timer2_INT_CNT = 0;
	
	TCNT2 = TIMER2_Init_Value_g ;
	
	/*TIMER2_PRESCALER == CLK_SRC_PRESCALING_1024*/
	TCCR2 |= 0X07;
}

/******************************************************************************
* \Syntax          : void TIMER2_off(void)
* \Description     : Disable Timer 2 by set the prescaller =0
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TIMER2_off(void)
{
	/*TIMER2_PRESCALER == 0*/
	TCCR2 |= 0X00;
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/

