#ifndef INPUTFUNCS_HPP_INCLUDED
#define INPUTFUNCS_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <sstream>

#include "outputFuncs.hpp"
#include "Env.hpp"

// Enum servant à la lecture char by char de l'input
enum class ExpectChar{Param, EndError, EndFlags, EndFlag, EqualPair, EndPair};
void mainInput(Env &env);
#define _mainInput() mainInput(env)

string basicInput();

#endif // INPUTFUNCS_HPP_INCLUDED
