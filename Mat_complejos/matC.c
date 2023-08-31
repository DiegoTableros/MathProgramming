#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "bib_complejos.h"
#include "bib_matC.h"

int main(int argc, char *argv[]) {
	///Archivos
	FILE *ent, *sal;
	///Nombres de archivos
	char *noment="matC.txt", *nomsal="resultado.txt";
	matriz res,a,b={A:NULL, m:0, n:0};
	///Abrimos el archivo de entrada
	ent=fopen(noment, "rt");
	if(ent==NULL){
    	int mi_error=errno; 
		printf("Hubo un error en la lectura del archivo. Codigo: %d. Mensaje: <<%s>>\nPor finalizar la ejecucion del programa.\n", 
		mi_error, strerror(mi_error));
		return -1;
	}
	///Comienzo del programa
	printf("Matrices con entradas complejas.\n\n");
	leeMatriz(&a,ent);
	leeMatriz(&b,ent);
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
	fprintf(sal, "Las matrices ingresadas son:\n");
	fprintf(sal,"\nA (%d x %d):\n", a.m, a.n);
	imprime_matriz(a, sal);
	fprintf(sal,"\nB (%d x %d):\n", b.m, b.n);
	imprime_matriz(b, sal);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"A+B:\n");
	res=suma_matriz(a,b,sal);
	if(res.m!=0 && res.n!=0) {
		imprime_matriz(res,sal);	
	}
	libera_espacio(&res);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"A-B:\n");
	res=resta_matriz(a,b,sal);
	if(res.m!=0 && res.n!=0) {
		imprime_matriz(res,sal);	
	}
	libera_espacio(&res);
	fprintf(sal,"\n\n");
	
	fprintf(sal,"AB:\n");
	res=multiplica_matriz(a,b,sal);
	if(res.m!=0 && res.n!=0) {
		imprime_matriz(res,sal);	
	}
	libera_espacio(&res);
	fprintf(sal,"\n\n");
	
	libera_espacio(&a);
	libera_espacio(&b);
	fclose(ent);
	fclose(sal);
	printf("Fin del programa.\n");
	system("PAUSE");
	return 0;
}
