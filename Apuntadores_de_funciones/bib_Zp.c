#include <stdio.h>
#include <stdlib.h>
#include "bib_Zp.h"

zp leerzp(int p, FILE *archivo){
	zp a;
	a.p=p;
	fscanf(archivo,"%d",&a.n);
	a.n=simpzp(a);
	return a;
}

int escribirzp(zp a, FILE *archivo){
	fprintf(archivo,"%3d",a.n);
	return 0;
}

int simpzp(zp a){
  	///Simplificar un numero sacando modulo p
	a.n=(a.n%a.p+a.p)%a.p;
	return a.n;
}

zp sumazp(zp a, zp b){
	zp res;
	res.p=a.p;
	res.n=a.n+b.n;
	res.n=simpzp(res);
	return res;
}

zp restazp(zp a, zp b){
	zp res;
	res.p=a.p;
	res.n=a.n-b.n;
	res.n=simpzp(res);
	return res;
}

zp multiplicazp(zp a, zp b){
	zp res;
	res.p=a.p;
	res.n=a.n*b.n;
	res.n=simpzp(res);
	return res;
}

zp inversazp(zp d){
	int r,q,s,s0,s1,a,b;
	a=d.n;
	b=d.p;
	s0=0;
	s1=1;
	while((r=a%b)!=0){
		q=a/b;
		a=b;
		b=r;
		s=s0;
		s0=s1-q*s0;
		s1=s;
	}
	d.n=s0;
	d.n=simpzp(d);
	return d;
}

zp dividezp(zp a, zp b){
	zp res;
	res=inversazp(b);
	res=multiplicazp(a,res);
	return res;
}
