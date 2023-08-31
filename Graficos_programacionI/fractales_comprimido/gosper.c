#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "gosper.h"

int nivelRecursionGosper;
double longitudGosper;
double GSEGMENT;
double miX0Gosper;
double miY0Gosper;
LOGO *tortugaAuxGosper;

int LGosper(int n, double l, LOGO *tortuga);
int RGosper(int n, double l, LOGO *tortuga);

int iniciaGosper(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionGosper=n;
	longitudGosper=l;
	GSEGMENT=1.0/sqrt(7.0);
	miX0Gosper=x;
	miY0Gosper=y;
	tortugaAuxGosper=tortuga;
	return 0;
}

int dibujaGosper(void){
	inicia(miX0Gosper, miY0Gosper, 0, ABAJO, tortugaAuxGosper);
	RGosper(nivelRecursionGosper,longitudGosper,tortugaAuxGosper);
	return 0;
}

int RGosper(int n, double l, LOGO *tortuga) {
	double UNIT;
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	UNIT=l*GSEGMENT;
	der(75,tortuga);
	LGosper(n-1,UNIT,tortuga);
	izq(60,tortuga);
	RGosper(n-1,UNIT,tortuga);
	RGosper(n-1,UNIT,tortuga);
	izq(120,tortuga);
	RGosper(n-1,UNIT,tortuga);
	izq(60,tortuga);
	LGosper(n-1,UNIT,tortuga);
	der(120,tortuga);
	LGosper(n-1,UNIT,tortuga);
	der(60,tortuga);
	RGosper(n-1,UNIT,tortuga);
	izq(15,tortuga);
	return 0;
}

int LGosper(int n, double l, LOGO *tortuga) {
	double UNIT;
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	UNIT=l*GSEGMENT;
	der(15,tortuga);
	LGosper(n-1,UNIT,tortuga);
	izq(60,tortuga);
	RGosper(n-1,UNIT,tortuga);
	izq(120,tortuga);
	RGosper(n-1,UNIT,tortuga);
	der(60,tortuga);
	LGosper(n-1,UNIT,tortuga);
	der(120,tortuga);
	LGosper(n-1,UNIT,tortuga);
	LGosper(n-1,UNIT,tortuga);
	der(60,tortuga);
	RGosper(n-1,UNIT,tortuga);
	izq(75,tortuga);
	return 0;
}
