#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bib_gaussianos.h"
#include "bib_matG.h"

int libera_espacio(matriz *mat){
    int i;
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

matriz crea_matriz(int m, int n) {
    ///Inicializamos una matriz
    matriz ret={m, n, NULL};
    int i;
    ///Generamos las filas de apuntadores
    ret.A=(G**)malloc(m*sizeof(G));
    ///Si no hubo error al generarlas
    if (ret.A!=NULL){
        for(i=0; i<m; i++){
            ///En cada apuntador fila generamos espacios columnas
            ret.A[i]=(G*)malloc(n*sizeof(G));
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

int leeMatriz(matriz *mat, FILE *archivo) {
    int m, n, i, j;
    if (mat == NULL) return -1;
    fscanf(archivo,"%d", &m);
    fscanf(archivo,"%d", &n);
    *mat = crea_matriz(m,n);
    for(i=0; i<m; i++) {
        for (j=0; j<n; j++){
            mat->A[i][j]=leerG(archivo);
        }
    }
    return 0;
}

int imprime_matriz(matriz mat, FILE *archivo){
    int i, j;
    for (i=0; i<mat.m; i++){
        for (j=0; j<mat.n; j++){
            escribeG(mat.A[i][j], archivo);
        }
        fprintf(archivo,"\n");
    }
    return 0;
}

matriz suma_matriz(matriz X, matriz Y, FILE *archivo){
    matriz ret;
    int i, j;
    ret.m=ret.n=0;
    ret.A=NULL;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        fprintf(archivo,"No se puede realizar la suma matricial.\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=sumaG(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matriz resta_matriz(matriz X, matriz Y, FILE *archivo){
    matriz ret={0,0,NULL};
    int i, j;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        fprintf(archivo,"No se puede realizar la resta matricial.\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=restaG(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matriz multiplica_matriz(matriz X, matriz Y, FILE *archivo) {
    matriz ret={0,0,NULL};
    int i,j,k,p;
    p=X.n;
    if(X.n!=Y.m) {
        fprintf(archivo,"No se puede realizar el producto matricial.\n");
        return ret;
    }
    ret=crea_matriz(X.m,Y.n);
    for(i=0; i<ret.m; i++) {
    	for(j=0; j<ret.n; j++) {
    		ret.A[i][j]=creaG(0,0);
		}
	}
    for(i=0; i<ret.m; i++){
    	for(j=0; j<ret.n; j++) {
    		for(k=0; k<p; k++) {
    			ret.A[i][j]=sumaG(ret.A[i][j], multiplicaG(X.A[i][k], Y.A[k][j]));
			}
		}
	}
    return ret;
}
