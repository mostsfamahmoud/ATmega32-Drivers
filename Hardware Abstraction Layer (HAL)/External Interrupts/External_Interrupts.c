/******************************************************************************
 * Module: External Interrupts
 *
 * File Name: External_Interrupts.c
 *
 * Description: Source file for The AVR External Interrupts Driver.
 *
 * Author: Mostafa Mahmoud
 *
 *******************************************************************************/

#include "External_Interrupts.h"

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/

/* External INT0 enable and configuration function */
void INT0_Init(void)
{
	/* Application Dependent 
		GPIO_setPinDirection(PORTD_ID, PD2, PIN_INPUT);   // Configure INT0/PD2 as I/P pin 
		GPIO_enablePullUp(PORTD_ID, PD2, PULL_UP);        // Enable Internal Pull Up resistor of PB2 

		SET_BIT(MCUCR,ISC01);       // Trigger INT0 with the falling edge (ISC01 = 1 , ISC00 = 0)
		CLEAR_BIT(MCUCR,ISC00);
	*/

	SET_BIT(GICR,INT0);      /* Enable external interrupt pin INT0 */
}



/* External INT1 enable and configuration function */
void INT1_Init(void)
{
	/* Application Dependent 
		GPIO_setPinDirection(PORTD_ID, PD3, PIN_INPUT);   // Configure INT1/PD3 as I/P pin 

		SET_BIT(MCUCR,ISC11);         // Trigger INT1 with the rising edge (ISC11 = 1 , ISC10 = 1) 
		SET_BIT(MCUCR,ISC10);
	*/

	SET_BIT(GICR,INT1);      /* Enable external interrupt pin INT1 */
}



/* External INT2 enable and configuration function */
void INT2_Init(void)
{
	/* Application Dependent 
		GPIO_setPinDirection(PORTB_ID, PB2, PIN_INPUT);   // Configure INT2/PB2 as I/P pin 
		GPIO_enablePullUp(PORTB_ID, PB2, PULL_UP);        // Enable Internal Pull Up resistor of PB2 
		CLEAR_BIT(MCUCSR,ISC2);                           // Trigger INT2 with the falling edge (ISC2 = 0)
	*/

	SET_BIT(GICR,INT2);      /* Enable external interrupt pin INT2 */
}


/*******************************************************************************
 *                          INTERRUPT SERVICE ROUTINES                         *
 *******************************************************************************/

/* INT0 (ISR) that is responsible for  */
ISR(INT0_vect)
{
	/* Application Dependant */
}


/* INT1 (ISR) that is responsible for  */
ISR(INT1_vect)
{
	/* Application Dependant */
}


/* INT2 (ISR) that is responsible for  */
ISR(INT2_vect)
{
	/* Application Dependant */
}




