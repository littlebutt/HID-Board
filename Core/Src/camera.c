#include "camera.h"
#include "camera_cfg.h"
#include "camera_sccb.h"
#include "stm32f103xe.h"
#include "delay.h"

#include <stdint.h>

/* ATK-MC7725F模块制造商ID和产品ID */
#define CAMERA_MID 0x7FA2
#define CAMERA_PID 0x7721

/* ATK-MC7725F模块数据结构体 */
static struct
{
    struct {
        uint16_t width;                 /* 宽度 */
        uint16_t height;                /* 高度 */
    } output;                           /* 输出图像大小 */
    struct {
        enum
        {
            FRAME_HANDLE_DONE = 0x00,   /* 处理完成 */
            FRAME_HANDLE_PEND,          /* 等待处理 */
        } handle_flag;                  /* 处理标记 */
        uint16_t count;                 /* 计数 */
    } frame;                            /* 接收图像帧信息 */
} g_camera_sta = {0};

/**
 * @brief       ATK-MC7725F模块写寄存器
 * @param       reg: 寄存器地址
 *              dat: 待写入的值
 * @retval      无
 */
static void camera_write_reg(uint8_t reg, uint8_t dat)
{
    camera_sccb_3_phase_write(CAMERA_SCCB_ADDR, reg, dat);
}

/**
 * @brief       ATK-MC7725F模块读寄存器
 * @param       reg: 寄存器的地址
 * @retval      读取到的寄存器值
 */
static uint8_t camera_read_reg(uint8_t reg)
{
    uint8_t dat = 0;
    
    camera_sccb_2_phase_write(CAMERA_SCCB_ADDR, reg);
    camera_sccb_2_phase_read(CAMERA_SCCB_ADDR, &dat);
    
    return dat;
}

/**
 * @brief       ATK-MC7725F模块硬件初始化
 * @param       无
 * @retval      无
 */
static void camera_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能GPIO时钟 */
    CAMERA_WRST_GPIO_CLK_ENABLE();
    CAMERA_RRST_GPIO_CLK_ENABLE();
    CAMERA_OE_GPIO_CLK_ENABLE();
    CAMERA_D0_GPIO_CLK_ENABLE();
    CAMERA_D1_GPIO_CLK_ENABLE();
    CAMERA_D2_GPIO_CLK_ENABLE();
    CAMERA_D3_GPIO_CLK_ENABLE();
    CAMERA_D4_GPIO_CLK_ENABLE();
    CAMERA_D5_GPIO_CLK_ENABLE();
    CAMERA_D6_GPIO_CLK_ENABLE();
    CAMERA_D7_GPIO_CLK_ENABLE();
    CAMERA_RCLK_GPIO_CLK_ENABLE();
    CAMERA_WEN_GPIO_CLK_ENABLE();
    CAMERA_VSYNC_INT_GPIO_CLK_ENABLE();
    
    /* 初始化WRST引脚 */
    gpio_init_struct.Pin    = CAMERA_WRST_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_WRST_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化RRST引脚 */
    gpio_init_struct.Pin    = CAMERA_RRST_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_RRST_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化OE引脚 */
    gpio_init_struct.Pin    = CAMERA_OE_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_OE_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D0引脚 */
    gpio_init_struct.Pin    = CAMERA_D0_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D0_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D1引脚 */
    gpio_init_struct.Pin    = CAMERA_D1_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D1_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D2引脚 */
    gpio_init_struct.Pin    = CAMERA_D2_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D2_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D3引脚 */
    gpio_init_struct.Pin    = CAMERA_D3_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D3_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D4引脚 */
    gpio_init_struct.Pin    = CAMERA_D4_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D4_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D5引脚 */
    gpio_init_struct.Pin    = CAMERA_D5_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D5_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D6引脚 */
    gpio_init_struct.Pin    = CAMERA_D6_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D6_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化D7引脚 */
    gpio_init_struct.Pin    = CAMERA_D7_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_D7_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化RCLK引脚 */
    gpio_init_struct.Pin    = CAMERA_RCLK_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_RCLK_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化WEN引脚 */
    gpio_init_struct.Pin    = CAMERA_WEN_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_WEN_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化VSYNC引脚 */
    gpio_init_struct.Pin    = CAMERA_VSYNC_INT_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_IT_RISING;
    gpio_init_struct.Pull   = GPIO_NOPULL;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_VSYNC_INT_GPIO_PORT, &gpio_init_struct);
    HAL_NVIC_SetPriority(CAMERA_VSYNC_INT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAMERA_VSYNC_INT_IRQn);
    
    CAMERA_WRST(1);
    CAMERA_RRST(1);
    CAMERA_OE(1);
    CAMERA_RCLK(1);
    CAMERA_WEN(1);
}

