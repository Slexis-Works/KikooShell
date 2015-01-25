#ifndef SON_HPP_INCLUDED
#define SON_HPP_INCLUDED

#include <iostream>
#include <wininet.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class SoundManager{
public:
    SoundManager();
    ~SoundManager();

    bool play(string path);
    bool say(LPSTR text, string voice="JeanJean"); // FIXME Ne supporte pas les caractères spéciaux. Voxygen renvoie du vide.
    void cleanStop();


private:
    vector< pair<sf::Music*, string> >  m_sons;
    sf::Int32 m_nbSnd;
};


#endif // SON_HPP_INCLUDED
