#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "triangles.h"

int nivelRecursionTriangles;
double longitudTriangles;
double miX0Triangles;
double miY0Triangles;
LOGO *tortugaAuxTriangles;

int NESTEDTRIANGLE(int n, double l, LOGO *tortuga);

int iniciaTriangles(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionTriangles=n;
	longitudTriangles=l;
	miX0Triangles=x;
	miY0Triangles=y;
	tortugaAuxTriangles=tortuga;
	return 0;
}

int dibujaTriangles(void){
	inicia(miX0Triangles, miY0Triangles, 0, ABAJO, tortugaAuxTriangles);
	NESTEDTRIANGLE(nivelRecursionTriangles,longitudTriangles,tortugaAuxTriangles);
	return 0;
}

int NESTEDTRIANGLE(int n, double l, LOGO *tortuga){
	int i;
	if(n==0) {
		return 0;
	}
	for(i=0; i<3; i++) {
		NESTEDTRIANGLE(n-1,l/2.0,tortuga);
		avanza(l,tortuga);
		der(120,tortuga);
	}
	return 0;
}
