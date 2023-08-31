#ifndef _H_GAUSSIANOS_
#define _H_GAUSSIANOS_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _G_ {
    int a,b;
}G;

void escribeG(G x, FILE *archivo);
G leerG(FILE *archivo);
G creaG(int real, int ima);
G sumaG(G x, G y);
G restaG(G x, G y);
G multiplicaG(G x, G y);
G conjugadoG(G x);
int norma(G x);

#ifdef __cplusplus
}
#endif

#endif
