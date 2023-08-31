#include <stdio.h>
#include <stdlib.h>
#define crea_arreglo(tam) (C*)malloc((tam+1)*sizeof(C))
#define EPS 1e-5

typedef struct _C_ {
    double a,b;
}C;

void escribeC(C x);
int es_C_cero(C num);
C leerC(void);
C creaC(double real, double ima);
C sumaC(C x, C y);
C restaC(C x, C y);
C multiplicaC(C x, C y);
C conjugado(C x);
C divideC(C x, C y);
double norma(C x);

typedef struct _Px_{
	int g;
	C *c;
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
Px multi_monomio(Px a, C mon, int gradMon);
Px divide_polinomio(Px a, Px b, Px *r);
Px MCD(Px a, Px b);
Px integral(Px pol);
Px derivada(Px pol);
C evaluacion(Px pol, C num);

int main(int argc, char *argv[]) {
	Px res,a,b,q,r={c:NULL, g:-1};
	C n;
	printf("Polinomios con coeficientes complejos.\n\n");
	
	a=leer_polinomio();
	printf("\n");
	b=leer_polinomio();
	printf("\n");
	printf("Ingrese un numero complejo para evaluacion: ");
	n=leerC();
	printf("\n");
	
	printf("Los polinomios ingresados son:");
	printf("\nA(x) = ");
	imprime_polinomio(a);
	printf("\nB(x) = ");
	imprime_polinomio(b);
	printf("\n\n");
	
	printf("Evaluaciones para A(x) con x="); escribeC(n); printf(":\n");
	printf("A(x)= "); escribeC(evaluacion(a,n)); printf("\n");
	res=derivada(a);
	printf("Derivada(A)(x)= "); escribeC(evaluacion(res,n)); printf("\n");
	libera(&res);
	res=integral(a);
	printf("Integral(A)(x)= "); escribeC(evaluacion(res,n)); printf("\n");
	libera(&res);
	printf("\n");
	
	printf("Evaluaciones para B(x) con x="); escribeC(n); printf(":\n");
	printf("B(x)= "); escribeC(evaluacion(b,n)); printf("\n");
	res=derivada(b);
	printf("Derivada(B)(x)= "); escribeC(evaluacion(res,n)); printf("\n");
	libera(&res);
	res=integral(b);
	printf("Integral(B)(x)= "); escribeC(evaluacion(res,n)); printf("\n");
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
	
	printf("División A/B :\n");
	q=divide_polinomio(a, b, &r);
	if(a.g<b.g) {
		"No se puede efectuar la división.\n";
	}
	printf("Cociente = ");
	imprime_polinomio(q);
	printf("\nResiduo = ");
	imprime_polinomio(r);
	printf("\n\n");
	
	printf("MCD(A,B) :\n");
	res=MCD(a,b);
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
    	ret.c[i]=leerC();
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
		if(!es_C_cero(pol.c[i])) {
			escribeC(pol.c[i]);
			printf(" x^%d ",i);
		}
	}
  	if(pol.g>=1 && !es_C_cero(pol.c[1])) {
  		escribeC(pol.c[1]);
		printf(" x ");
	}
	if(pol.g>=0 && !es_C_cero(pol.c[0])) {
		escribeC(pol.c[0]);
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
		ret.c[i]=creaC(-a.c[i].a,-a.c[i].b);
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
		ret.c[i]=sumaC(a.c[i],b.c[i]);	
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
	while(ret.g>=0 && es_C_cero(ret.c[ret.g])) {
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
		ret.c[i]=restaC(a.c[i],b.c[i]);	
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=creaC(-b.c[i].a,-b.c[i].b);	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];
		}
	}
	while(ret.g>=0 && es_C_cero(ret.c[ret.g])) {
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
		ret.c[i]=creaC(0.0,0.0);
	}
	for (i=0; i<=a.g; i++) {
    	for(j=0; j<=b.g; j++) {
      		ret.c[i+j]=sumaC(ret.c[i+j],multiplicaC(a.c[i],b.c[j]));
		}
	}
	return ret;
}

