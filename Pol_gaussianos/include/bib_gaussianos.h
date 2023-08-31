#ifndef _H_POLREAL_
#define _H_POLREAL_

#ifdef __cplusplus
extern "C" {
#endif

///Gomplejos a+bi con a,b enteros
typedef struct _G_ {
    int a,b;
}G;

void escribeG(G x, FILE *archivo);
int es_G_cero(G num);
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
