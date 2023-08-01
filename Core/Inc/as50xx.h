/*
 * as50xx.h
 *
 *  Created on: Jul 31, 2023
 *      Author: VR
 */

#ifndef INC_AS50XX_H_
#define INC_AS50XX_H_


#include "stm32g4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define		_ENCODER_SPI			hspi3
#define		_ENCODER_USE_FREERTOS		0  /* NOT FreeRTOS by default */
#define     _ENCODER_NSS_GPIO GPIOA
#define     _ENCODER_NSS_PIN GPIO_PIN_15
#define 	_ENCODER_READMASK 0x3fff


/**
  * @brief  Read encoder data into given var
  * @param  given variable by ref
  * @param  timeout Timeout duration
  * @retval bool status
  */
bool as50_read(uint16_t * data, uint32_t timeout);

#ifdef __cplusplus
extern "C" {
#endif

#endif /* INC_AS50XX_H_ */
