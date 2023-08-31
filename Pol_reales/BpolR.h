#ifndef _H_POLREAL_
#define _H_POLREAL_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Rx_{
	int g;
	double *c;
}Rx;

Rx leer_polinomio(FILE *archivo);
void imprime_polinomio(Rx p, FILE *archivo);
Rx copia(Rx a);
Rx copia_neg(Rx a);
int libera(Rx *a);
int es_cero(Rx a);
Rx suma_polinomio(Rx a, Rx b);
Rx resta_polinomio(Rx a, Rx b);
Rx multiplica_polinomio(Rx a, Rx b);
Rx multi_monomio(Rx a, double mon, int gradMon);
Rx divide_polinomio(Rx a, Rx b, Rx *r);
Rx mcd(Rx a, Rx b);
Rx integral(Rx pol);
Rx derivada(Rx pol);
double evaluacion(Rx pol, double num);

#ifdef __cplusplus
}
#endif

#endif
