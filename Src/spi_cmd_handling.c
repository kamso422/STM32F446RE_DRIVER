/*
 * spi_cmd_handling.c
 *
 *  Created on: Jul 22, 2025
 *      Author: chikamso
 */

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

//command codes
#define COMMAND_LED_CTRL		0x50
#define COMMAND_SENSOR_READ		0x51
#define COMMAND_LED_READ		0x52
#define COMMAND_PRINT			0x53
#define COMMAND_ID_READ			0x54

#define LED_ON					1
#define LED_OFF					0

//arduino analog pins
#define ANALOG_PIN0				0
#define ANALOG_PIN1				1
#define ANALOG_PIN2				2
#define ANALOG_PIN3				3
#define ANALOG_PIN4				4

//arduino led
#define LED_PIN					9

uint8_t SPI_VerifyResponse(uint8_t ackbyte);
uint8_t dataLen = 0;

int main(void)
{
	uint8_t dummy_byte = 0xFF;
	uint8_t dummy_read;
	RESET_SPI1_REG();
    gpio_handle_t SPI_Pin;
    gpio_handle_t command1;
    gpio_handle_t command2;
    gpio_handle_t command3;
    gpio_handle_t command4;
    gpio_handle_t command5;

    char* message = "master is up";
    uint8_t len = strlen(message);

    memset(&SPI_Pin,0,sizeof(gpio_handle_t));
    memset(&command1,0,sizeof(gpio_handle_t));

    //Enable peripheral Clock for GPIO pins
    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOB, ENABLE);

    //Set up the button
    command1.gpioReg = GPIOB;
    command1.gpioConfigure.MODE = GPIO_MODE_INPUT;
    command1.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    command1.gpioConfigure.OTYPE = GPIO_PP;
    command1.gpioConfigure.PUPD = GPIO_PU;
    command1.gpioConfigure.pinNumber = GPIO_PIN_NO_5;

    //Initialize button
    gpioInit(&command1);

    //Set up the SPI1 pins
    SPI_Pin.gpioReg = GPIOA;
    SPI_Pin.gpioConfigure.MODE = GPIO_MODE_ALFN;
    SPI_Pin.gpioConfigure.ALTF = AF5;
    SPI_Pin.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    SPI_Pin.gpioConfigure.PUPD = GPIO_NO_PUPD;
    SPI_Pin.gpioConfigure.OTYPE = GPIO_PP;

    //Set up the MOSI pin  D11
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_7;
    gpioInit(&SPI_Pin);
    //Configure the MISO pin D12
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_6;
    gpioInit(&SPI_Pin);
    //Set up the clock pin D13
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_5;
    gpioInit(&SPI_Pin);
    //Set up the NSS pin A2
    SPI_Pin.gpioConfigure.pinNumber = GPIO_PIN_NO_4;
    gpioInit(&SPI_Pin);

    //setup the buttons for the command buttons
    command2.gpioReg = GPIOA;
    command2.gpioConfigure.MODE = GPIO_MODE_INPUT;
    command2.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    command2.gpioConfigure.PUPD = GPIO_PU;
    command2.gpioConfigure.OTYPE = GPIO_PP;
    command2.gpioConfigure.pinNumber = GPIO_PIN_NO_0;
    gpioInit(&command2);

    command3.gpioReg = GPIOA;
    command3.gpioConfigure.MODE = GPIO_MODE_INPUT;
    command3.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    command3.gpioConfigure.PUPD = GPIO_PU;
    command3.gpioConfigure.OTYPE = GPIO_PP;
    command3.gpioConfigure.pinNumber = GPIO_PIN_NO_1;
    gpioInit(&command3);

    command4.gpioReg = GPIOA;
    command4.gpioConfigure.MODE = GPIO_MODE_INPUT;
    command4.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    command4.gpioConfigure.PUPD = GPIO_PU;
    command4.gpioConfigure.OTYPE = GPIO_PP;
    command4.gpioConfigure.pinNumber = GPIO_PIN_NO_15;
    gpioInit(&command4);

    command5.gpioReg = GPIOA;
    command5.gpioConfigure.MODE = GPIO_MODE_INPUT;
    command5.gpioConfigure.OSPEED = GPIO_LOW_SPEED;
    command5.gpioConfigure.PUPD = GPIO_PU;
    command5.gpioConfigure.OTYPE = GPIO_PP;
    command5.gpioConfigure.pinNumber = GPIO_PIN_NO_9;
    gpioInit(&command5);

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
    theSpi.SPIConfig.SPI_SclkSpeed = SPI_CLK_SPEED_DIV128;

    spiInit(&theSpi);

    setSSOE(SPI1, ENABLE);

    while(1){
    	uint8_t ackbyte;
    	while(!GPIO_ReadFromInputPin(command1.gpioReg, command1.gpioConfigure.pinNumber)){
    		spiEnable(SPI1,ENABLE);
    		//1. CMD_LED_CTRL <pin no(1)> <value(1)>
    		uint8_t arg[2];
    		uint8_t commandcode = COMMAND_LED_CTRL;
    		SPI_SendData(SPI1, &commandcode, 1);
    		SPI_ReceiveData(SPI1,&dummy_read,1);
    		//send some dummy bit to fetch the response from the slave
    		SPI_SendData(SPI1,&dummy_byte,1);
    		SPI_ReceiveData(SPI1,&ackbyte,1);
    		//Verify the response
    		if(SPI_VerifyResponse(ackbyte)){
    		    arg[0] = LED_PIN;
    		    arg[1] = LED_ON;
    		    SPI_SendData(SPI1,arg,2);
    		    SPI_ReceiveData(SPI1,&dummy_read,2);
    	    }
    		spiEnable(SPI1,DISABLE);
    		delay;
    	}
    	while(!GPIO_ReadFromInputPin(command2.gpioReg, command2.gpioConfigure.pinNumber)){
    		spiEnable(SPI1,ENABLE);
    		//2. CMD_SENSOR_READ <pin no(1)>
    		uint8_t arg;
    		uint8_t commandcode = COMMAND_SENSOR_READ;
    		SPI_SendData(SPI1, &commandcode, 1);
    		SPI_ReceiveData(SPI1,&dummy_read,1);
    		//send some dummy bit to fetch the response from the slave
    		SPI_SendData(SPI1,&dummy_byte,1);
    		SPI_ReceiveData(SPI1,&ackbyte,1);
    		//Verify the response
    		if(SPI_VerifyResponse(ackbyte)){
    			arg = ANALOG_PIN0;
    			SPI_SendData(SPI1,&arg,1);
    			SPI_ReceiveData(SPI1,&dummy_read,1);
    		}
    		spiEnable(SPI1,DISABLE);
    		delay;
    	}
    	while(!GPIO_ReadFromInputPin(command3.gpioReg, command3.gpioConfigure.pinNumber)){
    		spiEnable(SPI1,ENABLE);
    		//3. CMD_LED_READ <pin no()>
    		uint8_t arg;
    		uint8_t ledState;
    		uint8_t commandcode = COMMAND_LED_READ;
    		SPI_SendData(SPI1, &commandcode, 1);
    		SPI_ReceiveData(SPI1,&dummy_read,1);
    		//send some dummy bit to fetch the response from the slave
    		SPI_SendData(SPI1,&dummy_byte,1);
    		SPI_ReceiveData(SPI1,&ackbyte,1);
    		if(SPI_VerifyResponse(ackbyte)){
    			arg = LED_PIN;
    			SPI_SendData(SPI1,&arg,1);
    			SPI_ReceiveData(SPI1,&dummy_read,1);
    			//send dummy byte to get led state
        		SPI_SendData(SPI1,&dummy_byte,1);
        		SPI_ReceiveData(SPI1,&ledState,1);
    		}
    		spiEnable(SPI1,DISABLE);
    		delay;
    	}
    	while(!GPIO_ReadFromInputPin(command4.gpioReg, command4.gpioConfigure.pinNumber)){
    		spiEnable(SPI1,ENABLE);
    		//char dump[15];
    		uint8_t ackbyte;
    		uint8_t commandcode = COMMAND_PRINT;
    		SPI_SendData(SPI1, &commandcode, 1);
    		SPI_ReceiveData(SPI1,&dummy_read,1);
    		//send some dummy bit to fetch the response from the slave
    		SPI_SendData(SPI1,&dummy_byte,1);
    		SPI_ReceiveData(SPI1,&ackbyte,1);
    		if(SPI_VerifyResponse(ackbyte)){
    			SPI_SendData(SPI1,&len,1);
    			SPI_ReceiveData(SPI1,&dummy_read,1);
    		}
    		//Sending message
   			SPI_SendData(SPI1,(uint8_t*)message,len);
    	    //SPI_ReceiveData(SPI1,(uint8_t*)dump,len);
    		spiEnable(SPI1,DISABLE);
    		delay;
    	}
    }
    while(1);
}

uint8_t SPI_VerifyResponse(uint8_t ackbyte){
	if(ackbyte == 0xF5){
		//ack
		return 1;
	}
	return 0;
}
