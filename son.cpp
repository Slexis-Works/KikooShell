#include "son.hpp"

void Env::setVoice(string nV){
    // @TODO Vérifier que la voix est disponible
    m_voice=nV;
}

bool Env::play(string path, sf::Uint8 flags){
    if(flags&F_SM_SYNC){ // Si le truc plante, wait jusqu'à 2sec
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
    return true;
}

void Env::cleanStop(){
    for(size_t i=0; i<m_sons.size(); i++){
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

bool Env::say(const char text[], sf::Uint16 flags){
    // TODO Vérifier en MD5 si le truc n'a pas déjà été DL, puisqu'on rm qu'à la fin. Le HMAC serait-il utile du coup... ?
    // Se référer à http://ws.voxygen.fr/documentation.html
    if(!(flags&F_SMS_NODISP))
        cout << "Fauw aykoutay " << m_voice << " deer \"" << text << '"' << endl;

    sf::Http http;
    http.setHost("http://voxygen.fr/");
    sf::Http::Request req;
    req.setMethod(sf::Http::Request::Get);

    sf::String txtToConv;
    txtToConv=text;
    LPCSTR charBef((char*)txtToConv.toUtf8().c_str()); // Environ 0% de chances que ceci marche chez vous
    // Accès impossible...
    //*(charBef+2)='X';
    //cout << "Charbef : " << charBef << endl << "text   : " << text << endl;
    LPSTR charEnc((LPSTR)new char[2048]);
    DWORD bufL=2048;
    InternetCanonicalizeUrl(charBef, charEnc, &bufL, 0);
    string encTxt(charEnc);
    //cout << "Encoded : " << charBef << " from " << encTxt << endl;
    //delete charEnc;

    req.setUri("/sites/all/modules/voxygen_voices/assets/proxy/index.php?method=redirect&text="+encTxt+"&header=headerless&coding=ogg%3A1.0&voice="+m_voice); // ogg:1.0 désigne le format et la qualité. 0.0 ne semble que baisser le volume...
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

    //cout << "newPath=" << newPath << endl;
    if(newPath.size()<21){
        cout << "Flaim deuh shershé leuh som (statue " << rep.getStatus() << ")" << endl;
        return false;
    }
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
        cout << endl << endl << "Faudray vayrifyay day truuk kan mem." << endl;
        return false;
    }
}

bool Env::say(const char text[], string voice, sf::Uint16 flags){
    if(!(flags&F_SMS_NODISP))
        cout << "Fauw aykoutay " << voice << " deer \"" << text << '"' << endl;

    sf::Http http;
    http.setHost("http://voxygen.fr/");
    sf::Http::Request req;
    req.setMethod(sf::Http::Request::Get);

    sf::String txtToConv;
    txtToConv=text;
    LPCSTR charBef((char*)txtToConv.toUtf8().c_str());
    LPSTR charEnc((LPSTR)new char[2048]);
    DWORD bufL=2048;
    InternetCanonicalizeUrl(charBef, charEnc, &bufL, 0);
    string encTxt(charEnc);
    req.setUri("/sites/all/modules/voxygen_voices/assets/proxy/index.php?method=redirect&text="+encTxt+"&header=headerless&coding=ogg%3A1.0&voice="+voice); // ogg:1.0 désigne le format et la qualité. 0.0 ne semble que baisser le volume...
    sf::Http::Response rep(http.sendRequest(req));
    string newPath(rep.getField("Location"));
    if(newPath.size()<21){
        stringstream errMsg;
        errMsg << "Flaim deuh shershé leuh som (statue " << rep.getStatus() << ")";
        err(errMsg.str());
        cout << endl << "Faudray vayrifyay day truuk kan mem. Jeanr ton daikaudeur TNT." << endl;
        return false;
    }
    http.setHost("http://ws.voxygen.fr");
    req.setUri(newPath.substr(20));
    rep=http.sendRequest(req);

    stringstream sFileName;
    sFileName << "trhuKaintern/taaYaiMpai/Voxygen" << m_nbSnd++ << ".ogg";


    string repMP3(rep.getBody());
    if(repMP3.size()>10){
        ofstream tempFile(sFileName.str(), ios::binary);
        tempFile.write(repMP3.c_str(), repMP3.size());
        tempFile.close();
        play(sFileName.str(), flags&0xFF);
        return true;
    }else{
        stringstream errMsg;
        errMsg << "Flaim deuh shershé leuh som (statue " << rep.getStatus() << ")";
        err(errMsg.str());
        cout << endl << "Faudray vayrifyay day truuk kan mem. Jeanr ton daikaudeur TNT." << endl;
        return false;
    }
}


bool Env::sayRand(vector<string> possib, sf::Uint16 flags){
    return say(possib[rand()%possib.size()].c_str(), flags);
}
bool Env::sayRand(vector<string> possib, string voice, sf::Uint16 flags){
    return say(possib[rand()%possib.size()].c_str(), voice, flags);
}
