/*
 * STM32F44xx__driver.h
 *
 *  Created on: Jun 1, 2025
 *      Author: chika
 */

#ifndef STM32F44XX__DRIVER_H_
#define STM32F44XX__DRIVER_H_

#include <stdint.h>
#include <stddef.h>
/*
 *Define memory base addresses
 */
#define SRAM_BASEADDR 					0x20000000U
#define FLASH_BASEADDR					0x08000000U


/*
 * Defining base address for peripheral buses
 */
#define APB1_BUS_BASEADDR				0x40000000U
#define APB2_BUS_BASEADDR				0x40010000U
#define AHB1_BUS_BASEADDR				0x40020000U
#define AHB2_BUS_BASEADDR				0x50000000U
#define AHB3_BUS_BASEADDR				0x60000000U

#define RCC_PERI_BASEADDR				0x40023800U

#define NVIC_ISER0						((volatile uint32_t*)0xE000E100U)  //0-31
#define NVIC_ISER1						((volatile uint32_t*)0xE000E104U)  //32-63
#define NVIC_ISER2						((volatile uint32_t*)0xE000E108U)  //64-95
#define NVIC_ISER3						((volatile uint32_t*)0xE000E10CU)  //96-127

#define NVIC_ICER0						((volatile uint32_t*)0xE000E180U)  //0-31
#define NVIC_ICER1						((volatile uint32_t*)0xE000E184U)  //32-63
#define NVIC_ICER2						((volatile uint32_t*)0xE000E188U)  //64-95
#define NVIC_ICER3						((volatile uint32_t*)0xE000E18CU)  //96-127

#define NVIC_IPR0						((volatile uint32_t*)0xE000E400U)

/*
 * Define the base address for the GPIOx peripherals
 */
#define GPIOA_PERI_BASEADDR				0x40020000U
#define GPIOB_PERI_BASEADDR				0x40020400U
#define GPIOC_PERI_BASEADDR				0x40020800U
#define GPIOD_PERI_BASEADDR				0x40020C00U
#define GPIOE_PERI_BASEADDR				0x40021000U
#define GPIOF_PERI_BASEADDR				0x40021400U
#define GPIOG_PERI_BASEADDR				0x40021800U
#define GPIOH_PERI_BASEADDR				0x40021C00U

/*
 * Define the base address for the USARTx peripherals
 */
#define USART1_PERI_BASEADDR			0x40011000U
#define USART2_PERI_BASEADDR			0x40004400U
#define USART3_PERI_BASEADDR			0x40004800U
#define USART6_PERI_BASEADDR			0x40011400U

/*
 * Define the base address for the I2Cx peripherals
 */
#define I2C1_PERI_BASEADDR				0x40005400U
#define I2C2_PERI_BASEADDR				0x40005800U
#define I2C3_PERI_BASEADDR				0x40005C00U

/*
 * Define the base address for the SPIx peripherals
 */
#define SPI1_PERI_BASEADDR				0x40013000U
#define SPI2_PERI_BASEADDR				0x40003800U
#define SPI3_PERI_BASEADDR				0x40003C00U
#define SPI4_PERI_BASEADDR				0x40013400U

/*
 *Define the base address for the SYSCFG
 */
#define SYSCFG_PERI_BASEADDR			0x40013800U
#define EXTI_PERI_BASEADDR				0x40013C00U

#define ENABLE 							1
#define DISABLE							0
#define SET								ENABLE
#define RESET							DISABLE
#define FLAG_SET						ENABLE
#define FLAG_RESET						DISABLE

