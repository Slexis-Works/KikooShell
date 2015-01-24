#ifndef MAINSTRUCTS_HPP_INCLUDED
#define MAINSTRUCTS_HPP_INCLUDED

#include <windows.h>
#include <string>
#include <vector>

using namespace std;

struct Env{ // Environnement, qui passe de fonction en fonction
    string userName;
    string cwd;
    string cmd; // Derni�re commande tap�e...
    vector<string> args; // Et ses params
    HANDLE cO;
    HANDLE cI;
};



#endif // MAINSTRUCTS_HPP_INCLUDED
