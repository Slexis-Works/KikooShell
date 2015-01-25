#include "main.hpp"

int main(){
    /*system("cd ../../"); // On se remet dans le root
    system("tree .");
    system("pause");*/

    // Main Inits
    Env env;
    SoundManager SM;

    // Win32 inits
    env.cI=GetStdHandle(STD_INPUT_HANDLE);
    env.cO=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT consRect;
    COORD bufSize;
    GetConsoleScreenBufferInfo(env.cO, &csbi);
    consRect.Top=0; consRect.Left=0;
    consRect.Right=csbi.dwMaximumWindowSize.X-1;
    consRect.Bottom=csbi.dwMaximumWindowSize.Y-1;
    bufSize.X=csbi.dwMaximumWindowSize.X;
    bufSize.Y=csbi.dwMaximumWindowSize.Y;
    SetConsoleScreenBufferSize(env.cO, bufSize);
    SetConsoleWindowInfo(env.cO, true, &consRect);

    //SetConsoleCP(65001); SetConsoleOutputCP(65001);
    SetConsoleCP(1252); SetConsoleOutputCP(1252);

    //Other inits
    srand(time(NULL));


    setCCol(FOREGROUND_GREEN);
    cout << "kikoOshell 0.1 ";
    // Afficher l'heure et une phrase débile
    { // Scope pour grosse variable temporaire, m'enfin à voir comment c'est mis en mémoire...
        string phrases[]={
            "Sans huile de palme depuis 2015 (mais avec d'autres trucs pires)",
            "Mal au crâne ? Avalez un KShell !",
            "Garanti ou intégralement remboursé !"
        };
        cout << phrases[rand()%3] << endl;

    }

    setCCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Now loading!" << endl;
    setCCol(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "For your pleasure!" << endl;
    for(unsigned char nbM=0;nbM<20;nbM++){
        COORD matrixPos;
        matrixPos.X=0; matrixPos.Y=3;
        unsigned int matrixArea(bufSize.X*(bufSize.Y-3));
        FillConsoleOutputCharacter(env.cO, ' ',  matrixArea, matrixPos, NULL);
        FillConsoleOutputAttribute(env.cO, FOREGROUND_GREEN, matrixArea, matrixPos, NULL);
        for(unsigned int nbN=0;nbN<matrixArea/3;nbN++){
            COORD charPos=matrixPos;
            charPos.X+=rand()%bufSize.X;
            charPos.Y+=rand()%(bufSize.Y-3);
            FillConsoleOutputCharacter(env.cO, '0'+rand()%10, 1, charPos, NULL);
        }
       sf::sleep(sf::milliseconds(50));
    }
    system("cls");
    cout << "Automaticly switched language to: Frremçèh" << endl << endl;
    setCCol(7);
    Sleep(1000+rand()%1000);
    do{
        cout << "Vautre heedantiphyam : ";
        env.userName=basicInput();
        ifstream fPswd("laYgen/" + env.userName + "/password.ksh");
        if(fPswd){
            string truePswd, userPswd;
            fPswd >> truePswd;
            cout << "Votreuh maudepasss : "; userPswd=basicInput();
            if(truePswd!=userPswd){
                cout << "Mauvay maudeuhpasse. Leuh mdp est " << truePswd << endl;
                env.userName.clear();
            }
        }else{
            cout << "Ce pégu n'existe pas." << endl;
            env.userName.clear();
        }
    }while(env.userName.empty());

    env.cwd="|laYgen|" + env.userName + "|médocs";
    setCCol(3 | FOREGROUND_INTENSITY);
    cout << endl << "Bhyaimveunuhe " << env.userName << " !" << endl;
    cout << "Chayl spayssyalysay en kikoOscript v. 0.1" << endl;
    cout << "127.0.0.1 sur localhost" << endl << endl;
    setCCol(7);

    do{
        _mainInput();

        if(env.cmd=="cwd"){
            if(env.args.size()){
                string nPath(env.args[0]);
                if(nPath.find('/')==string::npos && nPath.find('\\')==string::npos){
                    if(nPath[0]=='|'){
                        env.cwd=nPath;
                    }else{
                        env.cwd+='|' + nPath;
                    }
                    cout << "Jeuh man tap deuh si sa egzeest." << endl;
                    // Quand même gérer à partir du dossier courant... ./ t'insulte, ../ remonte mais pas trop, / root
                    // Voir l'erreur INVALID_HANDLE pour voir l'existence (+LS) https://msdn.microsoft.com/en-us/library/windows/desktop/aa365200(v=vs.85).aspx
                }else{
                    cout << "Sihe ta pahe kaumpree faut maytre | poor lay doçyé." << endl;
                }
            }else{
                cout << "Koman tahe ooblyay un daussyay !" << endl;
            }
        }else if(env.cmd=="ls"){
            SM.say("Ben alors la machine a vapeur elle devrait traverser les crans. Sauf que la SNCF est encore en graive. Salauds de pauvres !");
            //SM.say("Woufwouwouwouwouwfoufw ah"); On dirait Fak u Gooby
            //SM.say("Bien le bonjour les gens.");
        }else if(env.cmd=="sl"){
            cout << "Des trucs" << endl;
            cout << "Probablement d'autres trucs..." << endl;
            cout << "Et, de sûr, encore d'autres trucs." << endl;
        }else if(env.cmd=="sleep"){
            char* phrases[]={
                "J'me taperais bien une p'tite sieste.",
                "Regardez tous ces gens trop contents !",
                "J'allions me suicider. Parce que pour dormir c'est top."
            };
            SM.say(phrases[rand()%3]);
            setCCol(FOREGROUND_GREEN | FOREGROUND_RED);
            cout << "Livre dort :" << endl;
            setCCol(7);
            cout << "- EKShellent !" << endl << "   Jerry Traifaur" << endl;
            cout << "- Au moins ça plante moins que Windows." << endl << "   Roger Toukompry" << endl;
            cout << "- anph1 hum os adap t o jem naurmo" << endl << "   Jean-Kévin Kikoo" << endl;
            cout << "- Mais K(ikooSh)ell m*rde !" << endl << "   Un rageux." << endl;

        // Reste à unifier les exécutables, ou balancer la commande dans le vide, si Windows le fait
        }else if(env.cmd=="GraphicalShit"){
            if(env.args.size()){
                ShellExecute(NULL, "open", "preaugram/windob/GraphicalShit.exe" , env.args[0].c_str(), NULL, NULL);
                SM.say("Quand sa aura fini faudra faire deux fois Windows+D, sinon les gens ils vont avoir peur !"); // Le plus devient un "p'cent"
            }else{
                ShellExecute(NULL, "open", "preaugram/windob/GraphicalShit.exe" , NULL, NULL, NULL);
                cout << "Spécifiez un nombre pour plus de fun !" << endl;
            }
        }else if(env.userName==env.cmd){
            cout << "Bravo, ça c'est ton nom d'utilisateur." << endl;
        }else if(env.cmd!="quit"){
            cout << "Layreur ay antre la shez ai mwa." << endl;
        }
    }while(env.cmd!="quit");

    cout << "Quittance..." << endl;
    char* phrasesFin[]={
        "C'est triste que vous partiez dayja. Gertrude avait fait des patates.",
        "Attention aux poules dans le champ derriere la ferme. Elles n'ont pas ete traites.",
        "De toutes fassons je vous aimais pas."
    };
    SM.say(phrasesFin[rand()%3]);
    sf::sleep(sf::seconds(5));

    return 0;
}
