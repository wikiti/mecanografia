#ifndef _H_DISPLAY
#define _H_DISPLAY

#include <sstream>
#include <iostream>
#include <iomanip>

#ifdef _WIN32
  #include <windows.h>
  #include <stdio.h>
  #include <conio.h>
#endif

namespace DISPLAY
{
  #ifdef _WIN32
  enum color_t { NINGUNO = -1, NEGRO, AZUL, VERDE, TURQUESA, ROJO, MORADO, AMARILLO, GRIS_C, GRIS, AZUL_C, VERDE_C, TURQUESA_C, ROJO_C, MORADO_C, AMARILLO_C, BLANCO };
  #else
  #ifdef __linux__
  enum color_t { NINGUNO = 0, NEGRO, AZUL, VERDE, TURQUESA, ROJO, MORADO, AMARILLO, GRIS_C, GRIS, AZUL_C, VERDE_C, TURQUESA_C, ROJO_C, MORADO_C, AMARILLO_C, BLANCO };
  #endif
  #endif

  class Display
  {
    public:
      Display(){};
      static const char* cambiar(color_t texto = BLANCO, color_t fondo = NEGRO)
      {
#ifdef _WIN32
        if(texto < 0) texto = BLANCO;
        if(fondo < 0) fondo = NEGRO;
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fondo*16 + texto);
        return "";
#else
#ifdef __linux__
        std::stringstream s;
        s << "\033[";
        if (!texto && !fondo)
          s << "0";
          
        if (texto)
        {
          s << 29 + texto;
          if (fondo)
            s << ";";
        }
        if (fondo)
          s << 39 + fondo;

        s << "m";
        
        // cout?
        
        return s.str().c_str();
#endif
#endif
      }
      
      static const char* gotoxy(unsigned int column, unsigned int line)
      {
#ifdef _WIN32
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
  
        return "";
#else
#ifdef __linux__

#endif
#endif
      }
      
      static const char* clear()
      {
#ifdef _WIN32
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        if (hStdOut == INVALID_HANDLE_VALUE) return "";

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return "";
        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(
          hStdOut,
          (TCHAR) ' ',
          cellCount,
          homeCoords,
          &count
          )) return "";

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
          hStdOut,
          csbi.wAttributes,
          cellCount,
          homeCoords,
          &count
          )) return "";

        /* Move the cursor home */
        SetConsoleCursorPosition( hStdOut, homeCoords );
        return "";
#else
#ifdef __linux__

#endif
#endif
      }
  };
}

#endif

