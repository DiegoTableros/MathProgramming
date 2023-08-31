#include <stdio.h>
#include <stdlib.h>
#include "bib_complejos.h"
#define EPS 1e-5

void escribeC(C x, FILE *archivo){
    if(x.a!=0.0) {
        ///Hay parte real
        if(x.a>0.0) {
        	fprintf(archivo,"+");
		}
		fprintf(archivo,"%lg",x.a);
    }
    ///Si hay parte ima
    if(x.b!=0.0) {
        if(x.b>0.0) {
            fprintf(archivo,"+");
        }
        if(x.b==-1.0) {
            fprintf(archivo,"-");
        }
        if(x.b!=1.0 && x.b!=-1.0) {
            fprintf(archivo,"%lg",x.b);
        }
        fprintf(archivo,"i");
    }
}

int es_C_cero(C num) {
	return (num.a==0.0 && num.b==0.0);
}

C leerC(FILE *archivo){
    double x,y;
    fscanf(archivo,"%lg%lg",&x,&y);
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
