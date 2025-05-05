/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define OV_WRST_Pin GPIO_PIN_6
#define OV_WRST_GPIO_Port GPIOE
#define OV_D0_Pin GPIO_PIN_0
#define OV_D0_GPIO_Port GPIOF
#define OV_D1_Pin GPIO_PIN_1
#define OV_D1_GPIO_Port GPIOF
#define OV_D2_Pin GPIO_PIN_2
#define OV_D2_GPIO_Port GPIOF
#define OV_D3_Pin GPIO_PIN_3
#define OV_D3_GPIO_Port GPIOF
#define OV_D4_Pin GPIO_PIN_4
#define OV_D4_GPIO_Port GPIOF
#define OV_D5_Pin GPIO_PIN_5
#define OV_D5_GPIO_Port GPIOF
#define OV_D6_Pin GPIO_PIN_6
#define OV_D6_GPIO_Port GPIOF
#define OV_D7_Pin GPIO_PIN_7
#define OV_D7_GPIO_Port GPIOF
#define JS_Z_Pin GPIO_PIN_10
#define JS_Z_GPIO_Port GPIOF
#define FATFS_SIG_Pin GPIO_PIN_0
#define FATFS_SIG_GPIO_Port GPIOC
#define OV_RRST_Pin GPIO_PIN_2
#define OV_RRST_GPIO_Port GPIOC
#define OV_OE_Pin GPIO_PIN_3
#define OV_OE_GPIO_Port GPIOC
#define JS_X_Pin GPIO_PIN_5
#define JS_X_GPIO_Port GPIOA
#define JS_Y_Pin GPIO_PIN_6
#define JS_Y_GPIO_Port GPIOA
#define OV_VSYNC_Pin GPIO_PIN_7
#define OV_VSYNC_GPIO_Port GPIOA
#define OV_SCL_Pin GPIO_PIN_4
#define OV_SCL_GPIO_Port GPIOC
#define DS_IN_Pin GPIO_PIN_0
#define DS_IN_GPIO_Port GPIOG
#define OLED_SCL_Pin GPIO_PIN_10
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_11
#define OLED_SDA_GPIO_Port GPIOB
#define KB_COL4_Pin GPIO_PIN_14
#define KB_COL4_GPIO_Port GPIOD
#define KB_COL3_Pin GPIO_PIN_15
#define KB_COL3_GPIO_Port GPIOD
#define KB_COL2_Pin GPIO_PIN_2
#define KB_COL2_GPIO_Port GPIOG
#define KB_COL1_Pin GPIO_PIN_3
#define KB_COL1_GPIO_Port GPIOG
#define KB_ROW5_Pin GPIO_PIN_4
#define KB_ROW5_GPIO_Port GPIOG
#define KB_ROW4_Pin GPIO_PIN_5
#define KB_ROW4_GPIO_Port GPIOG
#define KB_ROW3_Pin GPIO_PIN_6
#define KB_ROW3_GPIO_Port GPIOG
#define KB_ROW2_Pin GPIO_PIN_7
#define KB_ROW2_GPIO_Port GPIOG
#define KB_ROW1_Pin GPIO_PIN_8
#define KB_ROW1_GPIO_Port GPIOG
#define OV_SDA_Pin GPIO_PIN_6
#define OV_SDA_GPIO_Port GPIOC
#define MCO_Pin GPIO_PIN_8
#define MCO_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_14
#define LED_GPIO_Port GPIOG
#define OV_WEN_Pin GPIO_PIN_6
#define OV_WEN_GPIO_Port GPIOB
#define OV_RCLK_Pin GPIO_PIN_7
#define OV_RCLK_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
