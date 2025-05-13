#ifndef __USBD_HID_KEYBOARD_H
#define __USBD_HID_KEYBOARD_H

#include  "usbd_ioreq.h"
#include <stdint.h>

#define HID_EPIN_ADDR                 0x81U
#define HID_EPIN_SIZE2                0x08U

#define USB_HID_CONFIG_DESC_SIZ       34U
#define USB_HID_DESC_SIZ              9U
#define HID_KEYBOARD_REPORT_DESC_SIZE 63U

#define HID_DESCRIPTOR_TYPE           0x21U
#define HID_REPORT_DESC               0x22U

#ifndef HID_HS_BINTERVAL
#define HID_HS_BINTERVAL            0x07U
#endif /* HID_HS_BINTERVAL */

#ifndef HID_FS_BINTERVAL
#define HID_FS_BINTERVAL            0x0AU
#endif /* HID_FS_BINTERVAL */

#define HID_REQ_SET_PROTOCOL          0x0BU
#define HID_REQ_GET_PROTOCOL          0x03U

#define HID_REQ_SET_IDLE              0x0AU
#define HID_REQ_GET_IDLE              0x02U

#define HID_REQ_SET_REPORT            0x09U
#define HID_REQ_GET_REPORT            0x01U

typedef enum
{
  HID_IDLE2 = 0,
  HID_BUSY2,
}
HID_StateTypeDef2;


typedef struct
{
  uint32_t             Protocol;
  uint32_t             IdleState;
  uint32_t             AltSetting;
  HID_StateTypeDef2     state;
}
USBD_HID_HandleTypeDef2;

extern USBD_ClassTypeDef  USBD_HID2;
#define USBD_HID_CLASS2    &USBD_HID2

uint8_t USBD_HID_SendReport2(USBD_HandleTypeDef *pdev,
                            uint8_t *report,
                            uint16_t len);

uint32_t USBD_HID_GetPollingInterval2(USBD_HandleTypeDef *pdev);

#endif