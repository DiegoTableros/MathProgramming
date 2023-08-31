#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 

typedef struct _empresa_ {
	char institucion[64];
	unsigned int tel;
}empresa;

typedef struct _entradaDirectorio_{
	char nombre[32],apellidoPaterno[32],apellidoMaterno[32];
	int edad;
	double altura;
	unsigned short lada;
	unsigned int telFijo, telCel;
	char estado[64];
	char anotacion[64];
	empresa trabajo;                               
}EntradaDirectorio;

int agrega_entrada(FILE *directorio, EntradaDirectorio info);
int obtener_entrada(FILE *directorio, EntradaDirectorio *info); 
int mostrar_contacto(FILE *archivo, int contacto);
EntradaDirectorio leer_contacto(void);
int mostrar_todos_contactos(FILE *directorio);
int mostrar_contactos(FILE *directorio);
int modificar_contacto(FILE *directorio, int a, int b);
int modificar_campo(FILE *directorio, int a, int b);
int borrar_contacto(FILE *directorio, int a, int b);

int main(int argc, char *argv[]){
	///Archivo para guardar los datos
	FILE *archivoBinario;
	int i,seguir,comando,total,num;
	EntradaDirectorio entrada;
	archivoBinario=fopen("directorio.bin", "ab+");
	if (archivoBinario == NULL){
    	int errAuxiliar;          
    	errAuxiliar = errno;      
    	fprintf(stderr,"No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n",errAuxiliar,strerror(errAuxiliar));                                            
		return 0;
	}
	printf("DIRECTORIO\n\n");
	///INSTRUCCIONES
	do{
		printf("Digite el comando de la opcion deseada:\n");
		printf("\t1) Mostrar todos los contactos guardados.\n");
		printf("\t2) Mostrar un contacto (dado su numero).\n");
		printf("\t3) Agregar un nuevo contacto.\n");
		printf("\t4) Editar un contacto completo.\n");
		printf("\t5) Editar un campo de un contacto.\n");
		printf("\t6) Borrar un contacto.\n");
		printf("\t7) Borrar todo el directorio.\n");
		do{
			printf("\tComando: ");
			scanf("%d",&comando);
		}while(comando<1 || comando>7);
		switch(comando) {
			case 1:
				printf("Contactos actualmente en el directorio:\n");
				mostrar_todos_contactos(archivoBinario);
				break;
			case 2:
				printf("Contactos en el directorio:\n");
				mostrar_contactos(archivoBinario);
				printf("\n\tDigite el numero de contacto: ");
				scanf("%d",&num);
				mostrar_contacto(archivoBinario,num);
				break;
			case 3:
				printf("Digite la informacion del nuevo contacto:\n");
				entrada=leer_contacto();
				agrega_entrada(archivoBinario,entrada);
				printf("\tContacto añadido\n");
				break;
			case 4:
				printf("Contactos en el directorio:\n");
				total=mostrar_contactos(archivoBinario);
				printf("\n\tDigite el numero de contacto a editar: ");
				scanf("%d",&num);
				modificar_contacto(archivoBinario,total,num);
				printf("\tContacto editado\n");
				break;
			case 5:
				printf("Contactos en el directorio:\n");
				total=mostrar_contactos(archivoBinario);
				printf("\n\tDigite el numero de contacto a editar: ");
				scanf("%d",&num);
				modificar_campo(archivoBinario,total,num);
				printf("\tContacto editado\n");
				break;
			case 6:
				printf("Contactos en el directorio:\n");
				total=mostrar_contactos(archivoBinario);
				printf("\n\tDigite el numero de contacto a borrar: ");
				scanf("%d",&num);
				borrar_contacto(archivoBinario,total,num);
				printf("\tContacto borrado\n");
				break;
			case 7:
				printf("Borrando todo el directorio\n");
				fclose(archivoBinario);
				archivoBinario=fopen("directorio.bin", "wb+");
				printf("Directorio borrado.\n");
				break;
		}
		printf("\nPara finalizar digite 0, para continuar digite 1: ");
		scanf("%d",&seguir);
	}while(seguir);
	printf("Fin de ejecucion\n");
	fclose(archivoBinario);
	system("PAUSE");
	return 0;
}

