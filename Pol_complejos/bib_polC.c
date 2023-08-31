#include <stdio.h>
#include <stdlib.h>
#include "bib_complejos.h"
#include "bib_polC.h"
#define crea_arreglo(tam) (C*)malloc((tam+1)*sizeof(C))
#define EPS 1e-5

Px leer_polinomio(FILE *archivo) {
	Px ret;
	int i;
	fscanf(archivo, "%d", &(ret.g));
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	fprintf(archivo, "Error de almacenamiento.\n");
    	ret.g = -1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
    	ret.c[i]=leerC(archivo);
	}
	return ret;
}

void imprime_polinomio(Px pol, FILE *archivo) {
	int i;
	if(pol.g<0){
    	fprintf(archivo,"0");
    	return;
  	}
	for(i=pol.g; i>=2; i--) {
		if(!es_C_cero(pol.c[i])) {
			escribeC(pol.c[i], archivo);
			fprintf(archivo," x^%d ",i);
		}
	}
  	if(pol.g>=1 && !es_C_cero(pol.c[1])) {
  		escribeC(pol.c[1],archivo);
		fprintf(archivo," x ");
	}
	if(pol.g>=0 && !es_C_cero(pol.c[0])) {
		escribeC(pol.c[0],archivo);
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
