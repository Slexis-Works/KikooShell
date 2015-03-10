#include "Env.hpp"

Env::Env(): cI(GetStdHandle(STD_INPUT_HANDLE)), cO(GetStdHandle(STD_OUTPUT_HANDLE)),
    dirt(0), maxDirt(15), // 10 pour bien faire ch
    m_txtCol(FOREGROUND_WHITE | FOREGROUND_INTENSITY), m_bgCol(0),
    m_dlFile(""),
    helpnxt(HelpNext::None),
    args(""),
    m_voice("JeanJean"), m_nbSnd(0)

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

bool Env::addPath(string &nP, bool isFile){ // Les dossiers se terminent automatiquement par |, les fichiers doivent se terminer par /|.[^|]$/
    // Vérifie que le nouveau chemin ne sort pas des limites après avoir enlevé les multi-|
    // Si tout va bien, adddPath devient le chemin combiné avec le CWD terminé par |
    // sauf s'il commençait par |
    // Retourne false sans changer le path sinon : s'il contient des caractères interdits de Windaube
    string finalPath;
    if(!(nP.find('/')==string::npos && nP.find('\\')==string::npos)){
        err("Sihe ta pahe kaumpree faut maytre | poor lay doçyé.");
        return false;
    }
    //info("String valide.");
    if(nP.size()<2 && nP.find('.')!=string::npos){
        err("Ratay.");
        return false;
    }
    for(signed long ch=0;ch<((signed long)nP.size())-1;ch++){ // Vérifier la narrowing conversion sur des plateformes 64 bits
        // D'après Faye faut y laisser cout << "Reading chars: " << nP[ch] << " and " << nP[ch+1] << endl;
        if(nP[ch]=='|' && nP[ch+1]=='|'){
            nP.erase(nP.begin()+ch+1);
            ch--;
            err("Leuh shemaim a hun | an trau. J'leuh vyr : " + nP);
        }
    }
    bool allowDots=true;
    size_t subPathPos(0); // Position d'où on reprend s'il y a [..|]*x
    unsigned short nbParent(0);
    for(signed long ch=0;ch<((signed long)nP.size())-2;ch++){
        if(nP[ch]!='.'){
            allowDots=false; // Capital qu'il soit ici : |..|trucs
        }else{
            if(nP[ch+1]=='.'){
                if(allowDots && nP[ch+2]=='|'){
                    nbParent++;
                    ch+=2;
                    subPathPos=ch;
                    /* if(allowDots && nP[ch=1]=='.' && nP[ch+2]=='.'){
                    nP.erase(nP.begin()+ch+2);
                    ch--;
                    err("Contient un . en trop. Simplification : " + nP);*/
                }else{
                    err("Sheumaim mhalphaurmet !");
                    return false;
                }
            }/* Il semble que les points soient autorisés. Bréf.
            Sauf s'il commence par un point
            Mais y'a les fichiers aussi... Flags
            else if(nP.substr(ch+2).find('|')!=string::npos){
                err("Ce point n'a rien à foutre là : " + nP.substr(ch, nP.substr(ch+2).find('|')));
                return false;
            }*/
        }
    }

    // @TODO analyser nP pour vérifier qu'il ne contient pas de dossiers nommés "." ou "..", peut-être avant, peut-être après
    if(nP[0]!='|'){
        if(nbParent){
            string curDir("|");
            vector<string> dirs;
            for(size_t ch=1;ch<cwd.size();ch++){
                if(cwd[ch]=='|'){
                    dirs.push_back(curDir);
                    curDir="|";
                }else
                    curDir+=cwd[ch];
            }
            if(dirs.size()>=nbParent){
                curDir.clear();
                for(size_t i=0;i<dirs.size()-nbParent;i++){
                    curDir+=dirs[i];
                }
                nP=curDir+nP.substr(subPathPos);
            }else{
                err("Hé mec tu t'assomes là.");
                return false;
            }
        }else
            nP=cwd+nP; // On ne devrait modifier qu'à la fin, si jamais false
    }
    if(!(isFile || nP[nP.size()-1]=='|'))
        nP+='|';
    stringstream infoSStr;
    infoSStr << "Remontage de " << nbParent << " dossiers. Résultat : " << nP;
    //info(infoSStr.str());

    return true;
}

string Env::getWinPath(){
    string path=cwd;
    replace(path.begin(), path.end(), '|', '\\');
    return "..\\root"+path;
}

bool Env::getWinPath(string &nP, bool isFile){
    if(nP.size()){
        //info("Mixage de " + nP + " avec " + cwd);
        if(addPath(nP, isFile)){
            replace(nP.begin(), nP.end(), '|', '\\');
            nP="..\\root"+nP;
            return true;
        }else
            return false;
    }else{
        nP=getWinPath();
        return true;
    }
}


bool Env::download(string host, string path, string fileName, Flags fl){
    // @TODO Vérifier que le nom est valide
    ifstream fileExists(/*"trhuKaintern/taaYaiMpai/" + */fileName);
    if(fileExists){
        if(!(fl&F_DL_NOWARN))
            warn("Le fichier existe déjà. Téléchargement inutile.");
        return true;
    }
    fileExists.close();

    m_dlFile=path;

    CURL *curl=curl_easy_init();
    if(curl){
        CURLcode res;

        curl_easy_setopt(curl, CURLOPT_URL, "http://curl.haxx.se/libcurl/c/curl_easy_init.html");
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Env::saveDL);
        res=curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }


    return false;
}

bool Env::download(string url, string pathFile, Flags fl){
    if(url.size()){
        CURL *curl=curl_easy_init();
        FILE *dlFile=fopen(pathFile.c_str(), "wb");
        if(curl && dlFile){
            CURLcode res;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            // Sans ceci le fichier est incomplet jusqu'à ce qu'on quitte le KSh... *facepalm*
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, dlFile);
            if(hasFlag("nOsweg") || hasFlag("blabla")){
                info("Taylayshargeuman...");
            }else{
                curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &progress_callback);
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            }
            if(hasFlag("tgHTTPS"))
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            if(hasFlag("followSTP"))
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            if(hasFlag("blabla"))
                curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            res=curl_easy_perform(curl);
            info("Okay, performed.");

            fclose(dlFile);
            curl_easy_cleanup(curl);
        }else
            err("Un pot cible d'ouvrir le fichier. F*it chier.");
    }
}


/*bool Env::download(string host, string pathFile, Flags fl){
    // @TODO Vérifier que le nom est valide
    ifstream fileExists(pathFile);
    if(fileExists){
        if(fl&F_DL_NOWARN)
            warn("Le fichier existe déjà. Téléchargement inutile.");
        return true;
    }
    fileExists.close();

    sf::Http http(host);
    sf::Http::Request req(path, sf::Http::Request::Get);
    sf::Http::Response rep(http.sendRequest(req));
    if(rep.getStatus()/100==2){
        string repData(rep.getBody());
        if(repData.size()){
            ofstream tempFile(pathF, ios::binary);
            tempFile.write(repData.c_str(), repData.size());
            tempFile.close();
            return true;
        }else{
            err("Le contenu retourné est vide.");
            return false;
        }
    }else{
        stringstream errSstr;
        errSstr << "Erreur HTTP : " << rep.getStatus();
        err(errSstr.str());
        return false;
    }
}*/
