#include <stdio.h>
#include <stdlib.h>
#include "bib_Zp.h"
#include "bib_polZp.h"
#define crea_arreglo(tam) (zp*)malloc((tam+1)*sizeof(zp))

Px leer_polinomio(int primo, FILE *archivo){
	Px ret;
	int i;
	fscanf(archivo,"%d", &(ret.g));
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g = -1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
    	ret.c[i]=leerzp(primo,archivo);
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
		if(pol.c[i].n!=0) {
			if(pol.c[i].n>0) {
				fprintf(archivo,"+");
			}
			escribirzp(pol.c[i],archivo);
			fprintf(archivo," x^%d ", i);
		}
	}
  	if(pol.g>=1 && pol.c[1].n!=0) {
  		if(pol.c[1].n>0) {
  			fprintf(archivo,"+");
		}
		escribirzp(pol.c[1],archivo);
		fprintf(archivo," x ");
	}
	if(pol.g>=0 && pol.c[0].n!=0) {
		if(pol.c[0].n>0) {
			fprintf(archivo,"+");
		}
		escribirzp(pol.c[0],archivo);
	}
}

Px copia(Px a) {
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
		ret.c[i]=creazp(a.c[i].n,a.c[i].p);
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
		ret.c[i]=creazp(-a.c[i].n,a.c[i].p);
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
		ret.c[i]=sumazp(a.c[i],b.c[i]);	
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
	while(ret.g>=0 && ret.c[ret.g].n==0) {
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
		ret.c[i]=restazp(a.c[i],b.c[i]);	
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=creazp(-b.c[i].n,b.c[i].p);	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];
		}
	}
	while(ret.g>=0 && ret.c[ret.g].n==0) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Px multiplica_polinomio(Px a, Px b, int primo) {
	int i, j;
	Px ret;
	ret.g=a.g+b.g;
	if((ret.c=crea_arreglo(ret.g))==NULL){
    printf("Error de almacenamiento.\n");
		ret.g = -1;
		return ret;
	}
	for (i=0; i<=ret.g; i++) {
		ret.c[i]=creazp(0,primo);
	}
	for (i=0; i<=a.g; i++) {
    	for(j=0; j<=b.g; j++) {
      		ret.c[i+j]=sumazp(ret.c[i+j],productozp(a.c[i],b.c[j]));
		}
	}
	while(ret.g>=0 && ret.c[ret.g].n==0) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Px multi_monomio(Px a, zp mon, int gradMon, int primo) {
	int i;
	Px ret;
	ret.g=a.g+gradMon;
  	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for(i=0; i<=ret.g; i++){
		ret.c[i]=creazp(0,primo);
	}
	for(i=gradMon; i<=ret.g; i++) {
		ret.c[i]=productozp(a.c[i-gradMon],mon);
	}
	return ret;
}

Px divide_polinomio(Px a, Px b, Px *r, int primo) {
	Px q, aux, a_aux={g:-1, c:NULL};
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
    	q.g=-1;
    	return q;
	}
	for (i=0; i<=q.g; i++){
		q.c[i]=creazp(0,primo);
	}
	do{
    	grad=a.g-b.g;
    	q.c[grad]=divisionzp(a.c[a.g],b.c[b.g]);
		aux=multi_monomio(b,q.c[grad],grad,primo);
		a_aux=resta_polinomio(a,aux);
		libera(&a);
		libera(&aux);
		a = a_aux;
		libera(r);
		*r=copia(a);
	}while(!es_cero(*r) && (r->g>=b.g));
	return q;
}

Px MCD(Px a, Px b, int primo) {
	Px aux1,aux2,residuo={g:-1,c:NULL};
    if(es_cero(b)) {
        return copia(a);
	}
    aux1=copia(a);
    aux2=copia(b);
    divide_polinomio(aux1,aux2,&residuo,primo);
	while(!es_cero(residuo)) {
        aux1=copia(aux2);
        libera(&aux2);
		aux2=copia(residuo);
		libera(&residuo);
		divide_polinomio(aux1,aux2,&residuo,primo);
		libera(&aux1);
    }
    return aux2;
}

Px integral(Px pol, int primo){
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
	ret.c[0]=creazp(0,primo);
	for(i=0; i<=pol.g; i++) {
		ret.c[i+1]=divisionzp(pol.c[i],creazp(i+1,primo));
	}
	return ret;
}

Px derivada(Px pol, int primo){
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
		ret.c[i-1]=productozp(pol.c[i],creazp(i,primo));
	}
	return ret;
}

zp evaluacion(Px pol, zp num, int primo) {
    zp res=creazp(0,primo);
    int i;
    for(i=pol.g; i>0; i--) {
        res=productozp(num,sumazp(pol.c[i],res));
    }
    res=sumazp(res,pol.c[0]);
    return res;
}
