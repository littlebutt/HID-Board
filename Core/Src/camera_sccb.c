#include "camera_sccb.h"
#include "stm32f103xe.h"
#include "delay.h"

/* SCCB接口读写通讯地址bit0 */
#define CAMERA_SCCB_WRITE  0x00
#define CAMERA_SCCB_READ   0x01

#if (CAMERA_SCCB_GPIO_PULLUP != 0)
/**
 * @brief       设置SCCB接口SDA引脚为输出模式
 * @param       无
 * @retval      无
 */
static void camera_sccb_set_sda_output(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    gpio_init_struct.Pin    = CAMERA_SCCB_SDA_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_SCCB_SDA_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       设置SCCB接口SDA引脚为输入模式
 * @param       无
 * @retval      无
 */
static void camera_sccb_set_sda_input(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    gpio_init_struct.Pin    = CAMERA_SCCB_SDA_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_SCCB_SDA_GPIO_PORT, &gpio_init_struct);
}
#endif

/**
 * @brief       SCCB接口延时函数
 * @param       无
 * @retval      无
 */
static inline void camera_sccb_delay(void)
{
    delay_us(10);
}

/**
 * @brief       SCCB接口起始信号
 * @param       无
 * @retval      无
 */
static void camera_sccb_start(void)
{
    CAMERA_SCCB_SDA(1);
    CAMERA_SCCB_SCL(1);
    camera_sccb_delay();
    CAMERA_SCCB_SDA(0);
    camera_sccb_delay();
    CAMERA_SCCB_SCL(0);
}

/**
 * @brief       SCCB接口停止信号
 * @param       无
 * @retval      无
 */
static void camera_sccb_stop(void)
{
    CAMERA_SCCB_SDA(0);
    camera_sccb_delay();
    CAMERA_SCCB_SCL(1);
    camera_sccb_delay();
    CAMERA_SCCB_SDA(1);
    camera_sccb_delay();
}

/**
 * @brief       SCCB接口主机向从机写入一个字节数据
 * @param       dat: 待写入的一个字节数据
 * @retval      无
 */
static void camera_sccb_write_byte(uint8_t dat)
{
    int8_t dat_index;
    uint8_t dat_bit;
    
    for (dat_index=7; dat_index>=0; dat_index--)
    {
        dat_bit = (dat >> dat_index) & 0x01;
        CAMERA_SCCB_SDA(dat_bit);
        camera_sccb_delay();
        CAMERA_SCCB_SCL(1);
        camera_sccb_delay();
        CAMERA_SCCB_SCL(0);
    }
    
    CAMERA_SCCB_SDA(1);
    camera_sccb_delay();
    CAMERA_SCCB_SCL(1);
    camera_sccb_delay();
    CAMERA_SCCB_SCL(0);
}

/**
 * @brief       SCCB接口主机向从机读取一个字节数据
 * @param       dat: 读取到的一个字节数据
 * @retval      无
 */
static void camera_sccb_read_byte(uint8_t *dat)
{
    int8_t dat_index;
    uint8_t dat_bit;
    
#if (CAMERA_SCCB_GPIO_PULLUP != 0)
    camera_sccb_set_sda_input();
#endif
    
    for (dat_index=7; dat_index>=0; dat_index--)
    {
        camera_sccb_delay();
        CAMERA_SCCB_SCL(1);
        dat_bit = CAMERA_SCCB_READ_SDA();
        *dat |= (dat_bit << dat_index);
        camera_sccb_delay();
        CAMERA_SCCB_SCL(0);
    }
    
    camera_sccb_delay();
    CAMERA_SCCB_SCL(1);
    camera_sccb_delay();
    CAMERA_SCCB_SCL(0);
    camera_sccb_delay();
    CAMERA_SCCB_SDA(0);
    camera_sccb_delay();
    
#if (CAMERA_SCCB_GPIO_PULLUP != 0)
    camera_sccb_set_sda_output();
#endif
}

/**
 * @brief       ATK-MC7725F SCCB接口初始化
 * @param       无
 * @retval      无
 */
void camera_sccb_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能SCL、SDA引脚GPIO时钟 */
    CAMERA_SCCB_SCL_GPIO_CLK_ENABLE();
    CAMERA_SCCB_SDA_GPIO_CLK_ENABLE();
    
    /* 初始化SCL引脚 */
    gpio_init_struct.Pin    = CAMERA_SCCB_SCL_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_SCCB_SCL_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化SDA引脚 */
    gpio_init_struct.Pin    = CAMERA_SCCB_SDA_GPIO_PIN;
#if (CAMERA_SCCB_GPIO_PULLUP != 0)
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
#else
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_OD;
#endif
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAMERA_SCCB_SDA_GPIO_PORT, &gpio_init_struct);
    
    camera_sccb_stop();
}

/**
 * @brief       SCCB接口3阶段写传输
 * @param       id_addr : ID Address
 *              sub_addr: Sub-address
 *              dat     : Write Data
 * @retval      无
 */
void camera_sccb_3_phase_write(uint8_t id_addr, uint8_t sub_addr, uint8_t dat)
{
    camera_sccb_start();
    camera_sccb_write_byte((id_addr << 1) | CAMERA_SCCB_WRITE);
    camera_sccb_write_byte(sub_addr);
    camera_sccb_write_byte(dat);
    camera_sccb_stop();
}

/**
 * @brief       SCCB接口2阶段写传输
 * @param       id_addr : ID Address
 *              sub_addr: Sub-address
 * @retval      无
 */
void camera_sccb_2_phase_write(uint8_t id_addr, uint8_t sub_addr)
{
    camera_sccb_start();
    camera_sccb_write_byte((id_addr << 1) | CAMERA_SCCB_WRITE);
    camera_sccb_write_byte(sub_addr);
    camera_sccb_stop();
}

/**
 * @brief       SCCB接口2阶段读传输
 * @param       id_addr: ID Address
 *              dat: 读取到的数据
 * @retval      无
 */
void camera_sccb_2_phase_read(uint8_t id_addr, uint8_t *dat)
{
    camera_sccb_start();
    camera_sccb_write_byte((id_addr << 1) | CAMERA_SCCB_READ);
    camera_sccb_read_byte(dat);
    camera_sccb_stop();
}
