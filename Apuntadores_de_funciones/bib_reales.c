#include <stdlib.h>
#include <stdio.h>
#include "bib_reales.h"

void escribeR(double x, FILE *archivo){
	fprintf(archivo,"%6lg",x);
}

double leerR(FILE *archivo){
	double ret;
	fscanf(archivo,"%lg",&ret);
	return ret;
}

double creaR(double num){
	return num;
}

double sumaR(double x, double y){
	return x+y;
}

double restaR(double x, double y){
	return x-y;
}

double multiplicaR(double x, double y){
	return x*y;
}

double divideR(double x, double y){
	return x/y;
}
