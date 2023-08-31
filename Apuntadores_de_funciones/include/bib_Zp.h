#ifndef _H_ZP_
#define _H_ZP_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _zp_ {
	int p,n;
}zp;

zp leerzp(int p, FILE *archivo);
int escribirzp(zp a, FILE *archivo);
int simpzp(zp a);
zp sumazp(zp a, zp b);
zp restazp(zp a, zp b);
zp multiplicazp(zp a, zp b);
zp inversazp(zp a);
zp dividezp(zp a, zp b);

#ifdef __cplusplus
}
#endif

#endif
