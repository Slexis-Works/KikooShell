#ifndef INPUTFUNCS_HPP_INCLUDED
#define INPUTFUNCS_HPP_INCLUDED

#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>

#include "outputFuncs.hpp"
#include "mainStructs.hpp"

void mainInput(Env &env);
#define _mainInput() mainInput(env)

string basicInput();

#endif // INPUTFUNCS_HPP_INCLUDED
