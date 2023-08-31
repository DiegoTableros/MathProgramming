#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Q_{
    int p,q;
}Q;

int mcd(int a, int b);
Q simplificaQ(Q a);
void escribeQ(Q a);
Q leerQ(void);
Q creaQ(int num, int den);
Q sumaQ(Q a, Q b);
Q restaQ(Q a, Q b);
Q multiplicaQ(Q a, Q b);
Q divideQ(Q a, Q b);

typedef struct _matriz_{
    int m, n;
    Q **A;
}matrizQ;

int libera_espacio(matrizQ *mat);
matrizQ crea_matriz(int m, int n);
int leeMatriz(matrizQ *mat);
int imprime_matriz(matrizQ mat);
matrizQ suma_matriz(matrizQ X, matrizQ Y);
matrizQ resta_matriz(matrizQ X, matrizQ Y);
matrizQ multiplica_matriz(matrizQ X, matrizQ Y);

int main(int argc, char *argv[]) {
    matrizQ X, Y, res;
    printf("Matrices con entradas Racionales.\n\n");
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

int libera_espacio(matrizQ *mat){
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

matrizQ crea_matriz(int m, int n) {
    ///Inicializamos una matriz
    matrizQ ret={m, n, NULL};
    int i;
    ///Generamos las filas de apuntadores
    ret.A=(Q**)malloc(m*sizeof(Q));
    ///Si no hubo error al generarlas
    if (ret.A!=NULL){
        for(i=0; i<m; i++){
            ///En cada apuntador fila generamos espacios columnas
            ret.A[i]=(Q*)malloc(n*sizeof(Q));
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

int leeMatriz(matrizQ *mat) {
    int m, n, i, j;
    if (mat == NULL) return -1; ///codigo de error
    printf("Digite el numero de filas m: ");
    scanf("%d", &m);
    printf("Digite el numero de columnas n: ");
    scanf("%d", &n);
    ///Generamos un espacio de memoria m*n y guardamos en mat
    *mat = crea_matriz(m,n);
    printf("Digite las entradas racionales de la matriz:\n");
    for(i=0; i<m; i++) {
        for (j=0; j<n; j++){
            printf("[%2d,%2d]=\n", i, j);
            mat->A[i][j]=leerQ();
            //scanf("%lg", &(mat->A[i][j]));
        }
    }
    return 0; ///codigo de terminacion exitosa
}

int imprime_matriz(matrizQ mat){
    int i, j;
    for (i=0; i<mat.m; i++){
        for (j=0; j<mat.n; j++){
            escribeQ(mat.A[i][j]);
        }
        printf("\n");
    }
    return 0;
}

matrizQ suma_matriz(matrizQ X, matrizQ Y){
    matrizQ ret;
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
            ret.A[i][j]=sumaQ(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matrizQ resta_matriz(matrizQ X, matrizQ Y){
    matrizQ ret={0,0,NULL};
    int i, j;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        printf("No se puede realizar la resta matricial\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=restaQ(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matrizQ multiplica_matriz(matrizQ X, matrizQ Y) {
    matrizQ ret={0,0,NULL};
    int i,j,k;
    Q aux;
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
            aux=creaQ(0,1);
            for(j=0; j<X.n; j++) {
                aux=sumaQ(aux,multiplicaQ(X.A[i][j],Y.A[i][j]));
            }
            ret.A[i][k]=aux;
        }
    }
    return ret;
}

int mcd(int a, int b) {
	///Definimos el residuo "r"
  	int r=0;
  	///Valores absolutos
  	a=(a<0?-a:a);
  	b=(b<0?-b:b);
  	///Caso b==0, el MCD es a
  	if(b==0) {
    	return a;
    }
  	///Algoritmo de Euclides
  	while((r=a%b)!=0) {
    	a=b;
      	b=r;
    }
  	///Retornamos el ultimo residuo distinto de cero
  	return b;
}

Q simplificaQ(Q a) {
	///Declaramos un racional para regresar
  	Q retorna=a;
  	///Sacamos el MCD del numerador y denominador
  	int div=mcd(a.p, a.q);
  	///Si el MCD es mayor que 1
  	if(div>1) {
    	retorna.p/=div;
      	retorna.q/=div;
    }
  	///Si el denominador es negativo, alternamos signos
  	if(retorna.q<0) {
    	retorna.q*=-1;
      	retorna.p*=-1;
    }
  	return retorna;
}

void escribeQ(Q a) {
	char buferTemporal[128];
	int l;
	sprintf(buferTemporal, "%d", a.p);
	l=strlen(buferTemporal);
	if (a.q!=1 && a.p!=0) {
		sprintf(buferTemporal+l, "/%d", a.q);
	}
	printf("%12s",buferTemporal);
}

Q leerQ(void) {
	Q A;
	do{
		printf("Ingrese el numerador y el denominador: ");\
        scanf("%d%d", &A.p, &A.q);
    }while(A.q==0);
    A=simplificaQ(A);
	return A;
}

Q creaQ(int num, int den) {
	Q r = {num, den};
	r=simplificaQ(r);
	return r;
}

Q sumaQ(Q a, Q b) {
    Q res;
    res.p=a.p*b.q+a.q*b.p;
    res.q=a.q*b.q;
    res=simplificaQ(res);
    return res;
}

Q restaQ(Q a, Q b) {
    Q res;
    res.p=a.p*b.q-a.q*b.p;
    res.q=a.q*b.q;
    res=simplificaQ(res);
    return res;
}

Q multiplicaQ(Q a, Q b){
    Q res;
    res.p=a.p*b.p;
    res.q=a.q*b.q;
    res=simplificaQ(res);
    return res;
}

Q divideQ(Q a, Q b){
    Q res;
    res.p=a.p*b.q;
    res.q=a.q*b.p;
    res=simplificaQ(res);
    return res;
}