typedef struct{
	volatile uint32_t MODER;			/*GPIO port mode register... Address offset: 0x00*/
	volatile uint32_t OTYPER;			/*GPIO port output type register... Address offset: 0x04*/
	volatile uint32_t OSPEEDER;			/*GPIO port output speed register... Address offset: 0x08*/
	volatile uint32_t PUPDR;			/*GPIO port pull-up/pull-down register... Address offset: 0x0C*/
	volatile uint32_t IDR;				/*GPIO port input data register... Address offset: 0x10*/
	volatile uint32_t ODR;				/*GPIO port output data register... Address offset: 0x14*/
	volatile uint32_t BSRR;				/*GPIO port bit set/reset register... Address offset:0x18*/
	volatile uint32_t LCKR;				/*GPIO port configuration lock register... Address offset:0x1C*/
	volatile uint32_t AFRL;				/*GPIO alternate function low register... Address offset: 0x20*/
	volatile uint32_t AFRH;				/*GPIO alternate function high register... Address offset: 0x24*/
}GPIO_RegDef_t;

/*
 * Define the GPIO ports
 */
#define GPIOA							((GPIO_RegDef_t*)GPIOA_PERI_BASEADDR)
#define GPIOB							((GPIO_RegDef_t*)GPIOB_PERI_BASEADDR)
#define GPIOC							((GPIO_RegDef_t*)GPIOC_PERI_BASEADDR)
#define GPIOD							((GPIO_RegDef_t*)GPIOD_PERI_BASEADDR)
#define GPIOE							((GPIO_RegDef_t*)GPIOE_PERI_BASEADDR)
#define GPIOF							((GPIO_RegDef_t*)GPIOF_PERI_BASEADDR)
#define GPIOG							((GPIO_RegDef_t*)GPIOG_PERI_BASEADDR)
#define GPIOH							((GPIO_RegDef_t*)GPIOH_PERI_BASEADDR)

typedef struct{
	volatile uint32_t SR;				/*Status register... Address offset: 0x00*/
	volatile uint32_t DR;				/*Data register... Address offset: 0x04*/
	volatile uint32_t BRR;				/*Baud rate register... Address offset: 0x08*/
	volatile uint32_t CR1;				/*Control register 1... Address offset: 0x0C*/
	volatile uint32_t CR2;				/*Control register 2... Address offset: 0x10*/
	volatile uint32_t CR3;				/*Control register 3... Address offset: 0x14*/
	volatile uint32_t GTPR;				/*Guard time and prescaler register... Address offset: 0x18*/
}USART_RegDef_t;

/*
 * Define the USART peripheral
 */
#define USART1							((USART_RegDef_t*)USART1_PERI_BASEADDR)
#define USART2							((USART_RegDef_t*)USART2_PERI_BASEADDR)
#define USART3							((USART_RegDef_t*)USART3_PERI_BASEADDR)
#define USART6							((USART_RegDef_t*)USART6_PERI_BASEADDR)

typedef struct{
	volatile uint32_t CR1;				/*SPI control register 1... Address offset: 0x00*/
	volatile uint32_t CR2;				/*SPI control register 2... Address offset: 0x04*/
	volatile uint32_t SR;				/*SPI status register... Address offset: 0x08*/
	volatile uint32_t DR;				/*SPI data register... Address offset: 0x0C*/
	volatile uint32_t CRCPR;			/*SPI CRC polynomial register... Address offset: 0x10*/
	volatile uint32_t RXCRCR;			/*SPI RX CRC register... Address offset: 0x14*/
	volatile uint32_t TXCRCR;			/*SPI TX CRC register... Address offset: 0x18*/
	volatile uint32_t I2SCFGR;			/*SPI_I2S configuration register... Address offset: 0x1C*/
	volatile uint32_t I2SPR;			/*SPI_I2S prescaler register... Address offset: 0x20*/
}SPI_RegDef_t;

/*
 * Define SPIx peripherals
 */
#define SPI1							((SPI_RegDef_t*)SPI1_PERI_BASEADDR)
#define SPI2							((SPI_RegDef_t*)SPI2_PERI_BASEADDR)
#define SPI3							((SPI_RegDef_t*)SPI3_PERI_BASEADDR)
#define SPI4							((SPI_RegDef_t*)SPI4_PERI_BASEADDR)

