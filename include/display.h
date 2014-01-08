#ifndef _H_DISPLAY
#define _H_DISPLAY

#include <windows.h>

enum color_t { NEGRO, AZUL, VERDE, TURQUESA, ROJO, MORADO, AMARILLO, GRIS_C, GRIS, AZUL_C, VERDE_C, TURQUESA_C, ROJO_C, MORADO_C, AMARILLO_C, BLANCO };
class Display
{
  public:
    Display(){};
    static void cambiar(color_t texto = BLANCO, color_t fondo = NEGRO)
	{
	  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fondo*16 + texto);
	}
};

#endif

