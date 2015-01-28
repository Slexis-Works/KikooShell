#include "son.hpp"


SoundManager::SoundManager() : m_nbSnd(0)
{

}

SoundManager::~SoundManager(){
    for(sf::Int32 i=0; i<m_sons.size(); i++){
        delete m_sons[i].music;
        //cout << "Suppression de " << m_sons[i].second;
        m_sons.erase(m_sons.begin()+i);
    }
}

bool SoundManager::play(string path, sf::Uint8 flags){
    if(flags&F_SM_SYNC){
        sf::Music music;
        music.openFromFile(path);
        music.play();
        while(music.getStatus()!=sf::Music::Stopped){
            sf::sleep(sf::milliseconds(100));
        }
    }else{
        Track newTrack;
        newTrack.path=path;
        newTrack.flags=flags;
        newTrack.music=new sf::Music;
        newTrack.music->openFromFile(path);
        newTrack.music->play();
        m_sons.push_back(newTrack);
        //cout << "Lecture de " << path << endl;

        // Nettoyage
    }
    cleanStop();
}

void SoundManager::cleanStop(){
    for(sf::Int32 i=0; i<m_sons.size(); i++){
        if(m_sons[i].music->getStatus()==sf::Sound::Stopped){
            delete m_sons[i].music;
            //cout << "Suppression de " << m_sons[i].second << endl;
            m_sons.erase(m_sons.begin()+i);
            i--;
        }
    }
    /* Si ça joue encore : (faut des flags)
    while(newSound.getStatus()!=sf::Sound::Stopped){
        sf::sleep(sf::milliseconds(25));
    } */

}

bool SoundManager::say(LPSTR text, sf::Uint16 flags, string voice){
    // TODO Vérifier en MD5 si le truc n'a pas déjà été DL, puisqu'on rm qu'à la fin. Le HMAC serait-il utile du coup... ?
    // Se référer à http://ws.voxygen.fr/documentation.html
    if(!(flags&F_SMS_NODISP))
        cout << "Fauw aykoutay " << voice << " deer \"" << text << '"' << endl;

    sf::Http http;
    http.setHost("http://voxygen.fr/");
    sf::Http::Request req;
    req.setMethod(sf::Http::Request::Get);

    LPCSTR charBef(text);
    LPTSTR charEnc((LPTSTR)new char[2048]);
    DWORD bufL=2048;
    InternetCanonicalizeUrl(charBef, charEnc, &bufL, NULL);
    string encTxt(charEnc);
    delete charEnc;

    req.setUri("/sites/all/modules/voxygen_voices/assets/proxy/index.php?method=redirect&text="+encTxt+"&header=headerless&coding=ogg%3A1.0&voice="+voice); // ogg:1.0 désigne le format et la qualité. 0.0 ne semble que baisser le volume...

    sf::Http::Response rep(http.sendRequest(req));
    //cout << "Status " << rep.getStatus() << endl;
    string newPath(rep.getField("Location"));

    /*charBef=newPath.c_str();
    ZeroMemory(charEnc, 512);
    bufL=512;
    InternetCanonicalizeUrl(charBef, charEnc, &bufL, ICU_DECODE);
    cout << "Decoded : " << charEnc << endl;*/

    //cout << "Lecture depuis " << "http://ws.voxygen.fr" << newPath.substr(20) << endl;

    /* Un test pour reproduire le HMAC nécessaire à voxygen
    char * hash_md5 = HMAC("", "");
    cout << "Hashage : " << HMAC(HMAC(HMAC(HMAC(HMAC(HMAC(HMAC("coding=mp3:160-0","")+"frequency=48000","")+"header=headerless","")+"parsing=tags","")+"text=Une%20d%C3%A9monstration%20en%20fran%C3%A7ais.")+"user=demo")+"voice=Philippe") << endl;*/

    http.setHost("http://ws.voxygen.fr");
    req.setUri(newPath.substr(20));
    rep=http.sendRequest(req);
    //cout << "Réponse : " << rep.getStatus() /*<< " " << rep.getBody() */<< endl;

    stringstream sFileName;
    sFileName << "trhuKaintern/taaYaiMpai/Voxygen" << m_nbSnd++ << ".ogg";

    string repMP3(rep.getBody());
    if(repMP3.size()>10){
        ofstream tempFile(sFileName.str(), ios::binary);
        tempFile.write(repMP3.c_str(), repMP3.size());
        tempFile.close();
        play(sFileName.str(), flags&0xFF); // Filtrage des 8 derniers flags
        return true;
    }else{
        cout << "Impossible de charger le son depuis http://ws.voxygen.fr" << newPath.substr(20) << endl;
        return false;
    }
}
