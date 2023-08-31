#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bib_gaussianos.h"

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

void escribeG(G x, FILE *archivo){
	char bufferTemporal[128];
	memset(bufferTemporal,'\0',sizeof(bufferTemporal));
	int l;
    if(x.a!=0) {
        sprintf(bufferTemporal,"%d",x.a);
    }
    if(x.b!=0) {
        if(x.b>0) {
        	l=strlen(bufferTemporal);	
            sprintf(bufferTemporal+l,"+");
        }
        if(x.b==-1) {
            l=strlen(bufferTemporal);	
            sprintf(bufferTemporal+l,"-");
        }
        if(x.b!=1 && x.b!=-1) {
            l=strlen(bufferTemporal);	
            sprintf(bufferTemporal+l,"%d",x.b);
        }
        l=strlen(bufferTemporal);	
        sprintf(bufferTemporal+l,"i");
    }
    ///Caso cero
    if(x.a==0 && x.b==0) {
    	sprintf(bufferTemporal,"0");
    }
    fprintf(archivo,"%14s",bufferTemporal);
}

G leerG(FILE *archivo){
    int x,y;
    fscanf(archivo,"%d%d",&x,&y);
    return creaG(x,y);
}
