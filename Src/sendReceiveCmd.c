/*
 * sendReceiveCmd.c
 *
 *  Created on: Jul 16, 2025
 *      Author: chikamso
 */


/*
 * ButtonSend.c
 *
 *  Created on: Jul 3, 2025
 *      Author: chikamso
 */



#include "STM32F44xx__driver.h"
#include "STM32F44xxgpio__driver.h"
#include "STM32F44xxSPI__driver.h"
#include <stdlib.h>
#include <string.h>
#define delay for(uint32_t i = 0; i < 250000; i++)
/*
 * Create a function for sending out data using
 * the blocking method
 */
//void disableClock(gpio_handle_t* handle);

int main(void)
{
	RESET_SPI1_REG();
    char* TxBuffer = "Hello World";
    gpio_handle_t SPI_Pin;
    gpio_handle_t sendButton;
    memset(&SPI_Pin,0,sizeof(gpio_handle_t));
    memset(&sendButton,0,sizeof(gpio_handle_t));

    //Enable peripheral Clock for GPIO pins
    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOB, ENABLE);

    //Set up the button
    sendButton.gpioReg = GPIOB;
    sendButton.gpioConfigure.MODE = GPIO_MODE_INPUT;
    sendButton.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    sendButton.gpioConfigure.OTYPE = GPIO_PP;
    sendButton.gpioConfigure.PUPD = GPIO_PU;
    sendButton.gpioConfigure.pinNumber = GPIO_PIN_NO_5;

    //Initialize button
    gpioInit(&sendButton);

    //Set up the SPI1 pins
    SPI_Pin.gpioReg = GPIOA;
    SPI_Pin.gpioConfigure.MODE = GPIO_MODE_ALFN;
    SPI_Pin.gpioConfigure.ALTF = AF5;
    SPI_Pin.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    SPI_Pin.gpioConfigure.PUPD = GPIO_NO_PUPD;
    SPI_Pin.gpioConfigure.OTYPE = GPIO_PP;

    //Set up the MOSI pin
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_7;
    gpioInit(&SPI_Pin);
    //Configure the MISO pin
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_6;
    gpioInit(&SPI_Pin);
    //Set up the clock pin
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_5;
    gpioInit(&SPI_Pin);
    //Set up the NSS pin
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_4;
    gpioInit(&SPI_Pin);

    SPI_Handle_t theSpi;
    memset(&theSpi,0,sizeof(SPI_Handle_t));

    //Enable the peripheral clock for SPI peripheral
    SPI_PeriClockControl(SPI1, ENABLE);
    //Initialize the SPI peripheral
    theSpi.pSPIx = SPI1;
    theSpi.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_SIMPLEX_TXONLY;
    theSpi.SPIConfig.SPI_CPHA = SPI_CPHA1;
    theSpi.SPIConfig.SPI_CPOL = SPI_CPOL0;
    theSpi.SPIConfig.SPI_DFF = DFF8;
    theSpi.SPIConfig.SPI_DeviceMode = MASTER;
    theSpi.SPIConfig.SPI_SSM = SSM_HW;
    theSpi.SPIConfig.SPI_SclkSpeed = SPI_CLK_SPEED_DIV32;

    uint8_t dataLen = strlen(TxBuffer);

    spiInit(&theSpi);
    setSSOE(SPI1, ENABLE);
    while(1){
    	while(GPIO_ReadFromInputPin(sendButton.gpioReg, sendButton.gpioConfigure.pinNumber));
    	//delay;
    	spiEnable(SPI1, ENABLE);
    	SPI_SendData(SPI1, &dataLen, 1);
    	SPI_SendData(SPI1, (uint8_t*)TxBuffer, strlen(TxBuffer));
    	spiEnable(SPI1, DISABLE);
    	delay;
    }
    while(1);
}
