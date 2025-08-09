/*
 * InterruptSend.c
 *
 *  Created on: Jul 8, 2025
 *      Author: chikamso
 */


#include "STM32F44xx__driver.h"
#include "STM32F44xxgpio__driver.h"
#include "STM32F44xxSPI__driver.h"
#include <stdlib.h>
#include <string.h>

#define delay	for(uint16_t i = 0; i < 65500; i++)

char* TxBuffer = "Hello World";

int main(void)
{
	//RESET_SPI1_REG();
    //char* TxBuffer = "Hello World";
    gpio_handle_t SPI_Pin;
    gpio_handle_t button;
    memset(&button,0,sizeof(gpio_handle_t));
    memset(&SPI_Pin,0,sizeof(gpio_handle_t));

    //Enable peripheral Clock for GPIO pins
    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOB, ENABLE);

    //Setup the button for trigger
    button.gpioReg = GPIOB;
    button.gpioConfigure.MODE = GPIO_IT_MODE_FT;
    button.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    button.gpioConfigure.OTYPE = GPIO_PP;
    button.gpioConfigure.PUPD = GPIO_PU;
    button.gpioConfigure.pinNumber = GPIO_PIN_NO_0;

    gpioInit(&button);
    //Setting up the interrupts
    GPIO_IRQConfig(EXTI0_IRQ_NUM, ENABLE);
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
    //SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_6;
    //gpioInit(&SPI_Pin);
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
    theSpi.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    theSpi.SPIConfig.SPI_CPHA = SPI_CPHA1;
    theSpi.SPIConfig.SPI_CPOL = SPI_CPOL0;
    theSpi.SPIConfig.SPI_DFF = DFF8;
    theSpi.SPIConfig.SPI_DeviceMode = MASTER;
    theSpi.SPIConfig.SPI_SSM = SSM_HW;
    theSpi.SPIConfig.SPI_SclkSpeed = SPI_CLK_SPEED_DIV16;

    spiInit(&theSpi);
    setSSOE(SPI1, ENABLE);
    while(1);
    EXTI0_IRQHandler();
}

void EXTI0_IRQHandler(void){
	delay;
	GPIO_IRQHandling(GPIO_PIN_NO_0);
    spiEnable(SPI1, ENABLE);
    SPI_SendData(SPI1, (uint8_t*)TxBuffer, strlen(TxBuffer)+1);
    spiEnable(SPI1, DISABLE);
}

