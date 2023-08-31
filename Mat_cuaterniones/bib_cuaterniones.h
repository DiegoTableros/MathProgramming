#ifndef _H_CUATERNIONES_
#define _H_CUATERNIONES_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _H_ {
    double a,b,c,d;
}H;

H leerCua(FILE *archivo);
void escribeCua(H x, FILE *archivo);
H sumaCua(H x, H y);
H restaCua(H x, H y);
H multiplicaCua(H x, H y);
H conjugadoCua(H x);
H creaCua(double A, double B, double C, double D);
double normaCua(H x);
H inversoCua(H x);
H divideCua(H x, H y);

#ifdef __cplusplus
}
#endif

#endif
