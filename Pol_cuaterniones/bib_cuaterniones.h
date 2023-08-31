#ifndef _H_CUATERNIONES_
#define _H_CUATERNIONES_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _H_ {
    double a,b,c,d;
}H;

H leerH(FILE *archivo);
int es_H_cero(H x);
H creaH(double A, double B, double C, double D);
void escribeH(H x, FILE *archivo);
H sumaH(H x, H y);
H restaH(H x, H y);
H multiplicaH(H x, H y);
H conjugadoH(H x);
double normaH(H x);
H inversoH(H x);
H divideH(H x, H y);

#ifdef __cplusplus
}
#endif

#endif
