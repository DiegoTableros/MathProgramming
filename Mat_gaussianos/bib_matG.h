#ifndef _H_MGAUSSIANOS_
#define _H_MGAUSSIANOS_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _matriz_{
    int m, n;
    G **A;
}matriz;

int libera_espacio(matriz *mat);
matriz crea_matriz(int m, int n);
int leeMatriz(matriz *mat, FILE *archivo);
int imprime_matriz(matriz mat, FILE *archivo);
matriz suma_matriz(matriz X, matriz Y, FILE *archivo);
matriz resta_matriz(matriz X, matriz Y, FILE *archivo);
matriz multiplica_matriz(matriz X, matriz Y, FILE *archivo);

#ifdef __cplusplus
}
#endif

#endif
