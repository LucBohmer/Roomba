// ---------------------------------------------------------------------
// Wrapper for gatttool
//
// By Hugo Arends
// May 2017
// ---------------------------------------------------------------------

#ifndef GATT_WRAPPER_H
#define GATT_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define DBG(a,b,c) printf("[%-20s %02d] %s", a, b, c)
//#define DBG(a,b,c) //

void gatt_start(const char *mac);
int gatt_connect(void);
void gatt_read(char *r);
void gatt_write(const char *s);
int gatt_disconnect(void);
int gatt_exit(void);

#ifdef __cplusplus
}
#endif

#endif
