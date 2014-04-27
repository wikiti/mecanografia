/*
 * main.cpp
 *
 *  Created on: 23/05/2013
 *      Author: Dani
 */

#include <iostream>
#include <string>
#include <fstream>

#include <time.h>
#include <windows.h>
#include <conio.h>

#include "display.h"

using namespace DISPLAY;
using namespace std;

enum modo_tipeado {normal = 0, hardcore, repalabra};

void leer(string& texto)
{
  getline(cin, texto, '#');
  Display::gotoxy(0,0);

  cout << texto << " " << endl;
}

modo_tipeado elegir_modo(int argc, char* argv[])
{
  if(argc == 2)
  {
    string arg(argv[1]);
    if(arg == "hardcore")
      return hardcore;
    else if(arg == "repalabra")
      return repalabra;
  }
  
  return normal;
}

int main(int argc, char* argv[])
{
  Display::clear();
  Display::cambiar(BLANCO);
  cout << " Introduzca el texto que desea practicar a" << char(164) << "adiendo un \'#\' al final." << endl ;
  cout << " Posteriormente, escriba su texto hasta completarlo." << endl << endl;
  
  Display::cambiar(GRIS_C);
  string texto;
  leer(texto);

  Display::clear();
  Display::cambiar(GRIS_C);
  Display::gotoxy(0,0);
  cout << texto;
  
  Display::cambiar(VERDE_C);
  Display::gotoxy(0,0);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
  
  modo_tipeado tipeado = elegir_modo(argc, argv);
  unsigned int errores = 0;
  unsigned int i = 0;
  
  clock_t tiempo_inicial = clock();
  unsigned char ch = 'a';
  
  while(i < texto.length() )
  {
    ch = getch();
    if(ch == char(3)) break;

    if(ch == '\r' && texto[i] == '\n')
    {
      cout << endl;
      i++;
    }
    else if(ch == (unsigned char)texto[i])
    {
      cout << texto[i];
      i++;
    }
    else if(tipeado == hardcore)
    {
      Display::cambiar(GRIS_C);
      Display::gotoxy(0,0);
      cout << texto << endl;
      Display::gotoxy(0,0);
      Display::cambiar(VERDE_C);
      i = 0;
      
      errores++;
    }
    else if(tipeado == repalabra)
    {
      errores++; 
      if(texto[i] == ' ' or texto[i] == '\n')
        continue;
      
      for( ; i > 0 and (texto[i] != ' ' and texto[i] != '\n'); i--);
      if(i > 0) i++; // Colocarse delante del espacio
      
      Display::cambiar(GRIS_C);
      Display::gotoxy(0,0);
      cout << texto << endl;
      Display::gotoxy(0,0);
      Display::cambiar(VERDE_C);
      for(unsigned int j = 0; j < i and i != 0; j++) cout << texto[j];
    }
    else 
    {
      errores++;
    }
  }
  
  Display::clear();

  Display::gotoxy(0,0);
  Display::cambiar(VERDE_C);
  for(unsigned int j = 0; j < texto.length(); j++)
  {
    if(j >= i) Display::cambiar(GRIS_C);
    cout << texto[j];
  }
  
  Display::cambiar(BLANCO);
  cout << endl << endl << "  -- Estad\241sticas --" << endl << endl;
  Display::cambiar(GRIS_C);
  
  cout << " Caracteres completados:\t" << i << "/" << texto.length() << " caracteres" << endl;
  cout << " N\243mero de errores:\t\t" << errores << ((errores == 1)? " error " : " errores") << endl;
  
  cout << " Tiempo empleado:\t\t" << ((float)clock()-tiempo_inicial)/CLOCKS_PER_SEC << "s" << endl;
  cout << " Tiempo medio por tecla:\t" << ((float)clock()-tiempo_inicial)/CLOCKS_PER_SEC/texto.length() << "s" << endl << endl;

  system("pause");
}

