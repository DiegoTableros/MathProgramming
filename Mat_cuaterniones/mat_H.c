#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _H_ {
    double a,b,c,d;
}H;

H leerCua(void);
void escribeCua(H x);
H sumaCua(H x, H y);
H restaCua(H x, H y);
H multiplicaCua(H x, H y);
H conjugadoCua(H x);
H creaCua(double A, double B, double C, double D);
double normaCua(H x);
H inversoCua(H x);
H divideCua(H x, H y);

typedef struct _matriz_{
    int m, n;
    H **A;
}matrizH;

int libera_espacio(matrizH *mat);
matrizH crea_matriz(int m, int n);
int leeMatriz(matrizH *mat);
int imprime_matriz(matrizH mat);
matrizH suma_matriz(matrizH X, matrizH Y);
matrizH resta_matriz(matrizH X, matrizH Y);
matrizH multiplica_matriz(matrizH X, matrizH Y);

int main(int argc, char *argv[]) {
    matrizH X, Y, res;
    printf("Matrices con entradas Cuaterniones.\n\n");
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

int libera_espacio(matrizH *mat){
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

matrizH crea_matriz(int m, int n) {
    ///Inicializamos una matriz
    matrizH ret={m, n, NULL};
    int i;
    ///Generamos las filas de apuntadores
    ret.A=(H**)malloc(m*sizeof(H));
    ///Si no hubo error al generarlas
    if (ret.A!=NULL){
        for(i=0; i<m; i++){
            ///En cada apuntador fila generamos espacios columnas
            ret.A[i]=(H*)malloc(n*sizeof(H));
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

int leeMatriz(matrizH *mat) {
    int m, n, i, j;
    if (mat == NULL) return -1; ///codigo de error
    printf("Digite el numero de filas m: ");
    scanf("%d", &m);
    printf("Digite el numero de columnas n: ");
    scanf("%d", &n);
    ///Generamos un espacio de memoria m*n y guardamos en mat
    *mat = crea_matriz(m,n);
    printf("Digite las entradas en cuaterniones de la matriz:\n");
    for(i=0; i<m; i++) {
        for (j=0; j<n; j++){
            printf("[%2d,%2d]=\n", i, j);
            mat->A[i][j]=leerCua();
            //scanf("%lg", &(mat->A[i][j]));
        }
    }
    return 0; ///codigo de terminacion exitosa
}

int imprime_matriz(matrizH mat){
    int i, j;
    for (i=0; i<mat.m; i++){
        for (j=0; j<mat.n; j++){
            escribeCua(mat.A[i][j]);
            printf("\t");
        }
        printf("\n");
    }
    return 0;
}

matrizH suma_matriz(matrizH X, matrizH Y){
    matrizH ret;
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
            ret.A[i][j]=sumaCua(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matrizH resta_matriz(matrizH X, matrizH Y){
    matrizH ret={0,0,NULL};
    int i, j;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        printf("No se puede realizar la resta matricial\n");
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

matrizH multiplica_matriz(matrizH X, matrizH Y) {
    matrizH ret={0,0,NULL};
    int i,j,k;
    H aux;
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
            aux=creaCua(0.0,0.0,0.0,0.0);
            for(j=0; j<X.n; j++) {
                aux=sumaCua(aux,multiplicaCua(X.A[i][j],Y.A[i][j]));
            }
            ret.A[i][k]=aux;
        }
    }
    return ret;
}

void escribeCua(H x){
    ///Parte a
    if(x.a!=0.0) {
        printf("%lg ",x.a);
    }
    ///Parte b
    if(x.b!=0.0) {
        if(x.b>0.0) {
            printf("+");
        }
        if(x.b!=1.0 && x.b!=-1.0) {
            printf("%lg",x.b);
        }
        if(x.b==-1.0) {
            printf("-");
        }
        printf("i ");
    }
    ///Parte c
    if(x.c!=0.0) {
        if(x.c>0.0) {
            printf("+");
        }
        if(x.c!=1.0 && x.c!=-1.0) {
            printf("%lg",x.c);
        }
        if(x.c==-1.0) {
            printf("-");
        }
        printf("j ");
    }
    ///Parte d
    if(x.d!=0.0) {
        if(x.d>0.0) {
            printf("+");
        }
        if(x.d!=1.0 && x.d!=-1.0) {
            printf("%lg",x.d);
        }
        if(x.d==-1.0) {
            printf("-");
        }
        printf("k");
    }
    ///Caso cero
    if(x.a==0.0 && x.b==0.0 && x.c==0.0 && x.d==0.0) {
    	printf("0");
	}
}

H creaCua(double A, double B, double C, double D) {
	H ret;
  	ret.a=A; ret.b=B; ret.c=C; ret.d=D;
  	return ret;
}

H leerCua(void){
    H num;
    printf("Digite a,b,c y d: ");
    scanf("%lg%lg%lg%lg",&num.a,&num.b,&num.c,&num.d);
    return num;
}

H sumaCua(H x, H y){
    H res;
    res.a=x.a+y.a;
    res.b=x.b+y.b;
    res.c=x.c+y.c;
    res.d=x.d+y.d;
    return res;
}

H restaCua(H x, H y){
    H res;
    res.a=x.a-y.a;
    res.b=x.b-y.b;
    res.c=x.c-y.c;
    res.d=x.d-y.d;
    return res;
}

H multiplicaCua(H x, H y){
    H res;
    res.a=x.a*y.a-x.b*y.b-x.c*y.c-x.d*y.d;
    res.b=x.a*y.b+x.b*y.a+x.c*y.d-x.d*y.c;
    res.c=x.a*y.c-x.b*y.d+x.c*y.a+x.d*y.b;
    res.d=x.a*y.d+x.b*y.c-x.c*y.b+x.d*y.a;
    return res;
}

H conjugadoCua(H x){
    x.b=-x.b;
    x.c=-x.c;
    x.d=-x.d;
    return x;
}

double normaCua(H x){
    return sqrt(x.a*x.a+x.b*x.b+x.c*x.c+x.d*x.d);
}

H inversoCua(H x){
    H res;
    res=conjugadoCua(x);
    double norm2=normaCua(x)*normaCua(x);
    res.a/=norm2;
    res.b/=norm2;
    res.c/=norm2;
    res.d/=norm2;
    return res;
}

H divideCua(H x, H y){
    H res;
    res=multiplicaCua(x,inversoCua(y));
    return res;
}

