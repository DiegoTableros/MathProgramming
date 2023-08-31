#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "bib_racionales.h"
#include "bib_reales.h"
#include "bib_cuaterniones.h"
#include "bib_gaussianos.h"
#include "bib_Zp.h"
#include "bib_complejos.h"

///Enumerado de coeficientes del 0 al 5 y enumerado de las funciones del 0 al 3
enum tipoCoeficiente{numQ,numR,numH,numG,numZp,numC,total};
enum funcion{suma,resta,multiplicacion,division};

///Union para almacenar todos los tipos en uno a la vez
typedef union _coeficiente_{
	Q racional;
	double real;
	H cuaternion;
	G gaussiano;
	zp zprimo;
	C complejo;
}coeficiente;

///Funciones base
coeficiente leer_coeficiente(int tipo,int p,FILE *f);
void escribe_coeficiente(FILE *f,coeficiente a,enum tipoCoeficiente tipo);
coeficiente operacion(coeficiente a, coeficiente b, void *operacion, enum tipoCoeficiente tipo);
void imprime_operacion(FILE *f,coeficiente a,coeficiente b,coeficiente c,enum tipoCoeficiente tipo,enum funcion operacion;);
int igual_a_cero(coeficiente a,enum tipoCoeficiente tipo);

int main(int argc, char *argv[]) {
	///Coeficientes a utilizar
	coeficiente a,b,c;
	///Variables enteras auxiliares
	int com,primo=0;
	///Arreglo de funciones
	void *funciones[]={sumaQ,sumaR,sumaH,sumaG,sumazp,sumaC,restaQ,restaR,restaH,restaG,restazp,restaC,multiplicaQ,multiplicaR,multiplicaH,multiplicaG,multiplicazp,multiplicaC,divideQ,divideR,divideH,NULL,dividezp,divideC};
	///Cosas de archivos
	FILE *ent,*sal;
	char *noment="coeficientes.txt",*nomsal="resultado.txt";
	///Apertura del archivo de entrada
	ent=fopen(noment,"rt");
	if(ent==NULL){
		int mi_error=errno;
		printf("\nError al abrir archivo. Codigo: %d. Mensaje: <<%s>>.\nFinalizando ejecucion del programa.\n",mi_error,strerror(mi_error));
		return -1;
	}
	///Lectura del coeficiente a manejar	
	fscanf(ent,"%d",&com);
	///Lectura de los dos coeficientes, CASO ESPECIAL PARA ZP=4
	if(com!=4) {
		a=leer_coeficiente(com,primo,ent);
		b=leer_coeficiente(com,primo,ent);
	} else {
		fscanf(ent,"%d",&primo);
		a=leer_coeficiente(com,primo,ent);
		b=leer_coeficiente(com,primo,ent);
	}
	///Apertura del archivo salida
	sal=fopen(nomsal,"wt");
	if(sal==NULL){
		int mi_error=errno;
		printf("\nError al abrir archivo. Codigo: %d. Mensaje: <<%s>>.\nFinalizando ejecucion del programa.\n",mi_error,strerror(mi_error));
		fclose(ent);
		system("PAUSE");
		return -1;
	}
	///Titulo
	switch(com) {
		case numQ:
			printf("Apuntadores a funciones con racionales.\n\n");
			fprintf(sal,"Apuntadores a funciones con racionales.\n");
			break;
		case numR:
			printf("Apuntadores a funciones con reales.\n\n");
			fprintf(sal,"Apuntadores a funciones con reales.\n");
			break;
		case numH:
			printf("Apuntadores a funciones con cuaterniones.\n\n");
			fprintf(sal,"Apuntadores a funciones con cuaterniones.\n");
			break;
		case numG:
			printf("Apuntadores a funciones con gaussianos.\n\n");
			fprintf(sal,"Apuntadores a funciones con gaussianos.\n");
			break;
		case numZp:
			printf("Apuntadores a funciones con Zp.\n\n");
			fprintf(sal,"Apuntadores a funciones con Zp.\n");
			break;
		case numC:
			printf("Apuntadores a funciones con complejos.\n\n");
			fprintf(sal,"Apuntadores a funciones con complejos.\n");
			break;
	}
	///Suma
	fprintf(sal,"\nSuma:\n");
	c=operacion(a,b,funciones[com],com);
	imprime_operacion(sal,a,b,c,com,suma);
	///Resta
	fprintf(sal,"\nResta:\n");
	c=operacion(a,b,funciones[com+total],com);
	imprime_operacion(sal,a,b,c,com,resta);
	///Producto
	fprintf(sal,"\nProducto:\n");
	c=operacion(a,b,funciones[com+total*2],com);
	imprime_operacion(sal,a,b,c,com,multiplicacion);
	///Division, CASO ESPECIAL PARA GAUSSIANOS=3
	fprintf(sal,"\nDivision:\n");
	if(com!=3){
		///CASO ESPECIAL DENOMINADOR CERO
		if(igual_a_cero(b,com)){
			fprintf(sal,"No se puede realizar la división.\n");
		}else{
			c=operacion(a,b,funciones[com+total*3],com);
			imprime_operacion(sal,a,b,c,com,division);
		}
	}else{
		fprintf(sal,"La division en G no está definida.\n");
	}
	///Cerrar archivos y FIN	
	fclose(ent);
	fclose(sal);
	system("PAUSE");	
	return 0;
}

