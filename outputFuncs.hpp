#ifndef OUTPUTFUNCS_HPP_INCLUDED
#define OUTPUTFUNCS_HPP_INCLUDED

#include <windows.h>
#include <iostream>

#include "Env.hpp"

using namespace std;

// Contrôles de la sortie
#define setCCol(flags) SetConsoleTextAttribute(env.cO, flags)

void loc(unsigned short x, unsigned short y);
void drawVLine(unsigned short x, unsigned short y, unsigned short h, char c);

// Autres
void dispHelp(Env &env);

#endif // OUTPUTFUNCS_HPP_INCLUDED
