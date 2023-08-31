#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_racionales.h"

int mcd(int a, int b) {
  	int r=0;
  	a=(a<0?-a:a);
  	b=(b<0?-b:b);
  	if(b==0) {
    	return a;
    }
  	while((r=a%b)!=0) {
    	a=b;
      	b=r;
    }
  	return b;
}

Q simplificaQ(Q a) {
  	Q retorna=a;
  	int div=mcd(a.p, a.q);
  	if(div>1) {
    	retorna.p/=div;
      	retorna.q/=div;
    }
  	if(retorna.q<0) {
    	retorna.q*=-1;
      	retorna.p*=-1;
    }
  	return retorna;
}

void escribeQ(Q a, FILE *archivo) {
	char buferTemporal[128];
	int l;
	sprintf(buferTemporal, "%d", a.p);
	l=strlen(buferTemporal);
	if (a.q!=1 && a.p!=0) {
		sprintf(buferTemporal+l, "/%d", a.q);
	}
	fprintf(archivo,"%7s",buferTemporal);
}

Q leerQ(FILE *archivo) {
	Q A;
	fscanf(archivo,"%d%d", &A.p, &A.q);
    A=simplificaQ(A);
	return A;
}

Q creaQ(int num, int den) {
	Q r = {num, den};
	r=simplificaQ(r);
	return r;
}

Q sumaQ(Q a, Q b) {
    Q res;
    res.p=a.p*b.q+a.q*b.p;
    res.q=a.q*b.q;
    res=simplificaQ(res);
    return res;
}

Q restaQ(Q a, Q b) {
    Q res;
    res.p=a.p*b.q-a.q*b.p;
    res.q=a.q*b.q;
    res=simplificaQ(res);
    return res;
}

Q multiplicaQ(Q a, Q b){
    Q res;
    res.p=a.p*b.p;
    res.q=a.q*b.q;
    res=simplificaQ(res);
    return res;
}

Q divideQ(Q a, Q b){
    Q res;
    res.p=a.p*b.q;
    res.q=a.q*b.p;
    res=simplificaQ(res);
    return res;
}
