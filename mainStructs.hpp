#ifndef MAINSTRUCTS_HPP_INCLUDED
#define MAINSTRUCTS_HPP_INCLUDED

#include <windows.h>
#include <string>
#include <vector>

using namespace std;

enum class HelpNext{None, Haylp, Fomayday, Ausekoure};

struct Env{ // Environnement, qui passe de fonction en fonction
    // N�cessaires � l'interface
    HANDLE cO;
    HANDLE cI;

    // N�cessaires au fonctionnement interne
    string cmd; // Derni�re commande tap�e...
    vector<string> args; // Et ses params

    HelpNext helpnxt;

    // Param�tres utilisateurs
    string userName;
    string cwd;
    unsigned char dirt;
    unsigned char maxDirt;
    unsigned char txtCol;
    unsigned char bgCol;
    string defVoice;
};



#endif // MAINSTRUCTS_HPP_INCLUDED
