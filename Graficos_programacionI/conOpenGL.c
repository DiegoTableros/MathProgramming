#include <windows.h>
#include <gl/gl.h>

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

#include "logo.h"
#include "koch.h"
#include "dragon.h"
#include "hilbert.h"
#include "sierpinsky.h"
#include "abelson.h"
#include "gosper.h"
#include "mandelbrot.h"
#include "polygon.h"
#include "malmberg.h"
#include "triangles.h"
#include "hooked.h"
#define escX 0.125
#define escY 0.125
#define MX 0.0
#define MY 0.0

typedef void (*DibujaSegmentos)(double, double, double, double);
extern DibujaSegmentos dibujaSegmento;
void segmento(double, double, double, double);
DibujaSegmentos dibujaSegmento=segmento;

int WINAPI WinMain (HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow){
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "graficos";
    RegisterClass (&wc);

    misFractales miFractal;
    LOGO miTortuga;
    char *miParametro;
    if (iCmdShow>1) miParametro = lpCmdLine;
    if (strlen(lpCmdLine)==0) miParametro="hooked";
    
    asignaModoDibujarSegmento(segmento, &miTortuga);
   	
	if(strncmp(miParametro,"dragon", 6)==0) {
    	///a) ABELSON'S DRAGON. NivelRecur=11
      	iniciaDragon(11, 0.225, 2.0, -3.0, &miTortuga);
		miFractal=dibujaDragon;
	}else if(strncmp(miParametro,"hilbert", 7)==0) {
    	///b) HILBERT'S CURVE. NivelRecur=5. Paridad=1.0
      	iniciaHilbert(5, 0.45, 1.0, -7.0, -6.5, &miTortuga);
		miFractal=dibujaHilbert;
	}else if(strncmp(miParametro,"sierpinsky", 10)==0) {
    	///c) SIERPINSKY'S CURVE. NivelRecur=4
      	iniciaSierpinsky(10, 0.45, -7.0, 7.0, &miTortuga);
		miFractal=dibujaSierpinsky;
	}else if(strncmp(miParametro,"abelson", 7)==0) {
    	///d) ABELSON'S CURVE. NivelRecur=10
      	iniciaAbelson(10, 0.25, -4.0, 4.0, &miTortuga);
		miFractal=dibujaAbelson;
	}else if(strncmp(miParametro, "koch", 4)==0){
    	///e) KOCH'S SNOWFLAKE. NivelRecur=6
        iniciaKoch(6, 12.0, -6.0, 4.0, &miTortuga);
        miFractal = dibujaKoch;
    }else if(strncmp(miParametro, "gosper", 6)==0){
    	///f) GOSPER'S FLOWSNAKE. NivelRecur=4
        iniciaGosper(4, 12.0, -7.0, 2.0, &miTortuga);
        miFractal=dibujaGosper;
    } else if(strncmp(miParametro, "mandelbrot", 10)==0){
    	///g) MANDELBROT'S SQUARE SNOWFLAKE. NivelRecur=3
        iniciaMandelbrot(3, 8.0, -4.0, 4.0, &miTortuga);
        miFractal=dibujaMandelbrot;
    } else if(strncmp(miParametro, "polygon", 7)==0){
    	/*h) ABELSON'S CORNERED POLYGONS. Parámetros:
			Cuadrados (5.0, 90.0, 0.5, -2.5, 2.5, &miTortuga)
			Estrellado (5.0, 144.0, 0.5, -2.5, 0.0, &miTortuga)
			Triangular (5.0, 120.0, 0.5, -2.5, 2.5, &miTortuga)
			Hexagonal (3.0, 60.0, 0.5, -1.5, 2.5, &miTortuga)
      	*/
        iniciaPolygon(3.0, 60.0, 0.5, -1.5, 2.5, &miTortuga);
        miFractal=dibujaPolygon;
    } else if(strncmp(miParametro, "weave", 8)==0){
    	///i) MALMBERG'S WEAVE. NivelRecur=2. Parametro=-1.0
        iniciaMalmberg(2,15.0,-1.0,-7.5,-0.75, &miTortuga);
        miFractal=dibujaMalmberg;
    }else if(strncmp(miParametro, "triangles", 9)==0){
    	///j) ABELSON'S NESTED TRIANGLES. NivelRecur=7
        iniciaTriangles(7,15.0,-7.5,6.0, &miTortuga);
        miFractal=dibujaTriangles;
    }else if(strncmp(miParametro, "hooked", 6)==0){
    	///k) MANDELBROT'S HOOKED SNOWFLAKE. NivelRecur=3
        iniciaHooked(3, 14.0, -7.5, -4.0, &miTortuga);
        miFractal=dibujaHooked;
    }else if(strncmp(miParametro, "maze", 4)==0){
    	///l) MALMBERG'S MAZE. NivelRecur=2
        iniciaMalmberg(2, 12.0, 1.0, -7.5, -1.0, &miTortuga);
        miFractal=dibujaMalmberg;
    }
	hWnd=CreateWindow("graficos",miParametro,WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,0, 0, 2*256, 2*256,NULL, NULL, hInstance, NULL);
    EnableOpenGL (hWnd, &hDC, &hRC);
	while (!bQuit){
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)){
            if (msg.message == WM_QUIT){
                bQuit = TRUE;
            }else{
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }else{
            /* OpenGL animation code goes here */
            glClearColor (1.0f, 1.0f, 1.0f, 0.5f);
            glClear (GL_COLOR_BUFFER_BIT);
            glPushMatrix();
            glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glColor3d(0.0, 0.0, 0.0);
            miFractal();
			glPopMatrix ();
            SwapBuffers (hDC);
			///ROTACION
            //theta += 1.0f;
            Sleep(1);
        }
    }
    DisableOpenGL (hWnd, hDC, hRC);
	DestroyWindow (hWnd);
	return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam) {
    switch (message){
    	case WM_CREATE:
        	return 0;
    	case WM_CLOSE:
        	PostQuitMessage (0);
        	return 0;
    	case WM_DESTROY:
        	return 0;
    	case WM_KEYDOWN:
        	switch (wParam){
        		case VK_ESCAPE:
            	PostQuitMessage(0);
            	return 0;
        	}
        	return 0;
		default:
        	return DefWindowProc (hWnd, message, wParam, lParam);
    }
}

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC){
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
	*hDC = GetDC (hWnd);
	ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
}

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC){
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

void segmento(double x1, double y1, double x2, double y2){
	glBegin (GL_LINES);
    glVertex2d (MX+escX*x1, MY+escY*y1);
    glVertex2d (MX+escX*x2, MY+escY*y2);
	glEnd();
}

