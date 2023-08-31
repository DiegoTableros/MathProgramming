#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define crea_arreglo(tam) (H*)malloc((tam+1)*sizeof(H))
#define EPS 1e-6

///Cuaterniones: a+bi+cj+dk con a,b,c,d reales
///Se representan con "H"
typedef struct _H_ {
    double a,b,c,d;
}H;

H leerH(void);
int es_H_cero(H x);
H creaH(double A, double B, double C, double D);
void escribeH(H x);
H sumaH(H x, H y);
H restaH(H x, H y);
H multiplicaH(H x, H y);
H conjugadoH(H x);
double normaH(H x);
H inversoH(H x);
H divideH(H x, H y);

typedef struct _Px_{
	int g;
	H *c;
}Px;

Px leer_polinomio();
void imprime_polinomio(Px pol);
Px copia(Px a);
Px copia_neg(Px a);
int libera(Px *a);
int es_cero(Px a);
Px suma_polinomio(Px a, Px b);
Px resta_polinomio(Px a, Px b);
Px multiplica_polinomio(Px a, Px b);
Px multi_monomio(Px a, H mon, int gradMon);
Px divide_polinomio(Px a, Px b, Px *r);
Px MCD(Px a, Px b);
Px integral(Px pol);
Px derivada(Px pol);
H evaluacion(Px pol, H num);

int main(int argc, char *argv[]) {
	Px res,a,b,q,r={c:NULL, g:-1};
	H n;
	printf("Polinomios con coeficientes cuaterniones.\n\n");	
	a=leer_polinomio();
	printf("\n");
	b=leer_polinomio();
	printf("\n");
	printf("Ingrese un numero cuaternion para evaluacion: ");
	n=leerH();
	printf("\n");
	
	printf("Los polinomios ingresados son:");
	printf("\nA(x) = ");
	imprime_polinomio(a);
	printf("\nB(x) = ");
	imprime_polinomio(b);
	printf("\n\n");
	
	printf("Evaluaciones para A(x) con x="); escribeH(n); printf(":\n");
	printf("A(x)= "); escribeH(evaluacion(a,n)); printf("\n");
	res=derivada(a);
	printf("Derivada(A)(x)= "); escribeH(evaluacion(res,n)); printf("\n");
	libera(&res);
	res=integral(a);
	printf("Integral(A)(x)= "); escribeH(evaluacion(res,n)); printf("\n");
	libera(&res);
	printf("\n");
	
	printf("Evaluaciones para B(x) con x="); escribeH(n); printf(":\n");
	printf("B(x)= "); escribeH(evaluacion(b,n)); printf("\n");
	res=derivada(b);
	printf("Derivada(B)(x)= "); escribeH(evaluacion(res,n)); printf("\n");
	libera(&res);
	res=integral(b);
	printf("Integral(B)(x)= "); escribeH(evaluacion(res,n)); printf("\n");
	libera(&res);
	printf("\n");
	
	printf("Suma A+B :\n");
	res=suma_polinomio(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	printf("Resta A-B :\n");
	res=resta_polinomio(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	printf("Producto A*B :\n");
	res=multiplica_polinomio(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	printf("División A/B :\n");
	q=divide_polinomio(a, b, &r);
	if(a.g<b.g) {
		printf("No se puede efectuar la división.\n");
	}
	printf("Cociente = ");
	imprime_polinomio(q);
	printf("\nResiduo = ");
	imprime_polinomio(r);
	printf("\n\n");
	libera(&r);
	libera(&q);
	
	printf("MCD(A,B): \n");
	res=MCD(a,b);
	imprime_polinomio(res);
	libera(&res);
	printf("\n\n");
	
	libera(&a);
	libera(&b);
	system("PAUSE");
	return 0;
}

Px leer_polinomio() {
	Px ret;
	int i;
	printf("Digite el grado del polinomio: ");
	scanf("%d", &(ret.g));
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g = -1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
    	printf("Digite el coeficiente de x^%d:\n", i);
    	ret.c[i]=leerH();
	}
	return ret;
}

void imprime_polinomio(Px pol) {
	int i;
	if(pol.g<0){
    	printf("0");
    	return;
  	}
	for(i=pol.g; i>=2; i--) {
		if(!es_H_cero(pol.c[i])){
			escribeH(pol.c[i]);
			printf(" x^%d ", i);
		}
	}
  	if(pol.g>=1 && !es_H_cero(pol.c[1])){
  		escribeH(pol.c[1]);
		printf(" x ");
	}
	if(pol.g>=0 && !es_H_cero(pol.c[0])) {
		escribeH(pol.c[0]);
	}
}

Px copia(Px a) {
	Px ret;
	int i;
	ret.g = a.g;
	if (ret.g<0){
    	ret.c=NULL;
		return ret;
	}
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for(i=0; i<=ret.g; i++) {
		ret.c[i]=a.c[i];
	}
	return ret;
}

Px copia_neg(Px a) {
	Px ret;
	int i;
	ret.g = a.g;
	if (ret.g<0){
    	ret.c=NULL;
    	return ret;
	}
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for(i=0; i<=ret.g; i++) {
		ret.c[i]=creaH(-a.c[i].a,-a.c[i].b,-a.c[i].c,-a.c[i].d);
	}
	return ret;
}

int libera(Px *a) {
	if(a->c!=NULL) {
		free(a->c);
	}
	a->g=-1;
	a->c=NULL;
	return 0;	
}

int es_cero(Px a) {
	return a.g<0;
}

Px suma_polinomio(Px a, Px b) {
	Px ret;
	int i, min;
	if (a.g<0){
    	return copia(b);
	}
	if (b.g<0){
    	return copia(a);
	}
	min=(a.g<b.g?a.g:b.g);
	ret.g=(min==a.g?b.g:a.g);
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
		ret.g=-1;
    	return ret;
	}
	for (i=0; i<=min; i++) {
		ret.c[i]=sumaH(a.c[i],b.c[i]);	
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=b.c[i];	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];	
		}
	}
	while(ret.g>=0 && es_H_cero(ret.c[ret.g])) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Px resta_polinomio(Px a, Px b) {
	Px ret;
	int i, min;
	if (a.g<0){
    	return copia(b);
	}
	if (b.g<0){
    	return copia(a);
	}
	min=(a.g<b.g?a.g:b.g);
	ret.g=(min==a.g?b.g:a.g);
	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
		ret.g=-1;
    	return ret;
	}
	for (i=0; i<=min; i++) {
		ret.c[i]=restaH(a.c[i],b.c[i]);
	}
	if (a.g==min){
    	for(; i<=ret.g; i++){
    		ret.c[i]=creaH(-b.c[i].a,-b.c[i].b,-b.c[i].c,-b.c[i].d);	
		}
	} else {
		for(; i<=ret.g; i++){
			ret.c[i]=a.c[i];
		}
	}
	while(ret.g>=0 && es_H_cero(ret.c[ret.g])) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Px multiplica_polinomio(Px a, Px b) {
	int i, j;
	Px ret;
	ret.g=a.g+b.g;
	if((ret.c=crea_arreglo(ret.g))==NULL){
    printf("Error de almacenamiento.\n");
		ret.g = -1;
		return ret;
	}
	for (i=0; i<=ret.g; i++) {
		ret.c[i]=creaH(0.0,0.0,0.0,0.0);
	}
	for (i=0; i<=a.g; i++) {
    	for(j=0; j<=b.g; j++) {
      		ret.c[i+j]=sumaH(ret.c[i+j],multiplicaH(a.c[i],b.c[j]));
		}
	}
	while(ret.g>=0 && es_H_cero(ret.c[ret.g])) {
		ret.g--;
	}
	if (ret.g<0){
		free(ret.c);
		ret.c = NULL;
	}
	return ret;
}

