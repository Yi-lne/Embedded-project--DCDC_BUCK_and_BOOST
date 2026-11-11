/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BOOST_ADJ_SWITCH_Pin GPIO_PIN_0
#define BOOST_ADJ_SWITCH_GPIO_Port GPIOA
#define BOOST_ADJ_SWITCH_EXTI_IRQn EXTI0_IRQn
#define BOOST_ADJ_ADC_Pin GPIO_PIN_2
#define BOOST_ADJ_ADC_GPIO_Port GPIOA
#define BOOST_ADJ_DRIVER_Pin GPIO_PIN_3
#define BOOST_ADJ_DRIVER_GPIO_Port GPIOA
#define VOLTMETER_ADC_Pin GPIO_PIN_4
#define VOLTMETER_ADC_GPIO_Port GPIOA
#define BUCK_ADJ_ADC_Pin GPIO_PIN_6
#define BUCK_ADJ_ADC_GPIO_Port GPIOA
#define BUCK_ADJ_DRIVER_Pin GPIO_PIN_10
#define BUCK_ADJ_DRIVER_GPIO_Port GPIOB
#define BUCK_ADJ_SWITCH_Pin GPIO_PIN_11
#define BUCK_ADJ_SWITCH_GPIO_Port GPIOB
#define BUCK_ADJ_SWITCH_EXTI_IRQn EXTI15_10_IRQn

/* USER CODE BEGIN Private defines */



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
