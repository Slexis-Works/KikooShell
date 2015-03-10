#include "inputFuncs.hpp"

void mainInput(Env &env){
    // TODO sauter une ligne si le curseur n'est pas à X=0
    //CONSOLE_CURSOR_INFO cci;
    //GetConsoleCursorInfo(env.cO, &cci);GetCons
    //GetConvertStg() ??

    // Les mains sales encrassent l'écran
    env.dirt++;
    if(env.dirt>env.maxDirt){
        env.stCol(0);
    }else if(env.dirt==env.maxDirt){
        env.stCol(FOREGROUND_INTENSITY);
    }else if(env.dirt+5>env.maxDirt){
        env.darkenTxt();
    }

    env.tCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "=ndaube ] " << env.cwd;
    env.dCol();
    cout << " ~$ ";

    // Franchement en une Regex ou 2 c'est bouclé...
    string com;
    getline(cin, com);

    env.resetFlags();
    env.fcmd=com;
    //while(com[0]==' ')
    if(com.find(' ')==string::npos){
        env.cmd=com;
    }else{
        string par(com.substr(com.find(' ')+1)),
                curParam, pairKey;
        ExpectChar ec=ExpectChar::Param;
        bool inQuote(false), beginParam(false);
        env.cmd=com.substr(0, com.find(' '));
        env.fparams=par; // Peut rester des espaces. Osef ça sert pas.
        //env.info("Parameters : " + par);
        par+=' '; // Da trek, leuh reutoure
        for(signed long ch=0;ch<(signed long)par.size();ch++){
            if(inQuote?(par[ch]=='\''):(par[ch]==' ')){
                switch(ec){
                case ExpectChar::EndError:
                    env.err("Harguumam incorèkt : " + curParam);
                    ec=ExpectChar::Param;
                    curParam.clear();
                    break;
                case ExpectChar::EndFlags:
                    for(size_t nF=0;nF<curParam.size();nF++)
                        env.addFlag1(curParam[nF]);
                    ec=ExpectChar::Param;
                    curParam.clear();
                    break;
                case ExpectChar::EndFlag:
                    env.addFlag(curParam);
                    ec=ExpectChar::Param;
                    curParam.clear();
                    break;
                case ExpectChar::EqualPair:
                    env.err("Faudray ptaytre maytre hum aygal...");
                    ec=ExpectChar::Param;
                    curParam.clear();
                    break;
                case ExpectChar::EndPair:
                    if(par[ch-1]=='¤'){ // Caractère d'échappement trop bien
                        curParam[curParam.size()-1]='\'';
                    }else{
                        env.addPair(pairKey, curParam);
                        inQuote=false;
                        ec=ExpectChar::Param;
                        curParam.clear();
                    }
                    break;
                default:break; // Ce truc qui veut rien dire en fait
                }
                // ch++ gentil, j'autorise le collage.
            }else if(ec==ExpectChar::Param){
                if(par[ch]=='@'){
                    ec=ExpectChar::EndFlags;
                    beginParam=true;
                }else if(par[ch]=='#'){
                    ec=ExpectChar::EndFlag;
                    beginParam=true;
                }else if(par[ch]=='&'){
                    pairKey.clear();
                    ec=ExpectChar::EqualPair;
                    beginParam=true;
                }else{
                    ec=ExpectChar::EndError;
                    curParam=par[ch];
                }
                if(beginParam){
                    if(par.end()!=par.begin()+ch+1 && par[ch+1]==' '){
                        ec=ExpectChar::Param;
                        env.err("Paramaytreuh haimkeaurekt : " + par[ch]);
                    }
                    beginParam=false;
                }
            }else if(par[ch]=='=' && ec==ExpectChar::EqualPair){
                // Checker si ensuite y'a une quote
                ec=ExpectChar::EndPair;
                if(par.end()!=par.begin()+ch+1 && par[ch+1]==' '){
                    ec=ExpectChar::Param;
                    env.err("Fokolé c mye : " + curParam + "=... ou halaur ta ri1 my.");
                }else if(par.end()!=par.begin()+ch+1 && par[ch+1]=='`'){
                    inQuote=true;
                    ch++;
                    pairKey=curParam;
                }else{
                    pairKey=curParam;
                }
                curParam.clear();
            }else{
                curParam+=par[ch];
            }
        }
        if(inQuote)
            env.err("Gyemè nom férmè");
        if(ec==ExpectChar::EqualPair)
            env.err("Faudray ptaytre maytre hum aygal...");
    }


    /* Wut wis dat
    for(signed long ch=0;ch<com.size();ch++){
        if(com[ch])
    }*/

    /* Méthode feignasse :
    stringstream rep;
    string strrep;
    getline(cin, strrep);

    rep << strrep;
    env.cmd=string();
    env.args.clear();
    rep >> env.cmd;
    string newArg;
    while(rep >> newArg){
        env.args.push_back(newArg);
        newArg.clear();
    }*/
}

string basicInput(){
    string rep;
    getline(cin, rep);
    return rep;
}
