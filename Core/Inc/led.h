#ifndef __LED_H
#define __LED_H

typedef struct
{
    unsigned char r, g, b;
} led_color;

typedef struct
{
    led_color c[17];
} led_ctx;

void led_send_data(led_ctx ctx);



#endif // __LED_H