/**
 * @brief       ATK-MC7725F模块软件复位
 * @param       无
 * @retval      无
 */
static void camera_sw_reset(void)
{
    camera_write_reg(CAMERA_REG_COM7, 0x80);
    delay_ms(2);
}

/**
 * @brief       获取ATK-MC7725F模块制造商ID
 * @param       无
 * @retval      制造商ID
 */
static uint16_t camera_get_mid(void)
{
    uint16_t mid;
    
    mid = camera_read_reg(CAMERA_REG_MIDH) << 8;
    mid |= camera_read_reg(CAMERA_REG_MIDL);
    
    return mid;
}

/**
 * @brief       获取ATK-MC7725F模块产品ID
 * @param       无
 * @retval      产品ID
 */
static uint16_t camera_get_pid(void)
{
    uint16_t pid;
    
    pid = camera_read_reg(CAMERA_REG_PID) << 8;
    pid |= camera_read_reg(CAMERA_REG_VER);
    
    return pid;
}

/**
 * @brief       初始化ATK-MD7725F寄存器配置
 * @param       无
 * @retval      无
 */
static void camera_init_reg(void)
{
    uint8_t cfg_index;
    
    for (cfg_index=0; cfg_index<(sizeof(CAMERA_init_cfg)/sizeof(CAMERA_init_cfg[0])); cfg_index++)
    {
        camera_write_reg(CAMERA_init_cfg[cfg_index][0], CAMERA_init_cfg[cfg_index][1]);
        switch (CAMERA_init_cfg[cfg_index][0])
        {
            case CAMERA_REG_HSIZE:
            {
                g_camera_sta.output.width = CAMERA_init_cfg[cfg_index][1] << 2;
                break;
            }
            case CAMERA_REG_VSIZE:
            {
                g_camera_sta.output.height = CAMERA_init_cfg[cfg_index][1] << 1;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

/**
 * @brief       获取ATK-MD7725F端口D0~D7的一字节数据
 * @param       无
 * @retval      ATK-MD7725F端口D0~D7的一字节数据
 */
static inline uint8_t camera_get_byte_data(void)
{
    uint8_t dat = 0;
    
#if (CAMERA_DATA_PIN_IN_SAME_GPIO_PORT == 0)
    dat |= (((CAMERA_D0_GPIO_PORT->IDR & CAMERA_D0_GPIO_PIN) == 0) ? (0) : (1)) << 0;
    dat |= (((CAMERA_D1_GPIO_PORT->IDR & CAMERA_D1_GPIO_PIN) == 0) ? (0) : (1)) << 1;
    dat |= (((CAMERA_D2_GPIO_PORT->IDR & CAMERA_D2_GPIO_PIN) == 0) ? (0) : (1)) << 2;
    dat |= (((CAMERA_D3_GPIO_PORT->IDR & CAMERA_D3_GPIO_PIN) == 0) ? (0) : (1)) << 3;
    dat |= (((CAMERA_D4_GPIO_PORT->IDR & CAMERA_D4_GPIO_PIN) == 0) ? (0) : (1)) << 4;
    dat |= (((CAMERA_D5_GPIO_PORT->IDR & CAMERA_D5_GPIO_PIN) == 0) ? (0) : (1)) << 5;
    dat |= (((CAMERA_D6_GPIO_PORT->IDR & CAMERA_D6_GPIO_PIN) == 0) ? (0) : (1)) << 6;
    dat |= (((CAMERA_D7_GPIO_PORT->IDR & CAMERA_D7_GPIO_PIN) == 0) ? (0) : (1)) << 7;
#else
    dat = CAMERA_DATE_GPIO_PORT->IDR & CAMERA_DATA_READ_MASK;
#endif
    
    return dat;
}

/**
 * @brief       初始化ATK-MC7725F模块
 * @param       无
 * @retval      CAMERA_EOK  : ATK-MC7725模块初始化成功
 *              CAMERA_ERROR: ATK-MC7725模块初始化失败
 */
uint8_t camera_init(void)
{
    uint16_t mid;
    uint16_t pid;
    
    camera_hw_init();          /* ATK-MC7725F模块硬件初始化 */
    camera_sccb_init();        /* ATK-MC7725F SCCB接口初始化 */
    camera_sw_reset();         /* ATK-MC7725F模块软件复位 */
    
    mid = camera_get_mid();    /* 获取制造商ID */
    if (mid != CAMERA_MID)
    {
        return CAMERA_ERROR;
    }
    
    pid = camera_get_pid();    /* 获取产品ID */
    if (pid != CAMERA_PID)
    {
        return CAMERA_ERROR;
    }
    
    camera_init_reg();         /* 初始化ATK-MD7725F寄存器配置 */
    
    return CAMERA_EOK;
}

/**
 * @brief       设置ATK-MC7725F模块灯光模式
 * @param       mode: CAMERA_LIGHT_MOED_AUTO  : Auto
 *                    CAMERA_LIGHT_MOED_SUNNY : Sunny
 *                    CAMERA_LIGHT_MOED_CLOUDY: Cloudy
 *                    CAMERA_LIGHT_MOED_OFFICE: Office
 *                    CAMERA_LIGHT_MOED_HOME  : Home
 *                    CAMERA_LIGHT_MOED_NIGHT : Night
 * @retval      CAMERA_EOK   : 设置ATK-MC7725模块灯光模式成功
 *              CAMERA_EINVAL: 传入参数错误
 */
uint8_t camera_set_light_mode(camera_light_mode_t mode)
{
    switch (mode)
    {
        case CAMERA_LIGHT_MODE_AUTO:
        {
            camera_write_reg(CAMERA_REG_COM8, 0xFF);
            camera_write_reg(CAMERA_REG_COM5, 0x65);
            camera_write_reg(CAMERA_REG_ADVFL, 0x00);
            camera_write_reg(CAMERA_REG_ADVFH, 0x00);
            break;
        }
        case CAMERA_LIGHT_MODE_SUNNY:
        {
            camera_write_reg(CAMERA_REG_COM8, 0xFD);
            camera_write_reg(CAMERA_REG_BLUE, 0x5A);
            camera_write_reg(CAMERA_REG_RED, 0x5C);
            camera_write_reg(CAMERA_REG_COM5, 0x65);
            camera_write_reg(CAMERA_REG_ADVFL, 0x00);
            camera_write_reg(CAMERA_REG_ADVFH, 0x00);
            break;
        }
        case CAMERA_LIGHT_MODE_CLOUDY:
        {
            camera_write_reg(CAMERA_REG_COM8, 0xFD);
            camera_write_reg(CAMERA_REG_BLUE, 0x58);
            camera_write_reg(CAMERA_REG_RED, 0x60);
            camera_write_reg(CAMERA_REG_COM5, 0x65);
            camera_write_reg(CAMERA_REG_ADVFL, 0x00);
            camera_write_reg(CAMERA_REG_ADVFH, 0x00);
            break;
        }
        case CAMERA_LIGHT_MODE_OFFICE:
        {
            camera_write_reg(CAMERA_REG_COM8, 0xFD);
            camera_write_reg(CAMERA_REG_BLUE, 0x84);
            camera_write_reg(CAMERA_REG_RED, 0x4C);
            camera_write_reg(CAMERA_REG_COM5, 0x65);
            camera_write_reg(CAMERA_REG_ADVFL, 0x00);
            camera_write_reg(CAMERA_REG_ADVFH, 0x00);
            break;
        }
        case CAMERA_LIGHT_MODE_HOME:
        {
            camera_write_reg(CAMERA_REG_COM8, 0xFD);
            camera_write_reg(CAMERA_REG_BLUE, 0x96);
            camera_write_reg(CAMERA_REG_RED, 0x40);
            camera_write_reg(CAMERA_REG_COM5, 0x65);
            camera_write_reg(CAMERA_REG_ADVFL, 0x00);
            camera_write_reg(CAMERA_REG_ADVFH, 0x00);
            break;
        }
        case CAMERA_LIGHT_MODE_NIGHT:
        {
            camera_write_reg(CAMERA_REG_COM8, 0xFF);
            camera_write_reg(CAMERA_REG_COM5, 0xE5);
            break;
        }
        default:
        {
            return CAMERA_EINVAL;
        }
    }
    
    return CAMERA_EOK;
}

/**
 * @brief       设置ATK-MC7725F模块色彩饱和度
 * @param       saturation: CAMERA_COLOR_SATURATION_0: +4
 *                          CAMERA_COLOR_SATURATION_1: +3
 *                          CAMERA_COLOR_SATURATION_2: +2
 *                          CAMERA_COLOR_SATURATION_3: +1
 *                          CAMERA_COLOR_SATURATION_4: 0
 *                          CAMERA_COLOR_SATURATION_5: -1
 *                          CAMERA_COLOR_SATURATION_6: -2
 *                          CAMERA_COLOR_SATURATION_7: -3
 *                          CAMERA_COLOR_SATURATION_8: -4
 * @retval      CAMERA_EOK   : 设置ATK-MC7725F模块色彩饱和度成功
 *              CAMERA_EINVAL: 传入参数错误
 */
uint8_t camera_set_color_saturation(camera_color_saturation_t saturation)
{
    switch (saturation)
    {
        case CAMERA_COLOR_SATURATION_0:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x80);
            camera_write_reg(CAMERA_REG_VSAT, 0x80);
            break;
        }
        case CAMERA_COLOR_SATURATION_1:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x70);
            camera_write_reg(CAMERA_REG_VSAT, 0x70);
            break;
        }
        case CAMERA_COLOR_SATURATION_2:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x60);
            camera_write_reg(CAMERA_REG_VSAT, 0x60);
            break;
        }
        case CAMERA_COLOR_SATURATION_3:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x50);
            camera_write_reg(CAMERA_REG_VSAT, 0x50);
            break;
        }
        case CAMERA_COLOR_SATURATION_4:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x40);
            camera_write_reg(CAMERA_REG_VSAT, 0x40);
            break;
        }
        case CAMERA_COLOR_SATURATION_5:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x30);
            camera_write_reg(CAMERA_REG_VSAT, 0x30);
            break;
        }
        case CAMERA_COLOR_SATURATION_6:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x20);
            camera_write_reg(CAMERA_REG_VSAT, 0x20);
            break;
        }
        case CAMERA_COLOR_SATURATION_7:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x10);
            camera_write_reg(CAMERA_REG_VSAT, 0x10);
            break;
        }
        case CAMERA_COLOR_SATURATION_8:
        {
            camera_write_reg(CAMERA_REG_USAT, 0x00);
            camera_write_reg(CAMERA_REG_VSAT, 0x00);
            break;
        }
        default:
        {
            return CAMERA_EINVAL;
        }
    }
    
    return CAMERA_EOK;
}