int borrar_contacto(FILE *directorio, int a, int b) {
	/// "a" es el total de contactos, "b" es el contacto a borrar
	int i,ret;
	EntradaDirectorio *entrada;
	///Creacion de arreglo de tamaño a
	if((entrada=(EntradaDirectorio*)malloc(a*sizeof(EntradaDirectorio)))==NULL) {
		printf("Error de almacenamiento.\n");
		return -1;
	}
	///Posicionamiento en inicio de archivo
	ret=fseek(directorio,0L,SEEK_SET);
	if(ret<0) {
		printf("Error al ir al inicio de archivo.\n");
		return -1;
	}
	///Guardamos todas las entradas en el arreglo previamente creado
	for (i=0; !feof(directorio); i++){
    	if (obtener_entrada(directorio,&entrada[i])<0) {
    		break;	
		}
	}
	///Cerramos y volvemos a abrir borrando todo
	fclose(directorio);
	directorio = fopen("directorio.bin", "wb+");
  	if (directorio == NULL){
    	int errAuxiliar;          
    	errAuxiliar = errno;
    	fprintf(stderr, "No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", errAuxiliar, strerror(errAuxiliar));                                            
    	return 0;                                                                   
	}
	///Copiamos todas las entradas menos la "b"
	for(i=0; i<a; i++) {
		if(i!=(b-1)) {
			agrega_entrada(directorio, entrada[i]);
		}
	}
	return 0;
}

int modificar_campo(FILE *directorio, int a, int b) {
	///"a" es el total de contactos y "b" el contacto del que queremos modificar un campo
	int i,ret,campo,campos;
	EntradaDirectorio *entrada;
	///Creamos arreglo para guardar contactos
	if((entrada=(EntradaDirectorio*)malloc(a*sizeof(EntradaDirectorio)))==NULL) {
		printf("Error de almacenamiento.\n");
		return -1;
	}
	///Vamos al inicio de archivo
	ret=fseek(directorio,0L,SEEK_SET);
	if(ret<0) {
		printf("Error al ir al inicio de archivo.\n");
		return -1;
	}
	///Guardamos todas las entradas del directorio
	for (i=0; !feof(directorio); i++){
    	if (obtener_entrada(directorio, &entrada[i])<0){
    		break;
		}
	}
	///Cerramos y volvemos a abrir el directorio
	fclose(directorio);
	directorio = fopen("directorio.bin", "wb+");
  	if (directorio == NULL){
    	int errAuxiliar;          
    	errAuxiliar = errno;
    	fprintf(stderr, "No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", errAuxiliar, strerror(errAuxiliar));                                            
    	return 0;                                                                   
	}
	///Preguntamos que campo quiere editar y modificamos la entrada correspondiente
	printf("\tDigite el campo a modificar:\n");
	printf("\t1) Nombre\n\t2) Apellido Paterno\n\t3) Apellido Materno\n\t4) Edad\n\t5) Altura\n\t6) LADA\n\t7) Tel fijo\n\t8) Celular\n\t9) Lugar de residencia\n\t10) Anotacion\n\t11) Trabajo\n");
	do{
		printf("\tCampo: ");
		scanf("%d",&campo);	
	}while(campo<1 || campo>11);
	switch(campo) {
		case 1:
			printf("\tNuevo nombre: ");
			scanf("%*c%[^\n]",entrada[b-1].nombre);
			break;
		case 2:
			printf("\tNuevo apellido paterno: ");
			scanf("%*c%[^\n]",entrada[b-1].apellidoPaterno);
			break;
		case 3:
			printf("\tNuevo apellido materno: ");
			scanf("%*c%[^\n]",entrada[b-1].apellidoMaterno);
			break;
		case 4:
			printf("\tNueva edad: ");
			scanf("%d",&(entrada[b-1].edad));
			break;
		case 5:
			printf("\tNueva altura (en metros): ");
			scanf("%lg",&(entrada[b-1].altura));
			break;
		case 6:
			printf("\tNueva LADA: ");
			scanf("%u",&(entrada[b-1].lada));
			break;
		case 7:
			printf("\tNuevo telefono fijo: ");
			scanf("%u",&(entrada[b-1].telFijo));
			break;
		case 8:
			printf("\tNuevo telefono celular: ");
			scanf("%u",&(entrada[b-1].telCel));
			break;
		case 9:
			printf("\tNuevo lugar de residencia: ");
			scanf("%*c%[^\n]",entrada[b-1].estado);
			break;
		case 10:
			printf("\tNueva anotacion: ");
			scanf("%*c%[^\n]",entrada[b-1].anotacion);
			break;
		case 11:
			printf("\t\tDigite el campo a modificar: \n");
			printf("\t\t1) Institucion\n\t\t2) Telefono\n");
			do{
				printf("\t\tCampo: ");
				scanf("%d",&campos);
			}while(campos<1 || campos>2);
			switch(campos) {
				case 1:
					printf("\t\tNueva institucion: ");
					scanf("%*c%[^\n]",entrada[b-1].trabajo.institucion);
					break;
				case 2:
					printf("\t\tNuevo telefono institucional: ");
					scanf("%u",&(entrada[b-1].trabajo.tel));
					break;
			}
			break;
			
	}
	///Finalmente copiamos todos los contactos al archivo
	for(i=0; i<a; i++) {
		agrega_entrada(directorio,entrada[i]);
	}
	return 0;
}

