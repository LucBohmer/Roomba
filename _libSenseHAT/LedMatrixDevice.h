#ifndef LEDMATRIXDEVICE_H
#define LEDMATRIXDEVICE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int init_fb(void);
int blank(void);
int clear(uint8_t r, uint8_t g, uint8_t b);
int invert(void);
int set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
int get_pixel(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b);

#ifdef __cplusplus
}
#endif

#endif