typedef struct{
	volatile uint32_t CR1;				/*I2C control register 1... Address offset: 0x00*/
	volatile uint32_t CR2;				/*I2C control register 2... Address offset: 0x04*/
	volatile uint32_t OAR1;				/*I2C own address register 1... Address offset: 0x08*/
	volatile uint32_t OAR2;				/*I2C own address register 2... Address offset: 0x0C*/
	volatile uint32_t DR;				/*I2C data register... Address offset: 0x10*/
	volatile uint32_t SR1;				/*I2C status register 1... Address offset: 0x14*/
	volatile uint32_t SR2;				/*I2C status register 2... Address offset: 0x18*/
	volatile uint32_t CCR;				/*I2C clock control register... Address offset: 0x1C*/
	volatile uint32_t TRISE;			/*I2C TRISE register... Address offset: 0x20*/
	volatile uint32_t FLTR;				/*I2C FLTR register... Address offset: 0x24*/
}I2C_RegDef_t;

/*
 * Define the I2Cx peripherals
 */
#define I2C1							((I2C_RegDef_t*)I2C1_PERI_BASEADDR)
#define I2C2							((I2C_RegDef_t*)I2C2_PERI_BASEADDR)
#define I2C3							((I2C_RegDef_t*)I2C3_PERI_BASEADDR)

typedef struct{
	volatile uint32_t MEMRMP;			/*SYSCFG memory remap register... Address offset: 0x00*/
	volatile uint32_t PMC;				/*SYSCFG peripheral mode configuration register... Address offset: 0x04*/
	volatile uint32_t EXTICR[4];			/*SYSCFG external interrupt configuration register 1... Address offset: 0x08*/
	volatile uint32_t CMPCR;			/*Compensation cell control register... Address offset: 0x20*/
	volatile uint32_t CFCGR;			/*SYSCFG configuration register...Address offset:0x2C*/
}SYSCFG_RegDef_t;

#define SYSCFG							((SYSCFG_RegDef_t*)SYSCFG_PERI_BASEADDR)

typedef struct{
	volatile uint32_t CR;				/*RCC clock control register... Address offset: 0x00*/
	volatile uint32_t PLLCFGR;			/*RCC PLL configuration register... Address offset: 0x04*/
	volatile uint32_t CFGR;				/*RCC clock configuration register... Address offset: 0x08*/
	volatile uint32_t CIR;				/*RCC clock interrupt register... Address offset: 0x0C*/
	volatile uint32_t AHB1RSTR;			/*RCC AHB1 peripheral reset register... Address offset: 0x10*/
	volatile uint32_t AHB2RSTR;			/*RCC AHB2 peripheral reset register... Address offset: 0x14*/
	volatile uint32_t AHB3RSTR;			/*RCC AHB3 peripheral reset register... Address offset: 0x18*/
	uint32_t RESERVERD0;				/*Reserved memory: Address offset: 0x1C*/
	volatile uint32_t APB1RSTR;			/*RCC APB1 peripheral reset register... Address offset: 0x20*/
	volatile uint32_t APB2RSTR;			/*RCC APB2 peripheral reset register... Address offset: 0x24*/
	uint32_t RESERVED1[2];				/*Reserverd memory: Address offset: 0x28,0x2C*/
	volatile uint32_t AHB1ENR;			/*RCC AHB1 peripheral clock enable register... Address offset: 0x30*/
	volatile uint32_t AHB2ENR;			/*RCC AHB2 peripheral clock enable register... Address offset: 0x34*/
	volatile uint32_t AHB3ENR;			/*RCC AHB3 peripheral clock enable register... Address offset: 0x38*/
	uint32_t RESERVED2;					/*Reserved memory: Address offset: 0x3C*/
	volatile uint32_t APB1ENR;			/*RCC APB1 peripheral clock enable register... Address offset: 0x40*/
	volatile uint32_t APB2ENR;			/*RCC APB2 peripheral clock enable register... Address offset: 0x44*/
	uint32_t RESERVED3[2];				/*Reserved memory  Address offset: 0x48,0x4C*/
	volatile uint32_t AHB1LPENR;		/*RCC AHB1 peripheral clock enable in low power mode register... Address offset: 0x50*/
	volatile uint32_t AHB2LPENR;		/*RCC AHB2 peripheral clock enable in low power mode register... Address offset: 0x54*/
	volatile uint32_t AHB3LPENR;		/*RCC AHB3 peripheral clock enable in low power mode register... Address offset: 0x58*/
	uint32_t RESERVED4; 				/*Reseerved memory Address offset: 0x5C*/
	volatile uint32_t APB1LPENR;		/*RCC APB1 peripheral clock enable in low power mode register... Address offset: 0x60*/
	volatile uint32_t APB2LPENR;		/*RCC APB2 peripheral clock enabled in low power mode register... Address offset: 0x64*/
	uint32_t RESERVED5[2];				/*Reserved memory, Address offset: 0x68, 0x6C*/
	volatile uint32_t BDCR;				/*RCC Backup domain control register... Address offset: 0x70*/
	volatile uint32_t CSR;				/*RCC clock control & status register... Address offset: 0x74*/
	uint32_t RESERVED6[2];				/*Reserved memory, Address offset: 0x78,0x7C*/
	volatile uint32_t SSCGR;			/*RCC spread spectrum clock generation register... Address offset: 0x80*/
	volatile uint32_t PLL12SCFGR;		/*RCC PLLI2S configuration register... Address offset: 0x84*/
	volatile uint32_t PLLSAICFGR;		/*RCC PLL configuration register... Address offset: 0x88*/
	volatile uint32_t DCKCFGR;			/*RCC dedicated clock configuration register... Address offset: 0x8C*/
	volatile uint32_t CKGATENR;			/*RCC clocks gated enable register... Address offset: 0x90*/
	volatile uint32_t DCKCFGR2;			/*RCC dedicated clocks configuration register 2... Address offset: 0x94*/
}RCC_RegDef_t;

