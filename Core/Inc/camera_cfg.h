#ifndef __CAMERA_CFG_H
#define __CAMERA_CFG_H

#include <stdint.h>



#define CAMERA_REG_BLUE        0x01
#define CAMERA_REG_RED         0x02
#define CAMERA_REG_PID         0x0A
#define CAMERA_REG_VER         0x0B
#define CAMERA_REG_COM3        0x0C
#define CAMERA_REG_COM4        0x0D
#define CAMERA_REG_COM5        0x0E
#define CAMERA_REG_COM6        0x0F
#define CAMERA_REG_CLKRC       0x11
#define CAMERA_REG_COM7        0x12
#define CAMERA_REG_COM8        0x13
#define CAMERA_REG_COM9        0x14
#define CAMERA_REG_HSTART      0x17
#define CAMERA_REG_HSIZE       0x18
#define CAMERA_REG_VSTRT       0x19
#define CAMERA_REG_VSIZE       0x1A
#define CAMERA_REG_MIDH        0x1C
#define CAMERA_REG_MIDL        0x1D
#define CAMERA_REG_BDBase      0x22
#define CAMERA_REG_BDMStep     0x23
#define CAMERA_REG_AEW         0x24
#define CAMERA_REG_AEB         0x25
#define CAMERA_REG_VPT         0x26
#define CAMERA_REG_HOutSize    0x29
#define CAMERA_REG_EXHCH       0x2A
#define CAMERA_REG_EXHCL       0x2B
#define CAMERA_REG_VOutSize    0x2C
#define CAMERA_REG_ADVFL       0x2D
#define CAMERA_REG_ADVFH       0x2E
#define CAMERA_REG_HREF        0x32
#define CAMERA_REG_TGT_B       0x42
#define CAMERA_REG_FixGain     0x4D
#define CAMERA_REG_UFIX        0x60
#define CAMERA_REG_VFIX        0x61
#define CAMERA_REG_AWB_Ctrl0   0x63
#define CAMERA_REG_DSP_Ctrl1   0x64
#define CAMERA_REG_DSP_Ctrl2   0x65
#define CAMERA_REG_DSP_Ctrl3   0x66
#define CAMERA_REG_DSP_Ctrl4   0x67
#define CAMERA_REG_AWBCtrl3    0x6B
#define CAMERA_REG_GAM1        0x7E
#define CAMERA_REG_GAM2        0x7F
#define CAMERA_REG_GAM3        0x80
#define CAMERA_REG_GAM4        0x81
#define CAMERA_REG_GAM5        0x82
#define CAMERA_REG_GAM6        0x83
#define CAMERA_REG_GAM7        0x84
#define CAMERA_REG_GAM8        0x85
#define CAMERA_REG_GAM9        0x86
#define CAMERA_REG_GAM10       0x87
#define CAMERA_REG_GAM11       0x88
#define CAMERA_REG_GAM12       0x89
#define CAMERA_REG_GAM13       0x8A
#define CAMERA_REG_GAM14       0x8B
#define CAMERA_REG_GAM15       0x8C
#define CAMERA_REG_SLOP        0x8D
#define CAMERA_REG_EDGE1       0x90
#define CAMERA_REG_DNSOff      0x91
#define CAMERA_REG_EDGE2       0x92
#define CAMERA_REG_EDGE3       0x93
#define CAMERA_REG_MTX1        0x94
#define CAMERA_REG_MTX2        0x95
#define CAMERA_REG_MTX3        0x96
#define CAMERA_REG_MTX4        0x97
#define CAMERA_REG_MTX5        0x98
#define CAMERA_REG_MTX6        0x99
#define CAMERA_REG_MTX_Ctrl    0x9A
#define CAMERA_REG_BRIGHT      0x9B
#define CAMERA_REG_CNST        0x9C
#define CAMERA_REG_UVADJ0      0x9E
#define CAMERA_REG_SDE         0xA6
#define CAMERA_REG_USAT        0xA7
#define CAMERA_REG_VSAT        0xA8
#define CAMERA_REG_HUECOS      0xA9
#define CAMERA_REG_HUESIN      0xAA
#define CAMERA_REG_SIGN        0xAB

