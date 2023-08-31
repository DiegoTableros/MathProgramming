#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define crea_arreglo(tam) (Q*)malloc((tam+1)*sizeof(Q))

typedef struct _Q_ {
	int p,q;
}Q;

int mcd(int a, int b);
Q sumaQ(Q a, Q b);
Q restaQ(Q a, Q b);
Q simplificaQ(Q a);
void escribeQ(Q a);
Q leerQ(void);
Q divideQ(Q a, Q b);
Q multiplicaQ(Q a, Q b);
Q creaQ(int num, int den);

typedef struct _Px_{
	int g;
	Q *c;
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
Px multi_monomio(Px a, Q mon, int gradMon);
Px divide_polinomio(Px a, Px b, Px *r);
Px MCD(Px a, Px b);
Px integral(Px pol);
Px derivada(Px pol);
Q evaluacion(Px pol, Q num);

int main(int argc, char *argv[]) {
	Px res,a,b,q,r={c:NULL, g:-1};
	Q n;
	printf("Polinomios con coeficientes racionales.\n\n");
	
	a=leer_polinomio();
	printf("\n");
	b=leer_polinomio();
	printf("\n");
	printf("Ingrese un numero racional para evaluacion: ");
	n=leerQ();
	printf("\n");
	
	printf("Los polinomios ingresados son:");
	printf("\nA(x) = ");
	imprime_polinomio(a);
	printf("\nB(x) = ");
	imprime_polinomio(b);
	printf("\n\n");
	
	printf("Evaluaciones para A(x) con x="); escribeQ(n); printf(":\n");
	printf("A(x)= "); escribeQ(evaluacion(a,n)); printf("\n");
	res=derivada(a);
	printf("Derivada(A)(x)= "); escribeQ(evaluacion(res,n)); printf("\n");
	libera(&res);
	res=integral(a);
	printf("Integral(A)(x)= "); escribeQ(evaluacion(res,n)); printf("\n");
	libera(&res);
	printf("\n");
	
	printf("Evaluaciones para B(x) con x="); escribeQ(n); printf(":\n");
	printf("B(x)= "); escribeQ(evaluacion(b,n)); printf("\n");
	res=derivada(b);
	printf("Derivada(B)(x)= "); escribeQ(evaluacion(res,n)); printf("\n");
	libera(&res);
	res=integral(b);
	printf("Integral(B)(x)= "); escribeQ(evaluacion(res,n)); printf("\n");
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
	libera(&r);
	libera(&q);
	
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
    	ret.c[i]=leerQ();
	}
	while(ret.c[ret.g].p==0 && ret.g>=0) {
		ret.g--;
	}
	if(ret.g<0) {
		libera(&ret);
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
		if(pol.c[i].p!=0) {
			escribeQ(pol.c[i]);
			printf(" x^%d ",i);
		}
	}
  	if(pol.g>=1 && pol.c[1].p!=0) {
  		escribeQ(pol.c[1]);
		printf(" x ");
	}
	if(pol.g>=0 && pol.c[0].p!=0) {
		escribeQ(pol.c[0]);
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
		ret.c[i]=creaQ(-a.c[i].p,-a.c[i].q);
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
		ret.c[i]=sumaQ(a.c[i],b.c[i]);	
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
	while(ret.g>=0 && ret.c[ret.g].p==0) {
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
		ret.c[i]=restaQ(a.c[i],b.c[i]);	
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=creaQ(-b.c[i].p,-b.c[i].q);	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];
		}
	}
	while(ret.g>=0 && ret.c[ret.g].p==0) {
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
		ret.c[i]=creaQ(0,1);
	}
	for (i=0; i<=a.g; i++) {
    	for(j=0; j<=b.g; j++) {
      		ret.c[i+j]=sumaQ(ret.c[i+j],multiplicaQ(a.c[i],b.c[j]));
		}
	}
	return ret;
}

Px multi_monomio(Px a, Q mon, int gradMon) {
	int i;
	Px ret;
	ret.g=a.g+gradMon;
  	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
		ret.c[i]=creaQ(0,1);
	}
	for (i=gradMon; i<=ret.g; i++) {
		ret.c[i]=multiplicaQ(a.c[i-gradMon],mon);	
	}
	while(ret.g>=0 && ret.c[ret.g].p==0) {
		ret.g--;
	}
	if(ret.g<0) {
		libera(&ret);
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
		q.c[i]=creaQ(0,1);
	}
	do{
    	grad=a.g-b.g;
    	q.c[grad]=divideQ(a.c[a.g],b.c[b.g]);
		aux = multi_monomio(b, q.c[grad], grad);
		a_aux=resta_polinomio(a, aux);
		libera(&a);
		a = a_aux;
		libera(&aux);
		libera(r);
		*r=copia(a);
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
		libera(&aux1);
        aux1=copia(aux2);
        libera(&aux2);
		aux2=copia(residuo);
		libera(&residuo);
		divide_polinomio(aux1,aux2,&residuo);
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
	ret.c[0]=creaQ(0,1);
	for(i=0; i<=pol.g; i++) {
		ret.c[i+1]=divideQ(pol.c[i],creaQ(i+1,1));
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
		ret.c[i-1]=multiplicaQ(pol.c[i],creaQ(i,1));
	}
	return ret;
}

Q evaluacion(Px pol, Q num) {
    Q res=creaQ(0,1);
    int i;
    for(i=pol.g; i>0; i--) {
        res=multiplicaQ(num,sumaQ(pol.c[i],res));
    }
    res=sumaQ(res,pol.c[0]);
    return res;
}

int mcd(int a, int b){
	int r;
	if (a<0){
  		a=-a;
	}
	if (b < 0) {
  		b=-b;
	}
	if (b == 0) {
  		return a;
	}
	while ((r=a%b) != 0){
    	a = b;
		b = r;
	}
  	return b;
}

Q simplificaQ(Q a){
	int d;
	d=mcd(a.p,a.q);
	if (d>1){
    	a.p /= d;
    	a.q /= d;
  	}
  	if (a.q < 0){
    	a.p *= -1;
    	a.q *= -1;
  	}
	return a;
}

void escribeQ(Q a){
	char buferTemporal[128];
	int l;
	sprintf(buferTemporal, "%d", a.p);
	l = strlen(buferTemporal);
	if (a.q!= 1) sprintf(buferTemporal+l, "/%d", a.q);
	printf("%s", buferTemporal);
}

Q leerQ(void){
	Q A;
	do{
		printf("Digite el numerador y el denominador: "); scanf("%d%d", &A.p, &A.q);
    }while(A.q==0);
    A=simplificaQ(A);
	return A;
}

Q sumaQ(Q a, Q b) {
	Q retorna;
	retorna.p=(a.p*b.q+a.q*b.p);
	retorna.q=a.q*b.q;
	retorna=simplificaQ(retorna);
	return retorna;
}

Q restaQ(Q a, Q b) {
	Q retorna;
	retorna.p=(a.p*b.q-a.q*b.p);
	retorna.q=a.q*b.q;
	retorna=simplificaQ(retorna);
	return retorna;
}

Q creaQ(int num, int den){
	Q r = {num, den};
	r=simplificaQ(r);
	return r;
}

Q divideQ(Q a, Q b){
	Q retorna;
	retorna.p=a.p*b.q;
	retorna.q=a.q*b.p;
	retorna=simplificaQ(retorna);
	return retorna;
}

Q multiplicaQ(Q a, Q b) {
	Q retorna;
	retorna.p=a.p*b.p;
	retorna.q=a.q*b.q;
	retorna=simplificaQ(retorna);
	return retorna;
}