typedef struct{
	uint32_t IMR;						/*Interrupt mask register... Address offset: 0x00*/
	uint32_t EMR;						/*Event mask register...  Address offset: 0x04*/
	uint32_t RTSR;						/*Rising trigger selection register... 	Address offset: 0x08*/
	uint32_t FTSR;						/*Falling trigger selection register...Address offset: 0x0C*/
	uint32_t SWEIR;						/*Software interrupt event register... Address offset: 0x10*/
	uint32_t PR;						/*Pending register... Address offset: 0x14*/
}EXTI_RegDef_t;

#define EXTI ((EXTI_RegDef_t*)EXTI_PERI_BASEADDR)
#define RCC ((RCC_RegDef_t*)RCC_PERI_BASEADDR)

/*
 * Enabling GPIO peripheral clock
 */
#define GPIOA_PCLK_EN()					(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()					(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()					(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()					(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()					(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()					(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()					(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()					(RCC->AHB1ENR |= (1 << 7))

/*
 * Enabling the clock for the SYSCFG peripheral
 */
#define SYSCFG_PCLK_EN()				(RCC->APB2ENR |= (1 << 14));

/*
 * Enabling SPI peripheral clock
 */
#define SPI2_PCLK_EN()					(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()					(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()					(RCC->APB2ENR |= (1 << 13))
#define SPI1_PCLK_EN()					(RCC->APB2ENR |= (1 << 12))
/*
 * Disabling SPI peripheral clock
 */
#define SPI2_PCLK_DIS()					(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DIS()					(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DIS()					(RCC->APB2ENR &= ~(1 << 13))
#define SPI1_PCLK_DIS()					(RCC->APB2ENR &= ~(1 << 12))

/*
 * Disabling GPIO peripheral clock
 */
#define GPIOA_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DIS()				(RCC->AHB1ENR &= ~(1 << 7))

#define RESET_GPIOA_REG()				RCC->AHB1RSTR |= 0x1;\
										RCC->AHB1RSTR &= ~(0x1)
#define RESET_GPIOB_REG()				RCC->AHB1RSTR |= (0x1 << 1);\
										RCC->AHB1RSTR &= ~(0x1 << 1)
