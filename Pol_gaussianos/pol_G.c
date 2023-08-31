#include <stdio.h>
#include <stdlib.h>
#define crea_arreglo(tam) (G*)malloc((tam+1)*sizeof(G))

///Gomplejos a+bi con a,b enteros
typedef struct _G_ {
    int a,b;
}G;

void escribeG(G x);
int es_G_cero(G num);
G leerG(void);
G creaG(int real, int ima);
G sumaG(G x, G y);
G restaG(G x, G y);
G multiplicaG(G x, G y);
G conjugadoG(G x);
int norma(G x);

typedef struct _Px_{
	int g;
	G *c;
}Px;

Px leer_polinomio();
void imprime_polinomio(Px p);
Px copia(Px a);
Px copia_neg(Px a);
int libera(Px *a);
int es_cero(Px a);
Px suma_polinomio(Px a, Px b);
Px resta_polinomio(Px a, Px b);
Px multiplica_polinomio(Px a, Px b);
Px multi_monomio(Px a, G mon, int gradMon);
Px divide_polinomio(Px a, Px b, Px *r);
Px MCD(Px a, Px b);
Px integral(Px pol);
Px derivada(Px pol);
G evaluacion(Px pol, G num);

int main(int argc, char *argv[]) {
	Px res,a,b={c:NULL, g:-1};
	G n;
	printf("Polinomios con coeficientes gaussianos.\n\n");
	
	a=leer_polinomio();
	printf("\n");
	b=leer_polinomio();
	printf("\n");
	printf("Ingrese un numero gaussiano para evaluacion: ");
	n=leerG();
	printf("\n");
	
	printf("Los polinomios ingresados son:");
	printf("\nA(x) = ");
	imprime_polinomio(a);
	printf("\nB(x) = ");
	imprime_polinomio(b);
	printf("\n\n");
	
	printf("Evaluaciones para A(x) con x="); escribeG(n); printf(":\n");
	printf("A(x)= "); escribeG(evaluacion(a,n)); printf("\n");
	res=derivada(a);
	printf("Derivada(A)(x)= "); escribeG(evaluacion(res,n)); printf("\n");
	libera(&res);
	printf("\n");
	
	printf("Evaluaciones para B(x) con x="); escribeG(n); printf(":\n");
	printf("B(x)= "); escribeG(evaluacion(b,n)); printf("\n");
	res=derivada(b);
	printf("Derivada(B)(x)= "); escribeG(evaluacion(res,n)); printf("\n");
	libera(&res);
	printf("\n");
	
	printf("Suma A+B :\n");
	res=suma_polinomio(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	printf("Resta A-B :\n");
	res=resta_polinomio(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	printf("Producto A*B :\n");
	res=multiplica_polinomio(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	libera(&a);
	libera(&b);
	system("PAUSE");
	return 0;
}

Px leer_polinomio() {
	Px ret;
	int i;
	printf("Digite el grado del polinomio: ");
	scanf("%d", &(ret.g));
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g = -1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
    	printf("Digite el coeficiente de x^%d:\n", i);
    	ret.c[i]=leerG();
	}
	return ret;
}

void imprime_polinomio(Px pol) {
	int i;
	if(pol.g<0){
    	printf("0");
    	return;
  	}
	for(i=pol.g; i>=2; i--) {
		if(!es_G_cero(pol.c[i])) {
			escribeG(pol.c[i]);
			printf(" x^%d ",i);
		}
	}
  	if(pol.g>=1 && !es_G_cero(pol.c[1])) {
  		escribeG(pol.c[1]);
		printf(" x ");
	}
	if(pol.g>=0 && !es_G_cero(pol.c[0])) {
		escribeG(pol.c[0]);
	}
}

Px copia(Px a) {
	Px ret;
	int i;
	ret.g=a.g;
	if (ret.g<0){
    	ret.c=NULL;
		return ret;
	}
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for(i=0; i<=ret.g; i++) {
		ret.c[i]=a.c[i];
	}
	return ret;
}

Px copia_neg(Px a) {
	Px ret;
	int i;
	ret.g = a.g;
	if (ret.g<0){
    	ret.c=NULL;
    	return ret;
	}
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for(i=0; i<=ret.g; i++) {
		ret.c[i]=creaG(-a.c[i].a,-a.c[i].b);
	}
	return ret;
}

int libera(Px *a) {
	if(a->c!=NULL) {
		free(a->c);
	}
	a->g=-1;
	a->c=NULL;
	return 0;	
}

int es_cero(Px a) {
	return a.g<0;
}

Px suma_polinomio(Px a, Px b) {
	Px ret;
	int i, min;
	if (a.g<0){
    	return copia(b);
	}
	if (b.g<0){
    	return copia(a);
	}
	min=(a.g<b.g?a.g:b.g);
	ret.g=(min==a.g?b.g:a.g);
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
		ret.g=-1;
    	return ret;
	}
	for (i=0; i<=min; i++) {
		ret.c[i]=sumaG(a.c[i],b.c[i]);	
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=b.c[i];	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];	
		}
	}
	while(ret.g>=0 && es_G_cero(ret.c[ret.g])) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Px resta_polinomio(Px a, Px b) {
	Px ret;
	int i, min;
	if (a.g<0){
    	return copia(b);
	}
	if (b.g<0){
    	return copia(a);
	}
	min=(a.g<b.g?a.g:b.g);
	ret.g=(min==a.g?b.g:a.g);
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
		ret.g=-1;
    	return ret;
	}
	for (i=0; i<=min; i++) {
		ret.c[i]=restaG(a.c[i],b.c[i]);	
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=creaG(-b.c[i].a,-b.c[i].b);	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];
		}
	}
	while(ret.g>=0 && es_G_cero(ret.c[ret.g])) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Px multiplica_polinomio(Px a, Px b) {
	int i, j;
	Px ret;
	ret.g=a.g+b.g;
	if((ret.c=crea_arreglo(ret.g))==NULL){
    printf("Error de almacenamiento.\n");
		ret.g = -1;
		return ret;
	}
	for (i=0; i<=ret.g; i++) {
		ret.c[i]=creaG(0,0);
	}
	for (i=0; i<=a.g; i++) {
    	for(j=0; j<=b.g; j++) {
      		ret.c[i+j]=sumaG(ret.c[i+j],multiplicaG(a.c[i],b.c[j]));
		}
	}
	return ret;
}

