#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bib_cuaterniones.h"

void escribeH(H x, FILE *archivo){
	char buffer[128];
	int l;
	memset(buffer,'\0',sizeof(buffer));
    ///Parte a
    if(x.a!=0.0) {
        sprintf(buffer,"%lg",x.a);
    }
    ///Parte b
    if(x.b!=0.0) {
        if(x.b>0.0) {
        	l=strlen(buffer);
            sprintf(buffer+l,"+");
        }
        if(x.b!=1.0 && x.b!=-1.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"%lg",x.b);
        }
        if(x.b==-1.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"-");
        }
        l=strlen(buffer);
        sprintf(buffer+l,"i");
    }
    ///Parte c
    if(x.c!=0.0) {
        if(x.c>0.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"+");
        }
        if(x.c!=1.0 && x.c!=-1.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"%lg",x.c);
        }
        if(x.c==-1.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"-");
        }
        l=strlen(buffer);
        sprintf(buffer+l,"j");
    }
    ///Parte d
    if(x.d!=0.0) {
        if(x.d>0.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"+");
        }
        if(x.d!=1.0 && x.d!=-1.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"%lg",x.d);
        }
        if(x.d==-1.0) {
            l=strlen(buffer);
            sprintf(buffer+l,"-");
        }
        l=strlen(buffer);
        sprintf(buffer+l,"k");
    }
    ///Caso cero
    if(x.a==0.0 && x.b==0.0 && x.c==0.0 && x.d==0.0) {
    	sprintf(buffer,"0");
	}
	fprintf(archivo,"%20s",buffer);
}

H creaH(double A, double B, double C, double D) {
	H ret;
  	ret.a=A; ret.b=B; ret.c=C; ret.d=D;
  	return ret;
}

H leerH(FILE *archivo){
    H num;
    fscanf(archivo,"%lg%lg%lg%lg",&num.a,&num.b,&num.c,&num.d);
    return num;
}

H sumaH(H x, H y){
    H res;
    res.a=x.a+y.a;
    res.b=x.b+y.b;
    res.c=x.c+y.c;
    res.d=x.d+y.d;
    return res;
}

H restaH(H x, H y){
    H res;
    res.a=x.a-y.a;
    res.b=x.b-y.b;
    res.c=x.c-y.c;
    res.d=x.d-y.d;
    return res;
}

H multiplicaH(H x, H y){
    H res;
    res.a=x.a*y.a-x.b*y.b-x.c*y.c-x.d*y.d;
    res.b=x.a*y.b+x.b*y.a+x.c*y.d-x.d*y.c;
    res.c=x.a*y.c-x.b*y.d+x.c*y.a+x.d*y.b;
    res.d=x.a*y.d+x.b*y.c-x.c*y.b+x.d*y.a;
    return res;
}

H conjugadoH(H x){
    x.b=-x.b;
    x.c=-x.c;
    x.d=-x.d;
    return x;
}

double normaH(H x){
    return sqrt(x.a*x.a+x.b*x.b+x.c*x.c+x.d*x.d);
}

H inversoH(H x){
    H res;
    res=conjugadoH(x);
    double norm2=normaH(x)*normaH(x);
    res.a/=norm2;
    res.b/=norm2;
    res.c/=norm2;
    res.d/=norm2;
    return res;
}

H divideH(H x, H y){
    H res;
    res=multiplicaH(x,inversoH(y));
    return res;
}
