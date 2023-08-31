#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "malmberg.h"

int nivelRecursionMalmberg;
double longitudMalmberg;
double PARITY;
double X;
double miX0Malmberg;
double miY0Malmberg;
LOGO *tortugaAuxMalmberg;

int MAZE(int n, double l, LOGO *tortuga);
int INTERIOR(double l, LOGO *tortuga);

int iniciaMalmberg(int n, double l, double param, double x, double y, LOGO *tortuga){
	nivelRecursionMalmberg=n;
	longitudMalmberg=l;
	PARITY=-1.0;
	X=param;
	miX0Malmberg=x;
	miY0Malmberg=y;
	tortugaAuxMalmberg=tortuga;
	return 0;
}

int dibujaMalmberg(void){
	inicia(miX0Malmberg, miY0Malmberg, 0, ABAJO, tortugaAuxMalmberg);
	///Si X==1.0 se imprime el MAZE, sino se imprime el WEAVE
	MAZE(nivelRecursionMalmberg,longitudMalmberg,tortugaAuxMalmberg);
	return 0;
}

int MAZE(int n, double l, LOGO *tortuga){
	double UNIT;
	int i;
	if(n==0) {
		INTERIOR(l,tortuga);
		return 0;
	}
	UNIT=l/3.0;
	MAZE(n-1,UNIT,tortuga);
	izq(90,tortuga);
	MAZE(n-1,UNIT,tortuga);
	for(i=0; i<3; i++) {
		der(90,tortuga);
		MAZE(n-1,UNIT,tortuga);
	}
	for(i=0; i<3; i++) {
		izq(90,tortuga);
		MAZE(n-1,UNIT,tortuga);
	}
	der(90,tortuga);
	MAZE(n-1,UNIT,tortuga);
	return 0;
}

int INTERIOR(double l, LOGO *tortuga){
	PARITY=-1.0;
	double UNIT=l/5.0;
	if(X==1.0) {
		PARITY=1.0;
		izq(45,tortuga);
	}
	avanza(4.0*UNIT,tortuga);
	der(90*PARITY,tortuga);
	avanza(3.0*UNIT,tortuga);
	der(90*PARITY,tortuga);
	avanza(2.0*UNIT,tortuga);
	der(90*PARITY,tortuga);
	avanza(UNIT,tortuga);
	der(90*PARITY,tortuga);
	avanza(UNIT,tortuga);
	izq(90*PARITY,tortuga);
	avanza(UNIT,tortuga);
	izq(90*PARITY,tortuga);
	avanza(2.0*UNIT,tortuga);
	izq(90*PARITY,tortuga);
	avanza(3.0*UNIT,tortuga);
	izq(90*PARITY,tortuga);
	avanza(4.0*UNIT,tortuga);
	izq(90*PARITY,tortuga);
	avanza(4.0*UNIT,tortuga);
	der(90*PARITY,tortuga);
	if(X==1.0) {
		der(90,tortuga);
		avanza(4*UNIT,tortuga);
		izq(45,tortuga);
	}
	return 0;
}
