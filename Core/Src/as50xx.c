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
uint16_t spiR;

bool as50_read(uint16_t * data, uint32_t timeout)
{
	  HAL_GPIO_WritePin(_ENCODER_NSS_GPIO, _ENCODER_NSS_PIN, GPIO_PIN_RESET);
	  as50_delay(1);

	  if (HAL_SPI_TransmitReceive(&_ENCODER_SPI, (uint8_t*)&spiT, (uint8_t*)data, 1, timeout) == HAL_OK)
	  {
		  as50_delay(1);
		  *data = *data & _ENCODER_READMASK;
		  HAL_GPIO_WritePin(_ENCODER_NSS_GPIO, _ENCODER_NSS_PIN, GPIO_PIN_SET);
	  }
	  else
	  {
		  HAL_GPIO_WritePin(_ENCODER_NSS_GPIO, _ENCODER_NSS_PIN, GPIO_PIN_SET);
		  Error_Handler();
	  }
	  return true;
}
