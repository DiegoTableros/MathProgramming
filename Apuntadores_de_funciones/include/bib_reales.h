#ifndef _H_REALES_
#define _H_REALES_

#ifdef __cplusplus
extern "C" {
#endif

void escribeR(double x, FILE *archivo);
double leerR(FILE *archivo);
double creaR(double num);
double sumaR(double x, double y);
double restaR(double x, double y);
double multiplicaR(double x, double y);
double divideR(double x, double y);

#ifdef __cplusplus
}
#endif

#endif
