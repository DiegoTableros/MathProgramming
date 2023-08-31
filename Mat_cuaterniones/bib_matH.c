#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_cuaterniones.h"
#include "bib_matH.h"

int libera_espacio(matriz *mat){
    int i;
    for (i=0; i<mat->m; i++){
        free(mat->A[i]);
        mat->A[i]=NULL;
    }
    free(mat->A);
    mat->A=NULL;
    mat->m=mat->n=0;
    return 0;
}

matriz crea_matriz(int m, int n) {
    matriz ret={m,n,NULL};
    int i,j,k;
    ret.A=(H**)malloc(m*sizeof(H));
    if (ret.A!=NULL){
        for(i=0; i<m; i++){
            ret.A[i]=(H*)malloc(n*sizeof(H));
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
    if (mat == NULL){
		return -1;
	}
    fscanf(archivo,"%d", &m);
    fscanf(archivo,"%d", &n);
    *mat = crea_matriz(m,n);
    for(i=0; i<m; i++) {
        for (j=0; j<n; j++){
            mat->A[i][j]=leerCua(archivo);
        }
    }
    return 0;
}

int imprime_matriz(matriz mat, FILE *archivo){
    int i, j;
    for (i=0; i<mat.m; i++){
        for (j=0; j<mat.n; j++){
        	escribeCua(mat.A[i][j],archivo);
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
        fprintf(archivo,"No se puede realizar la suma matricial\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=sumaCua(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matriz resta_matriz(matriz X, matriz Y, FILE *archivo){
    matriz ret={0,0,NULL};
    int i, j;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        fprintf(archivo,"No se puede realizar la resta matricial\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=restaCua(X.A[i][j],Y.A[i][j]);
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
    		ret.A[i][j]=creaCua(0.0,0.0,0.0,0.0);
		}
	}
    for(i=0; i<ret.m; i++){
    	for(j=0; j<ret.n; j++) {
    		for(k=0; k<p; k++) {
    			ret.A[i][j]=sumaCua(ret.A[i][j],multiplicaCua(X.A[i][k],Y.A[k][j]));
			}
		}
	}
    return ret;
}

