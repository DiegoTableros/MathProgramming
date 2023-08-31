#ifndef _H_PCOMPLEJOS_
#define _H_PCOMPLEJOS_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Px_{
	int g;
	C *c;
}Px;

Px leer_polinomio(FILE *archivo);
void imprime_polinomio(Px p, FILE *archivo);
Px copia(Px a);
Px copia_neg(Px a);
int libera(Px *a);
int es_cero(Px a);
Px suma_polinomio(Px a, Px b);
Px resta_polinomio(Px a, Px b);
Px multiplica_polinomio(Px a, Px b);
Px multi_monomio(Px a, C mon, int gradMon);
Px divide_polinomio(Px a, Px b, Px *r);
Px MCD(Px a, Px b);
Px integral(Px pol);
Px derivada(Px pol);
C evaluacion(Px pol, C num);

#ifdef __cplusplus
}
#endif

#endif
