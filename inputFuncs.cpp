#include "inputFuncs.hpp"

void mainInput(Env &env){
    // TODO sauter une ligne si le curseur n'est pas à X=0
    //CONSOLE_CURSOR_INFO cci;
    //GetConsoleCursorInfo(env.cO, &cci);GetCons
    //GetConvertStg() ??

    setCCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << " " << env.cwd;
    setCCol(7);
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
