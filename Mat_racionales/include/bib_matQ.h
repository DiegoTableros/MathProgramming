#ifndef _H_MCOMPLEJOS_
#define _H_MCOMPLEJOS_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _matriz_{
    int m, n;
    Q **A;
}matrizQ;

int libera_espacio(matrizQ *mat);
matrizQ crea_matriz(int m, int n);
int leeMatriz(matrizQ *mat, FILE *archivo);
int imprime_matriz(matrizQ mat, FILE *archivo);
matrizQ suma_matriz(matrizQ X, matrizQ Y, FILE *archivo);
matrizQ resta_matriz(matrizQ X, matrizQ Y, FILE *archivo);
matrizQ multiplica_matriz(matrizQ X, matrizQ Y, FILE *archivo);

#ifdef __cplusplus
}
#endif

#endif