int modificar_contacto(FILE *directorio, int a, int b){
	///"a" es el total de contactos y "b" es el contacto a editar
	int i,ret;
	EntradaDirectorio *entrada;
	///Creacion de arreglo para contactos
	if((entrada=(EntradaDirectorio*)malloc(a*sizeof(EntradaDirectorio)))==NULL) {
		printf("Error de almacenamiento.\n");
		return -1;
	}
	///Ir al inicio del archivo
	ret=fseek(directorio,0L,SEEK_SET);
	if(ret<0) {
		printf("Error al ir al inicio de archivo.\n");
		return -1;
	}
	///Copiar todos los contactos al arreglo
	for (i=0; !feof(directorio); i++){
    	if (obtener_entrada(directorio, &entrada[i])<0){
    		break;
		}
	}
	///Cerrar el archivo y borrarlo
	fclose(directorio);
	directorio = fopen("directorio.bin", "wb+");
  	if (directorio == NULL){
    	int errAuxiliar;          
    	errAuxiliar = errno;
    	fprintf(stderr,"No se pudo abrir el archivo \"directorio.bin\" (%d:%s)\n", errAuxiliar, strerror(errAuxiliar));                                            
    	return 0;                                                                   
	}
	///Leemos toda la entrada nuevamente
	entrada[b-1]=leer_contacto();
	///Copiamos todos los contactos del arreglo al archivo
	for(i=0; i<a; i++) {
		agrega_entrada(directorio,entrada[i]);
	}
	return 0;
}

int mostrar_todos_contactos(FILE *directorio) {
	int ret,i;
	EntradaDirectorio entrada;
	///Ir al inicio del archivo
	ret=fseek(directorio,0L,SEEK_SET);
	if(ret<0) {
		printf("Error al ir al inicio de archivo.\n");
		return -1;
	}
	///Recorremos todo el archivo recuperando cada entrada
	for (i=0; !feof(directorio); i++){
    	///Fin del directorio, salimos del for
		if (obtener_entrada(directorio, &entrada)<0){
    		break;
		}
		///Impresion de contacto
    	printf("\n\t\tContacto %d)\n",i+1);
    	printf("\tNombre: %s %s %s\n",entrada.nombre,entrada.apellidoPaterno,entrada.apellidoMaterno);
    	printf("\tEdad: ");
    	if(entrada.edad!=0) {
    		printf("%d\n",entrada.edad);
		} else {
			printf("No registrada.\n");
		}
		printf("\tAltura (en metros): ");
    	if(entrada.altura!=0.0) {
    		printf("%lg\n",entrada.altura);
		} else {
			printf("No registrada.\n");
		}
		printf("\tTelefono fijo: ");                                           
    	if (entrada.telFijo!=0) {
    		printf("(%u) %u\n",entrada.lada,entrada.telFijo);	
		}else{
			printf("Sin numero telefonico.\n");	
		}
		printf("\tTelefono celular: ");                                        
    	if (entrada.telCel!=0){
    		printf("(%u) %u\n",entrada.lada,entrada.telCel);
		}else{
			printf("Sin numero telefonico.\n");  
		}
		printf("\tLugar de residencia: %s\n",entrada.estado);
		printf("\tAnotacion: %s\n",entrada.anotacion);
		printf("\tInstitucion: %s\n",entrada.trabajo.institucion);
		printf("\tTelefono institucional: ");                                        
    	if (entrada.trabajo.tel!=0){
    		printf("(%u) %u\n",entrada.lada,entrada.trabajo.tel);
		}else{
			printf("Sin numero telefonico.\n");  
		}
		printf("\n");
	}
	return 0;
}

int mostrar_contactos(FILE *directorio){
	int ret,i;
	EntradaDirectorio entrada;
	///Ir al inicio del archivo
	ret=fseek(directorio,0L,SEEK_SET);
	if(ret<0) {
		printf("Error al ir al inicio de archivo.\n");
		return -1;
	}
	///Recorremos todo el archivo recuperando cada entrada
	for (i=0; !feof(directorio); i++){
    	///Fin del directorio, salimos del for
		if (obtener_entrada(directorio, &entrada)<0){
    		break;
		}
		///Impresion de contacto SIMPLIFICADO
    	printf("\t%d) %s %s %s\n",i+1,entrada.nombre,entrada.apellidoPaterno,entrada.apellidoMaterno);
	}
	if (i==0) {
		printf("\t\tDirectorio vacio.\n");
	}else{
		printf("\t\tHay %d contactos en el directorio.\n", i);
	}
	return i;
}

