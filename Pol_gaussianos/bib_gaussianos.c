#include <stdio.h>
#include <stdlib.h>
#include "bib_gaussianos.h"

int es_G_cero(G num) {
	return (num.a==0 && num.b==0);
}

void escribeG(G x, FILE *archivo){
    ///Aqui estan todos los casos para escribir complejos
    if(x.a!=0) {
        ///Hay parte real
        fprintf(archivo,"%d",x.a);
    }
    ///Si hay parte ima
    if(x.b!=0) {
        if(x.b>0) {
            fprintf(archivo,"+");
        }
        if(x.b==-1) {
            fprintf(archivo,"-");
        }
        if(x.b!=1 && x.b!=-1) {
            fprintf(archivo,"%d",x.b);
        }
        fprintf(archivo,"i");
    }
}

G leerG(FILE *archivo){
    int x,y;
    fscanf(archivo,"%d%d",&x,&y);
    return creaG(x,y);
}

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
