#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logo.h"
#include "hooked.h"

int nivelRecursionHooked;
double longitudHooked;
double miX0Hooked;
double miY0Hooked;
LOGO *tortugaAuxHooked;

int RSNOW(int n, double l, LOGO *tortuga);
int LSNOW(int n, double l, LOGO *tortuga);

int iniciaHooked(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionHooked=n;
	longitudHooked=l;
	miX0Hooked=x;
	miY0Hooked=y;
	tortugaAuxHooked=tortuga;
	return 0;
}

int dibujaHooked(void){
	inicia(miX0Hooked, miY0Hooked, 0, ABAJO, tortugaAuxHooked);
	RSNOW(nivelRecursionHooked,longitudHooked,tortugaAuxHooked);
	return 0;
}

int RSNOW(int n, double l, LOGO *tortuga){
	double UNIT, SUNIT;
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	UNIT=l/3.0;
	SUNIT=(l*2.0*(sin(60*G2R)))/9.0;
	izq(60,tortuga);
	LSNOW(n-1,UNIT,tortuga);
	RSNOW(n-1,UNIT,tortuga);
	der(60,tortuga);
	RSNOW(n-1,UNIT,tortuga);
	der(60,tortuga);
	RSNOW(n-1,UNIT,tortuga);
	der(150,tortuga);
	RSNOW(n-1,SUNIT,tortuga);
	LSNOW(n-1,SUNIT,tortuga);
	izq(60,tortuga);
	RSNOW(n-1,SUNIT,tortuga);
	izq(60,tortuga);
	LSNOW(n-1,SUNIT,tortuga);
	RSNOW(n-1,SUNIT,tortuga);
	izq(90,tortuga);
	LSNOW(n-1,UNIT,tortuga);
	RSNOW(n-1,UNIT,tortuga);
	return 0;
}

int LSNOW(int n, double l, LOGO *tortuga){
	double UNIT, SUNIT;
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	UNIT=l/3.0;
	SUNIT=(l*2.0*(sin(60*G2R)))/9.0;
	LSNOW(n-1,UNIT,tortuga);
	RSNOW(n-1,UNIT,tortuga);
	der(90,tortuga);
	LSNOW(n-1,SUNIT,tortuga);
	RSNOW(n-1,SUNIT,tortuga);
	der(60,tortuga);
	LSNOW(n-1,SUNIT,tortuga);
	der(60,tortuga);
	RSNOW(n-1,SUNIT,tortuga);
	LSNOW(n-1,SUNIT,tortuga);
	izq(150,tortuga);
	LSNOW(n-1,UNIT,tortuga);
	izq(60,tortuga);
	LSNOW(n-1,UNIT,tortuga);
	izq(60,tortuga);
	LSNOW(n-1,UNIT,tortuga);
	RSNOW(n-1,UNIT,tortuga);
	der(60,tortuga);
	return 0;
}
