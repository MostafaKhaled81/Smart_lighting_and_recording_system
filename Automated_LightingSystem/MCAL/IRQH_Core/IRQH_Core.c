/*
 * IRQH_Core.c
 *
 * Created: 9/1/2023 5:48:17 PM
 *  Author: mk591
 */ 
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
#include "IRQH_Core.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void(*CallBack_PtrFunc[20])(void) = {Null};
	extern uint32 TIMER0_Number_OVRflows_g;
	extern uint32 TIMER0_Init_Value_g;
	
	extern uint32 TIMER2_Number_OVRflows_g ;
	extern uint32 TIMER2_Init_Value_g ;
	
	extern uint16 Timer0_INT_CNT;
	extern uint16 Timer2_INT_CNT;
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
* \Syntax          : void IRQH_SetGlobalINT(uint8)
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void IRQH_SetGlobalINT(uint8 Global_INT_Status)
{
	switch (Global_INT_Status)
	{
		case INT_ENABLE:
		SET_BIT(SREG,7);
		break;
		case INT_DISABLE:
		CLR_BIT(SREG,7);
		break;
		default:
		break;
	}
}

/******************************************************************************
* \Syntax          : void IRQH_SetExternalINIT(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void IRQH_SetExternalINIT(void)
{
	#if (INT_0 == INT_ENABLE)
	  SET_BIT(GICR,6);
	  #if (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_LOW_LEVEL)
	  CLR_BIT(MCUCR,0);
	  CLR_BIT(MCUCR,1);
	  #elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_LOGICAL_CHANGE)
	  SET_BIT(MCUCR,0);
	  CLR_BIT(MCUCR,1);
	  #elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	  CLR_BIT(MCUCR,0);
	  SET_BIT(MCUCR,1);
	  #elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	  SET_BIT(MCUCR,0);
	  SET_BIT(MCUCR,1);
	  #endif
	#endif
	
	#if (INT_1 == INT_ENABLE)
	  SET_BIT(GICR,7);
	  #if (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_LOW_LEVEL)
	  CLR_BIT(MCUCR,2);
	  CLR_BIT(MCUCR,3);
	  #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_LOGICAL_CHANGE)
	  SET_BIT(MCUCR,2);
	  CLR_BIT(MCUCR,3);
	  #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	  CLR_BIT(MCUCR,2);
	  SET_BIT(MCUCR,3);
	  #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	  SET_BIT(MCUCR,2);
	  SET_BIT(MCUCR,3);
	  #endif
	#endif
	
	#if (INT_2 == INT_ENABLE)
	  SET_BIT(GICR,5);
	  #if (EXT_INT2_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	  CLR_BIT(MCUCR,6);
	  #elif (EXT_INT2_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	  SET_BIT(MCUCR,6);
	  #endif
	#endif
}

/******************************************************************************
* \Syntax          : void IRQH_SetCallBack(uint8 Intrrupt_Vector_Index,void(*p)(void))
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void IRQH_SetCallBack(uint8 Intrrupt_Vector_Index,void(*p)(void))
{
	CallBack_PtrFunc[Intrrupt_Vector_Index]=p;
}

ISR(INT0_vect)
{
	if (CallBack_PtrFunc[External_Interrupt_Request_0_VECTOR_INDEX]!=Null)
	{
		(*CallBack_PtrFunc[External_Interrupt_Request_0_VECTOR_INDEX])();
	}
}

ISR(INT1_vect)
{
	if (CallBack_PtrFunc[External_Interrupt_Request_1_VECTOR_INDEX]!=Null)
	{
		(*CallBack_PtrFunc[External_Interrupt_Request_1_VECTOR_INDEX])();
	}
}

ISR(TIMER0_OVF_vect)
{	
	Timer0_INT_CNT++;
	
	if(Timer0_INT_CNT == TIMER0_Number_OVRflows_g)
	{
		(*CallBack_PtrFunc[Timer_Counter0_Overflow_VECTOR_INDEX])();
	}
}

ISR(TIMER2_OVF_vect)
{	
	Timer2_INT_CNT++;
	
	if(Timer2_INT_CNT == TIMER2_Number_OVRflows_g)
	{
		(*CallBack_PtrFunc[Timer_Counter2_Overflow_VECTOR_INDEX])();
	}
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/