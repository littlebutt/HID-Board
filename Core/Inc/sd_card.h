#ifndef __SD_CARD_H
#define __SD_CARD_H

#include "fatfs.h"
#include "stdio.h"
#include "string.h"

void sd_card_init();

int sd_card_write(const char *filename, BYTE *buf, size_t buflen);

int sd_card_read(const char *filename, BYTE *buf, size_t buflen);

void sd_card_deinit();


#endif // __SD_CARD_H