/**
 * @brief       设置ATK-MC7725F模块亮度
 * @param       brightness: CAMERA_BRIGHTNESS_0: +4
 *                          CAMERA_BRIGHTNESS_1: +3
 *                          CAMERA_BRIGHTNESS_2: +2
 *                          CAMERA_BRIGHTNESS_3: +1
 *                          CAMERA_BRIGHTNESS_4: 0
 *                          CAMERA_BRIGHTNESS_5: -1
 *                          CAMERA_BRIGHTNESS_6: -2
 *                          CAMERA_BRIGHTNESS_7: -3
 *                          CAMERA_BRIGHTNESS_8: -4
 * @retval      CAMERA_EOK   : 设置ATK-MC7725F模块亮度成功
 *              CAMERA_EINVAL: 传入参数错误
 */
uint8_t camera_set_brightness(camera_brightness_t brightness)
{
    switch (brightness)
    {
        case CAMERA_BRIGHTNESS_0:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x48);
            camera_write_reg(CAMERA_REG_SIGN, 0x06);
            break;
        }
        case CAMERA_BRIGHTNESS_1:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x38);
            camera_write_reg(CAMERA_REG_SIGN, 0x06);
            break;
        }
        case CAMERA_BRIGHTNESS_2:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x28);
            camera_write_reg(CAMERA_REG_SIGN, 0x06);
            break;
        }
        case CAMERA_BRIGHTNESS_3:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x18);
            camera_write_reg(CAMERA_REG_SIGN, 0x06);
            break;
        }
        case CAMERA_BRIGHTNESS_4:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x08);
            camera_write_reg(CAMERA_REG_SIGN, 0x06);
            break;
        }
        case CAMERA_BRIGHTNESS_5:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x08);
            camera_write_reg(CAMERA_REG_SIGN, 0x0E);
            break;
        }
        case CAMERA_BRIGHTNESS_6:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x18);
            camera_write_reg(CAMERA_REG_SIGN, 0x0E);
            break;
        }
        case CAMERA_BRIGHTNESS_7:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x28);
            camera_write_reg(CAMERA_REG_SIGN, 0x0E);
            break;
        }
        case CAMERA_BRIGHTNESS_8:
        {
            camera_write_reg(CAMERA_REG_BRIGHT, 0x38);
            camera_write_reg(CAMERA_REG_SIGN, 0x0E);
            break;
        }
        default:
        {
            return CAMERA_EINVAL;
        }
    }
    
    return CAMERA_EOK;
}

