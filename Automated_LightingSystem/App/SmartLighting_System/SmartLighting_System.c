/*
 * SmartLighting_System.c
 *
 * Created: 3/1/2024 12:49:15 AM
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
#include "SmartLighting_System.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 MorningNight_Flag=0;

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
* \Syntax          : void SmartLightingSystem_Inti(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void SmartLightingSystem_Init(void)
{
	PORT_INIT();
	IRQH_SetGlobalINT(INT_ENABLE);
	IRQH_SetExternalINIT();
	TIMER_Init();
	BH1750_Init();
	void (*ptr_FirstPartLight)(void)=&TurnOn_FirstPartLight;
	void (*ptr_SecondPartLight)(void)=&TurnOn_SecondPartLight;
	void (*ptr_FirstPartLight_OFF)(void)=&TurnOff_FirstPartLight;
	void (*ptr_SecondPartLight_OFF)(void)=&TurnOff_SecondPartLight;
	IRQH_SetCallBack(External_Interrupt_Request_0_VECTOR_INDEX,ptr_FirstPartLight);
	IRQH_SetCallBack(External_Interrupt_Request_1_VECTOR_INDEX,ptr_SecondPartLight);
	IRQH_SetCallBack(Timer_Counter0_Overflow_VECTOR_INDEX,ptr_FirstPartLight_OFF);
	IRQH_SetCallBack(Timer_Counter2_Overflow_VECTOR_INDEX,ptr_SecondPartLight_OFF);
}

/******************************************************************************
* \Syntax          : void Check_MorningOrNight(void)
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void Check_MorningOrNight(void)
{
	uint16 LightIntinsity=0;
	LightIntinsity=BH1750_ReadData();
	if (LightIntinsity >= Transitional_LightingIntenisity)
	{
		MorningNight_Flag=Morning_Mode;
	}
	else if (LightIntinsity < Transitional_LightingIntenisity)
	{
		MorningNight_Flag=Night_Mode;
	}
	else
	{
		//error
	}
}

/******************************************************************************
* \Syntax          : void TurnOn_GateLight(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TurnOn_GateLight(void)
{
	DIO_WriteChannel(Gate_Pin,PIN_HIGH);
}

/******************************************************************************
* \Syntax          : void TurnOff_GateLight(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TurnOff_GateLight(void)
{
	DIO_WriteChannel(Gate_Pin,PIN_LOW);
}

/******************************************************************************
* \Syntax          : void TurnOn_FirstPartLight(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TurnOn_FirstPartLight(void)
{
	if (MorningNight_Flag == Night_Mode)
	{
		DIO_WriteChannel(FirstPart_Pin,PIN_HIGH);
		TIMER0_on();
	}
}

/******************************************************************************
* \Syntax          : void TurnOff_FirstPartLight(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TurnOff_FirstPartLight(void)
{
	DIO_WriteChannel(FirstPart_Pin,PIN_LOW);
	TIMER0_off();
}

/******************************************************************************
* \Syntax          : void TurnOn_SecondPartLight(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TurnOn_SecondPartLight(void)
{
	if(MorningNight_Flag == Night_Mode)
	{
		DIO_WriteChannel(SecondPart_Pin,PIN_HIGH);
		TIMER2_on();
	}
}

/******************************************************************************
* \Syntax          : void TurnOff_SecondPartLight(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void TurnOff_SecondPartLight(void)
{
	DIO_WriteChannel(SecondPart_Pin,PIN_LOW);
	TIMER2_off();
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
