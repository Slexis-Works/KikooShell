#ifndef SON_HPP_INCLUDED
#define SON_HPP_INCLUDED

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

// Flags d'un son
#define F_SM_SYNC   1<<0 // Fonctionnement synchrone, ne retourne pas tant que le son n'a pas fini de jouer
// Flags de la méthode say
#define F_SMS_NODISP    1<<8 // Affiche "Fauw aykoutay..." pour s'il n'y a pas de son


using namespace std;

struct Track{
    sf::Music* music;
    string path;
    unsigned char flags;
};

class SoundManager{
public:
    SoundManager();
    ~SoundManager();

    bool play(string path, sf::Uint8 flags=0); // 8 flags, flags étendus et privés pour say
    bool say(const char text[], sf::Uint16 flags=0, string voice="JeanJean"); // FIXME Ne supporte pas les caractères spéciaux. Voxygen renvoie du vide.
    bool sayRand(vector<string> possib, sf::Uint16 flags=0, string voice="JeanJean");
    //bool say([])
    void cleanStop();


private:

    vector< Track >  m_sons;
    sf::Int32 m_nbSnd;
};


#endif // SON_HPP_INCLUDED