/**
 * @brief       设置ATK-MC7725F模块对比度
 * @param       contrast: CAMERA_CONTRAST_0: +4
 *                        CAMERA_CONTRAST_1: +3
 *                        CAMERA_CONTRAST_2: +2
 *                        CAMERA_CONTRAST_3: +1
 *                        CAMERA_CONTRAST_4: 0
 *                        CAMERA_CONTRAST_5: -1
 *                        CAMERA_CONTRAST_6: -2
 *                        CAMERA_CONTRAST_7: -3
 *                        CAMERA_CONTRAST_8: -4
 * @retval      CAMERA_EOK   : 设置ATK-MC7725F模块对比度成功
 *              CAMERA_EINVAL: 传入参数错误
 */
uint8_t camera_set_contrast(camera_contrast_t contrast)
{
    switch (contrast)
    {
        case CAMERA_CONTRAST_0:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x30);
            break;
        }
        case CAMERA_CONTRAST_1:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x2C);
            break;
        }
        case CAMERA_CONTRAST_2:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x28);
            break;
        }
        case CAMERA_CONTRAST_3:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x24);
            break;
        }
        case CAMERA_CONTRAST_4:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x20);
            break;
        }
        case CAMERA_CONTRAST_5:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x1C);
            break;
        }
        case CAMERA_CONTRAST_6:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x18);
            break;
        }
        case CAMERA_CONTRAST_7:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x14);
            break;
        }
        case CAMERA_CONTRAST_8:
        {
            camera_write_reg(CAMERA_REG_CNST, 0x10);
            break;
        }
        default:
        {
            return CAMERA_EINVAL;
        }
    }
    
    return CAMERA_EOK;
}

