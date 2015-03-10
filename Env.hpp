#ifndef ENV_HPP_INCLUDED
#define ENV_HPP_INCLUDED

#include <iostream>
#include <wininet.h>
#include <vector>
#include <string>
#include <regex>
#include <random>
#include <time.h>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <curl/curl.h>

#include "mainStructs.hpp"
#include "save.hpp"
#include "curlBkps.hpp"

//#include "son.hpp"

class Env{ // Environnement, qui passe de fonction en fonction
public:
    Env();
    ~Env();

    // Fonctions utilitaires du KSh
    // CWD
    bool addPath(string &nP, bool isFile=0);
    string getWinPath();
    bool getWinPath(string &nP, bool isFile=0);
    // CMD
    void resetFlags(){m_flags1.clear();m_flagsWords.clear();args.clear();}
    bool addFlag1(char nF){
        string test;
        test+=nF;
        if(hasFlag(nF)){
            warn("Koman ke ta déjah mee leu char " + test);
            return false;
        }else{
            m_flags1+=nF;
            //info("Flhag ajoo t : " + test);
            return true;
        }
    }
    bool addFlag(string nF){
        if(hasFlag(nF)){
            err("Koman ke ta déjah mee " + nF);
            return false;
        }else{
            //info("Hargumam troo v : " + nF);
            m_flagsWords.push_back(nF);
            return true;
        }
    }
    void addPair(string name, string value){/*info("Hajoo dhu paramaytr " + name + " kiveau " + value);*/args.setOpt(name, value);} // Le void fait tâche...

    bool hasFlag(char flag){return !(m_flags1.find(flag)==string::npos);}
    bool hasFlag(string flag){return (find(m_flagsWords.begin(), m_flagsWords.end(), flag)!=m_flagsWords.end());}



    // I/O
    // Screen I/O
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

    // Pourrait retourner false pour faire return err(); sans accolades
    void err(string msg){Col(FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE); cout << msg << endl; dCol();}
    void warn(string msg){Col(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_RED); cout << msg << endl; dCol();}
    void info(string msg){Col(FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_WHITE); cout << msg << endl; dCol();}

    // Files I/O
    bool download(string host, string path, string fileName, Flags fl=0); // proposer une surcharge qui gère automatiquement le nom avec un hash
    bool download(string url, string pathFile, Flags fl=0); // proposer une surcharge qui gère automatiquement le nom avec un hash
    //size_t saveDL(char *data, size_t taille, size_t nmemb, void *stream);

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
    HANDLE cI;
    HANDLE cO;

    // Nécessaires au fonctionnement interne
    string cmd; // Dernière commande tapée...
    string fcmd; // Full command
    string fparams; // Full params
    Save args;

    //vector<string> args; // Et ses params

    HelpNext helpnxt;

    // Paramètres utilisateurs
    string userName;
    string cwd;
    unsigned long dirt; // Comme ça les pégus ne profiteront pas du bug de l'overflow. Ou ce sont des no-lifes.
    unsigned char maxDirt;

private:
    // I/O
    unsigned char m_txtCol;
    unsigned char m_bgCol;

    string m_dlFile;

    string m_flags1; // Flags mono : @ car séquence random de caractères
    vector<string> m_flagsWords; // Flags normaux : # car mots normaux
    //vector<pair<string, stringstream>> m_flagsPair; // Flags couples nom/valeur : &nom=valeur car y'en a 2

    // Sound
    string m_voice;
    vector< Track >  m_sons;
    sf::Int32 m_nbSnd;

};


#endif // ENV_HPP_INCLUDED
