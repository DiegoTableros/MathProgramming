#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bib_complejos.h"

void escribeC(C x, FILE *archivo){
	char bufferTemporal[128];
	memset(bufferTemporal,'\0',sizeof(bufferTemporal));
	int l;
    if(x.a!=0.0) {
        sprintf(bufferTemporal,"%lg",x.a);
    }
    if(x.b!=0.0) {
        if(x.b>0.0) {
        	l=strlen(bufferTemporal);	
            sprintf(bufferTemporal+l,"+");
        }
        if(x.b==-1.0) {
            l=strlen(bufferTemporal);	
            sprintf(bufferTemporal+l,"-");
        }
        if(x.b!=1.0 && x.b!=-1.0) {
            l=strlen(bufferTemporal);	
            sprintf(bufferTemporal+l,"%lg",x.b);
        }
        l=strlen(bufferTemporal);	
        sprintf(bufferTemporal+l,"i");
    }
    ///Caso cero
    if(x.a==0.0 && x.b==0.0) {
    	sprintf(bufferTemporal,"0");
    }
    fprintf(archivo,"%16s",bufferTemporal);
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
