#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bib_racionales.h"

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

void escribeQ(Q a, FILE *archivo){
	char buferTemporal[128];
	int l;
	if(a.p==1 && a.q==1) {
		fprintf(archivo,"+");
		return;
	}
	if(a.p==-1 && a.q==1) {
		fprintf(archivo,"-");
		return;
	}
	if(a.p>0) {
		sprintf(buferTemporal, "+%d", a.p);
	} else {
		sprintf(buferTemporal, "%d", a.p);
	}
	if (a.q!=1){
		l = strlen(buferTemporal);
		sprintf(buferTemporal+l,"/%d",a.q);	
	}
	fprintf(archivo,"%s", buferTemporal);
}

Q leerQ(FILE *archivo){
	Q A;
    fscanf(archivo,"%d%d",&A.p,&A.q);
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

