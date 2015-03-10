#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED

#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>

#include "mainStructs.hpp"

using namespace std;

class Save{
public:
    Save(string path); // Peut générer des popups
    ~Save(); // Resauvegarder

    void clear(){m_save.clear();}

    string crypt(string str);
    string deCrypt(string str);

    bool    getB(string key);
    int     getI(string key);
    long    getL(string key);
    float   getF(string key);
    string getS(string key);

    void setOpt(string key, bool   value);
    void setOpt(string key, int    value);
    void setOpt(string key, long   value);
    void setOpt(string key, float  value);
    void setOpt(string key, string value);

    stringstream* check(string key);

    bool sauvegarder(); // bool pour sauvegarde en boucle si pb

private:
    string m_path;
    Flags m_flags;

    map<string, stringstream*> m_save; // En fonction de la clé, un flux

};

#endif // SAVE_H_INCLUDED
