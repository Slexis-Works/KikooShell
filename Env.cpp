#include "Env.hpp"

Env::Env(): cI(GetStdHandle(STD_INPUT_HANDLE)), cO(GetStdHandle(STD_OUTPUT_HANDLE)),
    dirt(0), maxDirt(15), // 10 pour bien faire ch
    m_txtCol(FOREGROUND_WHITE | FOREGROUND_INTENSITY), m_bgCol(0),
    m_voice("JeanJean"), m_nbSnd(0),
    helpnxt(HelpNext::None)

{
    srand(time(NULL));
}

Env::~Env(){
    for(size_t i=0; i<m_sons.size(); i++){
        delete m_sons[i].music;
        //cout << "Suppression de " << m_sons[i].second;
        m_sons.erase(m_sons.begin()+i);
    }
}

bool Env::addPath(string &nP){
    // Vérifie que le nouveau chemin ne sort pas des limites après avoir enlevé les multi-|
    // Si tout va bien, adddPath devient le chemin combiné avec le CWD terminé par |
    // sauf s'il commençait par |
    // Retourne false sans changer le path sinon : s'il contient des caractères interdits de Windaube
    if(!(nP.find('/')==string::npos && nP.find('\\')==string::npos))
        return false;
    err("String valide.");
    for(signed short ch=0;ch<nP.size()-1;ch++){
        cout << "Reading chars: " << nP[ch] << " and " << nP[ch+1] << endl;
        if(nP[ch]=='|' && nP[ch+1]=='|'){
            nP.erase(nP.begin()+ch+1);
            ch--;
            err("Contient un | en trop. Résultat : " + nP);
        }
    }


    return true;
}

