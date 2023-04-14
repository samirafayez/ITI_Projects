/*
 * GPIO.c
 *
 *  Created on: Feb 16, 2023
 *      Author: HP
 */

#include "std_defines.h"
#include "bit_math.h"
#include "01_GPIO/GPIO.h"
#include "01_GPIO/GPIO_prv.h"
#include "00_RCC/RCC.h"






GPIO_tenuErrorStatus GPIO_Init(GPIOcgf_t * Add_pu8cfgstruct)
{
	GPIO_tenuErrorStatus Loc_u8State = GPIO_enuOK;

	switch (Add_pu8cfgstruct->PORT)
	{

	case GPIO_PORTA:
		RCC_Peripheral_EnableSysClk(AHB1, GPIOA);

		if(Add_pu8cfgstruct->SPEED == GPIO_SPEED_LOW)
		{
			CLR_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));

		}
		else if (Add_pu8cfgstruct->SPEED == GPIO_SPEED_MEDIUM)
		{
			SET_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if(Add_pu8cfgstruct->SPEED == GPIO_SPEED_HIGH)
		{
			CLR_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if (Add_pu8cfgstruct->SPEED == GPIO_SPEED_VERYHIGH)
		{
			SET_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOA_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else
		{
			Loc_u8State = GPIO_enuNotOK;
		}


		if(Add_pu8cfgstruct->MODE == GPIO_PIN_PD || Add_pu8cfgstruct->MODE == GPIO_PIN_PU)
		{
			CLR_BIT(GPIOA_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOA_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));

			if(Add_pu8cfgstruct->MODE == GPIO_PIN_PD)
			{
				CLR_BIT(GPIOA_REG->GPIOx_PUPDR ,(Add_pu8cfgstruct->PIN)*2);
				SET_BIT(GPIOA_REG->GPIOx_PUPDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
			}
			else if(Add_pu8cfgstruct->MODE == GPIO_PIN_PU)
			{
				SET_BIT(GPIOA_REG->GPIOx_PUPDR ,(Add_pu8cfgstruct->PIN)*2);
				CLR_BIT(GPIOA_REG->GPIOx_PUPDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
			}


		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_PP || Add_pu8cfgstruct->MODE == GPIO_MODE_OPENDRAIN)
		{
			SET_BIT(GPIOA_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOA_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));

			if(Add_pu8cfgstruct->MODE == GPIO_MODE_PP)
			{
				CLR_BIT(GPIOA_REG->GPIOx_OTYPER ,Add_pu8cfgstruct->PIN );
			}
			else if(Add_pu8cfgstruct->MODE == GPIO_MODE_OPENDRAIN)
			{
				SET_BIT(GPIOA_REG->GPIOx_OTYPER ,Add_pu8cfgstruct->PIN );
			}
		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_ALTFUN )
		{
			CLR_BIT(GPIOA_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOA_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_ANALOG)
		{
			SET_BIT(GPIOA_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOA_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}

		break;
	case GPIO_PORTB:
		RCC_Peripheral_EnableSysClk(AHB1, GPIOB);

		if(Add_pu8cfgstruct->SPEED == GPIO_SPEED_LOW)
		{
			CLR_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if (Add_pu8cfgstruct->SPEED == GPIO_SPEED_MEDIUM)
		{
			SET_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if(Add_pu8cfgstruct->SPEED == GPIO_SPEED_HIGH)
		{
			CLR_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if (Add_pu8cfgstruct->SPEED == GPIO_SPEED_VERYHIGH)
		{
			SET_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOB_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else
		{
			Loc_u8State = GPIO_enuNotOK;
		}

		if(Add_pu8cfgstruct->MODE == GPIO_PIN_PD || Add_pu8cfgstruct->MODE == GPIO_PIN_PU)
		{
			CLR_BIT(GPIOB_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOB_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));

			if(Add_pu8cfgstruct->MODE == GPIO_PIN_PD)
			{
				CLR_BIT(GPIOB_REG->GPIOx_PUPDR ,(Add_pu8cfgstruct->PIN)*2);
				SET_BIT(GPIOB_REG->GPIOx_PUPDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
			}
			else if(Add_pu8cfgstruct->MODE == GPIO_PIN_PU)
			{
				SET_BIT(GPIOB_REG->GPIOx_PUPDR ,(Add_pu8cfgstruct->PIN)*2);
				CLR_BIT(GPIOB_REG->GPIOx_PUPDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
			}
		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_PP || Add_pu8cfgstruct->MODE == GPIO_MODE_OPENDRAIN)
		{
			SET_BIT(GPIOB_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOB_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));

			if(Add_pu8cfgstruct->MODE == GPIO_MODE_PP)
			{
				CLR_BIT(GPIOB_REG->GPIOx_OTYPER ,Add_pu8cfgstruct->PIN );
			}
			else if(Add_pu8cfgstruct->MODE == GPIO_MODE_OPENDRAIN)
			{
				SET_BIT(GPIOB_REG->GPIOx_OTYPER ,Add_pu8cfgstruct->PIN );
			}
		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_ALTFUN )
		{
			CLR_BIT(GPIOB_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOB_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_ANALOG)
		{
			SET_BIT(GPIOB_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOB_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		break;
	case GPIO_PORTC:
		RCC_Peripheral_EnableSysClk(AHB1, GPIOC);

		if(Add_pu8cfgstruct->SPEED == GPIO_SPEED_LOW)
		{
			CLR_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if (Add_pu8cfgstruct->SPEED == GPIO_SPEED_MEDIUM)
		{
			SET_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if(Add_pu8cfgstruct->SPEED == GPIO_SPEED_HIGH)
		{
			CLR_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if (Add_pu8cfgstruct->SPEED == GPIO_SPEED_VERYHIGH)
		{
			SET_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOC_REG->GPIOx_OSPEEDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else
		{
			Loc_u8State = GPIO_enuNotOK;
		}

		if(Add_pu8cfgstruct->MODE == GPIO_PIN_PD || Add_pu8cfgstruct->MODE == GPIO_PIN_PU)
		{

			CLR_BIT(GPIOC_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOC_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));

			if(Add_pu8cfgstruct->MODE == GPIO_PIN_PD)
			{
				CLR_BIT(GPIOC_REG->GPIOx_PUPDR ,(Add_pu8cfgstruct->PIN)*2);
				SET_BIT(GPIOC_REG->GPIOx_PUPDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
			}
			else if(Add_pu8cfgstruct->MODE == GPIO_PIN_PU)
			{
				SET_BIT(GPIOC_REG->GPIOx_PUPDR ,(Add_pu8cfgstruct->PIN)*2);
				CLR_BIT(GPIOC_REG->GPIOx_PUPDR ,(((Add_pu8cfgstruct->PIN)*2)+1));
			}


		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_PP || Add_pu8cfgstruct->MODE == GPIO_MODE_OPENDRAIN)
		{
			SET_BIT(GPIOC_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			CLR_BIT(GPIOC_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));

			if(Add_pu8cfgstruct->MODE == GPIO_MODE_PP)
			{
				CLR_BIT(GPIOC_REG->GPIOx_OTYPER ,Add_pu8cfgstruct->PIN );
			}
			else if(Add_pu8cfgstruct->MODE == GPIO_MODE_OPENDRAIN)
			{
				SET_BIT(GPIOC_REG->GPIOx_OTYPER ,Add_pu8cfgstruct->PIN );
			}
		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_ALTFUN )
		{
			CLR_BIT(GPIOC_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOC_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		else if(Add_pu8cfgstruct->MODE == GPIO_MODE_ANALOG)
		{
			SET_BIT(GPIOC_REG->GPIOx_MODER ,(Add_pu8cfgstruct->PIN)*2);
			SET_BIT(GPIOC_REG->GPIOx_MODER ,(((Add_pu8cfgstruct->PIN)*2)+1));
		}
		break;
	default:
		Loc_u8State = GPIO_enuNotOK;
		break;
	}

	return Loc_u8State;

}
GPIO_tenuErrorStatus GPIO_WritePinValue(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber, u8 Cpy_u8PinValue)
{
	GPIO_tenuErrorStatus Loc_u8State = GPIO_enuOK;
	if((Cpy_u8PortNumber<3) && (Cpy_u8PinNumber<16) && (Cpy_u8PinValue<2))
	{
		switch(Cpy_u8PortNumber)
		{
		case GPIO_PORTA:
			if(Cpy_u8PinValue == GPIO_HIGH)
				SET_BIT(GPIOA_REG->GPIOx_ODR,Cpy_u8PinNumber);
			else
				CLR_BIT(GPIOA_REG->GPIOx_ODR,Cpy_u8PinNumber);
			break;

		case GPIO_PORTB:
			if(Cpy_u8PinValue == GPIO_HIGH)
				SET_BIT(GPIOB_REG->GPIOx_ODR,Cpy_u8PinNumber);
			else
				CLR_BIT(GPIOB_REG->GPIOx_ODR,Cpy_u8PinNumber);
			break;
		case GPIO_PORTC:
			if(Cpy_u8PinValue == GPIO_HIGH)
				SET_BIT(GPIOC_REG->GPIOx_ODR,Cpy_u8PinNumber);
			else
				CLR_BIT(GPIOC_REG->GPIOx_ODR,Cpy_u8PinNumber);
			break;
		}

	}
	else
	{
		Loc_u8State = GPIO_enuNotOK;
	}

	return Loc_u8State;

}
GPIO_tenuErrorStatus GPIO_SetPortValue(u8 Cpy_u8PortNumber, u16 Cpy_u8PortValue)
{
	GPIO_tenuErrorStatus Loc_u8State = GPIO_enuOK;
	if(Cpy_u8PortNumber<3)
	{
		switch(Cpy_u8PortNumber)
		{

		case GPIO_PORTA:

			GPIOA_REG->GPIOx_ODR |= Cpy_u8PortValue;
			break;
		case GPIO_PORTB:

			GPIOB_REG->GPIOx_ODR |= Cpy_u8PortValue;
			break;
		case GPIO_PORTC:

			GPIOC_REG->GPIOx_ODR |= Cpy_u8PortValue;
			break;
		}
	}
	else
	{
		Loc_u8State = GPIO_enuNotOK;
	}
	return Loc_u8State;

}


GPIO_tenuErrorStatus GPIO_SelectAlternateFunc(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber, u8 Cpy_u8AlternateFunc)
{
	GPIO_tenuErrorStatus Loc_u8State = GPIO_enuOK;
	if((Cpy_u8PortNumber<3) && (Cpy_u8PinNumber<16) && (Cpy_u8AlternateFunc<16))
	{
		switch(Cpy_u8PortNumber)
		{
		case GPIO_PORTA:

			if(Cpy_u8AlternateFunc>7)
			{
				Cpy_u8AlternateFunc -= 8;
				GPIOA_REG->GPIOx_AFRH |= (Cpy_u8AlternateFunc<<(Cpy_u8PinNumber*4));
			}
			else
			{
				GPIOA_REG->GPIOx_AFRL |= (Cpy_u8AlternateFunc<<(Cpy_u8PinNumber*4));
			}

			break;

		case GPIO_PORTB:
			if(Cpy_u8AlternateFunc>7)
			{
				Cpy_u8AlternateFunc -= 8;
				GPIOB_REG->GPIOx_AFRH |= (Cpy_u8AlternateFunc<<(Cpy_u8PinNumber*4));
			}
			else
			{
				GPIOB_REG->GPIOx_AFRL |= (Cpy_u8AlternateFunc<<(Cpy_u8PinNumber*4));
			}

			break;

		case GPIO_PORTC:
			if(Cpy_u8AlternateFunc>7)
			{
				Cpy_u8AlternateFunc -= 8;
				GPIOC_REG->GPIOx_AFRH |= (Cpy_u8AlternateFunc<<(Cpy_u8PinNumber*4));
			}
			else
			{
				GPIOC_REG->GPIOx_AFRL |= (Cpy_u8AlternateFunc<<(Cpy_u8PinNumber*4));
			}

			break;

		}
	}
	else
	{
		Loc_u8State = GPIO_enuNotOK;
	}

	return Loc_u8State;

}


GPIO_tenuErrorStatus GPIO_ReadPinValue(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber, u8 * Add_pu8PinValue)
{
	GPIO_tenuErrorStatus Loc_u8State = GPIO_enuOK;
	if((Cpy_u8PortNumber<3) && (Cpy_u8PinNumber<16))
		switch (Cpy_u8PortNumber)
		{
		case GPIO_PORTA:
			* Add_pu8PinValue = GET_BIT(GPIOA_REG->GPIOx_IDR,Cpy_u8PinNumber);
			break;
		case GPIO_PORTB:
			* Add_pu8PinValue = GET_BIT(GPIOB_REG->GPIOx_IDR,Cpy_u8PinNumber);
			break;
		case GPIO_PORTC:
			* Add_pu8PinValue = GET_BIT(GPIOC_REG->GPIOx_IDR,Cpy_u8PinNumber);
			break;

		}
	else
	{
		Loc_u8State = GPIO_enuNotOK;
	}


	return Loc_u8State;
}



GPIO_tenuErrorStatus GPIO_TogglePinValue(u8 Cpy_u8PortNumber, u8 Cpy_u8PinNumber)
{
	GPIO_tenuErrorStatus Loc_u8State = GPIO_enuOK;
	if((Cpy_u8PortNumber<3) && (Cpy_u8PinNumber<16) )
	{
		switch(Cpy_u8PortNumber)
		{
		case GPIO_PORTA:
			TGL_BIT(GPIOA_REG->GPIOx_ODR,Cpy_u8PinNumber);
			break;

		case GPIO_PORTB:
			TGL_BIT(GPIOB_REG->GPIOx_ODR,Cpy_u8PinNumber);
			break;
		case GPIO_PORTC:
			TGL_BIT(GPIOC_REG->GPIOx_ODR,Cpy_u8PinNumber);
			break;
		}

	}
	else
	{
		Loc_u8State = GPIO_enuNotOK;
	}

	return Loc_u8State;



}
