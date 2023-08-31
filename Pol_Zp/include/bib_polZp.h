#ifndef _H_PZP_
#define _H_PZP_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Px_{
	int g;
	zp *c;
}Px;

Px leer_polinomio(int primo, FILE *archivo);
void imprime_polinomio(Px p, FILE *archivo);
Px copia(Px a);
Px copia_neg(Px a);
int libera(Px *a);
int es_cero(Px a);
Px suma_polinomio(Px a, Px b);
Px resta_polinomio(Px a, Px b);
Px multiplica_polinomio(Px a, Px b, int primo);
Px multi_monomio(Px a, zp mon, int gradMon, int primo);
Px divide_polinomio(Px a, Px b, Px *r, int primo);
Px MCD(Px a, Px b, int primo);
Px integral(Px pol, int primo);
Px derivada(Px pol, int primo);
zp evaluacion(Px pol, zp num, int primo);

#ifdef __cplusplus
}
#endif

#endif
