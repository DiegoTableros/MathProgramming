#include <stdio.h>
#include <stdlib.h>

typedef struct _matriz_{
    int m, n;
    double **A;
}matrizR;

int libera_espacio(matrizR *mat);
matrizR crea_matriz(int m, int n);
int leeMatriz(matrizR *mat);
int imprime_matriz(matrizR mat);
matrizR suma_matriz(matrizR X, matrizR Y);
matrizR resta_matriz(matrizR X, matrizR Y);
matrizR multiplica_matriz(matrizR X, matrizR Y);

int main(int argc, char *argv[]) {
    matrizR X, Y, res;
    printf("Matrices con entradas reales.\n\n");
    printf("Leyendo la primera matriz:\n");
    leeMatriz(&X);
    printf("\nLeyendo la segunda matriz:\n");
    leeMatriz(&Y);

    printf("\nMatriz X, m=%d, n=%d, A=%p\n", X.m, X.n, X.A);
    imprime_matriz(X);
    printf("\nMatriz Y, m=%d, n=%d, A=%p\n", Y.m, Y.n, Y.A);
    imprime_matriz(Y);

    printf("\nLa suma de X+Y es\n");
    res = suma_matriz(X,Y);
    imprime_matriz(res);
    libera_espacio(&res);

    printf("\nLa resta de X-Y es\n");
    res=resta_matriz(X,Y);
    imprime_matriz(res);
    libera_espacio(&res);

    printf("\nEl producto X*Y es\n");
    res=multiplica_matriz(X,Y);
    imprime_matriz(res);
    libera_espacio(&res);

    printf("\nFinalmente se libera el espacio creado: ");
    libera_espacio(&X);
    libera_espacio(&Y);
    libera_espacio(&res);
    printf("espacio liberado.\n\n");
    system("PAUSE");
    return 0;
}

int libera_espacio(matrizR *mat){
    int i;
    ///Vamos de fila en fila eliminando los espacios
    for (i=0; i<mat->m; i++){
        free(mat->A[i]);
        mat->A[i]=NULL;
    }
    ///Liberamos el apuntador completo
    free(mat->A);
    mat->A=NULL;
    ///Las dimensiones ahora son 0X0
    mat->m=mat->n=0;
    return 0;
}

matrizR crea_matriz(int m, int n) {
    ///Inicializamos una matriz
    matrizR ret={m, n, NULL};
    int i;
    ///Generamos las filas de apuntadores
    ret.A=(double**)malloc(m*sizeof(double*));
    ///Si no hubo error al generarlas
    if (ret.A!=NULL){
        for(i=0; i<m; i++){
            ///En cada apuntador fila generamos espacios columnas
            ret.A[i]=(double*)malloc(n*sizeof(double));
            ///Si hubo error de almacenamiento generando las columnas
            if (ret.A[i]==NULL){
                while(i>0){
                    free(ret.A[--i]);
                    ret.A[i] = NULL;
                }
                break;
            }
        }
    }
    return ret;
}

int leeMatriz(matrizR *mat) {
    int m, n, i, j;
    if (mat == NULL) return -1; ///codigo de error
    printf("Digite el numero de filas m: ");
    scanf("%d", &m);
    printf("Digite el numero de columnas n: ");
    scanf("%d", &n);
    ///Generamos un espacio de memoria m*n y guardamos en mat
    *mat = crea_matriz(m,n);
    printf("Digite las entradas de la matriz:\n");
    for(i=0; i<m; i++) {
        for (j=0; j<n; j++){
            printf("[%2d,%2d]= ", i+1, j+1);
            scanf("%lg", &(mat->A[i][j]));
        }
    }
    return 0; ///codigo de terminacion exitosa
}

int imprime_matriz(matrizR mat){
    int i, j;
    for (i=0; i<mat.m; i++){
        for (j=0; j<mat.n; j++){
            printf("%6lg ", mat.A[i][j]);
        }
        printf("\n");
    }
    return 0;
}

matrizR suma_matriz(matrizR X, matrizR Y){
    matrizR ret;
    int i, j;
    ///Limpiamos la matriz
    ret.m=ret.n=0;
    ret.A=NULL;
    ///Verificamos que se pueda realizar la suma matricial
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        printf("No se puede realizar la suma matricial\n");
        return ret;
    }
    ///Creamos la matriz de suma
    ret=crea_matriz(X.m, X.n);
    ///Hacemos la suma matricial
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=X.A[i][j]+Y.A[i][j];
        }
    }
    return ret;
}

matrizR resta_matriz(matrizR X, matrizR Y){
    matrizR ret={0,0,NULL};
    int i, j;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        printf("No se puede realizar la resta matricial\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=X.A[i][j]-Y.A[i][j];
        }
    }
    return ret;
}

matrizR multiplica_matriz(matrizR X, matrizR Y) {
    matrizR ret={0,0,NULL};
    int i,j,k;
    double aux;
    ///Las columnas de X deben ser las filas de Y
    if(X.n!=Y.m) {
        printf("No se puede realizar el producto matricial.\n");
        return ret;
    }
    ///Asignamos tamaño y espacio
    ret=crea_matriz(X.m,Y.n);
    ///Llenamos la matriz
    for(k=0; k<Y.n; k++) {
        for(i=0; i<X.m; i++) {
            aux=0;
            for(j=0; j<X.n; j++) {
                aux+=X.A[i][j]*Y.A[j][k];
            }
            ret.A[i][k]=aux;
        }
    }
    return ret;
}