Px derivada(Px pol){
	Px ret;
	int i;
	if(pol.g<=0) {
		ret.g=-1;
		ret.c=NULL;
		return ret;
	}
	ret.g=pol.g-1;
	if((ret.c=crea_arreglo(ret.g))==NULL) {
		printf("Error de almacenamiento.\n");
		ret.g=-1;
		return ret;
	}
	for(i=1; i<=pol.g; i++) {
		ret.c[i-1]=multiplicaG(pol.c[i],creaG(i,0));
	}
	return ret;
}

G evaluacion(Px pol, G num) {
    G res=creaG(0,0);
    int i;
    for(i=pol.g; i>0; i--) {
        res=multiplicaG(num,sumaG(pol.c[i],res));
    }
    res=sumaG(res,pol.c[0]);
    return res;
}

int es_G_cero(G num) {
	return (num.a==0 && num.b==0);
}

void escribeG(G x){
    ///Aqui estan todos los casos para escribir complejos
    if(x.a!=0) {
        ///Hay parte real
        printf("%d",x.a);
    }
    ///Si hay parte ima
    if(x.b!=0) {
        if(x.b>0) {
            printf("+");
        }
        if(x.b==-1) {
            printf("-");
        }
        if(x.b!=1 && x.b!=-1) {
            printf("%d",x.b);
        }
        printf("i");
    }
}

G leerG(void){
    int x,y;
    printf("Digite la parte real y la imaginaria: ");
    scanf("%d%d",&x,&y);
    return creaG(x,y);
}

G creaG(int real, int ima){
    G retorna;
    retorna.a=real;
    retorna.b=ima;
    return retorna;
}

G sumaG(G x, G y){
    G res;
    res.a=x.a+y.a;
    res.b=x.b+y.b;
    return res;
}

G restaG(G x, G y) {
    G res;
    res.a=x.a-y.a;
    res.b=x.b-y.b;
    return res;
}

G multiplicaG(G x, G y){
    G res;
    res.a=x.a*y.a-x.b*y.b;
    res.b=x.a*y.b+x.b*y.a;
    return res;
}

G conjugadoG(G x) {
    x.b=-x.b;
    return x;
}

int norma(G x) {
    ///return multiplicaG(x,conjugadoG(x));
    return (x.a*x.a+x.b*x.b);
}