int agrega_entrada(FILE *directorio, EntradaDirectorio info) {
	long pos;
	int ret;
	///Guardamos en que posicion estamos
	pos=ftell(directorio);
	///Ir al final del archivo
	ret = fseek(directorio, 0L, SEEK_END);
	if (ret < 0){
    	printf("Error al ir al final del archivo.\n");
    	return -1;
	}
	///Escribir la entrada al final
	ret=fwrite(&info, 1, sizeof(info), directorio);
	if (ret<sizeof(info)){
    	printf("Error al escribir la entrada al final del directorio.\n");
    	return -2;
	}
	///Regresamos a al posicion donde estabamos
	ret=fseek(directorio, pos, SEEK_SET);
	return 0;
}

int mostrar_contacto(FILE *directorio, int contacto) {
	int ret,i;
	EntradaDirectorio entrada;
	///Ir al inicio del archivo
	ret=fseek(directorio,0L,SEEK_SET);
	if(ret<0) {
		printf("Error al ir al inicio de archivo.\n");
		return -1;
	}
	///Recorrer todos los contactos
	for (i=0; !feof(directorio); i++){
		///Salir del for al finalizar contactos
    	if (obtener_entrada(directorio, &entrada)<0){
    		break;
		}
		///Cuando estemos en el contacto deseado
    	if(i+1==contacto) {
    		printf("\n\t\tContacto %d)\n",i+1);
    		printf("\tNombre: %s %s %s\n",entrada.nombre,entrada.apellidoPaterno,entrada.apellidoMaterno);
    		printf("\tEdad: ");
    		if(entrada.edad!=0) {
    			printf("%d\n",entrada.edad);
			} else {
				printf("No registrada.\n");
			}
			printf("\tAltura (en metros): ");
    		if(entrada.altura!=0.0) {
    			printf("%lg\n",entrada.altura);
			} else {
				printf("No registrada.\n");
			}
			printf("\tTelefono fijo: ");                                           
    		if (entrada.telFijo!=0) {
    			printf("(%u) %u\n",entrada.lada,entrada.telFijo);	
			} else {
				printf("Sin numero telefonico.\n");	
			}
			printf("\tTelefono celular: ");                                        
    		if (entrada.telCel!=0){
    			printf("(%u) %u\n",entrada.lada,entrada.telCel);
			} else {
				printf("Sin numero telefonico.\n");  
			}
			printf("\tLugar de residencia: %s\n",entrada.estado);
			printf("\tAnotacion: %s\n",entrada.anotacion);
			printf("\tInstitucion: %s\n",entrada.trabajo.institucion);
			printf("\tTelefono institucional: ");                                        
    		if (entrada.trabajo.tel!=0){
    			printf("(%u) %u\n",entrada.lada,entrada.trabajo.tel);
			}else{
				printf("Sin numero telefonico.\n");  
			}
			printf("\n");
		}
	}
	return 0;
}

EntradaDirectorio leer_contacto(void) {
	int ret;
	EntradaDirectorio entrada;
	printf("\tNombre: ");
	scanf("%*c%[^\n]", entrada.nombre);   
	printf("\tApellido paterno: ");
	scanf("%*c%[^\n]", entrada.apellidoPaterno);
	printf("\tApellido materno: ");
	scanf("%*c%[^\n]", entrada.apellidoMaterno);
	printf("\tEdad: ");
	scanf("%d", &(entrada.edad));
	printf("\tAltura (en metros): ");
	scanf("%lg",&(entrada.altura));
	printf("\tLADA: ");
	scanf("%u", &(entrada.lada));                    
	printf("\tTelefono fijo: ");
	scanf("%u", &(entrada.telFijo));             
	printf("\tTelefono celular: ");
	scanf("%u", &(entrada.telCel));
	printf("\tLugar de residencia: ");
	scanf("%*c%[^\n]",entrada.estado);
	printf("\tAnotacion: ");
	scanf("%*c%[^\n]",entrada.anotacion);
	printf("\tInstitucion afiliada: ");
	scanf("%*c%[^\n]",entrada.trabajo.institucion);
	printf("\tTelefono institucional: ");
	scanf("%u", &(entrada.trabajo.tel));
	return entrada;
}

int obtener_entrada(FILE *directorio, EntradaDirectorio *info) {
	int ret;
	ret = fread(info, 1, sizeof(EntradaDirectorio), directorio);
	if (ret<sizeof(info)){
    	int unError = errno;
    	if (ret == 0) return -2;
    	printf("\nError al leer informacion en el directorio (%d, %d, %s)\n", ret, unError, strerror(unError));
    	return -1;
	}
	return 0;
}