const uint8_t CAMERA_init_cfg[][2] = {
    {CAMERA_REG_CLKRC,     0x00},  /* 寄存器CLKRC */
    {CAMERA_REG_COM7,      0x46},  /* 寄存器COM7 */
    {CAMERA_REG_HSTART,    0x3F},  /* 寄存器HSTART */
    {CAMERA_REG_HSIZE,     0x50},  /* 寄存器HSIZE */
    {CAMERA_REG_VSTRT,     0x03},  /* 寄存器VSTRT */
    {CAMERA_REG_VSIZE,     0x78},  /* 寄存器VSIZE */
    {CAMERA_REG_HREF,      0x00},  /* 寄存器HREF */
    {CAMERA_REG_HOutSize,  0x50},  /* 寄存器HOutSize */
    {CAMERA_REG_VOutSize,  0x78},  /* 寄存器VOutSize */
    {CAMERA_REG_TGT_B,     0x7F},  /* 寄存器TGT_B */
    {CAMERA_REG_FixGain,   0x09},  /* 寄存器FixGain */
    {CAMERA_REG_AWB_Ctrl0, 0xE0},  /* 寄存器AWB_Ctrl0 */
    {CAMERA_REG_DSP_Ctrl1, 0xFF},  /* 寄存器DSP_Ctrl1 */
    {CAMERA_REG_DSP_Ctrl2, 0x00},  /* 寄存器DSP_Ctrl2 */
    {CAMERA_REG_DSP_Ctrl3, 0x00},  /* 寄存器DSP_Ctrl3 */
    {CAMERA_REG_DSP_Ctrl4, 0x00},  /* 寄存器DSP_Ctrl4 */
    {CAMERA_REG_COM8,      0xF0},  /* 寄存器COM8 */
    {CAMERA_REG_COM4,      0xC1},  /* 寄存器COM4 */
    {CAMERA_REG_COM6,      0xC5},  /* 寄存器COM6 */
    {CAMERA_REG_COM9,      0x11},  /* 寄存器COM9 */
    {CAMERA_REG_BDBase,    0x7F},  /* 寄存器BDBase */
    {CAMERA_REG_BDMStep,   0x03},  /* 寄存器BDMStep */
    {CAMERA_REG_AEW,       0x40},  /* 寄存器AEW */
    {CAMERA_REG_AEB,       0x30},  /* 寄存器AEB */
    {CAMERA_REG_VPT,       0xA1},  /* 寄存器VPT */
    {CAMERA_REG_EXHCL,     0x9E},  /* 寄存器EXHCL */
    {CAMERA_REG_AWBCtrl3,  0xAA},  /* 寄存器AWBCtrl3 */
    {CAMERA_REG_COM8,      0xFF},  /* 寄存器COM8 */
    {CAMERA_REG_EDGE1,     0x08},  /* 寄存器EDGE1 */
    {CAMERA_REG_DNSOff,    0x01},  /* 寄存器DNSOff */
    {CAMERA_REG_EDGE2,     0x03},  /* 寄存器EDGE2 */
    {CAMERA_REG_EDGE3,     0x00},  /* 寄存器EDGE3 */
    {CAMERA_REG_MTX1,      0xB0},  /* 寄存器MTX1 */
    {CAMERA_REG_MTX2,      0x9D},  /* 寄存器MTX2 */
    {CAMERA_REG_MTX3,      0x13},  /* 寄存器MTX3 */
    {CAMERA_REG_MTX4,      0x16},  /* 寄存器MTX4 */
    {CAMERA_REG_MTX5,      0x7B},  /* 寄存器MTX5 */
    {CAMERA_REG_MTX6,      0x91},  /* 寄存器MTX6 */
    {CAMERA_REG_MTX_Ctrl,  0x1E},  /* 寄存器MTX_Ctrl */
    {CAMERA_REG_BRIGHT,    0x08},  /* 寄存器BRIGHT */
    {CAMERA_REG_CNST,      0x20},  /* 寄存器CNST */
    {CAMERA_REG_UVADJ0,    0x81},  /* 寄存器UVADJ0 */
    {CAMERA_REG_SDE,       0x06},  /* 寄存器SDE */
    {CAMERA_REG_USAT,      0x65},  /* 寄存器USAT */
    {CAMERA_REG_VSAT,      0x65},  /* 寄存器VSAT */
    {CAMERA_REG_HUECOS,    0x80},  /* 寄存器HUECOS */
    {CAMERA_REG_HUESIN,    0x80},  /* 寄存器HUESIN */
    {CAMERA_REG_GAM1,      0x0C},  /* 寄存器GAM1 */
    {CAMERA_REG_GAM2,      0x16},  /* 寄存器GAM2 */
    {CAMERA_REG_GAM3,      0x2A},  /* 寄存器GAM3 */
    {CAMERA_REG_GAM4,      0x4E},  /* 寄存器GAM4 */
    {CAMERA_REG_GAM5,      0x61},  /* 寄存器GAM5 */
    {CAMERA_REG_GAM6,      0x6F},  /* 寄存器GAM6 */
    {CAMERA_REG_GAM7,      0x7B},  /* 寄存器GAM7 */
    {CAMERA_REG_GAM8,      0x86},  /* 寄存器GAM8 */
    {CAMERA_REG_GAM9,      0x8E},  /* 寄存器GAM9 */
    {CAMERA_REG_GAM10,     0x97},  /* 寄存器GAM10 */
    {CAMERA_REG_GAM11,     0xA4},  /* 寄存器GAM11 */
    {CAMERA_REG_GAM12,     0xAF},  /* 寄存器GAM12 */
    {CAMERA_REG_GAM13,     0xC5},  /* 寄存器GAM13 */
    {CAMERA_REG_GAM14,     0xD7},  /* 寄存器GAM14 */
    {CAMERA_REG_GAM15,     0xE8},  /* 寄存器GAM15 */
    {CAMERA_REG_SLOP,      0x20},  /* 寄存器SLOP */
    {CAMERA_REG_COM3,      0x50},  /* 寄存器COM3 */
    {CAMERA_REG_COM5,      0xF5},  /* 寄存器COM5 */
};

#endif