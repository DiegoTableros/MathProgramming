#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "koch.h"

int nivelRecursionKoch;
double longitudKoch;
double miX0Koch;
double miY0Koch;
LOGO *tortugaAuxKoch;

int SIDE(int n, double l, LOGO *tortuga);

int iniciaKoch(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionKoch=n;
	longitudKoch = l;
	miX0Koch=x;
	miY0Koch=y;
	tortugaAuxKoch = tortuga;
	return 0;
}

int dibujaKoch(void){
	int i;
	inicia(miX0Koch, miY0Koch, 0, ABAJO, tortugaAuxKoch);
	for(i=0; i<3; i++) {
		SIDE(nivelRecursionKoch,longitudKoch,tortugaAuxKoch);
		der(120,tortugaAuxKoch);
	}
	return 0;
}

int SIDE(int n, double l, LOGO *tortuga){
	double l3;
	if (n==0){
    	avanza(l,tortuga);
    	return 0;
 	}
  	l3=l/3.0;
  	SIDE(n-1, l3, tortuga);
  	izq(60, tortuga);
  	SIDE(n-1, l3, tortuga);
  	der(120, tortuga);
  	SIDE(n-1, l3, tortuga);
  	izq(60, tortuga);
  	SIDE(n-1, l3, tortuga); 
	return 0;
}
