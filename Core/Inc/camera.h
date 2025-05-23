#ifndef __CAMERA_H
#define __CAMERA_H
#include <stdint.h>

/* 定义是否使用同一GPIO端口连接ATK-MC7725F的D0~D7数据引脚 */
#define CAMERA_DATA_PIN_IN_SAME_GPIO_PORT  1

#if (CAMERA_DATA_PIN_IN_SAME_GPIO_PORT != 0)
/* 连接ATK-MC7725F模块D0~D7的GPIO端口 */
#define CAMERA_DATE_GPIO_PORT  GPIOC
/* 一次性读取连接至ATK-MC7725F的D0~D7的GPIO引脚数据的掩码 */
#define CAMERA_DATA_READ_MASK  0x00FF
#endif

/* 引脚定义 */
#define CAMERA_WRST_GPIO_PORT              GPIOD
#define CAMERA_WRST_GPIO_PIN               GPIO_PIN_6
#define CAMERA_WRST_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define CAMERA_RRST_GPIO_PORT              GPIOG
#define CAMERA_RRST_GPIO_PIN               GPIO_PIN_14
#define CAMERA_RRST_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)
#define CAMERA_OE_GPIO_PORT                GPIOG
#define CAMERA_OE_GPIO_PIN                 GPIO_PIN_15
#define CAMERA_OE_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)
#define CAMERA_D0_GPIO_PORT                GPIOC
#define CAMERA_D0_GPIO_PIN                 GPIO_PIN_0
#define CAMERA_D0_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_D1_GPIO_PORT                GPIOC
#define CAMERA_D1_GPIO_PIN                 GPIO_PIN_1
#define CAMERA_D1_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_D2_GPIO_PORT                GPIOC
#define CAMERA_D2_GPIO_PIN                 GPIO_PIN_2
#define CAMERA_D2_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_D3_GPIO_PORT                GPIOC
#define CAMERA_D3_GPIO_PIN                 GPIO_PIN_3
#define CAMERA_D3_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_D4_GPIO_PORT                GPIOC
#define CAMERA_D4_GPIO_PIN                 GPIO_PIN_4
#define CAMERA_D4_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_D5_GPIO_PORT                GPIOC
#define CAMERA_D5_GPIO_PIN                 GPIO_PIN_5
#define CAMERA_D5_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_D6_GPIO_PORT                GPIOC
#define CAMERA_D6_GPIO_PIN                 GPIO_PIN_6
#define CAMERA_D6_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_D7_GPIO_PORT                GPIOC
#define CAMERA_D7_GPIO_PIN                 GPIO_PIN_7
#define CAMERA_D7_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define CAMERA_RCLK_GPIO_PORT              GPIOB
#define CAMERA_RCLK_GPIO_PIN               GPIO_PIN_4
#define CAMERA_RCLK_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOB_CLK_ENABLE();   \
                                                    __HAL_RCC_AFIO_CLK_ENABLE();    \
                                                    __HAL_AFIO_REMAP_SWJ_NOJTAG();  \
                                                }while(0)
#define CAMERA_WEN_GPIO_PORT               GPIOB
#define CAMERA_WEN_GPIO_PIN                GPIO_PIN_3
#define CAMERA_WEN_GPIO_CLK_ENABLE()       do{ __HAL_RCC_GPIOB_CLK_ENABLE();   \
                                                    __HAL_RCC_AFIO_CLK_ENABLE();    \
                                                    __HAL_AFIO_REMAP_SWJ_NOJTAG();  \
                                                }while(0)
#define CAMERA_VSYNC_INT_GPIO_PORT         GPIOA
#define CAMERA_VSYNC_INT_GPIO_PIN          GPIO_PIN_8
#define CAMERA_VSYNC_INT_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)
#define CAMERA_VSYNC_INT_IRQn              EXTI9_5_IRQn
#define CAMERA_VSYNC_INT_IRQHandler        EXTI9_5_IRQHandler