/**
 * @brief       设置ATK-MC7725F模块特殊效果
 * @param       contrast: CAMERA_SPECIAL_EFFECT_NORMAL  : Normal
 *                        CAMERA_SPECIAL_EFFECT_BW      : B&W
 *                        CAMERA_SPECIAL_EFFECT_BLUISH  : Bluish
 *                        CAMERA_SPECIAL_EFFECT_SEPIA   : Sepia
 *                        CAMERA_SPECIAL_EFFECT_REDISH  : Redish
 *                        CAMERA_SPECIAL_EFFECT_GREENISH: Greenish
 *                        CAMERA_SPECIAL_EFFECT_NEGATIE : Negative
 * @retval      CAMERA_EOK   : 设置ATK-MC7725F模块特殊效果成功
 *              CAMERA_EINVAL: 传入参数错误
 */
uint8_t camera_set_special_effect(camera_special_effect_t effect)
{
    switch (effect)
    {
        case CAMERA_SPECIAL_EFFECT_NORMAL:
        {
            camera_write_reg(CAMERA_REG_SDE, 0x06);
            camera_write_reg(CAMERA_REG_UFIX, 0x80);
            camera_write_reg(CAMERA_REG_VFIX, 0x80);
            break;
        }
        case CAMERA_SPECIAL_EFFECT_BW:
        {
            camera_write_reg(CAMERA_REG_SDE, 0x26);
            camera_write_reg(CAMERA_REG_UFIX, 0x80);
            camera_write_reg(CAMERA_REG_VFIX, 0x80);
            break;
        }
        case CAMERA_SPECIAL_EFFECT_BLUISH:
        {
            camera_write_reg(CAMERA_REG_SDE, 0x1E);
            camera_write_reg(CAMERA_REG_UFIX, 0xA0);
            camera_write_reg(CAMERA_REG_VFIX, 0x40);
            break;
        }
        case CAMERA_SPECIAL_EFFECT_SEPIA:
        {
            camera_write_reg(CAMERA_REG_SDE, 0x1E);
            camera_write_reg(CAMERA_REG_UFIX, 0x40);
            camera_write_reg(CAMERA_REG_VFIX, 0xA0);
            break;
        }
        case CAMERA_SPECIAL_EFFECT_REDISH:
        {
            camera_write_reg(CAMERA_REG_SDE, 0x1E);
            camera_write_reg(CAMERA_REG_UFIX, 0x80);
            camera_write_reg(CAMERA_REG_VFIX, 0xC0);
            break;
        }
        case CAMERA_SPECIAL_EFFECT_GREENISH:
        {
            camera_write_reg(CAMERA_REG_SDE, 0x1E);
            camera_write_reg(CAMERA_REG_UFIX, 0x60);
            camera_write_reg(CAMERA_REG_VFIX, 0x60);
            break;
        }
        case CAMERA_SPECIAL_EFFECT_NEGATIVE:
        {
            camera_write_reg(CAMERA_REG_SDE, 0x46);
            break;
        }
        default:
        {
            return CAMERA_EINVAL;
        }
    }
    
    return CAMERA_EOK;
}