Px multi_monomio(Px a, H mon, int gradMon) {
	int i;
	Px ret;
	ret.g=a.g+gradMon;
  	if((ret.c=crea_arreglo(ret.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	ret.g=-1;
    	return ret;
	}
	for (i=0; i<=ret.g; i++){
		ret.c[i]=creaH(0.0,0.0,0.0,0.0);
	}
	for(i=0; i<=a.g; i++) {
		ret.c[i+gradMon]=multiplicaH(mon,a.c[i]);
	}
	return ret;
}

Px divide_polinomio(Px a, Px b, Px *r) {
	Px q={g:-1,c:NULL};
	Px aux={g:-1,c:NULL};
	Px a_aux={g:-1,c:NULL};
	int grad, i;
	a_aux=copia(a);
  	a=a_aux;
  	if(a.g<b.g){
    	q.g=-1;
    	q.c=NULL;
    	*r=copia(a);
		return q;
	}
	q.g=a.g-b.g;
	if((q.c=crea_arreglo(q.g))==NULL){
    	printf("Error de almacenamiento.\n");
    	q.g = -1;
    	return q;
	}
	for (i=0; i<=q.g; i++){
		q.c[i]=creaH(0.0,0.0,0.0,0.0);
	}
	do{
    	grad=a.g-b.g;
    	q.c[grad]=divideH(a.c[a.g],b.c[b.g]);
		aux=multi_monomio(b, q.c[grad], grad);
		a_aux=resta_polinomio(a,aux);
		libera(&a);
		libera(&aux);
		a=a_aux;
		libera(r);
		*r=copia(a);
	}while(!es_cero(*r) && (r->g>=b.g));
	return q;
}

Px MCD(Px a, Px b) {
	Px aux1,aux2,residuo={g:-1,c:NULL};
    if(es_cero(b)) {
        return copia(a);
	}
	if(es_cero(a)){
		return copia(b);
	}
	aux1=copia(a);
	aux2=copia(b);
	divide_polinomio(aux1,aux2,&residuo);
	while(!es_cero(residuo)) {
		libera(&aux1);
		aux1=copia(aux2);
		libera(&aux2);
		aux2=copia(residuo);
		libera(&residuo);
		divide_polinomio(aux1,aux2,&residuo);
	}
	return aux2;
}

Px integral(Px pol){
	Px ret;
	int i;
	if(pol.g<0) {
		ret.g=-1;
		ret.c=NULL;
		return ret;
	}
	ret.g=pol.g+1;
	if((ret.c=crea_arreglo(ret.g))==NULL) {
		printf("Error de almacenamiento.\n");
		ret.g=-1;
		return ret;
	}
	ret.c[0]=creaH(0.0,0.0,0.0,0.0);
	for(i=0; i<=pol.g; i++) {
		ret.c[i+1]=divideH(pol.c[i],creaH(i+1,0.0,0.0,0.0));
	}
	return ret;
}

Px derivada(Px pol){
	Px ret;
	int i;
	if(pol.g<=0) {
		ret.g=-1;
		ret.c=NULL;
		return ret;
	}
	ret.g=pol.g-1;
	if((ret.c=crea_arreglo(ret.g))==NULL) {
		printf("Error de almacenamiento.\n");
		ret.g=-1;
		return ret;
	}
	for(i=1; i<=pol.g; i++) {
		ret.c[i-1]=multiplicaH(pol.c[i],creaH(i,0.0,0.0,0.0));
	}
	return ret;
}

H evaluacion(Px pol, H num) {
    H res=creaH(0.0,0.0,0.0,0.0);
    int i;
    for(i=pol.g; i>0; i--) {
        res=multiplicaH(num,sumaH(pol.c[i],res));
    }
    res=sumaH(res,pol.c[0]);
    return res;
}

H leerH(void){
    H num;
    printf("Digite a,b,c y d: ");
    scanf("%lg%lg%lg%lg",&num.a,&num.b,&num.c,&num.d);
    return num;
}

int es_H_cero(H x) {
	return (x.a==0.0 && x.b==0.0 && x.c==0.0 && x.d==0.0);
}

H creaH(double A, double B, double C, double D) {
	H ret;
  	ret.a=A; ret.b=B; ret.c=C; ret.d=D;
  	return ret;
}

void escribeH(H x){
    ///Parte a
    if(x.a!=0.0) {
    	if(x.a>0.0) {
    		printf("+");
		}
        printf("%lg ",x.a);
    }
    ///Parte b
    if(x.b!=0.0) {
        if(x.b>0.0) {
            printf("+");
        }
        if(x.b!=1.0 && x.b!=-1.0) {
            printf("%lg",x.b);
        }
        if(x.b==-1.0) {
            printf("-");
        }
        printf("i ");
    }
    ///Parte c
    if(x.c!=0.0) {
        if(x.c>0.0) {
            printf("+");
        }
        if(x.c!=1.0 && x.c!=-1.0) {
            printf("%lg",x.c);
        }
        if(x.c==-1.0) {
            printf("-");
        }
        printf("j ");
    }
    ///Parte d
    if(x.d!=0.0) {
        if(x.d>0.0) {
            printf("+");
        }
        if(x.d!=1.0 && x.d!=-1.0) {
            printf("%lg",x.d);
        }
        if(x.d==-1.0) {
            printf("-");
        }
        printf("k");
    }
}

H sumaH(H x, H y){
    H res;
    res.a=x.a+y.a;
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
	res.b=x.b+y.b;
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	res.c=x.c+y.c;
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    res.d=x.d+y.d;
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
    return res;
}

H restaH(H x, H y){
    H res;
    res.a=x.a-y.a;
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
	res.b=x.b-y.b;
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	res.c=x.c-y.c;
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    res.d=x.d-y.d;
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
    return res;
}

H multiplicaH(H x, H y){
    H res;
    res.a=x.a*y.a-x.b*y.b-x.c*y.c-x.d*y.d;
    res.b=x.a*y.b+x.b*y.a+x.c*y.d-x.d*y.c;
    res.c=x.a*y.c-x.b*y.d+x.c*y.a+x.d*y.b;
    res.d=x.a*y.d+x.b*y.c-x.c*y.b+x.d*y.a;
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
    return res;
}

H conjugadoH(H x){
    x.b=-x.b;
    x.c=-x.c;
    x.d=-x.d;
    return x;
}

double normaH(H x){
    return sqrt(x.a*x.a+x.b*x.b+x.c*x.c+x.d*x.d);
}

H inversoH(H x){
    H res;
    res=conjugadoH(x);
    double norm2=normaH(x);
    norm2*=norm2;
    if(norm2==0.0) {
    	return x;
	}
    res.a/=norm2;
    res.b/=norm2;
    res.c/=norm2;
    res.d/=norm2;
    ///Epsilon
    if(-EPS<=res.a && res.a<=EPS){
    	res.a=0.0;
	}
    if(-EPS<=res.b && res.b<=EPS){
    	res.b=0.0;
	}
	if(-EPS<=res.c && res.c<=EPS){
    	res.c=0.0;
	}
    if(-EPS<=res.d && res.d<=EPS){
    	res.d=0.0;
	}
    return res;
}

H divideH(H x, H y){
    H res;
    res=multiplicaH(x,inversoH(y));
    return res;
}
