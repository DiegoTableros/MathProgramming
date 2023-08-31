#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "bib_cuaterniones.h"
#include "bib_poliH.h"

int main(int argc, char *argv[]) {
	///Archivos
	FILE *ent, *sal;
	///Nombres de archivos
	char *noment="poliH.txt", *nomsal="resultado.txt";
	Px res,a,b,q,r={c:NULL, g:-1};
	H n,w,x,y,z;
	///Abrimos el archivo de entrada
	ent=fopen(noment,"rt");
	if(ent==NULL){
    	int mi_error=errno; 
		printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
		mi_error, strerror(mi_error));
		return -1;
	}
	///Comienzo del programa
	printf("Polinomios con coeficientes cuaterniones.\n\n");
	a=leer_polinomio(ent);
	b=leer_polinomio(ent);
	n=leerH(ent);
	y=leerH(ent);
	z=leerH(ent);
	///Abrimos el archivo de salida
	sal=fopen(nomsal, "wt");
	if(sal==NULL){
    	int mi_error=errno; 
		printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
		mi_error, strerror(mi_error));
		///Cerramos archivo de entrada
		fclose(ent);
		return -1;
	}
	fprintf(sal, "Los polinomios ingresados son:\n");
	fprintf(sal,"\na(x) = ");
	imprime_polinomio(a, sal);
	fprintf(sal,"\nb(x) = ");
	imprime_polinomio(b, sal);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"a+b:\n");
	res=suma_polinomio(a,b);
	imprime_polinomio(res,sal);
	libera(&res);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"a-b:\n");
	res=resta_polinomio(a,b);
	imprime_polinomio(res,sal);
	libera(&res);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"a*b:\n");
	res=multiplica_polinomio(a,b);
	imprime_polinomio(res,sal);
	libera(&res);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"a/b:\n");
	q=divide_polinomio(a, b, &r);
	if(es_cero(q)) {
		fprintf(sal,"No se puede efectuar la división.");
	} else {
		fprintf(sal,"q = ");
		imprime_polinomio(q,sal);
		fprintf(sal,"\nr = ");
		imprime_polinomio(r,sal);
		libera(&q);
		libera(&r);
	}
	fprintf(sal,"\n\n");
	
	fprintf(sal,"(a,b):\n");
	res=MCD(a,b);
	imprime_polinomio(res,sal);
	libera(&res);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"a'(x):\n");
	res=derivada(a);
	imprime_polinomio(res,sal);
	x=evaluacion(res,n);
	fprintf(sal,"\na'(x) evaluada: ");
	escribeH(x,sal);
	fprintf(sal, "\n\n");
	libera(&res);
	fprintf(sal,"Integral indefinida A(x):\n");
	res=integral(a);
	imprime_polinomio(res,sal);
	fprintf(sal,"+C");
	w=evaluacion(res,y);
	x=evaluacion(res,z);
	///Integral definida de Y a Z
	x=restaH(x,w);
	fprintf(sal,"\nIntegral definida en los límites: ");
	escribeH(x,sal);
	fprintf(sal, "\n\n");
	libera(&res);
	
	fprintf(sal,"b'(x):\n");
	res=derivada(b);
	imprime_polinomio(res,sal);
	x=evaluacion(res,n);
	fprintf(sal,"\nb'(x) evaluada: ");
	escribeH(x,sal);
	fprintf(sal, "\n\n");
	libera(&res);
	fprintf(sal,"Integral indefinida B(x):\n");
	res=integral(b);
	imprime_polinomio(res,sal);
	fprintf(sal,"+C");
	w=evaluacion(res,y);
	x=evaluacion(res,z);
	///Integral definida de Y a Z
	x=restaH(x,w);
	fprintf(sal,"\nIntegral definida en los límites: ");
	escribeH(x,sal);
	fprintf(sal, "\n\n");
	libera(&res);
	
	libera(&a);
	libera(&b);
	fclose(ent);
	fclose(sal);
	printf("Fin del programa.\n");
	system("PAUSE");
	return 0;
}
