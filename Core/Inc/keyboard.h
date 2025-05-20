#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "main.h"
#include "usbd_hid_keyboard.h"

typedef struct
{
    uint16_t target_row_pin;
    GPIO_TypeDef *target_row_gpio_port;
    int key_pressed[];
} keyboard_ctx;

keyboard_ctx keyboard_new();

void keyboard_scan(keyboard_ctx *ctx);

void keyboard_send_report(int key);

#endif // __KEYBOARD_H