#include "SmartLighting_System.h"

int main(void)
{
	SmartLightingSystem_Init();
	
	while (1)
	{
		Check_MorningOrNight();
		if (MorningNight_Flag == Night_Mode)
		{
			TurnOn_GateLight();
		}
		else if (MorningNight_Flag == Morning_Mode)
		{
			TurnOff_GateLight();
			TurnOff_FirstPartLight();
			TurnOff_SecondPartLight();
		}
		else
		{
			//error
		}
	}
}