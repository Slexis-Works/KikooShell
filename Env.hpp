#ifndef ENV_HPP_INCLUDED
#define ENV_HPP_INCLUDED

#include <iostream>
#include <wininet.h>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "mainStructs.hpp"


//#include "son.hpp"

class Env{ // Environnement, qui passe de fonction en fonction
public:
    Env();
    ~Env();

    // Fonctions utilitaires du KSh
    bool addPath(string &nP);

    // I/O
    // Couleurs t=text b=background
    // s=set (comme défaut aussi) d=default (remet la valeur par défaut)
    void tCol(Flags flags){     SetConsoleTextAttribute(cO, m_bgCol|(flags&15));} // Ou récupérer TextAttribute
    void bCol(Flags flags){     SetConsoleTextAttribute(cO, m_txtCol|(flags&240));}
    void stCol(Flags flags){    m_txtCol=flags&15;
                                SetConsoleTextAttribute(cO, flags&15);}
    void sbCol(Flags flags){    m_bgCol=flags&240;
                                SetConsoleTextAttribute(cO, flags&240);}
    void sCol(Flags flags){     m_txtCol=flags&15;
                                m_bgCol=flags&240;
                                SetConsoleTextAttribute(cO, flags);}
    void Col(Flags flags){      SetConsoleTextAttribute(cO,flags);}
    void dtCol(){   SetConsoleTextAttribute(cO, m_txtCol);} // On devrait pas spécifier ici un BGColor ?
    void dbCol(){   SetConsoleTextAttribute(cO, m_bgCol);}
    void dCol(){    SetConsoleTextAttribute(cO,m_txtCol|m_bgCol);}

    void darkenTxt(){m_txtCol&=~FOREGROUND_INTENSITY;dCol();}
    void enlightTxt(){m_txtCol|=FOREGROUND_INTENSITY;dCol();}

    void err(string msg){Col(FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE); cout << msg << endl; dCol();}

    // Son
    bool play(string path, sf::Uint8 flags=0); // 8 flags, flags étendus et privés pour say
    void setVoice(string nV);
    bool say(const char text[], sf::Uint16 flags=0); // FIXME Ne supporte pas les caractères spéciaux. Voxygen renvoie du vide.
    bool say(const char text[], string voice, sf::Uint16 flags=0);
    bool sayRand(vector<string> possib, sf::Uint16 flags=0);
    bool sayRand(vector<string> possib, string voice, sf::Uint16 flags=0);
    //bool say([])
    void cleanStop();


// Variables publiques pour simplifier l'accès
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

private:
    // I/O
    unsigned char m_txtCol;
    unsigned char m_bgCol;

    // Sound
    string m_voice;
    vector< Track >  m_sons;
    sf::Int32 m_nbSnd;

};


#endif // ENV_HPP_INCLUDED
