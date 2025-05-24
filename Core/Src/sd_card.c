#include "sd_card.h"

static FATFS fs;

void sd_card_init()
{
  FRESULT f_res = f_mount(&fs, "0:", 1);
  if (f_res == FR_NO_FILESYSTEM)
  {
    f_res = f_mkfs("0:", 0, 0);
    if (f_res == FR_OK)
    {
      f_res = f_mount(NULL, "0:", 1);
      f_res = f_mount(&fs, "0:", 1);
    }
    else
    {
      while (1)
       ;
    }
  }
}

int sd_card_write(const char *filename, BYTE *buf, size_t buflen)
{
  FIL fp;
  FRESULT res;
  UINT f_num = 0;
  char target[64];
  memset(target, 0, sizeof(target));
  snprintf(target, sizeof(target), "0:%s", filename);
  UINT offset = 0;
  UINT bw;
  UINT block_size = 4096;  // 4KB
  res = f_open(&fp, filename, FA_CREATE_ALWAYS | FA_WRITE);
  if (res != FR_OK) return res;

  while (offset < buflen)
  {
    UINT write_size = (buflen - offset) > block_size ? block_size : (buflen - offset);
    res = f_write(&fp, buf + offset, write_size, &bw);
    if (res != FR_OK || bw < write_size)
    {
      f_close(&fp);
      return res != FR_OK ? res : FR_DISK_ERR;
    }
    offset += bw;
  }

  f_close(&fp);
  return (int)f_num;
}

int sd_card_read(const char *filename, BYTE *buf, size_t buflen)
{
  FIL fp;
  UINT f_num = 0;
  char target[64];
  memset(target, 0, sizeof(target));
  snprintf(target, sizeof(target), "0:%s", filename);
  FRESULT f_res = f_open(&fp, target, FA_OPEN_EXISTING | FA_READ);
  if (f_res == FR_OK)
  {
    f_res = f_read(&fp, buf, buflen, &f_num);
    if (f_res != FR_OK)
    {
      return -1;
    }
  }
  else
  {
    return -1;
  }
  f_close(&fp);
  return (int)f_num;
}

void sd_card_deinit()
{
  f_mount(NULL, "0:", 1);
}
