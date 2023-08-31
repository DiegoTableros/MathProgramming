#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "dragon.h"

int nivelRecursionDragon;
double longitudDragon;
double miX0Dragon;
double miY0Dragon;
LOGO *tortugaAuxDragon;

int LDragon(int n, double l, LOGO *tortuga);
int RDragon(int n, double l, LOGO *tortuga);

int iniciaDragon(int n, double l, double x, double y, LOGO *tortuga){
	nivelRecursionDragon=n;
	longitudDragon=l;
	miX0Dragon=x;
	miY0Dragon=y;
	tortugaAuxDragon=tortuga;
	return 0;
}

int dibujaDragon(void){
	inicia(miX0Dragon, miY0Dragon, 0, ABAJO, tortugaAuxDragon);
	LDragon(nivelRecursionDragon,longitudDragon,tortugaAuxDragon);
	return 0;
}

int LDragon(int n, double l, LOGO *tortuga) {
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	LDragon(n-1,l,tortuga);
	izq(90,tortuga);
	RDragon(n-1,l,tortuga);
	return 0;
}

int RDragon(int n, double l, LOGO *tortuga) {
	if(n==0) {
		avanza(l,tortuga);
		return 0;
	}
	LDragon(n-1,l,tortuga);
	der(90,tortuga);
	RDragon(n-1,l,tortuga);
	return 0;
}
