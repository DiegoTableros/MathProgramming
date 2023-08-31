#ifndef _H_RACIONALES_
#define _H_RACIONALES_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Q_{
    int p,q;
}Q;

int mcd(int a, int b);
Q simplificaQ(Q a);
void escribeQ(Q a, FILE *archivo);
Q leerQ(FILE *archivo);
Q creaQ(int num, int den);
Q sumaQ(Q a, Q b);
Q restaQ(Q a, Q b);
Q multiplicaQ(Q a, Q b);
Q divideQ(Q a, Q b);

#ifdef __cplusplus
}
#endif

#endif