/**
 * @brief       设置ATK-MC7725F模块输出模式
 * @param       width : 输出图像宽度（VGA，<=640；QVGA，<=320）
 *              height: 输出图像高度（VGA，<=480；QVGA，<=240）
 *              mode  : CAMERA_OUTPUT_MODE_VGA : VGA输出模式
 *                      CAMERA_OUTPUT_MODE_QVGA: QVGA输出模式
 * @retval      CAMERA_EOK   : 设置ATK-MC7725F模块输出模式成功
 *              CAMERA_EINVAL: 传入参数错误
 */
uint8_t camera_set_output(uint16_t width, uint16_t height, camera_output_mode_t mode)
{
    uint16_t xs;
    uint16_t ys;
    uint8_t hstart_raw;
    uint8_t hstart_new;
    uint8_t vstrt_raw;
    uint8_t vstrt_new;
    uint8_t href_raw;
    uint8_t href_new;
    uint8_t exhch;
    
    switch (mode)
    {
        case CAMERA_OUTPUT_MODE_VGA:
        {
            if ((width > CAMERA_VGA_WIDTH_MAX) || (height > CAMERA_VGA_HEIGHT_MAX))
            {
                return CAMERA_EINVAL;
            }
            break;
        }
        case CAMERA_OUTPUT_MODE_QVGA:
        {
            if ((width > CAMERA_QVGA_WIDTH_MAX) || (height > CAMERA_QVGA_HEIGHT_MAX))
            {
                return CAMERA_EINVAL;
            }
            break;
        }
        default:
        {
            return CAMERA_EINVAL;
        }
    }
    
    switch (mode)
    {
        case CAMERA_OUTPUT_MODE_VGA:
        {
            xs = (CAMERA_VGA_WIDTH_MAX - width) >> 1;
            ys = (CAMERA_VGA_HEIGHT_MAX - height) >> 1;
            camera_write_reg(CAMERA_REG_COM7, 0x06);
            camera_write_reg(CAMERA_REG_HSTART, 0x23);
            camera_write_reg(CAMERA_REG_HSIZE, 0xA0);
            camera_write_reg(CAMERA_REG_VSTRT, 0x07);
            camera_write_reg(CAMERA_REG_VSIZE, 0xF0);
            camera_write_reg(CAMERA_REG_HREF, 0x00);
            camera_write_reg(CAMERA_REG_HOutSize, 0xA0);
            camera_write_reg(CAMERA_REG_VOutSize, 0xF0);
            break;
        }
        case CAMERA_OUTPUT_MODE_QVGA:
        {
            xs = (CAMERA_QVGA_WIDTH_MAX - width) >> 1;
            ys = (CAMERA_QVGA_HEIGHT_MAX - height) >> 1;
            camera_write_reg(CAMERA_REG_COM7, 0x46);
            camera_write_reg(CAMERA_REG_HSTART, 0x3F);
            camera_write_reg(CAMERA_REG_HSIZE, 0x50);
            camera_write_reg(CAMERA_REG_VSTRT, 0x03);
            camera_write_reg(CAMERA_REG_VSIZE, 0x78);
            camera_write_reg(CAMERA_REG_HREF, 0x00);
            camera_write_reg(CAMERA_REG_HOutSize, 0x50);
            camera_write_reg(CAMERA_REG_VOutSize, 0x78);
            break;
        }
        default:
        {
            return CAMERA_EINVAL;
        }
    }
    
    hstart_raw = camera_read_reg(CAMERA_REG_HSTART);
    hstart_new = hstart_raw + (xs >> 2);
    camera_write_reg(CAMERA_REG_HSTART, hstart_new);
    camera_write_reg(CAMERA_REG_HSIZE, width >> 2);
    g_camera_sta.output.width = camera_read_reg(CAMERA_REG_HSIZE) << 2;
    
    vstrt_raw = camera_read_reg(CAMERA_REG_VSTRT);
    vstrt_new = vstrt_raw + (ys >> 1);
    camera_write_reg(CAMERA_REG_VSTRT, vstrt_new);
    camera_write_reg(CAMERA_REG_VSIZE, height >> 1);
    g_camera_sta.output.height = camera_read_reg(CAMERA_REG_VSIZE) << 1;
    
    href_raw = camera_read_reg(CAMERA_REG_HREF);
    href_new = ((ys & 0x01) << 6) | ((xs & 0x03) << 4) | ((height & 0x01) << 2) | (width & 0x03) | href_raw;
    camera_write_reg(CAMERA_REG_HREF, href_new);
    
    camera_write_reg(CAMERA_REG_HOutSize, width >> 2);
    camera_write_reg(CAMERA_REG_VOutSize, height >> 1);
    
    exhch = (href_raw | (width & 0x03) | ((height & 0x01) << 2));
    camera_write_reg(CAMERA_REG_EXHCH, exhch);
    
    return CAMERA_EOK;
}