#define RESET_GPIOC_REG()				RCC->AHB1RSTR |= (0x1 << 2);\
										RCC->AHB1RSTR &= ~(0x1 << 2)
#define RESET_GPIOD_REG()				RCC->AHB1RSTR |= (0x1 << 3);\
										RCC->AHB1RSTR &= ~(0x1 << 3)
#define RESET_GPIOE_REG()				RCC->AHB1RSTR |= (0x1 << 4);\
										RCC->AHB1RSTR &= ~(0x1 << 4)
#define RESET_GPIOF_REG()				RCC->AHB1RSTR |= (0x1 << 5);\
										RCC->AHB1RSTR &= ~(0x1 << 5)
#define RESET_GPIOG_REG()				RCC->AHB1RSTR |= (0x1 << 6);\
										RCC->AHB1RSTR &= ~(0x1 << 6)
#define RESET_GPIOH_REG()				RCC->AHB1RSTR |= (0x1 << 7);\
										RCC->AHB1RSTR &= ~(0x1 << 7)

/*
 * RESET SPI PERIPHERALS
 */
#define RESET_SPI3_REG()					RCC->APB1RSTR |= (0x1 << 15);\
											RCC->APB1RSTR &= ~(0x1 << 15)
#define RESET_SPI2_REG()					RCC->APB1RSTR |= (0x1 << 14);\
											RCC->APB1RSTR &= ~(0x1 << 14)
#define RESET_SPI1_REG()					RCC->APB2RSTR |= (0x1 << 12);\
											RCC->APB2RSTR &= ~(0x1 << 12)
#define RESET_SPI4_REG()					RCC->APB2RSTR |= (0x1 << 13);\
											RCC->APB2RSTR &= ~(0x1 << 13)

/******************************************Definition of the SPI_CR1 bit field register**************************/
#define CR_CPHA							0
#define CR_CPOL							1
#define CR_MSTR							2
#define CR_BR							3
#define CR_SPE							6
#define CR_LSBFIRST						7
#define CR_SSI							8
#define CR_SSM							9
#define CR_RXONLY						10
#define CR_DFF							11
#define CR_CRCNEXT						12
#define CR_CRCEN						13
#define CR_BIDIOE						14
#define CR_BIDIMODE						15

/******************************************Definition of the SPI_CR2 bit field register**************************/
#define CR_RXDMAEN						0
#define CR_TXDMAEN						1
#define CR_SSOE							2
#define CR_FRF							4
#define CR_ERRIE						5
#define CR_RXNEIE						6
#define CR_TXEIE						7

/******************************************Definition of the SPI_SR bit field register**************************/
#define CR_RXNE							0
#define CR_TXE							1
#define CR_CHSIDE						2
#define CR_UDR							3
#define CR_CRCERR						4
#define CR_MODF							5
#define CR_OVR							6
#define CR_BSY							7
#define CR_FRE							8

/*
 * Status flags for SPI
 */
#define SR_FRE							(0x1 << CR_FRE)
#define SR_BSY							(0x1 << CR_BSY)
#define SR_OVR							(0x1 << CR_MODF)
#define SR_CRCERR						(0x1 << CR_CRCERR)
#define SR_UDR							(0x1 << CR_UDR)
#define SR_CHSIDE						(0x1 << CR_CHSIDE)
#define SR_TXE							(0x1 << CR_TXE)
#define SR_RXNE							(0x1 << CR_RXNE)

/*
 * IRQ number for EXTI lines
 */
#define EXTI0_IRQ_NUM					6
#define EXTI1_IRQ_NUM					7
#define EXTI2_IRQ_NUM					8
#define EXTI3_IRQ_NUM					9
#define EXTI4_IRQ_NUM					10
#define EXTI9_5_IRQ_NUM					23
#define EXTI15_10_IRQ_NUM				40
/*
 * IRQ number for SPI peripherals
 */
#define SPI1_IRQ_NUM					35
#define SPI2_IRQ_NUM					36
#define SPI3_IRQ_NUM					51
#define SPI4_IRQ_NUM					84

#endif /* STM32F44XX__DRIVER_H_ */

