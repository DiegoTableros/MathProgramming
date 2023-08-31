#ifndef _H_POLREAL_
#define _H_POLREAL_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Px_{
	int g;
	H *c;
}Px;

Px leer_polinomio(FILE *archivo);
void imprime_polinomio(Px pol, FILE *archivo);
Px copia(Px a);
Px copia_neg(Px a);
int libera(Px *a);
int es_cero(Px a);
Px suma_polinomio(Px a, Px b);
Px resta_polinomio(Px a, Px b);
Px multiplica_polinomio(Px a, Px b);
Px multi_monomio(Px a, H mon, int gradMon);
Px divide_polinomio(Px a, Px b, Px *r);
Px MCD(Px a, Px b);
Px integral(Px pol);
Px derivada(Px pol);
H evaluacion(Px pol, H num);

#ifdef __cplusplus
}
#endif

#endif
