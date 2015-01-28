#include "main.hpp"

int main(int argc, char *argv[]){

    // Main Inits
    Env env;
    SoundManager SM;

    // Win32 inits
    env.cI=GetStdHandle(STD_INPUT_HANDLE);
    env.cO=GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(env.cO, &csbi);
    COORD bufSize(csbi.dwSize);

    /*SMALL_RECT consRect;
    consRect.Top=0; consRect.Left=0;
    consRect.Right=csbi.dwMaximumWindowSize.X*14/9-12; // Calcul estrange lié à la police, faut voir la vraie taille max
    consRect.Bottom=csbi.dwMaximumWindowSize.Y-1;
    bufSize.X=csbi.dwMaximumWindowSize.X*14/9-11;
    bufSize.Y=csbi.dwMaximumWindowSize.Y;
    SetConsoleScreenBufferSize(env.cO, bufSize);
    SetConsoleWindowInfo(env.cO, true, &consRect);*/

    //SetConsoleCP(65001); SetConsoleOutputCP(65001);
    SetConsoleCP(1252); SetConsoleOutputCP(1252);

    //Other inits
    srand(time(NULL));


    setCCol(FOREGROUND_GREEN);
    cout << "kikoOshell 0.2 ";
    // Afficher l'heure et une phrase débile
    { // Scope pour grosse variable temporaire, m'enfin à voir comment c'est mis en mémoire...
        char* phrases[]={
            "Sans huile de palme depuis 2015 (mais avec d'autres trucs pires)",
            "Mal au crâne ? Avalez un KShell !",
            "Garanti ou intégralement remboursé !",
            "Cliquez ici pour avoir l'OS en français. Ou là..."
        };
        setCCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        cout << phrases[rand()%4] << endl;

    }

    setCCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Now loading!" << endl;
    setCCol(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "For your pleasure!" << endl;
    for(unsigned char nbM=0;nbM<10;nbM++){
        COORD matrixPos;
        matrixPos.X=0; matrixPos.Y=3;
        unsigned int matrixArea(bufSize.X*(bufSize.Y-3)); // Dessine comme un porc dans tout le buffer vertical
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

    env.cwd="|laYgen|" + env.userName + "|maidocs";
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

        // Trucs qui n'ont rien à voir avec l'OS
        }else if(env.cmd=="tlecteur"){
            SM.say("Ben y'a beaucoup de choses a dire sur les tracteurs. Parce que les tracteurs, c'est ma passion depuis que je mesure trois pommes virgule deux.");
            string rep;
            do{
                cout << "Quoi qu'tu veux voir ?" << endl;
                setCCol(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "citation    faidyver    tautologie    nada" << endl;
                setCCol(7);
                rep=basicInput();
                if(rep=="citation"){
                    string cits[]={
                        "\"Un tracteur, dans un garage, n'est qu'un objet technique ; quand il est au labour, et s'incline dans le sillon pendant que la terre se verse, il peut être perçu comme beau.\" --Gilbert Simondon",
                        "Un tracteur, dans un garage, n'est qu'un objet technique. Quand il est au labour, et s'incline dans le sillon pendant que la terre se verse, il peut aitre persu comme beau. Magnifique citation de Gilbert Simondon",
                        "\"Le forceps doit être préférable au tracteur lorsqu'il s'agit de rectifier la position de la tête et de diminuer son diamètre transverse ; cependant il est possible d'employer le tracteur à ces opérations et avec plus d'avantages qu'on n'est peut-être porté à le croire au premier abord.\" -- Neil Arnott",
                        "Le forceps doit aitre pr'et f'et rable au tracteur lorsqu'il s'agit de rectifier la position de la taite et de diminuer son diamaitre transverse. Cependant il est possible d'employer le tracteur a ces op'et rations et avec plus d'avantages qu'on n'est peutaitre portai a le croire au premier abord. Un chouette cours de mes canique traditionnelle de Neil Arnott."
                    };
                    int cit=rand()%2;
                    cout << cits[cit*2] << endl;
                    SM.say((LPSTR)cits[cit*2+1].c_str(), F_SMS_NODISP);
                }else if(rep=="faidyver"){
                    stringstream sDispStr, sGetStr;
                    sDispStr << "Le tracteur a ";
                    sGetStr << "Le tracteur. A ";
                    string actions[]={
                        "violé", "violet",
                        "écrasé", "aikrazet",
                        "brulé", "brulet",
                        "mangé", "manjet",
                        "poussé", "pousset"
                    }, persos[]={
                        "la poule", "la vache", "le canard",
                        "le cheval", "le chien", "le cochon",
                        "le corbeau", "le mouton", "l'ours",
                        "le tracteur", "le tigre en papier", "la Gertrude",
                        "Emmanuel Daubert", "le KikooShell", "Raoul le cultivateur"
                    }, lieux[]={
                        "l'entrepôt à maïs", "l'entrepot a ma hisse",
                        "la forêt", "la foret",
                        "l'église", "les glises la",
                        "la voiture à Gérard", "la voiture a l'autre Jairard",
                        "le champ derrière la ferme", "le champ derri aire la ferme"
                    };
                    int rndPhrase=rand()%5;
                    sDispStr << actions[rndPhrase*2] << " ";
                    sGetStr << actions[rndPhrase*2+1] << ". ";
                    rndPhrase=rand()%15;
                    sDispStr << persos[rndPhrase] << " dans ";
                    sGetStr << persos[rndPhrase] << ". Dans ";
                    rndPhrase=rand()%5;
                    sDispStr << lieux[rndPhrase*2] << ".";
                    sGetStr << lieux[rndPhrase*2+1] << ".";
                    cout << sDispStr.str() << endl;
                    SM.say((LPSTR)sGetStr.str().c_str(), F_SMS_NODISP);
                }else if(rep=="tautologie"){
                }else if(rep!="nada"){
                    SM.say("Mais t'es un beurdin ! Faut mettre un truc que je te propose quoi...");
                }else{
                    SM.say("Dommage, j'avais beaucoup de choses cools sur les tracteurs. Parce que les tracteurs, ayeux pourquoi tu me tapes ?");
                }
            }while(rep!="nada");
            setCCol(7);
        }else if(env.cmd==":hap:"){
            SM.say("Onche onche a gauche", F_SMS_NODISP | F_SM_SYNC);
            cout << "\\:hap:\\ ONSH ONSH A GOCH" << endl;
            SM.say("Onche onche a droite", F_SMS_NODISP | F_SM_SYNC);
            cout << "/:hap:/ ONSH ONSH A DRWAT" << endl;
            SM.say("Onche onche au milieu", F_SMS_NODISP | F_SM_SYNC);
            cout << "|:hap:| ONSH ONSH AU MILYE" << endl;
            SM.say("Onche onche en haut", F_SMS_NODISP | F_SM_SYNC);
            cout << "\\:hap:/ ONSH ONSH AN HAU" << endl;
            SM.say("Onche onche en bas", F_SMS_NODISP | F_SM_SYNC);
            cout << "/:hap:\\ ONSH ONSH AN BA" << endl;
            SM.say("Onche onche et jypsien", F_SMS_NODISP | F_SM_SYNC);
            cout << "7:hap:L ONSH ONSH EGYPTI1" << endl;
            SM.say("Onche onche ondulay !", F_SMS_NODISP | F_SM_SYNC);
            cout << "~:hap:~ ONSH ONSH ONDULAY" << endl;
            SM.say("Onche onche, tu veux du punch, petit pataponche. Ce soir, c'est onche onche party !");
        }else if(env.cmd==":noel:" || env.cmd=="microsoft"){
            if(env.cmd==":noel:"){
                cout << "PFEUH ! HAP VAINCRA !" << endl;
                cout << "HAP EST GRAND !" << endl << "HAP EST BEAU !" << endl << "HAP EST FORT !" << endl;
            }else{
                cout << "PFEUH ! Linux vaincra !" << endl;
            }
            sf::sleep(sf::seconds(3));
            CHAR pathToWin[MAX_PATH]; //, pathToFiles[MAX_PATH];
            GetWindowsDirectory(pathToWin, MAX_PATH);
            for(unsigned char i=0;i<3;i++){
                MessageBeep(MB_ICONERROR);
                sf::sleep(sf::seconds(0.5));
            }
            SM.say("Une menace, a et T D tec T.", F_SMS_NODISP, "Agnes");
            for(unsigned char i=0;i<150;i++){
                sf::Uint64 fakeFile(rand()<<32 + rand());
                cout << "Suppression de " << pathToWin << "\\" <<  fakeFile << ".sys" << endl;
                sf::sleep(sf::milliseconds(rand()%30));
            }/*
            for(unsigned char i=0;i<100;i++){
                sf::Int64 fakeFile(rand()<<32 + rand());
                cout << "Suppression de " << pathToFiles << fakeFile << ".exe";
                sf::sleep(sf::milliseconds(rand()%50));
            }*/
            setCCol(7 | FOREGROUND_INTENSITY);
            // else ifcout << endl << "Pour plus de prudence pour les hapistes, votre ordinateur potentiellement rempli de documents noelistes a été formaté." << endl;
            sf::sleep(sf::seconds(5));
            while(true){
                setCCol(rand()%256);
                cout << (char)(rand()%256);
                //if(!rand()) system("echo ^G"); Si c'est pas fait directement
            }
            return 0;
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
        // Si toLowerCase!=, "PAS LA PEINE DE GUEULER !" MAIS JE SUIS CALME MOI !
        }else if(env.cmd!="quit"){
            cout << "Layreur ay antre la shez ai mwa." << endl;
        }
    }while(env.cmd!="quit");

    cout << "Quittance..." << endl;
    char* phrasesFin[]={
        "C'est triste que vous partiez dayja. Gertrude avait fait des patates.",
        "Attention aux poules dans le champ derriere la ferme. Elles n'ont pas aytay traites.",
        "De toutes fassons je vous aimais pas."
    };
    SM.say(phrasesFin[rand()%3]);
    sf::sleep(sf::seconds(5));

    return 0;
}
