#ifndef SON_HPP_INCLUDED
#define SON_HPP_INCLUDED

#include "Env.hpp"

// Flags d'un son
#define F_SM_SYNC   1<<0 // Fonctionnement synchrone, ne retourne pas tant que le son n'a pas fini de jouer
#define F_SM_THREAD 1<<1
// Flags de la méthode say
#define F_SMS_NODISP    1<<8 // Affiche "Fauw aykoutay..." pour s'il n'y a pas de son


using namespace std;


/*class SoundManager{
public:
    SoundManager(Env &env);
    ~SoundManager();

    bool play(string path, sf::Uint8 flags=0); // 8 flags, flags étendus et privés pour say
    bool say(const char text[], sf::Uint16 flags=0); // FIXME Ne supporte pas les caractères spéciaux. Voxygen renvoie du vide.
    bool say(const char text[], string voice, sf::Uint16 flags=0);
    bool sayRand(vector<string> possib, sf::Uint16 flags=0);
    bool sayRand(vector<string> possib, string voice, sf::Uint16 flags=0);
    //bool say([])
    void cleanStop();


private:
    const Env &m_env;

    vector< Track >  m_sons;
    sf::Int32 m_nbSnd;
};*/

#endif // SON_HPP_INCLUDED