/* IO操作 */
#define CAMERA_WRST(x)                     do{ x ?                                                                                         \
                                                    HAL_GPIO_WritePin(CAMERA_WRST_GPIO_PORT, CAMERA_WRST_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(CAMERA_WRST_GPIO_PORT, CAMERA_WRST_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
#define CAMERA_RRST(x)                     do{ x ?                                                                                         \
                                                    HAL_GPIO_WritePin(CAMERA_RRST_GPIO_PORT, CAMERA_RRST_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(CAMERA_RRST_GPIO_PORT, CAMERA_RRST_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
#define CAMERA_OE(x)                       do{ x ?                                                                                         \
                                                    HAL_GPIO_WritePin(CAMERA_OE_GPIO_PORT, CAMERA_OE_GPIO_PIN, GPIO_PIN_SET) :        \
                                                    HAL_GPIO_WritePin(CAMERA_OE_GPIO_PORT, CAMERA_OE_GPIO_PIN, GPIO_PIN_RESET);       \
                                                }while(0)
#define CAMERA_RCLK(x)                     do{ x ?                                                                                         \
                                                    (CAMERA_RCLK_GPIO_PORT->BSRR = (uint32_t)CAMERA_RCLK_GPIO_PIN) :                  \
                                                    (CAMERA_RCLK_GPIO_PORT->BRR = (uint32_t)CAMERA_RCLK_GPIO_PIN);                    \
                                                }while(0)
#define CAMERA_WEN(x)                      do{ x ?                                                                                         \
                                                    HAL_GPIO_WritePin(CAMERA_WEN_GPIO_PORT, CAMERA_WEN_GPIO_PIN, GPIO_PIN_SET) :      \
                                                    HAL_GPIO_WritePin(CAMERA_WEN_GPIO_PORT, CAMERA_WEN_GPIO_PIN, GPIO_PIN_RESET);     \
                                                }while(0)

/* ATK-MC7725F SCCB通讯地址 */
#define CAMERA_SCCB_ADDR   0x21


/* ATK-MC7725F模块在不同输出模式下的最大输出分辨率 */
#define CAMERA_VGA_WIDTH_MAX   640
#define CAMERA_VGA_HEIGHT_MAX  480
#define CAMERA_QVGA_WIDTH_MAX  320
#define CAMERA_QVGA_HEIGHT_MAX 240

/* ATK-MC7725F模块灯光模式枚举 */
typedef enum
{
    CAMERA_LIGHT_MODE_AUTO = 0x00,         /* Auto */
    CAMERA_LIGHT_MODE_SUNNY,               /* Sunny */
    CAMERA_LIGHT_MODE_CLOUDY,              /* Cloudy */
    CAMERA_LIGHT_MODE_OFFICE,              /* Office */
    CAMERA_LIGHT_MODE_HOME,                /* Home */
    CAMERA_LIGHT_MODE_NIGHT,               /* Night */
} camera_light_mode_t;

/* ATK-MC7725F模块色彩饱和度枚举 */
typedef enum
{
    CAMERA_COLOR_SATURATION_0 = 0x00,      /* +4 */
    CAMERA_COLOR_SATURATION_1,             /* +3 */
    CAMERA_COLOR_SATURATION_2,             /* +2 */
    CAMERA_COLOR_SATURATION_3,             /* +1 */
    CAMERA_COLOR_SATURATION_4,             /* 0 */
    CAMERA_COLOR_SATURATION_5,             /* -1 */
    CAMERA_COLOR_SATURATION_6,             /* -2 */
    CAMERA_COLOR_SATURATION_7,             /* -3 */
    CAMERA_COLOR_SATURATION_8,             /* -4 */
} camera_color_saturation_t;

/* ATK-MC7725F模块亮度枚举 */
typedef enum
{
    CAMERA_BRIGHTNESS_0 = 0x00,            /* +4 */
    CAMERA_BRIGHTNESS_1,                   /* +3 */
    CAMERA_BRIGHTNESS_2,                   /* +2 */
    CAMERA_BRIGHTNESS_3,                   /* +1 */
    CAMERA_BRIGHTNESS_4,                   /* 0 */
    CAMERA_BRIGHTNESS_5,                   /* -1 */
    CAMERA_BRIGHTNESS_6,                   /* -2 */
    CAMERA_BRIGHTNESS_7,                   /* -3 */
    CAMERA_BRIGHTNESS_8,                   /* -4 */
} camera_brightness_t;

/* ATK-MC7725F模块对比度枚举 */
typedef enum
{
    CAMERA_CONTRAST_0 = 0x00,              /* +4 */
    CAMERA_CONTRAST_1,                     /* +3 */
    CAMERA_CONTRAST_2,                     /* +2 */
    CAMERA_CONTRAST_3,                     /* +1 */
    CAMERA_CONTRAST_4,                     /* 0 */
    CAMERA_CONTRAST_5,                     /* -1 */
    CAMERA_CONTRAST_6,                     /* -2 */
    CAMERA_CONTRAST_7,                     /* -3 */
    CAMERA_CONTRAST_8,                     /* -4 */
} camera_contrast_t;

/* ATK-MC7725F模块特殊效果枚举 */
typedef enum
{
    CAMERA_SPECIAL_EFFECT_NORMAL = 0x00,   /* Normal */
    CAMERA_SPECIAL_EFFECT_BW,              /* B&W */
    CAMERA_SPECIAL_EFFECT_BLUISH,          /* Bluish */
    CAMERA_SPECIAL_EFFECT_SEPIA,           /* Sepia */
    CAMERA_SPECIAL_EFFECT_REDISH,          /* Redish */
    CAMERA_SPECIAL_EFFECT_GREENISH,        /* Greenish */
    CAMERA_SPECIAL_EFFECT_NEGATIVE,        /* Negative */
} camera_special_effect_t;

/* ATK-MC7725F模块输出模式枚举 */
typedef enum
{
    CAMERA_OUTPUT_MODE_VGA = 0x00,         /* VGA */
    CAMERA_OUTPUT_MODE_QVGA,               /* QVGA */
} camera_output_mode_t;

/* ATK-MC7725F模块获取图像方式枚举 */
typedef enum
{
    CAMERA_GET_FRAME_TYPE_NOINC = 0x00,    /* 目的地址不自增 */
    CAMERA_GET_FRAME_TYPE_AUTO_INC,        /* 目的地址自增 */
} camera_get_frame_type_t;

/* 错误代码 */
#define CAMERA_EOK     0   /* 没有错误 */
#define CAMERA_ERROR   1   /* 错误 */
#define CAMERA_EINVAL  2   /* 非法参数 */
#define CAMERA_EEMPTY  3   /* 资源为空 */

/* 操作函数 */
uint8_t camera_init(void);                                                                     /* 初始化ATK-MC7725F模块 */
uint8_t camera_set_light_mode(camera_light_mode_t mode);                                  /* 设置ATK-MC7725F模块灯光模式 */
uint8_t camera_set_color_saturation(camera_color_saturation_t saturation);                /* 设置ATK-MC7725F模块色彩饱和度 */
uint8_t camera_set_brightness(camera_brightness_t brightness);                            /* 设置ATK-MC7725F模块亮度 */
uint8_t camera_set_contrast(camera_contrast_t contrast);                                  /* 设置ATK-MC7725F模块对比度 */
uint8_t camera_set_special_effect(camera_special_effect_t effect);                        /* 设置ATK-MC7725F模块特殊效果 */
uint8_t camera_set_output(uint16_t width, uint16_t height, camera_output_mode_t mode);    /* 设置ATK-MC7725F模块输出模式 */
void camera_enable_output(void);                                                               /* 使能ATK-MD7725F模块输出图像 */
void camera_disable_output(void);                                                              /* 禁止ATK-MC7725F模块输出图像 */
uint16_t camera_get_output_width(void);                                                        /* 获取ATK-MC7725F模块输出图像宽度 */
uint16_t camera_get_output_height(void);                                                       /* 获取ATK-MC7725F模块输出图像高度 */
uint8_t camera_get_frame(volatile uint16_t *dts, camera_get_frame_type_t type);           /* 获取ATK-MC7725F模块输出的一帧图像数据 */


#endif // __CAMERA_H