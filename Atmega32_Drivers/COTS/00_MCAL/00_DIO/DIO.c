#include "../../LIB/std_defines.h"
#include "../../LIB/bit_math.h"
#include "DIO.h"
#include "DIO_Cfg.h"
#include "DIO_piv.h"






DIO_tenuErrorStatus DIO_enuInit(void){
	u8 i;
	u8 Loc_u8PortNumber=0;
	u8 Loc_u8PinNumber=0;
	
	for (i=0;i<32;i++){
		Loc_u8PortNumber = i/8;
		Loc_u8PinNumber = i%8;
		
		switch (Loc_u8PortNumber)
		{
			case(PORTA_REG):
			if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT){
				SET_BIT(DDRA,Loc_u8PinNumber);
			}
			else{
				CLR_BIT(DDRA,Loc_u8PinNumber);
				
				if(DIO_strPinCfg[i].DIO_InputStatus ==DIO_INPUT_PULLUP)
				{
					SET_BIT(PORTA,Loc_u8PinNumber);
				}
				else{
					CLR_BIT(PORTA,Loc_u8PinNumber);
				}
			}
			break;
			case(PORTB_REG):
			if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT)
			{
				SET_BIT(DDRB,Loc_u8PinNumber);
			}
			else{
				CLR_BIT(DDRB,Loc_u8PinNumber);
				if(DIO_strPinCfg[i].DIO_InputStatus ==DIO_INPUT_PULLUP)
				{
					SET_BIT(PORTB,Loc_u8PinNumber);
				}
				else{
					CLR_BIT(PORTB,Loc_u8PinNumber);
				}
			}
			break;
			case(PORTC_REG):
			if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT)
			{
				SET_BIT(DDRC,Loc_u8PinNumber);
			}
			else{
				CLR_BIT(DDRC,Loc_u8PinNumber);
				if(DIO_strPinCfg[i].DIO_InputStatus ==DIO_INPUT_PULLUP)
				{
					SET_BIT(PORTC,Loc_u8PinNumber);
				}
				else{
					CLR_BIT(PORTC,Loc_u8PinNumber);
				}
			}
			break;
			case(PORTD_REG):
			if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT)
			{
				SET_BIT(DDRD,Loc_u8PinNumber);
			}
			else{
				CLR_BIT(DDRD,Loc_u8PinNumber);
				if(DIO_strPinCfg[i].DIO_InputStatus ==DIO_INPUT_PULLUP){
					SET_BIT(PORTD,Loc_u8PinNumber);
				}
				else{
					CLR_BIT(PORTD,Loc_u8PinNumber);
				}
			}
			break;
		}
	}
	return DIO_enuOK;
}



DIO_tenuErrorStatus DIO_enuSetPin(DIO_tenuPins Cpy_u8PinNumber){
	u8 Loc_u8PortNumber=0;
	u8 Loc_u8PinNumber=0;

	Loc_u8PortNumber= Cpy_u8PinNumber/8;
	Loc_u8PinNumber = Cpy_u8PinNumber%8;


	switch (Loc_u8PortNumber){
		case PORTA_REG:
		SET_BIT(PORTA,Loc_u8PinNumber);
		break;
		
		case PORTB_REG:
		
		SET_BIT(PORTB,Loc_u8PinNumber);
		break;
		case PORTC_REG:

		SET_BIT(PORTC,Loc_u8PinNumber);
		break;

		case PORTD_REG:
		
		SET_BIT(PORTD,Loc_u8PinNumber);
		break;
		
	}

	return DIO_enuOK;
}
DIO_tenuErrorStatus DIO_enuClearPin(DIO_tenuPins Cpy_u8PinNumber)
{
	u8 Loc_u8PortNumber=0;
	u8 Loc_u8PinNumber=0;

	Loc_u8PortNumber= Cpy_u8PinNumber/8;
	Loc_u8PinNumber = Cpy_u8PinNumber%8;


	switch (Loc_u8PortNumber){
		
		case PORTA_REG:
		CLR_BIT(PORTA,Loc_u8PinNumber);
		break;
		
		case PORTB_REG:
		
		CLR_BIT(PORTB,Loc_u8PinNumber);
		break;
		case PORTC_REG:

		CLR_BIT(PORTC,Loc_u8PinNumber);
		break;

		case PORTD_REG:
		
		CLR_BIT(PORTD,Loc_u8PinNumber);
		break;
		
	}

	return DIO_enuOK;
}


