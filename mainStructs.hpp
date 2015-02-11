#ifndef MAINSTRUCTS_HPP_INCLUDED
#define MAINSTRUCTS_HPP_INCLUDED

#include <windows.h>
#include <string>
#include <vector>

using namespace std;

enum class HelpNext{None, Haylp, Fomayday, Ausekoure};

struct Env{ // Environnement, qui passe de fonction en fonction
    // Nécessaires à l'interface
    HANDLE cO;
    HANDLE cI;

    // Nécessaires au fonctionnement interne
    string cmd; // Dernière commande tapée...
    vector<string> args; // Et ses params

    HelpNext helpnxt;

    // Paramètres utilisateurs
    string userName;
    string cwd;
    unsigned char dirt;
    unsigned char maxDirt;
    unsigned char txtCol;
    unsigned char bgCol;
    string defVoice;
};



#endif // MAINSTRUCTS_HPP_INCLUDED
