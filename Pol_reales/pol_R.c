#include <stdio.h>
#include <stdlib.h>
#define crea_arreglo(tam) (double*)malloc((tam+1)*sizeof(double))

typedef struct _Rx_{
	int g;
	double *c;
}Rx;

Rx leer_polinomio();
void imprime_polinomio(Rx p);
Rx copia(Rx a);
Rx copia_neg(Rx a);
int libera(Rx *a);
int es_cero(Rx a);
Rx suma_polinomio(Rx a, Rx b);
Rx resta_polinomio(Rx a, Rx b);
Rx multiplica_polinomio(Rx a, Rx b);
Rx multi_monomio(Rx a, double mon, int gradMon);
Rx divide_polinomio(Rx a, Rx b, Rx *r);
Rx mcd(Rx a, Rx b);
Rx integral(Rx pol);
Rx derivada(Rx pol);
double evaluacion(Rx pol, double num);

int main(int argc, char *argv[]) {
	Rx res,a,b,q,r={c:NULL, g:-1};
	double n;
	printf("Polinomios con coeficientes reales.\n\n");
	
	a=leer_polinomio();
	printf("\n");
	b=leer_polinomio();
	printf("\n");
	printf("Ingrese un numero real para evaluacion: ");
	scanf("%lg",&n);
	
	printf("Los polinomios ingresados son:");
	printf("\nA(x) = ");
	imprime_polinomio(a);
	printf("\nB(x) = ");
	imprime_polinomio(b);
	printf("\n\n");
	
	printf("Evaluaciones para A(x):\n");
	printf("A(%lg)=%lg\n", n, evaluacion(a,n));
	res=derivada(a);
	printf("Derivada(A)(%lg)=%lg\n", n, evaluacion(res,n));
	libera(&res);
	res=integral(a);
	printf("Integral(A)(%lg)=%lg\n", n, evaluacion(res,n));
	libera(&res);
	printf("\n");
	
	printf("Evaluaciones para B(x):\n");
	printf("B(%lg)=%lg\n", n, evaluacion(b,n));
	res=derivada(b);
	printf("Derivada(B)(%lg)=%lg\n", n, evaluacion(res,n));
	libera(&res);
	res=integral(b);
	printf("Integral(B)(%lg)=%lg\n", n, evaluacion(res,n));
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
	if(es_cero(q)) {
		"No se puede efectuar la división.\n";
	}
	printf("Cociente = ");
	imprime_polinomio(q);
	printf("\nResiduo = ");
	imprime_polinomio(r);
	printf("\n\n");
	
	printf("MCD(A,B) :\n");
	res=mcd(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	libera(&a);
	libera(&b);
	libera(&q);
	libera(&r);
	system("PAUSE");
	return 0;
}

Rx leer_polinomio() {
	Rx ret;
	int i;
	printf("Digite el grado del polinomio: ");
	scanf("%d", &(ret.g));
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g = -1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
    	printf("Digite el coeficiente de x^%d: ", i);
    	scanf("%lg", &(ret.c[i]));
	}
	return ret;
}

void imprime_polinomio(Rx pol) {
	int i;
	if(pol.g<0){
    	printf("0");
    	return;
  	}
	for(i=pol.g; i>=2; i--) {
		if(pol.c[i]!=0.0) {
			if(pol.c[i]>0.0) {
				printf("+");
			}
			printf("%lg x^%d ", pol.c[i], i);
		}
	}
  	if(pol.g>=1 && pol.c[1]!=0.0) {
  		if(pol.c[1]>0.0) {
  			printf("+");
		}
		printf("%lg x ", pol.c[1]);
	}
	if(pol.g>=0 && pol.c[0]!=0.0) {
		if(pol.c[0]>0.0) {
			printf("+");
		}
		printf("%lg ", pol.c[0]);
	}
}

Rx copia(Rx a) {
	Rx ret;
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
		ret.c[i]=a.c[i];
	}
	return ret;
}

Rx copia_neg(Rx a) {
	Rx ret;
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
		ret.c[i]=-a.c[i];
	}
	return ret;
}

int libera(Rx *a) {
	if(a->c!=NULL) {
		free(a->c);
	}
	a->g=-1;
	a->c=NULL;
	return 0;	
}

int es_cero(Rx a) {
	return a.g<0;
}

Rx suma_polinomio(Rx a, Rx b) {
	Rx ret;
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
		ret.c[i]=a.c[i]+b.c[i];	
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
	while(ret.g>=0 && ret.c[ret.g]==0.0) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Rx resta_polinomio(Rx a, Rx b) {
	Rx ret;
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
		ret.c[i]=a.c[i]-b.c[i];	
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=-b.c[i];	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];	
		}
	}
	while(ret.g>=0 && ret.c[ret.g]==0.0) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Rx multiplica_polinomio(Rx a, Rx b) {
	int i, j;
	Rx ret;
	ret.g=a.g+b.g;
	if((ret.c=crea_arreglo(ret.g))==NULL){
    printf("Error de almacenamiento.\n");
		ret.g = -1;
		return ret;
	}
	for (i=0; i<=ret.g; i++) {
		ret.c[i]=0.0;
	}
	for (i=0; i<=a.g; i++) {
    	for(j=0; j<=b.g; j++) {
      		ret.c[i+j]+=a.c[i]*b.c[j];
		}
	}
	return ret;
}

Rx multi_monomio(Rx a, double mon, int gradMon) {
	int i;
	Rx ret;
	ret.g=a.g+gradMon;
  	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
		ret.c[i]=0.0;
	}
	for (i=gradMon; i<=ret.g; i++) {
		ret.c[i]=a.c[i-gradMon]*mon;	
	}
	return ret;
}

Rx divide_polinomio(Rx a, Rx b, Rx *r) {
	Rx q, aux, a_aux;
	int grad, i;
	a_aux=copia(a);
  	a=a_aux;
  	if (a.g<b.g){
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
		q.c[i]=0.0;
	}
	do{
    	grad=a.g-b.g;
    	q.c[grad] = a.c[a.g]/b.c[b.g];
    	aux = multi_monomio(b, q.c[grad], grad);
    	a_aux=resta_polinomio(a, aux);
    	libera(&a);
    	libera(&aux);
    	a = a_aux;
		libera(r);
    	*r=copia(a);
	}while(!es_cero(*r) && (r->g>=b.g));
	return q;
}

Rx mcd(Rx a, Rx b) {
	Rx aux1,aux2,residuo={g:-1,c:NULL};
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

Rx integral(Rx pol){
	Rx ret;
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
	ret.c[0]=0.0;
	for(i=0; i<=pol.g; i++) {
		ret.c[i+1]=pol.c[i]/(i+1.0);
	}
	return ret;
}

Rx derivada(Rx pol){
	Rx ret;
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
		ret.c[i-1]=pol.c[i]*i;
	}
	return ret;
}

double evaluacion(Rx pol, double num) {
    double res=0.0;
    int i;
    for(i=pol.g; i>0; i--) {
        res=num*(pol.c[i]+res);
    }
    res+=pol.c[0];
    return res;
}
