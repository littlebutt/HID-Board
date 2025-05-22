#include "led.h"
#include "main.h"
#include "stm32f103xe.h"


#define LED_GPIO        GPIOG
#define LED_PIN_MASK    (1U << 14)

#define LED_HIGH()      (LED_GPIO->BSRR = LED_PIN_MASK)
#define LED_LOW()       (LED_GPIO->BRR  = LED_PIN_MASK)

// 延时函数：72MHz 下每个循环约 13.9ns
static inline void delay_cycles(uint32_t cycles)
{
    while (cycles--) {
        __asm volatile("nop");
    }
}

// 发送一个 bit（1 or 0）
static inline void send_bit(uint8_t bit)
{
    if (bit)
    {
        LED_HIGH();
        delay_cycles(20); // ≈ 700ns
        LED_LOW();
        delay_cycles(10); // ≈ 350ns
    }
    else
    {
        LED_HIGH();
        delay_cycles(7);  // ≈ 250ns
        LED_LOW();
        delay_cycles(23); // ≈ 800ns
    }
}

// 发送 24bit 颜色数据（G R B）
void _led_send_data(led_color color)
{
    uint8_t data[3] = { color.g, color.r, color.b };

    for (int byte = 0; byte < 3; byte++)
    {
        for (int bit = 0; bit < 8; bit++)
        {
            send_bit(data[byte] & (0x80 >> bit));
        }
    }

    // WS2812 reset：低电平 ≥ 50μs；72MHz下用 delay_cycles
    LED_LOW();
    for (volatile int i = 0; i < 3000; i++) {
        __NOP();  // 粗略估算：~50-60μs
    }
}

void led_send_data(led_ctx ctx)
{
    for (int i = 0; i < 17; i++)
    {
        _led_send_data(ctx.c[i]);
    }
}