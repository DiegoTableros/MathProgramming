#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "abelson.h"

int nivelRecursionAbelson;
double longitudAbelson;
double miX0Abelson;
double miY0Abelson;
LOGO *tortugaAuxAbelson;

int CAbelson(int n, double l, LOGO *tortuga);

int iniciaAbelson(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionAbelson=n;
	longitudAbelson=l;
	miX0Abelson=x;
	miY0Abelson=y;
	tortugaAuxAbelson=tortuga;
	return 0;
}

int dibujaAbelson(void){
	inicia(miX0Abelson, miY0Abelson, 0, ABAJO, tortugaAuxAbelson);
	CAbelson(nivelRecursionAbelson,longitudAbelson,tortugaAuxAbelson);
	return 0;
}

int CAbelson(int n, double l, LOGO *tortuga){
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	CAbelson(n-1,l,tortuga);
	der(90,tortuga);
	CAbelson(n-1,l,tortuga);
	izq(90,tortuga);
	return 0;
}