Px multi_monomio(Px a, C mon, int gradMon) {
	int i;
	Px ret;
	ret.g=a.g+gradMon;
  	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
		ret.c[i]=creaC(0.0,0.0);
	}
	for (i=gradMon; i<=ret.g; i++) {
		ret.c[i]=multiplicaC(a.c[i-gradMon],mon);	
	}
	return ret;
}

Px divide_polinomio(Px a, Px b, Px *r) {
	Px q, aux, a_aux;
	int grad, i;
	a_aux=copia(a);
  	a=a_aux;
  	if(a.g<b.g){
    	q.g=-1;
    	q.c=NULL;
    	*r=copia(a);
		return q;
	}
	q.g=a.g-b.g;
	if((q.c=crea_arreglo(q.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	q.g = -1;
    	return q;
	}
	for (i=0; i<=q.g; i++){
		q.c[i]=creaC(0.0,0.0);
	}
	do{
    	grad=a.g-b.g;
    	q.c[grad]=divideC(a.c[a.g],b.c[b.g]);
		aux = multi_monomio(b, q.c[grad], grad);
		a_aux=resta_polinomio(a, aux);
		libera(&a);
		libera(&aux);
		a = a_aux;
		libera(r);
		*r=copia(a);
		/*imprime_polinomio(*r);
		printf("\n");
		system("PAUSE");*/
	}while(!es_cero(*r) && (r->g>=b.g));
	return q;
}

Px MCD(Px a, Px b) {
	Px aux1,aux2,residuo={g:-1,c:NULL};
    if(es_cero(b)) {
        return copia(a);
	}
    aux1=copia(a);
    aux2=copia(b);
    divide_polinomio(aux1,aux2,&residuo);
	while(!es_cero(residuo)) {
        aux1=copia(aux2);
        libera(&aux2);
		aux2=copia(residuo);
		libera(&residuo);
		divide_polinomio(aux1,aux2,&residuo);
		libera(&aux1);
    }
    return aux2;
}

Px integral(Px pol){
	Px ret;
	int i;
	if(pol.g<0) {
		ret.g=-1;
		ret.c=NULL;
		return ret;
	}
	ret.g=pol.g+1;
	if((ret.c=crea_arreglo(ret.g))==NULL) {
		printf("Error de almacenamiento.\n");
		ret.g=-1;
		return ret;
	}
	ret.c[0]=creaC(0.0,0.0);
	for(i=0; i<=pol.g; i++) {
		ret.c[i+1]=divideC(pol.c[i],creaC(i+1.0,0));
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
		ret.c[i-1]=multiplicaC(pol.c[i],creaC(i,0.0));
	}
	return ret;
}

C evaluacion(Px pol, C num) {
    C res=creaC(0.0,0.0);
    int i;
    for(i=pol.g; i>0; i--) {
        res=multiplicaC(num,sumaC(pol.c[i],res));
    }
    res=sumaC(res,pol.c[0]);
    return res;
}

void escribeC(C x){
    if(x.a!=0.0) {
        ///Hay parte real
        if(x.a>0.0) {
        	printf("+");
		}
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
}

int es_C_cero(C num) {
	return (num.a==0.0 && num.b==0.0);
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
    if(-EPS<=res.a && res.a<=EPS) {
    	res.a=0.0;
	}
	if(-EPS<=res.b && res.b<=EPS) {
    	res.b=0.0;
	}
    return res;
}

C restaC(C x, C y) {
    C res;
    res.a=x.a-y.a;
    res.b=x.b-y.b;
    if(-EPS<=res.a && res.a<=EPS) {
    	res.a=0.0;
	}
	if(-EPS<=res.b && res.b<=EPS) {
    	res.b=0.0;
	}
    return res;
}

C multiplicaC(C x, C y){
    C res;
    res.a=x.a*y.a-x.b*y.b;
    res.b=x.a*y.b+x.b*y.a;
    ///Epsilon
    if(-EPS<=res.a && res.a<=EPS) {
    	res.a=0.0;
	}
	if(-EPS<=res.b && res.b<=EPS) {
    	res.b=0.0;
	}
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
    if(-EPS<=res.a && res.a<=EPS) {
    	res.a=0.0;
	}
	if(-EPS<=res.b && res.b<=EPS) {
    	res.b=0.0;
	}
    return res;
}
