#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "hilbert.h"

int nivelRecursionHilbert;
double longitudHilbert;
double paridadHilbert;
double miX0Hilbert;
double miY0Hilbert;
LOGO *tortugaAuxHilbert;

int HilbertRecursivo(int n, double l, double paridad, LOGO *tortuga);

int iniciaHilbert(int n, double l, double paridad, double x, double y, LOGO *tortuga){
	nivelRecursionHilbert=n;
	longitudHilbert=l;
	paridadHilbert=paridad;
	miX0Hilbert=x;
	miY0Hilbert=y;
	tortugaAuxHilbert=tortuga;
	return 0;
}

int dibujaHilbert(void){
	inicia(miX0Hilbert, miY0Hilbert, 0, ABAJO, tortugaAuxHilbert);
	HilbertRecursivo(nivelRecursionHilbert,longitudHilbert,paridadHilbert,tortugaAuxHilbert);
	return 0;
}

int HilbertRecursivo(int n, double l, double paridad, LOGO *tortuga){
	if(n==0) {
		return 0;
	}
	izq(paridad*90,tortuga);
	HilbertRecursivo(n-1,l,-paridad,tortuga);
	avanza(l,tortuga);
	der(paridad*90,tortuga);
	HilbertRecursivo(n-1,l,paridad,tortuga);
	avanza(l,tortuga);
	HilbertRecursivo(n-1,l,paridad,tortuga);
	der(paridad*90,tortuga);
	avanza(l,tortuga);
	HilbertRecursivo(n-1,l,-paridad,tortuga);
	izq(paridad*90,tortuga);
	return 0;
}
