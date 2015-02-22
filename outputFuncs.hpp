#ifndef OUTPUTFUNCS_HPP_INCLUDED
#define OUTPUTFUNCS_HPP_INCLUDED

#include <windows.h>
#include <iostream>

#include "Env.hpp"

#define setCCol(flags) SetConsoleTextAttribute(env.cO, flags)

void dispHelp(Env &env);

#endif // OUTPUTFUNCS_HPP_INCLUDED