DIO_tenuErrorStatus DIO_enuGetPin(DIO_tenuPins Cpy_u8PinNumber, u8 * Add_pu8PinValue)
{
	u8 Loc_u8PortNumber =0;
	u8 Loc_u8PinNumber =0;
	
	Loc_u8PortNumber = Cpy_u8PinNumber/8;
	Loc_u8PinNumber = Cpy_u8PinNumber%8;
	

	switch (Loc_u8PortNumber){
		
		case PORTA_REG:
		*Add_pu8PinValue = GET_BIT(PINA,Loc_u8PinNumber);
		break;
		
		case PORTB_REG:
		*Add_pu8PinValue = GET_BIT(PINB,Loc_u8PinNumber);
		break;
		
		case PORTC_REG:
		*Add_pu8PinValue = GET_BIT(PINC,Loc_u8PinNumber);
		break;

		case PORTD_REG:
		*Add_pu8PinValue = GET_BIT(PIND,Loc_u8PinNumber);
		break;
		
	}
	return DIO_enuOK;
}

DIO_tenuErrorStatus DIO_enuSetValue(DIO_tenuPins Cpy_u8PinNumber,u8 DIO_u8AssignValue)
{
	
	u8 Loc_u8PortNumber =0;
	u8 Loc_u8PinNumber =0;
	
	Loc_u8PortNumber = Cpy_u8PinNumber/8;
	Loc_u8PinNumber = Cpy_u8PinNumber%8;
	

	switch (Loc_u8PortNumber){
		
		case PORTA_REG:
		ASSIGN_REG(PORTA,DIO_u8AssignValue);
		break;
		
		case PORTB_REG:
		ASSIGN_REG(PORTB,DIO_u8AssignValue);
		break;
		
		case PORTC_REG:
		ASSIGN_REG(PORTC,DIO_u8AssignValue);
		break;

		case PORTD_REG:
		ASSIGN_REG(PORTD,DIO_u8AssignValue);
		break;
		
	}
	return DIO_enuOK;
}


DIO_tenuErrorStatus DIO_enuSetPinValue(DIO_tenuPins Cpy_u8PinNumber, DIO_tenuValue Cpy_u8AssignValue)
{
	DIO_tenuErrorStatus Loc_u8State = DIO_enuOK;
	u8 Loc_u8PortNumber =0;
	u8 Loc_u8PinNumber =0;
	
	Loc_u8PortNumber = Cpy_u8PinNumber/8;
	Loc_u8PinNumber = Cpy_u8PinNumber%8;
	
	if(Cpy_u8AssignValue == HIGH)
	{
		switch (Loc_u8PortNumber){
			
			case PORTA_REG:
			PORTA |= (1<<Loc_u8PinNumber);
			break;
			
			case PORTB_REG:
			PORTB |= (1<<Loc_u8PinNumber);
			break;
			
			case PORTC_REG:
			PORTC |= (1<<Loc_u8PinNumber);
			break;

			case PORTD_REG:
			PORTD |= (1<<Loc_u8PinNumber);
			break;
			
			default:
			Loc_u8State = DIO_enuNotOK;
			break;
			
		}
		
	}
	else
	{
		switch (Loc_u8PortNumber){
			
			case PORTA_REG:
			PORTA &= ~(1<<Loc_u8PinNumber);
			break;
			
			case PORTB_REG:
			PORTB &= ~(1<<Loc_u8PinNumber);
			break;
			
			case PORTC_REG:
			PORTC &= ~(1<<Loc_u8PinNumber);
			break;

			case PORTD_REG:
			PORTD &= ~(1<<Loc_u8PinNumber);
			break;
			
			default:
			Loc_u8State = DIO_enuNotOK;
			break;
			
		}

	}

	
	
	
	return Loc_u8State;
}

DIO_tenuErrorStatus DIO_enuTogglePin(DIO_tenuPins Cpy_u8PinNumber)
{
	DIO_tenuErrorStatus Loc_u8State = DIO_enuOK;
	u8 Loc_u8PortNumber =0;
	u8 Loc_u8PinNumber =0;
	
	Loc_u8PortNumber = Cpy_u8PinNumber/8;
	Loc_u8PinNumber = Cpy_u8PinNumber%8;
	
	switch (Loc_u8PortNumber){
		
		case PORTA_REG:
		PORTA ^= (1<<Loc_u8PinNumber);
		break;
		
		case PORTB_REG:
		PORTB ^= (1<<Loc_u8PinNumber);
		break;
		
		case PORTC_REG:
		PORTC ^= (1<<Loc_u8PinNumber);
		break;

		case PORTD_REG:
		PORTD ^= (1<<Loc_u8PinNumber);
		break;
		
		default:
		Loc_u8State = DIO_enuNotOK;
		break;
		
	}
	return Loc_u8State;
	
}