#include <stdio.h>
#include <stdlib.h>
#include "logo.h"
#include "polygon.h"

double LIMIT;
double sizePolygon;
double anglePolygon;
double lPolygon;
double miX0Polygon;
double miY0Polygon;
LOGO *tortugaAuxPolygon;

int CORNERPOLY(double size, double angle, double totalturn, LOGO *tortuga);
int CORNERPOLYSTEP(double size, double angle, LOGO *tortuga);

int iniciaPolygon(double size, double angle, double l, double x, double y, LOGO *tortuga){
	sizePolygon=size;
	anglePolygon=angle;
	lPolygon=l;
	LIMIT=l;
	miX0Polygon=x;
	miY0Polygon=y;
	tortugaAuxPolygon=tortuga;
	return 0;
}

int dibujaPolygon(void){
	inicia(miX0Polygon, miY0Polygon, 0, ABAJO, tortugaAuxPolygon);
	CORNERPOLY(sizePolygon,anglePolygon,0.0,tortugaAuxPolygon);
	return 0;
}

int CORNERPOLY(double size, double angle, double totalturn, LOGO *tortuga){
	if(size<LIMIT) {
		return 0;
	}
	CORNERPOLYSTEP(size,angle,tortuga);
	totalturn=totalturn+angle;
	if(((int)totalturn)%360!=0) {
		CORNERPOLY(size,angle,totalturn,tortuga);
	}
	return 0;
}

int CORNERPOLYSTEP(double size, double angle, LOGO *tortuga){
	avanza(size,tortuga);
	CORNERPOLY(size/2.0,-1.0*angle,0,tortuga);
	der(angle,tortuga);
	return 0;
}
