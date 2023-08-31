#ifndef _H_ZP_
#define _H_ZP_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _zp_ {
	int p,n;	
}zp;

zp leerzp(int p, FILE *archivo);
void escribirzp(zp a, FILE *archivo);
int simpzp(zp a);
zp sumazp(zp a, zp b);
zp restazp(zp a, zp b);
zp productozp(zp a, zp b);
zp inversazp(zp a);
zp divisionzp(zp a, zp b);
zp creazp(int n, int p);

#ifdef __cplusplus
}
#endif

#endif
