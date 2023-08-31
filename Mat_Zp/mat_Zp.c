#include <stdio.h>
#include <stdlib.h>

typedef struct _zp_ {
	int p,n;
}zp;

zp leerzp(int p);
int escribirzp(zp a);
int simpzp(zp a);
zp sumazp(zp a, zp b);
zp restazp(zp a, zp b);
zp productozp(zp a, zp b);
zp inversazp(zp a);
zp divisionzp(zp a, zp b);

typedef struct _matriz_{
    int m, n;
    zp **A;
}matrizZp;

int libera_espacio(matrizZp *mat);
matrizZp crea_matriz(int m, int n);
int leeMatriz(matrizZp *mat);
int imprime_matriz(matrizZp mat);
matrizZp suma_matriz(matrizZp X, matrizZp Y);
matrizZp resta_matriz(matrizZp X, matrizZp Y);
matrizZp multiplica_matriz(matrizZp X, matrizZp Y);

int primo;

int main(int argc, char *argv[]) {
    matrizZp X, Y, res;
    printf("Matrices con entradas en Zp.\n");
    printf("Digite un numero primo: ");
    scanf("%d",&primo);
    printf("\nLeyendo la primera matriz:\n");
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

int libera_espacio(matrizZp *mat){
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

matrizZp crea_matriz(int m, int n) {
    ///Inicializamos una matriz
    matrizZp ret={m, n, NULL};
    int i;
    ///Generamos las filas de apuntadores
    ret.A=(zp**)malloc(m*sizeof(zp));
    ///Si no hubo error al generarlas
    if (ret.A!=NULL){
        for(i=0; i<m; i++){
            ///En cada apuntador fila generamos espacios columnas
            ret.A[i]=(zp*)malloc(n*sizeof(zp));
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

int leeMatriz(matrizZp *mat) {
    int m, n, i, j;
    if (mat == NULL) return -1; ///codigo de error
    printf("Digite el numero de filas m: ");
    scanf("%d", &m);
    printf("Digite el numero de columnas n: ");
    scanf("%d", &n);
    ///Generamos un espacio de memoria m*n y guardamos en mat
    *mat = crea_matriz(m,n);
    printf("Digite las entradas Zp de la matriz:\n");
    for(i=0; i<m; i++) {
        for (j=0; j<n; j++){
            printf("[%2d,%2d]=\n", i, j);
            mat->A[i][j]=leerzp(primo);
            //scanf("%lg", &(mat->A[i][j]));
        }
    }
    return 0; ///codigo de terminacion exitosa
}

int imprime_matriz(matrizZp mat){
    int i, j;
    for (i=0; i<mat.m; i++){
        for (j=0; j<mat.n; j++){
            printf("%6d",mat.A[i][j].n);
            printf("\t");
        }
        printf("\n");
    }
    return 0;
}

matrizZp suma_matriz(matrizZp X, matrizZp Y){
    matrizZp ret;
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
            ret.A[i][j]=sumazp(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matrizZp resta_matriz(matrizZp X, matrizZp Y){
    matrizZp ret={0,0,NULL};
    int i, j;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        printf("No se puede realizar la resta matricial\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=restazp(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matrizZp multiplica_matriz(matrizZp X, matrizZp Y) {
    matrizZp ret={0,0,NULL};
    int i,j,k;
    zp aux;
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
            aux.n=0;
            aux.p=primo;
            for(j=0; j<X.n; j++) {
                aux=sumazp(aux,productozp(X.A[i][j],Y.A[i][j]));
            }
            ret.A[i][k]=aux;
        }
    }
    return ret;
}

zp leerzp(int p){
	zp a;
	a.p=p;
	printf("Ingrese por favor un entero: ");
	scanf("%d",&a.n);
	a.n=simpzp(a);
	return a;
}

int escribirzp(zp a){
	printf("%d",a.n);
	return 0;
}

int simpzp(zp a){
  	///Simplificar un numero sacando modulo p
	a.n=(a.n%a.p+a.p)%a.p;
	return a.n;
}

zp sumazp(zp a, zp b){
	zp res;
	res.p=a.p;
	res.n=a.n+b.n;
	res.n=simpzp(res);
	return res;
}

zp restazp(zp a, zp b){
	zp res;
	res.p=a.p;
	res.n=a.n-b.n;
	res.n=simpzp(res);
	return res;
}

zp productozp(zp a, zp b){
	zp res;
	res.p=a.p;
	res.n=a.n*b.n;
	res.n=simpzp(res);
	return res;
}

zp inversazp(zp d){
	int r,q,s,s0,s1,a,b;
	a=d.n;
	b=d.p;
	s0=0;
	s1=1;
	while((r=a%b)!=0){
		q=a/b;
		a=b;
		b=r;
		s=s0;
		s0=s1-q*s0;
		s1=s;
	}
	d.n=s0;
	d.n=simpzp(d);
	return d;
}

zp divisionzp(zp a, zp b){
	zp res;
	res=inversazp(b);
	res=productozp(a,res);
	return res;
}

