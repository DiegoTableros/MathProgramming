#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logo.h"
#include "sierpinsky.h"

int nivelRecursionSierpinsky;
double longitudSierpinsky;
double DIAG;
double miX0Sierpinsky;
double miY0Sierpinsky;
LOGO *tortugaAuxSierpinsky;

int ONESIDE(int n, LOGO *tortuga);

int iniciaSierpinsky(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionSierpinsky=n;
	longitudSierpinsky=l;
	DIAG=l/sqrt(2.0);
	miX0Sierpinsky=x;
	miY0Sierpinsky=y;
	tortugaAuxSierpinsky=tortuga;
	return 0;
}

int dibujaSierpinsky(void){
	int i;
	inicia(miX0Sierpinsky, miY0Sierpinsky, 0, ABAJO, tortugaAuxSierpinsky);
	for(i=0; i<4; i++) {
		ONESIDE(nivelRecursionSierpinsky,tortugaAuxSierpinsky);
		der(45,tortugaAuxSierpinsky);
		avanza(DIAG,tortugaAuxSierpinsky);
		der(45,tortugaAuxSierpinsky);
	}
	return 0;
}

int ONESIDE(int n, LOGO *tortuga) {
	if(n==0) {
		return 0;
	}
	ONESIDE(n-1,tortuga);
	der(45,tortuga);
	avanza(DIAG,tortuga);
	der(45,tortuga);
	ONESIDE(n-1,tortuga);
	izq(90,tortuga);
	avanza(longitudSierpinsky,tortuga);
	izq(90,tortuga);
	ONESIDE(n-1,tortuga);
	der(45,tortuga);
	avanza(DIAG,tortuga);
	der(45,tortuga);
	ONESIDE(n-1,tortuga);
	return 0;
}