/**
 * @brief       使能ATK-MD7725F模块输出图像
 * @param       无
 * @retval      无
 */
void camera_enable_output(void)
{
    CAMERA_OE(0);
}

/**
 * @brief       禁止ATK-MD7725F模块输出图像
 * @param       无
 * @retval      无
 */
void camera_disable_output(void)
{
    CAMERA_OE(1);
}

/**
 * @brief       获取ATK-MC7725F模块输出图像宽度
 * @param       无
 * @retval      ATK-MC7725F模块输出图像宽度
 */
uint16_t camera_get_output_width(void)
{
    return g_camera_sta.output.width;
}

/**
 * @brief       获取ATK-MC7725F模块输出图像高度
 * @param       无
 * @retval      ATK-MC7725F模块输出图像高度
 */
uint16_t camera_get_output_height(void)
{
    return g_camera_sta.output.height;
}

/**
 * @brief       获取ATK-MC7725F模块输出的一帧图像数据
 * @param       dts : 图像数据返回首地址
 *              type: CAMERA_GET_FRAME_TYPE_NOINC   : 目的地址固定
 *                    CAMERA_GET_FRAME_TYPE_AUTO_INC: 目的地址自动自增
 * @retval      CAMERA_EOK   : 获取ATK-MC7725F模块输出的一帧图像数据成功
 *              CAMERA_EINVAL: 传入参数错误
 *              CAMERA_EEMPTY: 图像数据为空
 */
