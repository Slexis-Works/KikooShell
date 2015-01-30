#ifndef MAINSTRUCTS_HPP_INCLUDED
#define MAINSTRUCTS_HPP_INCLUDED

#include <windows.h>
#include <string>
#include <vector>

using namespace std;

struct Env{ // Environnement, qui passe de fonction en fonction
    HANDLE cO;
    HANDLE cI;

    string cmd; // Dernière commande tapée...
    vector<string> args; // Et ses params
    string userName;
    string cwd;
    unsigned char dirt;
    unsigned char maxDirt;
    unsigned char txtCol;
};



#endif // MAINSTRUCTS_HPP_INCLUDED
