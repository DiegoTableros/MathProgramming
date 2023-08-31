#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "mandelbrot.h"

int nivelRecursionMandelbrot;
double longitudMandelbrot;
double miX0Mandelbrot;
double miY0Mandelbrot;
LOGO *tortugaAuxMandelbrot;

int EDGE(int n, double l, LOGO *tortuga);

int iniciaMandelbrot(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionMandelbrot=n;
	longitudMandelbrot=l;
	miX0Mandelbrot=x;
	miY0Mandelbrot=y;
	tortugaAuxMandelbrot=tortuga;
	return 0;
}

int dibujaMandelbrot(void){
	int i;
	inicia(miX0Mandelbrot, miY0Mandelbrot, 0, ABAJO, tortugaAuxMandelbrot);
	for(i=0; i<4; i++) {
		EDGE(nivelRecursionMandelbrot,longitudMandelbrot,tortugaAuxMandelbrot);
		der(90,tortugaAuxMandelbrot);
	}
	return 0;
}

int EDGE(int n, double l, LOGO *tortuga) {
	double UNIT;
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	UNIT=l/4.0;
	EDGE(n-1,UNIT,tortuga);
	izq(90,tortuga);
	EDGE(n-1,UNIT,tortuga);
	der(90,tortuga);
	EDGE(n-1,UNIT,tortuga);
	der(90,tortuga);
	EDGE(n-1,UNIT,tortuga);
	EDGE(n-1,UNIT,tortuga);
	izq(90,tortuga);
	EDGE(n-1,UNIT,tortuga);
	izq(90,tortuga);
	EDGE(n-1,UNIT,tortuga);
	der(90,tortuga);
	EDGE(n-1,UNIT,tortuga);
	return 0;
}
