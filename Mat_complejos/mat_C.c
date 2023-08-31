#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _C_ {
    double a,b;
}C;

void escribeC(C x);
C leerC(void);
C creaC(double real, double ima);
C sumaC(C x, C y);
C restaC(C x, C y);
C multiplicaC(C x, C y);
C conjugado(C x);
C divideC(C x, C y);
double norma(C x);

typedef struct _matriz_{
    int m, n;
    C **A;
}matrizC;

int libera_espacio(matrizC *mat);
matrizC crea_matriz(int m, int n);
int leeMatriz(matrizC *mat);
int imprime_matriz(matrizC mat);
matrizC suma_matriz(matrizC X, matrizC Y);
matrizC resta_matriz(matrizC X, matrizC Y);
matrizC multiplica_matriz(matrizC X, matrizC Y);

int main(int argc, char *argv[]) {
    matrizC X, Y, res;
    printf("Matrices con entradas complejas.\n\n");
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

int libera_espacio(matrizC *mat){
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

matrizC crea_matriz(int m, int n) {
    ///Inicializamos una matriz
    matrizC ret={m, n, NULL};
    int i;
    ///Generamos las filas de apuntadores
    ret.A=(C**)malloc(m*sizeof(C));
    ///Si no hubo error al generarlas
    if (ret.A!=NULL){
        for(i=0; i<m; i++){
            ///En cada apuntador fila generamos espacios columnas
            ret.A[i]=(C*)malloc(n*sizeof(C));
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

int leeMatriz(matrizC *mat) {
    int m, n, i, j;
    if (mat == NULL) return -1; ///codigo de error
    printf("Digite el numero de filas m: ");
    scanf("%d", &m);
    printf("Digite el numero de columnas n: ");
    scanf("%d", &n);
    ///Generamos un espacio de memoria m*n y guardamos en mat
    *mat = crea_matriz(m,n);
    printf("Digite las entradas complejas de la matriz:\n");
    for(i=0; i<m; i++) {
        for (j=0; j<n; j++){
            printf("[%2d,%2d]\n", i, j);
            mat->A[i][j]=leerC();
        }
    }
    return 0; ///codigo de terminacion exitosa
}

int imprime_matriz(matrizC mat){
    int i, j;
    for (i=0; i<mat.m; i++){
        for (j=0; j<mat.n; j++){
            escribeC(mat.A[i][j]);
            printf("\t");
        }
        printf("\n");
    }
    return 0;
}

matrizC suma_matriz(matrizC X, matrizC Y){
    matrizC ret;
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
            ret.A[i][j]=sumaC(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matrizC resta_matriz(matrizC X, matrizC Y){
    matrizC ret={0,0,NULL};
    int i, j;
    if( (X.m!=Y.m) || (X.n!=Y.n)){
        printf("No se puede realizar la resta matricial\n");
        return ret;
    }
    ret=crea_matriz(X.m, X.n);
    for(i=0; i<X.m; i++) {
        for (j=0; j<X.n; j++) {
            ret.A[i][j]=restaC(X.A[i][j],Y.A[i][j]);
        }
    }
    return ret;
}

matrizC multiplica_matriz(matrizC X, matrizC Y) {
    matrizC ret={0,0,NULL};
    int i,j,k;
    C aux;
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
            aux=creaC(0.0,0.0);
            for(j=0; j<X.n; j++) {
                aux=sumaC(aux,multiplicaC(X.A[i][j],Y.A[i][j]));
            }
            ret.A[i][k]=aux;
        }
    }
    return ret;
}

void escribeC(C x){
    ///Aqui estan todos los casos para escribir complejos
    if(x.a!=0.0) {
        ///Hay parte real
        printf("%lg",x.a);
    }
    ///Si hay parte ima
    if(x.b!=0.0) {
        if(x.b>0.0) {
            printf("+");
        }
        if(x.b==-1.0) {
            printf("-");
        }
        if(x.b!=1.0 && x.b!=-1.0) {
            printf("%lg",x.b);
        }
        printf("i");
    }
    ///Caso cero
    if(x.a==0.0 && x.b==0.0) {
        printf("0");
    }
}

C leerC(void){
    double x,y;
    printf("Digite la parte real y la imaginaria: ");
    scanf("%lg%lg",&x,&y);
    return creaC(x,y);
}

C creaC(double real, double ima){
    C retorna;
    retorna.a=real;
    retorna.b=ima;
    return retorna;
}

C sumaC(C x, C y){
    C res;
    res.a=x.a+y.a;
    res.b=x.b+y.b;
    return res;
}

C restaC(C x, C y) {
    C res;
    res.a=x.a-y.a;
    res.b=x.b-y.b;
    return res;
}

C multiplicaC(C x, C y){
    C res;
    res.a=x.a*y.a-x.b*y.b;
    res.b=x.a*y.b+x.b*y.a;
    return res;
}

C conjugado(C x) {
    x.b=-x.b;
    return x;
}

C divideC(C x, C y) {
    double div=multiplicaC(y,conjugado(y)).a;
    C res=multiplicaC(x,conjugado(y));
    res.a/=div;
    res.b/=div;
    return res;
}

double norma(C x) {
    return sqrt((x.a*x.a)+(x.b*x.b));
}
