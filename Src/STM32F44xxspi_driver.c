/*
 * STM32F44xxspi_driver.c
 *
 *  Created on: Jun 5, 2025
 *      Author: chika
 */

#include "STM32F44xxSPI__driver.h"
#include "STM32F44xx__driver.h"

uint8_t checkStatusFlag(SPI_RegDef_t* pSPIx, uint32_t flagName){
	if(pSPIx->SR & flagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_PeriClockControl(SPI_RegDef_t* pSPIx,uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pSPIx == SPI1){
			SPI1_PCLK_EN();
		}else if(pSPIx == SPI2){
			 SPI2_PCLK_EN();
		}else if(pSPIx == SPI3){
			SPI3_PCLK_EN();
		}else{
			SPI4_PCLK_EN();
		}
	}else{
		if(pSPIx == SPI1){
			SPI1_PCLK_DIS();
		}else if(pSPIx == SPI2){
			SPI2_PCLK_DIS();
		}else if(pSPIx == SPI3){
			SPI3_PCLK_DIS();
		}else{
			SPI4_PCLK_DIS();
		}
	}
}

void spiInit(SPI_Handle_t* handle){
	uint32_t value = 0;
	//Setting mode for peripheral; SLAVE OR MASTER
	if(handle->SPIConfig.SPI_DeviceMode == SLAVE){
		handle->pSPIx->CR1 &= ~(0x1 << CR_MSTR);
	}else if(handle->SPIConfig.SPI_DeviceMode == MASTER){
		value |= (0x1 << CR_MSTR);
		handle->pSPIx->CR1 |= value;
		value = 0;
	}
	//Bus configuration
	if(handle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD){
		value &= ~(0x1 << CR_BIDIMODE);
		handle->pSPIx->CR1 |= value;
		value = 0;
	}else if(handle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		handle->pSPIx->CR1 |= (0x1 << CR_BIDIMODE);
	}else if(handle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		handle->pSPIx->CR1 |= (0x1 << CR_RXONLY);
	}else if(handle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_TXONLY){
		handle->pSPIx->CR1 |= (0x1 << CR_BIDIMODE);
		handle->pSPIx->CR1 |= (0x1 << CR_BIDIOE);
	}
	//Setting the Data frame for data transmission
	if(handle->SPIConfig.SPI_DFF ==  DFF8){
		handle->pSPIx->CR1 &= ~(0x1 << CR_DFF);
	}else{
		handle->pSPIx->CR1 |= (0x1 << CR_DFF);
	}
	//Setting the clock phase
	if(handle->SPIConfig.SPI_CPHA == SPI_CPHA1){
		handle->pSPIx->CR1 &= ~(0x1 << CR_CPHA);
	}else{
		handle->pSPIx->CR1 |= (0x1 << CR_CPHA);
	}
	//Setting the clock polarity
	if(handle->SPIConfig.SPI_CPOL == SPI_CPOL0){
		handle->pSPIx->CR1 &= ~(0x1 << CR_CPOL);
	}else{
		handle->pSPIx->CR1 |= (0x1 << CR_CPOL);
	}
	//Setting software slave management
	if(handle->SPIConfig.SPI_SSM == SSM_HW){
		handle->pSPIx->CR1 &= ~(0x1 << CR_SSM);
	}else{
		handle->pSPIx->CR1 |= (0x1 << CR_SSM);
	}
	//Setting the speed
	value |= (handle->SPIConfig.SPI_SclkSpeed << CR_BR);
	handle->pSPIx->CR1 |= value;
}

void spiDeInit(SPI_RegDef_t* pSPIx){
	if(pSPIx == SPI1){
		RESET_SPI1_REG();
	}else if(pSPIx == SPI2){
		RESET_SPI2_REG();
	}else if(pSPIx == SPI3){
		RESET_SPI3_REG();
	}else{
		RESET_SPI4_REG();
	}
}

void SPI_SendData(SPI_RegDef_t* pSPIx, uint8_t *pTxBuffer, uint32_t Len){
	while(Len > 0){
		while(checkStatusFlag(pSPIx,SR_TXE)){
			if(pSPIx->CR1 & (0x1 << CR_DFF)){
				pSPIx->DR = *((uint16_t*)pTxBuffer);
				(uint16_t*)pTxBuffer++;
				Len--;
				Len--;
			}else{
				pSPIx->DR = *pTxBuffer;
				pTxBuffer++;
				Len--;
			}
		}
	}
}
void setSSI(SPI_RegDef_t* pSPIx, uint8_t en_di){
	if(en_di == ENABLE){
		pSPIx->CR1 |= (0x1 << CR_SSI);
	}else
		pSPIx->CR1 &= ~(0x1 << CR_SSI);
}
void setSSOE(SPI_RegDef_t* pSPIx, uint8_t en_di){
	if(en_di == ENABLE){
		pSPIx->CR2 |= (0x1 << CR_SSOE);
	}else
		pSPIx->CR2 &= ~(0x1 << CR_SSOE);
}
void spiEnable(SPI_RegDef_t* pSPIx, uint8_t en_di){
	if(en_di == ENABLE){
		pSPIx->CR1 |= (0x1 << CR_SPE);
	}else{
		while(checkStatusFlag(pSPIx,SR_BSY));
		pSPIx->CR1 &= ~(0x1 << CR_SPE);
	}
}