uint8_t camera_get_frame(volatile uint16_t *dts, camera_get_frame_type_t type)
{
    uint16_t width_index;
    uint16_t height_index;
    uint16_t dat;
    
    if (g_camera_sta.frame.handle_flag == FRAME_HANDLE_DONE)
    {
        return CAMERA_EEMPTY;
    }
    
    CAMERA_RRST(0);
    CAMERA_RCLK(0);
    CAMERA_RCLK(1);
    CAMERA_RCLK(0);
    CAMERA_RRST(1);
    CAMERA_RCLK(1);
    for (height_index=0; height_index<g_camera_sta.output.height; height_index++)
    {
        for (width_index=0; width_index<g_camera_sta.output.width; width_index++)
        {
            CAMERA_RCLK(0);
            dat = (camera_get_byte_data() << 8);
            CAMERA_RCLK(1);
            CAMERA_RCLK(0);
            dat |= camera_get_byte_data();
            CAMERA_RCLK(1);
            *dts = dat;
            switch (type)
            {
                case CAMERA_GET_FRAME_TYPE_NOINC:
                {
                    break;
                }
                case CAMERA_GET_FRAME_TYPE_AUTO_INC:
                {
                    dts++;
                    break;
                }
                default:
                {
                    return CAMERA_EINVAL;
                }
            }
        }
    }
    
    g_camera_sta.frame.handle_flag = FRAME_HANDLE_DONE;
    g_camera_sta.frame.count++;
    
    return CAMERA_EOK;
}

/**
 * @brief       ATK-MD7725F VSYNC外部中断服务函数
 * @param       无
 * @retval      无
 */
void CAMERA_VSYNC_INT_IRQHandler(void)
{
    if (__HAL_GPIO_EXTI_GET_IT(CAMERA_VSYNC_INT_GPIO_PIN) != RESET)
    {
        if (g_camera_sta.frame.handle_flag == FRAME_HANDLE_DONE)
        {
            CAMERA_WRST(0);
            CAMERA_WEN(1);
            CAMERA_WRST(1);
            g_camera_sta.frame.handle_flag = FRAME_HANDLE_PEND;
        }
        else
        {
            CAMERA_WEN(0);
        }
        
        __HAL_GPIO_EXTI_CLEAR_IT(CAMERA_VSYNC_INT_GPIO_PIN);
    }
}