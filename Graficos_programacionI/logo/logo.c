/*
 * Veronica Bola~nos
 * Materia: Programaci'on I
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logo.h"


int inicia(double x, double y, int grados, char pluma, LOGO* tortuga)
{
  tortuga->x=x;
  tortuga->y=y;
  tortuga->pluma = pluma;
  tortuga->grados = grados;
  
  return 0;
}

int asignaModoDibujarSegmento(void (*dibujaSegmento)(double, double, double, double), LOGO *tortuga)
{
  return (tortuga->dibujaSegmento = dibujaSegmento)!=NULL;
}

int der(int g, LOGO* tortuga)
{
  tortuga->grados = (((tortuga->grados-g)%360)+360)%360;
  
  return 0;
}

int izq(int g, LOGO* tortuga)
{
  return der(-g, tortuga);
}

int avanza(double l, LOGO* tortuga)
{
  double x=tortuga->x, y=tortuga->y;
  
  tortuga->x += l*cos(tortuga->grados*G2R);
  tortuga->y += l*sin(tortuga->grados*G2R);
  if (tortuga->pluma == ABAJO)
    tortuga->dibujaSegmento(x, y, tortuga->x, tortuga->y);

  return 0;
}

int retrocede(double l, LOGO* tortuga)
{
  return avanza(-l, tortuga);
}

int coloca(double x, double y, int grados, char pluma, LOGO* tortuga)
{
  tortuga->x=x;
  tortuga->y=y;
  tortuga->pluma = pluma;
  tortuga->grados = grados;

  return 0;
}

