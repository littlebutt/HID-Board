#include "joystick.h"
#include "main.h"

joystick_ctx *joystick_init(ADC_HandleTypeDef *hadc)
{
  joystick_ctx *ctx = (joystick_ctx *)malloc(sizeof(joystick_ctx));
  if (ctx == NULL)
  {
    return NULL;
  }
  HAL_ADC_Start_DMA(hadc, ctx->j_value, 2);
  return ctx;
}

int joystick_get_value(joystick_ctx *ctx)
{
  ctx->j_x = ctx->j_value[0] & 0xFF;
  ctx->j_y = ctx->j_value[1] & 0xFF;
  ctx->j_z = HAL_GPIO_ReadPin(JS_Z_GPIO_Port, JS_Z_Pin);
  return 0;
}