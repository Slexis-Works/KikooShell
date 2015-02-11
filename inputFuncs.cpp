#include "inputFuncs.hpp"

void mainInput(Env &env){
    // TODO sauter une ligne si le curseur n'est pas à X=0
    //CONSOLE_CURSOR_INFO cci;
    //GetConsoleCursorInfo(env.cO, &cci);GetCons
    //GetConvertStg() ??

    // Les mains sales encrassent l'écran
    env.dirt++;
    if(env.dirt>env.maxDirt){
        env.txtCol=0;
    }else if(env.dirt==env.maxDirt){
        env.txtCol=FOREGROUND_INTENSITY;
    }else if(env.dirt>env.maxDirt-5){
        env.txtCol&=~FOREGROUND_INTENSITY;
    }

    setCCol(env.bgCol|FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "=ndaube ] " << env.cwd;
    setCCol(env.bgCol|env.txtCol);
    cout << " ~$ ";
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
    }

}

string basicInput(){
    string rep;
    getline(cin, rep);
    return rep;
}
