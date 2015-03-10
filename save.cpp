#include "save.hpp"

Save::Save(string path): m_path(path)
{
    srand(time(0));
    ifstream fichier(path);
    if(fichier){
        fichier.seekg(0, ios::end);
        //int taille(fichier.tellg());
        //td::cout << "Taille : " << taille << " undefined random unity" << endl;
        if(fichier.tellg()<5){
        //Valeurs par défaut

    }else{
        fichier.seekg(0, ios::beg);

            while(fichier.tellg()>=0){
                string newKey;
                stringstream *sstr=new stringstream();
                char key[64], value[64];
                fichier >> key >> value;
                //fichier >> value; Simplifié ci-dessus
                newKey=deCrypt(key);
                *sstr << deCrypt(value);
                //float test;
                //*sstr >> test;
                //sstr << lect;
                //m_save[newKey];//<< lect;
                m_save[newKey]=sstr;
                //check("Test");
                //td::cout << "Key : " << newKey << "\tValue : " << sstr->str() << "\tPosition : " << fichier.tellg() << "/" << taille << endl;
            }
        }
    }
}

Save::~Save(){
    if(getB("_SaveQuit")) sauvegarder(); // Flag interne
    for(map<string, stringstream*>::iterator iter=m_save.begin(); iter!=m_save.end(); iter++){
        delete iter->second;
    }
}




bool Save::sauvegarder(){
    //Itérage
    ofstream fich("src/save.slws");
    if(!fich) return false;

    //unsigned int i(0), taille=m_save.size(); Inutiles au final
    for(map<string, stringstream*>::iterator iter=m_save.begin(); iter!=m_save.end(); iter++){
        fich << crypt(iter->first) << " " << crypt(iter->second->str()) << (iter==--m_save.end()?"":" ");
    }

    cout << "Sauvegarde finie" << endl;
    return true;
}

string Save::crypt(string str){
    if(str=="") str="{:*-?*-*-Empty@String-*-!*-(*}"; // Inspiré du FTP
    stringstream sstr;
    string newStr;
    unsigned int nChar(0);
    unsigned int sequence[10]={16, 43, 38, 95, 9, 20, 77, 62, 51, 84};
    for(unsigned int i=0; i<str.size(); i++){
        nChar=str[i];
        nChar+=sequence[i%10];
        sstr << (unsigned char)nChar;
    }
    sstr >> newStr;
    return newStr;
}

string Save::deCrypt(string str){
    stringstream sstr;
    string newStr;
    unsigned int nChar(0);
    unsigned int sequence[10]={16, 43, 38, 95, 9, 20, 77, 62, 51, 84};
    for(unsigned int i=0; i<str.size(); i++){
        nChar=str[i];
        nChar-=sequence[i%10];
        sstr << (unsigned char)nChar;
    }
    sstr >> newStr;
    if(newStr=="{:*-?*-*-Empty@String-*-!*-(*}") newStr="";
    return newStr;
}



bool    Save::getB(string key){
    //Décryptage, plus qu'un simple true ou false je pense
    //Why not des nombres pairs...
    //Owiii bonne idée
    if(!m_save.count(key)) return false;
    int ret;
    *m_save[key] >> ret;
    m_save[key]->seekg(0, ios::beg);
    return !(ret%2);
}

int     Save::getI(string key){
    if(!m_save.count(key)) return 0;
    int ret;
    //td::cout << "Le sstr contient : " << m_save[key]->str();
    *m_save[key] >> ret;
    m_save[key]->seekg(0, ios::beg);
    //td::cout << " Ret = " << ret << endl;
    return ret;
}

long    Save::getL(string key){
    if(!m_save.count(key)) return 0;
    long ret;
    *m_save[key] >> ret;
    m_save[key]->seekg(0, ios::beg);
    return ret;
}

float   Save::getF(string key){
    if(!m_save.count(key)) return 0.0f;
    float ret;
    *m_save[key] >> ret;
    m_save[key]->seekg(0, ios::beg);
    return ret;
}

string Save::getS(string key){
    if(!m_save.count(key)) return "";
    /*string ret;
    *m_save[key] >> ret;
    m_save[key]->seekg(0, ios::beg);
    return ret;*/
    return m_save[key]->str();
}


void Save::setOpt(string key, bool   value){
    int rando=2*(rand()%500)+!value;
    *check(key) << rando;
}

void Save::setOpt(string key, int    value){
    *check(key) << value;
}

void Save::setOpt(string key, long   value){
    *check(key) << value;
}

void Save::setOpt(string key, float  value){
    *check(key) << value;
}

void Save::setOpt(string key, string value){
    *check(key) << value;
}

stringstream* Save::check(string key){
    if(m_save.count(key)){
        //m_save[key]->str(""); Mon FTP m'a montré que c'était impossible de redéfinir après si c'était vide - mais isolé ça marche, ptêtre problèmes avec >> et espaces...
        delete m_save[key];
        //return m_save[key];
    }
    m_save[key]=new stringstream;
    return m_save[key];
}

