#ifndef __CAMERA_SCCB_H
#define __CAMERA_SCCB_H

#include "main.h"
#include <stdint.h>

/* 定义ATK-MC7725F的SCCB通讯引脚是否有外接上拉电阻 */
#define CAMERA_SCCB_GPIO_PULLUP            1

/* 引脚定义 */
#define CAMERA_SCCB_SCL_GPIO_PORT          GPIOD
#define CAMERA_SCCB_SCL_GPIO_PIN           GPIO_PIN_3
#define CAMERA_SCCB_SCL_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define CAMERA_SCCB_SDA_GPIO_PORT          GPIOG
#define CAMERA_SCCB_SDA_GPIO_PIN           GPIO_PIN_13
#define CAMERA_SCCB_SDA_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)

/* IO操作 */
#define CAMERA_SCCB_SCL(x)                 do{ x ?                                                                                                 \
                                                    HAL_GPIO_WritePin(CAMERA_SCCB_SCL_GPIO_PORT, CAMERA_SCCB_SCL_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(CAMERA_SCCB_SCL_GPIO_PORT, CAMERA_SCCB_SCL_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
#define CAMERA_SCCB_SDA(x)                 do{ x ?                                                                                                 \
                                                    HAL_GPIO_WritePin(CAMERA_SCCB_SDA_GPIO_PORT, CAMERA_SCCB_SDA_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(CAMERA_SCCB_SDA_GPIO_PORT, CAMERA_SCCB_SDA_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
#define CAMERA_SCCB_READ_SDA()             HAL_GPIO_ReadPin(CAMERA_SCCB_SDA_GPIO_PORT, CAMERA_SCCB_SDA_GPIO_PIN)

/* 操作函数 */
void camera_sccb_init(void);                                                       /* ATK-MC7725F SCCB接口初始化 */
void camera_sccb_3_phase_write(uint8_t id_addr, uint8_t sub_addr, uint8_t dat);    /* SCCB接口3阶段写传输 */
void camera_sccb_2_phase_write(uint8_t id_addr, uint8_t sub_addr);                 /* SCCB接口2阶段写传输 */
void camera_sccb_2_phase_read(uint8_t id_addr, uint8_t *dat);                      /* SCCB接口2阶段读传输 */

#endif
