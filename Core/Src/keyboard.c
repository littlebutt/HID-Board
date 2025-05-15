#include "keyboard.h"
#include "usbd_def.h"

#include <stdint.h>
#include <stm32f103xe.h>

extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t HID_Buffer[8] = {0};
uint8_t HID_Buffer_empty[8] = {0};
int keymap[18] = {
    0x53, // Num Lock
    0x54, // /
    0x55, // *
    0x56, // -
    0x5f, // 7
    0x60, // 8
    0x61, // 9
    0x57, // +
    0x5c, // 4
    0x5d, // 5
    0x5e, // 6
    0x59, // 1
    0x5a, // 2
    0x5b, // 3
    0x58, // Enter
    0x62, // 0
    0x63 // .
};

extern keyboard_ctx ctx;

void keyboard_send_report(int key)
{
    HID_Buffer[2] = key;
    HAL_Delay(10);
    USBD_HID_SendReport2(&hUsbDeviceFS, HID_Buffer, sizeof(HID_Buffer));
    HAL_Delay(10);
    USBD_HID_SendReport2(&hUsbDeviceFS, HID_Buffer_empty, sizeof(HID_Buffer_empty));
}

keyboard_ctx keyboard_new()
{
    keyboard_ctx ctx = {0};
    return ctx;
}

uint16_t TARGET_ROW_PIN[] = {KB_ROW1_Pin, KB_ROW2_Pin, KB_ROW3_Pin, KB_ROW4_Pin, KB_ROW5_Pin};
GPIO_TypeDef *TARGET_ROW_GPIO_PORT[] = {KB_ROW1_GPIO_Port, KB_ROW2_GPIO_Port, KB_ROW3_GPIO_Port, KB_ROW4_GPIO_Port, KB_ROW5_GPIO_Port};
uint16_t TARGET_COL_PIN[] = {KB_COL1_Pin, KB_COL2_Pin, KB_COL3_Pin, KB_COL4_Pin};
GPIO_TypeDef *TARGET_COL_GPIO_PORT[] = {KB_COL1_GPIO_Port, KB_COL2_GPIO_Port, KB_COL3_GPIO_Port, KB_COL4_GPIO_Port};

void keyboard_scan(keyboard_ctx *ctx)
{
    HAL_GPIO_WritePin(TARGET_ROW_GPIO_PORT[0], TARGET_ROW_PIN[0], GPIO_PIN_SET);
    for (int i = 1; i < 5; i++)
    {
        HAL_GPIO_WritePin(TARGET_ROW_GPIO_PORT[i], TARGET_ROW_PIN[i], GPIO_PIN_RESET);
    }
    for (int j = 0; j < 4; j++)
        {
            if (HAL_GPIO_ReadPin(TARGET_COL_GPIO_PORT[j], TARGET_COL_PIN[j]) == GPIO_PIN_SET)
            {
                keyboard_send_report(keymap[1]);
            }
        }
    // for (int i = 0; i < 5; i++)
    // {
    //     ctx->target_row_gpio_port = TARGET_ROW_GPIO_PORT[i];
    //     ctx->target_row_pin = TARGET_ROW_PIN[i];
    //     HAL_GPIO_WritePin(TARGET_ROW_GPIO_PORT[i], TARGET_ROW_PIN[i], GPIO_PIN_SET);
    //     HAL_Delay(20);
    //     for (int j = 0; j < 4; j++)
    //     {
    //         if (HAL_GPIO_ReadPin(TARGET_COL_GPIO_PORT[j], TARGET_COL_PIN[j]) == GPIO_PIN_SET)
    //         {
    //             keyboard_send_report(keymap[1]);
    //         }
    //     }
    //     ctx->target_row_gpio_port = 0;
    //     ctx->target_row_pin = 0;
    //     HAL_GPIO_WritePin(TARGET_ROW_GPIO_PORT[i], TARGET_ROW_PIN[i], GPIO_PIN_RESET);
    // }
}