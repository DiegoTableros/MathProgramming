#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 1e-6
#include "bib_cuaterniones.h"

H leerH(FILE *archivo){
    H num;
    fscanf(archivo,"%lg%lg%lg%lg",&num.a,&num.b,&num.c,&num.d);
    return num;
}

int es_H_cero(H x) {
	return (x.a==0.0 && x.b==0.0 && x.c==0.0 && x.d==0.0);
}

H creaH(double A, double B, double C, double D) {
	H ret;
  	ret.a=A; ret.b=B; ret.c=C; ret.d=D;
  	return ret;
}

void escribeH(H x, FILE *archivo){
    ///Parte a
    if(x.a!=0.0) {
    	if(x.a>0.0) {
    		fprintf(archivo,"+");
		}
        fprintf(archivo,"%lg ",x.a);
    }
    ///Parte b
    if(x.b!=0.0) {
        if(x.b>0.0) {
            fprintf(archivo,"+");
        }
        if(x.b!=1.0 && x.b!=-1.0) {
            fprintf(archivo,"%lg",x.b);
        }
        if(x.b==-1.0) {
            fprintf(archivo,"-");
        }
        fprintf(archivo,"i ");
    }
    ///Parte c
    if(x.c!=0.0) {
        if(x.c>0.0) {
            fprintf(archivo,"+");
        }
        if(x.c!=1.0 && x.c!=-1.0) {
            fprintf(archivo,"%lg",x.c);
        }
        if(x.c==-1.0) {
            fprintf(archivo,"-");
        }
        fprintf(archivo,"j ");
    }
    ///Parte d
    if(x.d!=0.0) {
        if(x.d>0.0) {
            fprintf(archivo,"+");
        }
        if(x.d!=1.0 && x.d!=-1.0) {
            fprintf(archivo,"%lg",x.d);
        }
        if(x.d==-1.0) {
            fprintf(archivo,"-");
        }
        fprintf(archivo,"k");
    }
}

H sumaH(H x, H y){
    H res;
    res.a=x.a+y.a;
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
	res.b=x.b+y.b;
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	res.c=x.c+y.c;
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    res.d=x.d+y.d;
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
    return res;
}

H restaH(H x, H y){
    H res;
    res.a=x.a-y.a;
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
	res.b=x.b-y.b;
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	res.c=x.c-y.c;
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    res.d=x.d-y.d;
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
    return res;
}

H multiplicaH(H x, H y){
    H res;
    res.a=x.a*y.a-x.b*y.b-x.c*y.c-x.d*y.d;
    res.b=x.a*y.b+x.b*y.a+x.c*y.d-x.d*y.c;
    res.c=x.a*y.c-x.b*y.d+x.c*y.a+x.d*y.b;
    res.d=x.a*y.d+x.b*y.c-x.c*y.b+x.d*y.a;
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
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
    double norm2=normaH(x);
    norm2*=norm2;
    if(norm2==0.0) {
    	return x;
	}
    res.a/=norm2;
    res.b/=norm2;
    res.c/=norm2;
    res.d/=norm2;
    ///Epsilon
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
    return res;
}

H divideH(H x, H y){
    H res;
    res=multiplicaH(x,inversoH(y));
    return res;
}
