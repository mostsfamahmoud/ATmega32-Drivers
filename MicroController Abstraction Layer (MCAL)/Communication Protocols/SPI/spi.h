/******************************************************************************
 * Module: SPI (Serial Peripheral Interface)
 *
 * File Name: spi.h
 *
 * Description: Header file for the AVR SPI driver
 *
 * Author: Mostafa Mahmoud
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_


#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//#define SPI_DOUBLE_SPEED_MODE

#define SPI_PINS_PORT_ID      PORTB_ID

#define SPI_SS_PIN_ID         PIN4_ID
#define SPI_MOSI_PIN_ID       PIN5_ID
#define SPI_MISO_PIN_ID       PIN6_ID
#define SPI_SCLK_PIN_ID       PIN7_ID


/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define SPI_DEFAULT_DATA_VALUE  0xFF

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	MSB_FIRST, LSB_FIRST
}SPI_DataOrder;

typedef enum{
	IDLE_LOW, IDLE_HIGH
}SPI_ClockPolarity;

typedef enum{
	LEADING, TRAILING
}SPI_DataSamplingEdge;


#ifdef SPI_DOUBLE_SPEED_MODE

typedef enum{
	FCPU_2, FCPU_8, FCPU_32, FCPU_64
}SPI_ClockRate_DoubleSpeed;

#else

typedef enum{
	FCPU_4, FCPU_16, FCPU_64, FCPU_128
}SPI_ClockRate_Normal;

#endif

typedef struct{
	SPI_DataOrder dataOrder;
	SPI_ClockPolarity idleState;
	SPI_DataSamplingEdge samplingEdge;

#ifdef SPI_DOUBLE_SPEED_MODE
	SPI_ClockRate_DoubleSpeed SCLK_freq;
#else
	SPI_ClockRate_Normal SCLK_freq;
#endif

}SPI_ConfigType;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description:
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(SPI_ConfigType *configPtr);

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(SPI_ConfigType *configPtr);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str);


#endif /* SPI_H_ */
