#ifndef _MI_MANDELBROT_H_
#define _MI_MANDELBROT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "logo.h"

int iniciaMandelbrot(int n, double l, double x, double y, LOGO *tortuga);
int dibujaMandelbrot(void);

#ifdef __cplusplus
}
#endif

#endif
