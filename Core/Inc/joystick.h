#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "stdlib.h"

typedef struct
{
  int j_x, j_y, j_z;
  uint32_t j_value[2];
} joystick_ctx;

joystick_ctx *joystick_init(ADC_HandleTypeDef *hadc);

int joystick_get_value(joystick_ctx *ctx);

#endif // __JOYSTICK_H