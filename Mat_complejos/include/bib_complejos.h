#ifndef _H_COMPLEJOS_
#define _H_COMPLEJOS_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _C_ {
    double a,b;
}C;

void escribeC(C x, FILE *archivo);
C leerC(FILE *archivo);
C creaC(double real, double ima);
C sumaC(C x, C y);
C restaC(C x, C y);
C multiplicaC(C x, C y);
C conjugado(C x);
C divideC(C x, C y);
double norma(C x);

#ifdef __cplusplus
}
#endif

#endif
