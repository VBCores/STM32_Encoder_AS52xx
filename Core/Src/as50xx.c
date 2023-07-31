/*
 * AS50xx.c
 *
 *  Created on: Jul 31, 2023
 *      Author: VR
 */

#include "as50xx.h"
#include "spi.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#if (_ENCODER_USE_FREERTOS == 1)
#include "cmsis_os.h"
#define as50_delay(x)   osDelay(x)
#else
#define as50_delay(x)   HAL_Delay(x)
#endif

uint16_t spiT = 0x3FFF; //read register
uint16_t spiR, rv;
//spiT = 0x3FFF;

HAL_StatusTypeDef rstatus;

uint16_t as50_read(uint32_t timeout)
{
	  HAL_GPIO_WritePin(_ENCODER_NSS_GPIO, _ENCODER_NSS_PIN, GPIO_PIN_RESET);
	  as50_delay(1);
	  rstatus = HAL_SPI_TransmitReceive(&_ENCODER_SPI, (uint8_t*)&spiT, (uint8_t*)&spiR, 1, 100);
	  as50_delay(1);
	  rv = spiR & _ENCODER_READMASK;
	  HAL_GPIO_WritePin(_ENCODER_NSS_GPIO, _ENCODER_NSS_PIN, GPIO_PIN_SET);
	  return rv;
}