coeficiente operacion(coeficiente a,coeficiente b,void *operacion,enum tipoCoeficiente tipo){
	///Declaracion de las distintas funciones binarias
	Q (*fQ)(Q,Q);
	double (*fR)(double,double);
	H (*fH)(H,H);
	G (*fG)(G,G);
	zp (*fzp)(zp,zp);
	C (*fC)(C,C);
	coeficiente ret;
	///Escogemos la operacion dependiendo del tipo
	switch(tipo){
		case numQ:
			fQ=operacion;
			ret.racional=fQ(a.racional,b.racional);
			break;
		case numR:
			fR=operacion;
			ret.real=fR(a.real,b.real);
			break;
		case numH:
			fH=operacion;
			ret.cuaternion=fH(a.cuaternion,b.cuaternion);
			break;
		case numG:
			fG=operacion;
			ret.gaussiano=fG(a.gaussiano,b.gaussiano);
			break;
		case numZp:
			fzp=operacion;
			ret.zprimo=fzp(a.zprimo,b.zprimo);
			break;
		case numC:
			fC=operacion;
			ret.complejo=fC(a.complejo,b.complejo);
			break;
	}
	return ret;
}

void escribe_coeficiente(FILE *archivo,coeficiente a,enum tipoCoeficiente tipo){
	///Directamente hacer impresion en el archivo
	switch(tipo){
		case numQ:
			escribeQ(a.racional,archivo);
			break;
		case numR:
			 escribeR(a.real,archivo);
			break;
		case numH:
            escribeH(a.cuaternion,archivo);
			break;
		case numG:
			escribeG(a.gaussiano,archivo);
			break;
		case numZp:
        	escribirzp(a.zprimo,archivo);
			break;
		case numC:
            escribeC(a.complejo,archivo);
			break;
	}
}

coeficiente leer_coeficiente(int tipo,int primo,FILE *archivo){
	///Recibimos el primo solo para el caso ZP
	coeficiente ret;
	switch(tipo){
		case numQ:
			ret.racional=leerQ(archivo);
			break;
		case numR:
			ret.real=leerR(archivo);
			break;
		case numH:
			ret.cuaternion=leerH(archivo);
			break;
		case numG:
			ret.gaussiano=leerG(archivo);
			break;
		case numZp:
			///CASO ESPECIAL ZP
			ret.zprimo=leerzp(primo,archivo);
			break;
		case numC:
			ret.complejo=leerC(archivo);
			break;
	}
	return ret;
}

void imprime_operacion(FILE *f,coeficiente a,coeficiente b,coeficiente c,enum tipoCoeficiente tipo,enum funcion operacion){
	///Imprimimos: "a" signo "b" igual "c"
	///Imprimimos "a"
	escribe_coeficiente(f,a,tipo);
	///Signo
	switch(operacion){
		case suma:
			fprintf(f," + ");
			break;
		case resta:
			fprintf(f," - ");
			break;
		case multiplicacion:
			fprintf(f," * ");
			break;
		case division:
			fprintf(f," / ");
			break;
	}
	///Imprimos "b"
	escribe_coeficiente(f,b,tipo);
	///Igual
	fprintf(f," = ");
	///Imprimimos "c"
	escribe_coeficiente(f,c,tipo);
	fprintf(f,"\n");
}

int igual_a_cero(coeficiente a,enum tipoCoeficiente tipo){
	///Checamos si el coeficiente es cero equivalente
	switch(tipo){
		case numQ:
			if(a.racional.p==0){
				return 1;
			}
			break;
		case numR:
			if(a.real==0.0){
				return 1;
			}
			break;
		case numH:
			if(a.cuaternion.a==0.0 && a.cuaternion.b==0.0 && a.cuaternion.c==0.0 && a.cuaternion.d==0.0){
				return 1;
			}
			break;
		case numG:
        	if(a.gaussiano.a==0 && a.gaussiano.b==0){
				return 1;
			}
			break;
		case numZp:
            if(a.zprimo.n==0){
				return 1;
			}
			break;
		case numC:
        	if(a.complejo.a==0.0 && a.complejo.b==0.0){
				return 1;
			}
			break;
	}
	///Si estamos aqui entonces no es cero
	return 0;
}

