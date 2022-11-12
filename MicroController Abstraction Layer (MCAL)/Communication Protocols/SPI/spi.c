/******************************************************************************
 * Module: SPI (Serial Peripheral Interface)
 *
 * File Name: spi.c
 *
 * Description: Source file for the AVR SPI driver
 *
 * Author: Mostafa Mahmoud
 *
 *******************************************************************************/

#include "spi.h"
#include <avr/io.h>
#include "Macros.h"

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/

/* Description:
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(SPI_ConfigType *configPtr)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output
	 * MISO(PB6) --> Input
	 * SCK(PB7)  --> Output
	 ********************************************/

	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_SS_PIN_ID  , PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_MOSI_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_MISO_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_SCLK_PIN_ID, PIN_OUTPUT);

    /************************** SPCR Description **************************
     * SPIE    = 0 Disable SPI Interrupt
     * SPE     = 1 Enable SPI Driver
     * MSTR    = 1 Enable Master
     * DORD    = (0 or 1) Dynamically configured by user --> Transmit (MSB or LSB) first
     * CPOL    = (0 or 1) Dynamically configured by user --> SCK is (Low or High) when idle
     * CPHA    = (0 or 1) Dynamically configured by user --> Sample Data with the (Leading or Trailing) edge
     * SPR1:0  = Dynamically configured by user --> Check enum SPI_ClockRate (Normal or DoubleSpeed)
     ***********************************************************************/


	SPCR = (1 << SPE) | (1 << MSTR) |
		   (configPtr->dataOrder << DORD)    | (configPtr->idleState << CPOL) |
		   (configPtr->samplingEdge << CPHA) | (configPtr->SCLK_freq << SPR0);

#ifdef SPI_DOUBLE_SPEED_MODE
	SET_BIT(SPSR,SPI2X);

#else
	CLEAR_BIT(SPSR,SPI2X);

#endif

}

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(SPI_ConfigType *configPtr)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7)  --> Input
	 ********************************************/
	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_SS_PIN_ID  , PIN_INPUT);
	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_MOSI_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_MISO_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_PINS_PORT_ID, SPI_SCLK_PIN_ID, PIN_INPUT);

    /************************** SPCR Description **************************
     * SPIE    = 0 Disable SPI Interrupt
     * SPE     = 1 Enable SPI Driver
     * MSTR    = 0 disable Master
     * DORD    = (0 or 1) Dynamically configured by user --> Transmit (MSB or LSB) first
     * CPOL    = (0 or 1) Dynamically configured by user --> SCK is (Low or High) when idle
     * CPHA    = (0 or 1) Dynamically configured by user --> Sample Data with the (Leading or Trailing) edge
     * SPR1:0  = Dynamically configured by user --> Check enum SPI_ClockRate (Normal or DoubleSpeed)
     ***********************************************************************/


	SPCR = (1 << SPE) | (configPtr->dataOrder << DORD) | (configPtr->idleState << CPOL) |
		   (configPtr->samplingEdge << CPHA) | (configPtr->SCLK_freq << SPR0);

#ifdef SPI_DOUBLE_SPEED_MODE
	SET_BIT(SPSR,SPI2X);

#else
	CLEAR_BIT(SPSR,SPI2X);

#endif


}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	/* Initiate the communication and send data by SPI */
	SPDR = data;

	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while (BIT_IS_CLEAR(SPSR, SPIF));

	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	return SPDR;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str)
{
	uint8 received_data = 0;

	/* Send the whole string */
	while(*str != '\0')
	{
		/* received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		received_data = SPI_sendReceiveByte(*str);
		str++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str)
{
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
