#include "main.hpp"

int main(int argc, char *argv[]){

    // Main Inits
    Env env;
    SoundManager SM(env);

    env.dirt=0;
    env.maxDirt=15; // 10 pour bien faire c
    env.txtCol=FOREGROUND_WHITE | FOREGROUND_INTENSITY;
    env.bgCol=0;
    env.defVoice="JeanJean";
    env.helpnxt=HelpNext::None;

    // Win32 inits
    env.cI=GetStdHandle(STD_INPUT_HANDLE);
    env.cO=GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(env.cO, &csbi);
    COORD bufSize(csbi.dwSize), winSize{csbi.srWindow.Right-csbi.srWindow.Left, csbi.srWindow.Bottom-csbi.srWindow.Top};

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


    setCCol(env.bgCol|FOREGROUND_GREEN);
    cout << "kikoOshell 0.3 ";
    // Afficher l'heure et une phrase débile
    { // Scope pour grosse variable temporaire, m'enfin à voir comment c'est mis en mémoire...
        string phrases[]={
            "Sans huile de palme depuis 2015 (mais avec d'autres trucs pires)",
            "Mal au crâne ? Avalez un KShell !",
            "Garanti ou intégralement remboursé !",
            "Cliquez ici pour avoir l'OS en français. Ou là..."
        };
        setCCol(env.bgCol|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        cout << phrases[rand()%4].c_str() << endl;

    }

    setCCol(env.bgCol|FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "Now loading!" << endl;
    setCCol(env.bgCol|FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "For your pleasure!" << endl;
    for(unsigned char nbM=0;nbM<10;nbM++){
        COORD matrixPos; // FIXME Pas forcément 3 suivant les dimensions de la fenêtre
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
    setCCol(env.bgCol|env.txtCol);
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
    setCCol(env.bgCol| 3 | FOREGROUND_INTENSITY);
    cout << endl << "Bhyaimveunuhe " << env.userName << " !" << endl;
    cout << "Chayl spayssyalysay en kikoOscript v. 0.1" << endl;
    cout << "127.0.0.1 sur localhost" << endl << endl;
    setCCol(env.bgCol|env.txtCol);

    do{
        _mainInput();
        // Si la fenêtre a été redimensionnée
        GetConsoleScreenBufferInfo(env.cO, &csbi);
        bufSize=csbi.dwSize;
        winSize=COORD{csbi.srWindow.Right-csbi.srWindow.Left, csbi.srWindow.Bottom-csbi.srWindow.Top};
        winSize.Y++; // D'après des observations
        stringstream ssTitle;
        ssTitle << "KikooShell - (" << winSize.X << "x" << winSize.Y << ") Propretay : (" << (int)env.dirt << "/" << (int)env.maxDirt << ")";
        SetConsoleTitle(ssTitle.str().c_str());

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
            SM.say("Ben alors la machine à vapeur elle devrait traverser l'écran. Sauf que la SNCF est encore en grève. Salauds de pauvres !");
            //SM.say("Woufwouwouwouwouwfoufw ah"); On dirait Fak u Gooby
            //SM.say("Bien le bonjour les gens.");
        }else if(env.cmd=="sl"){
            /*cout << "Des trucs" << endl;
            cout << "Probablement d'autres trucs..." << endl;
            cout << "Et, de sûr, encore d'autres trucs." << endl;*/
            string sPath(env.cwd);
            replace(sPath.begin(), sPath.end(), '|', '\\');
            cout << "Contenu de " << sPath << " :" << endl;
            sPath="..\\root\\"+sPath.substr(1)+"\\*";
            CHAR pathToSearch[MAX_PATH];
            strcpy(pathToSearch, sPath.c_str());
            WIN32_FIND_DATA ffd;
            HANDLE hFind=FindFirstFile(pathToSearch, &ffd);
            LARGE_INTEGER fileSize;
            if(hFind==INVALID_HANDLE_VALUE){
                SM.say("J'arrive pas à ouvrir le dossier. Narmol, narmol.");
                cout << "Dossier cherché : " << pathToSearch << endl;
            }else{
                do{
                    if(ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
                        cout << "Dossier : ";
                        if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED)){
                            setCCol(env.bgCol|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                            cout << ffd.cFileName << endl;
                            setCCol(env.bgCol|env.txtCol);
                        }else
                            cout << ffd.cFileName << endl;
                        sf::sleep(sf::milliseconds(50));
                    }else{
                        cout << "Fichier : ";
                        if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED|FILE_ATTRIBUTE_SPARSE_FILE)){
                            setCCol(env.bgCol|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                            cout << ffd.cFileName;
                            setCCol(env.bgCol|env.txtCol);
                        }else
                            cout << ffd.cFileName;
                        fileSize.LowPart=ffd.nFileSizeLow;
                        fileSize.HighPart=ffd.nFileSizeHigh;
                        if(fileSize.QuadPart>10000000){
                            cout << " (un obèse)" << endl;
                        }else{
                            sf::sleep(sf::microseconds(fileSize.QuadPart/4));
                            cout << " (" << fileSize.QuadPart << "octets)" << endl;
                        }
                    }
                }while(FindNextFile(hFind, &ffd));
            }

        }else if(env.cmd=="sleep"){
            SM.sayRand({
                "J'me taperais bien une p'tite sieste.",
                "Regardez tous ces gens trop contents !",
                "J'allions me suicider. Parce que pour dormir c'est top."
            });
            setCCol(env.bgCol|FOREGROUND_GREEN | FOREGROUND_RED);
            cout << "Livre dort :" << endl;
            setCCol(env.bgCol|env.txtCol);
            cout << "- EKShellent !" << endl << "   Jerry Traifaur" << endl;
            cout << "- Au moins ça plante moins que Windows." << endl << "   Roger Toukompry" << endl;
            cout << "- anph1 hum os adap t o jem naurmo" << endl << "   Jean-Kévin Kikoo" << endl;
            cout << "- Mais K(ikooSh)ell m*rde !" << endl << "   Un rageux." << endl;
        }else if(env.cmd=="kouleur"){
            if(env.args.size()){
                if(env.dirt>env.maxDirt-2){
                    SM.say("Désolé, mais c'est trop crade pour mettre de la couleur.");
                }else{
                    if(env.args[0]=="rooj"){
                        env.txtCol=FOREGROUND_RED | FOREGROUND_INTENSITY;
                        setCCol(env.bgCol|FOREGROUND_RED | FOREGROUND_INTENSITY);
                        SM.say("Rouge, c'est la couleur de Gertrude quand elle est en colère.");
                    }else if(env.args[0]=="vair"){
                        env.txtCol=FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                        setCCol(env.bgCol|FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        SM.say("Vert, ça me rappelle le lait que m'offrent les poules tous les soirs.");
                    }else if(env.args[0]=="bleu"){
                        env.txtCol=FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                        setCCol(env.bgCol|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        SM.say("Bleu, ben ça c'est les beaux paturages où y'a Raoul et son tracteur.");
                    }else{
                        cout << "Clampin, faut mettre ";
                        setCCol(env.bgCol|FOREGROUND_RED|FOREGROUND_INTENSITY); cout << "rooj ";
                        setCCol(env.bgCol|FOREGROUND_GREEN|FOREGROUND_INTENSITY); cout << "vair ";
                        setCCol(env.bgCol|env.txtCol); cout << "ou bien ";
                        setCCol(env.bgCol|FOREGROUND_BLUE|FOREGROUND_INTENSITY); cout << "bleu ";
                        setCCol(env.bgCol|env.txtCol); cout << "en plus." << endl;
                    }
                }
            }else{
                cout << "Clampin, faut mettre ";
                setCCol(env.bgCol|FOREGROUND_RED|FOREGROUND_INTENSITY); cout << "rooj ";
                setCCol(env.bgCol|FOREGROUND_GREEN|FOREGROUND_INTENSITY); cout << "vair ";
                setCCol(env.bgCol|env.txtCol); cout << "ou bien ";
                setCCol(env.bgCol|FOREGROUND_BLUE|FOREGROUND_INTENSITY); cout << "bleu ";
                setCCol(env.bgCol|env.txtCol); cout << "en plus." << endl;
            }
        }else if(env.cmd=="makeclean"){
            SM.sayRand({
                "J'ai amené la brosse à dent avec laquelle je nettoie le tracteur.",
                "Ben. Allons dans la salle de. Ben.",
                "Attention ça va faire plein de bubulles !",
                "Le cochon. Il as tout sali avec ses mains sales !"
            }, F_SMS_NODISP|F_SM_SYNC);
            system("CLS");

            if(env.dirt>=env.maxDirt){
                SM.say("C'était tellement crade que j'ai paumé la couleur.", F_SM_SYNC | F_SMS_NODISP);
                env.txtCol=FOREGROUND_WHITE | FOREGROUND_INTENSITY;
                env.dirt=0;
                if(env.dirt==env.maxDirt){
                    env.txtCol=0;
                    SM.say("C'est trop crade ! J'arrive pas à récurer. Faudrait changer ou rebooter.", F_SMS_NODISP);
                }else{
                    env.maxDirt--;
                    if(env.dirt==env.maxDirt){
                        env.txtCol=FOREGROUND_INTENSITY;
                        SM.say("J'ai fait du mieux qu'j'ai pu, mais ça va pas tiendrer longtemps.", F_SMS_NODISP);
                    }else if(env.dirt>env.maxDirt-5){
                        env.txtCol&=~FOREGROUND_INTENSITY;
                    }
                }
            }else{
                env.dirt=0;
                env.maxDirt--;
                if(env.dirt==env.maxDirt){
                    env.txtCol=FOREGROUND_INTENSITY;
                    SM.say("J'ai fait du mieux qu'j'ai pu, mais ça va pas tiendrer longtemps.", F_SMS_NODISP);
                }else if(env.dirt>env.maxDirt-5){
                    env.txtCol&=~FOREGROUND_INTENSITY;
                }else
                    env.txtCol|=FOREGROUND_INTENSITY;
            }
        }else if(env.cmd=="reboot"){
            SM.sayRand({
                "Surtout regardez pas le code source.",
                "Heu, évitez de le faire MAX_CALL_STACK fois.",
                "Encore un qu'a tout dégueulassé et qui rachète plutôt que de faire le ménage hein !"
            }, F_SM_SYNC);
            system("cls");
            return main(argc, argv);
        }else if(env.cmd=="ping" || env.cmd=="pong"){ // pOng en multi ? Ou param
            system("CLS");
            SM.say("Veuillez patienter.", F_SMS_NODISP | F_SM_SYNC);
            bool ballX(false), ballY(false);
            unsigned char j1X, j2X;
            //while(getchar!="ESC")
            while(true){

            }
        }else if(env.cmd=="haylp"){
            if(env.helpnxt==HelpNext::Haylp){
                dispHelp(env);
            }else{
                SM.say("Nan en fait faut mettre fomayday !");
                env.helpnxt=HelpNext::Ausekoure;
            }
        }else if(env.cmd=="fomayday"){
            if(env.helpnxt==HelpNext::Fomayday){
                dispHelp(env);
            }else{
                SM.say("Je confonds désolé, faut mettre ausekoure");
                env.helpnxt=HelpNext::Haylp;
            }
        }else if(env.cmd=="ausekoure"){
            if(env.helpnxt==HelpNext::Ausekoure){
                dispHelp(env);
            }else{
                SM.say("Loupé, c'était haylp !");
                env.helpnxt=HelpNext::Fomayday;
            }
        }else if(env.cmd=="help" || env.cmd=="aide" || env.cmd=="?"){
            SM.say("Désolé moi pas comprendre. Toi devoir mettre haylp, fomayday, ou ausekoure.");

        // Trucs qui n'ont rien à voir avec l'OS, mais dans l'esprit
        }else if(env.cmd=="wacist"){
            env.defVoice="Zozo";
            SM.sayRand({
                "Qu'est-ce t'as t'es raciste sale tête de Javel ?",
                "Tu veux voir ma banane ?",
                "Vas vivre dans la saleté vilain."
            });
            system("color f8");
            env.bgCol=BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY;
        }else if(env.cmd=="cowsay"){
            if(env.args.size()){
                string meuhs[]={ // Système probabiliste hautes performances
                    "meuh", "meuh", "meuh",
                    "",
                    "meeeeuh", "meeeeuh",
                    "mooouh",
                    "bêêêh", "MEUH"
                }, comm[]={
                    "Des fois elle est plus bavarde.",
                    "Je l'aime tellement que je crois qu'elle va remplacer Gertrude.",
                    "Je l'ai jamais vue autant causer !",
                    "C'est du patois charollais, vous pouvez pas comprendre."
                };
                string cowPhrase("Mais la vache. A dit");
                for(size_t meuh=0;meuh<env.args.size();meuh++)
                    cowPhrase+=" "+meuhs[rand()%9]; // Héhé, l'optimisation de s'arrêter à 9, comme ça y'a qu'un seul chiffre !
                cowPhrase+=". En fait ça veut dire \"";
                for(size_t mot=0;mot<env.args.size();mot++)
                    cowPhrase+=" " + env.args[mot];
                cowPhrase+=" \" " + comm[rand()%4];
                SM.say(cowPhrase.c_str());
            }else{
                SM.say("Ben la vache elle a rien à dire en ce moment.");
            }
        }else if(env.cmd=="tlecteur"){
            SM.say("Ben y'a beaucoup de choses à dire sur les tracteurs. Parce que les tracteurs, c'est ma passion depuis que je mesure trois pommes virgule deux.");
            string rep;
            do{
                cout << "Quoi qu'tu veux voir ?" << endl;
                setCCol(env.bgCol|FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "citation    faidyver    tautologie    nada" << endl;
                setCCol(env.bgCol|env.txtCol);
                rep=basicInput();
                if(rep=="citation"){
                    string cits[]={
                        "\"Un tracteur, dans un garage, n'est qu'un objet technique ; quand il est au labour, et s'incline dans le sillon pendant que la terre se verse, il peut être perçu comme beau.\" --Gilbert Simondon",
                        "Un tracteur, dans un garage, n'est qu'un objet technique. Quand il est au labour, et s'incline dans le sillon pendant que la terre se verse, il peut être perçu comme beau. Magnifique citation de Gilbert Simondon",
                        "\"Le forceps doit être préférable au tracteur lorsqu'il s'agit de rectifier la position de la tête et de diminuer son diamètre transverse ; cependant il est possible d'employer le tracteur à ces opérations et avec plus d'avantages qu'on n'est peut-être porté à le croire au premier abord.\" -- Neil Arnott",
                        "Le forceps doit être préférable au tracteur lorsqu'il s'agit de rectifier la position de la tête et de diminuer son diamètre transverse. Cependant il est possible d'employer le tracteur a ces opérations et avec plus d'avantages qu'on n'est peut-être porté à le croire au premier abord. Un chouette cours de mécanique traditionnelle de Neil Arnott.",
                        "\"L'astre attracteur, c'est un garage cosmique.\" -- Gérard l'agriculteur",
                        "L'astre attracteur, c'est un garage cosmique. J'y avions pensé pas plus tard qu'hier en rentrant le tracteur dans l'étable."
                    };
                    int cit=rand()%3;
                    cout << cits[cit*2] << endl;
                    SM.say((LPSTR)cits[cit*2+1].c_str(), F_SMS_NODISP);
                }else if(rep=="faidyver"){
                    stringstream sDispStr, sGetStr;
                    sDispStr << "Le tracteur a ";
                    sGetStr << "Le tracteur. A ";
                    string actions[]={
                        "violé",
                        "écrasé",
                        "brulé",
                        "mangé",
                        "poussé",
                    }, persos[]={
                        "la poule", "la vache", "le canard",
                        "le cheval", "le chien", "le cochon",
                        "le corbeau", "le mouton", "l'ours",
                        "le tracteur", "le tigre en papier", "la Gertrude",
                        "Emmanuel Daubert", "le KikooShell", "Raoul le cultivateur"
                    }, lieux[]={
                        "l'entrepôt à maïs",
                        "la forêt",
                        "l'église",
                        "la voiture à l'autre Gérard",
                        "le champ derrière la ferme"
                    };
                    int rndPhrase=rand()%5;
                    sDispStr << actions[rndPhrase] << " ";
                    sGetStr << actions[rndPhrase] << ". ";
                    rndPhrase=rand()%15;
                    sDispStr << persos[rndPhrase] << " dans ";
                    sGetStr << persos[rndPhrase] << ". Dans ";
                    rndPhrase=rand()%5;
                    sDispStr << lieux[rndPhrase] << ".";
                    sGetStr << lieux[rndPhrase] << ".";
                    cout << sDispStr.str() << endl;
                    SM.say((LPSTR)sGetStr.str().c_str(), F_SMS_NODISP);
                }else if(rep=="tautologie"){
                }else if(rep!="nada"){
                    SM.say("Mais t'es un beurdin ! Faut mettre un truc que je te propose quoi...");
                }else{
                    SM.say("Dommage, j'avais beaucoup de choses cools sur les tracteurs. Parce que les tracteurs, ayeux pourquoi tu me tapes ?");
                }
            }while(rep!="nada");
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
            SM.say("Onche onche, tu veux du punch, petit pataponche ? Ce soir, c'est onche onche party !");

            // Trow gentil ! Mais mérité.
            env.maxDirt=255;
            env.dirt=0;
        }else if(env.cmd==":noel:" || env.cmd=="microsoft"){
            if(env.cmd==":noel:"){
                cout << "PFEUH ! HAP VAINCRA !" << endl;
                cout << "HAP EST GRAND !" << endl << "HAP EST BEAU !" << endl << "HAP EST FORT !" << endl;
            }else{
                cout << "PFEUH ! Linux vaincra !" << endl;
            }
            sf::sleep(sf::seconds(3));
            for(unsigned char i=0;i<3;i++){
                MessageBeep(MB_ICONERROR);
                sf::sleep(sf::seconds(0.5));
            }
            //SM.say("Une menace, a et T D tec T.", F_SMS_NODISP, "Agnes");
            SM.say("Une menace, a été détectée.", "Agnes", F_SMS_NODISP);
            /*for(unsigned char i=0;i<15;i++){
                //sf::Uint64 fakeFile((rand()<<32) + rand());
                char *fakePath=new char[3*sizeof(int)];
                for(unsigned char i=0;i<3;i++){
                    *(int*)(fakePath+i*sizeof(int))=rand();
                    cout << "Added " << *(int*)(fakePath+i*sizeof(int)) << endl;
                }
                cout << "Suppression de " << pathToWin << "\\" <<  fakePath << ".sys" << endl;
                delete fakePath;
                sf::sleep(sf::milliseconds(rand()%30));
            }*/
            /*
            for(unsigned char i=0;i<100;i++){
                sf::Int64 fakeFile(rand()<<32 + rand());
                cout << "Suppression de " << pathToFiles << fakeFile << ".exe";
                sf::sleep(sf::milliseconds(rand()%50));
            }*/

            CHAR pathToWin[MAX_PATH], pathToRead[MAX_PATH]; //, pathToFiles[MAX_PATH];
            GetWindowsDirectory(pathToWin, MAX_PATH);
            strcpy(pathToRead,pathToWin);
            strcat(pathToRead, "\\*");
            WIN32_FIND_DATA ffd;
            HANDLE hFind=FindFirstFile(pathToRead, &ffd);
            LARGE_INTEGER fileSize;
            if(hFind==INVALID_HANDLE_VALUE){
                SM.say("T'as de la chance, je laisse ton disque dur en paix !");
                continue;
            }
            do{
                if(ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
                    cout << "Supprayssyiom duh daussyé ";
                    if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED)){
                        setCCol(env.bgCol|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                        cout << ffd.cFileName;
                        setCCol(env.bgCol|env.txtCol);
                    }else
                        cout << ffd.cFileName;
                    sf::sleep(sf::milliseconds(50));
                    cout << " OK" << endl;
                }else{
                    cout << "Dailaitage deuh " << pathToWin << "\\";
                    if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED|FILE_ATTRIBUTE_SPARSE_FILE)){
                        setCCol(env.bgCol|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                        cout << ffd.cFileName;
                        setCCol(env.bgCol|env.txtCol);
                    }else
                        cout << ffd.cFileName;
                    fileSize.LowPart=ffd.nFileSizeLow;
                    fileSize.HighPart=ffd.nFileSizeHigh;
                    sf::sleep(sf::microseconds(fileSize.QuadPart/4));
                    cout << " (" << fileSize.QuadPart/4 << "µs)" << endl;
                }
            }while(FindNextFile(hFind, &ffd));

            setCCol(env.bgCol|FOREGROUND_WHITE | FOREGROUND_INTENSITY);
            if(env.cmd==":noel:")
                cout << endl << "Pour plus de prudence pour les hapistes, votre ordinateur potentiellement rempli de documents noelistes a été formaté.";
            else
                cout << endl << "Hé ! On ne dit pas de gros mots ! Pour la peine, je vais faire planter ton truc !";
            sf::sleep(sf::seconds(5));
            while(true){
                setCCol(rand()%256);
                cout << (char)(rand()%256);
                //if(!rand()) system("echo ^G"); Si c'est pas fait directement
            }
            return 0;
        // Reste à unifier les exécutables, ou balancer la commande dans le vide, si Windows le fait
        }else if(env.cmd=="exec"){
            if(env.args.size()){
                if(env.args[0]=="GraphicalShit"){
                    if(env.args.size()>1){
                        ShellExecute(NULL, "open", "preaugram/windob/GraphicalShit.exe" , env.args[1].c_str(), NULL, 0);
                        SM.say("Quand ça aura fini faudra faire deux fois Windows+D, sinon les gens ils vont avoir peur !"); // Le plus devient un "p'cent"
                    }else{
                        ShellExecute(NULL, "open", "preaugram/windob/GraphicalShit.exe" , NULL, NULL, 0);
                        cout << "Spécifiez un nombre pour plus de fun !" << endl;
                    }
                }else{
                    executeInside(env.args[0]);
                }
            }else{
                cout << "Merci de spécifier un de vos exécutables, sans l'extension .exe" << endl;
                cout << "Tapez ";
                setCCol(FOREGROUND_GREEN|env.bgCol);
                cout << "sl \"|preaugram|windob\"";
                setCCol(env.bgCol|env.txtCol);
                cout << " pour en voir la liste." << endl;
            }
        }else if(env.cmd=="launch"){
            if(env.args.size()){
                executeOutside(env.args[0]);
            }

        // Bonus
        }else if(env.cmd=="fss" || env.cmd=="fsf"){
            SM.play("trhuKaintern/mhuzyKaIshemsom/free-software-song.ogg");
            cout << "Join us now and share the software;" << endl;
            sf::sleep(sf::seconds(6.0f));
            cout << "You'll be free, hackers, you'll be free." << endl;
            sf::sleep(sf::seconds(8.0f));
            cout << "Join us now and share the software;" << endl;
            sf::sleep(sf::seconds(3.0f));
            cout << "You'll be free, hackers, you'll be free." << endl << endl;
            sf::sleep(sf::seconds(9.0f));
            // 26s
            cout << "Hoarders can get piles of money," << endl;
            sf::sleep(sf::seconds(5.0f));
            cout << "That is true, hackers, that is true." << endl;
            sf::sleep(sf::seconds(6.0f)); // 37s
            cout << "But they cannot help their neighbors;" << endl;
            sf::sleep(sf::seconds(4.0f)); // 41s
            cout << "That's not good, hackers, that's not good." << endl << endl;
            sf::sleep(sf::seconds(10.0f));
            // 51s
            cout << "When we have enough free software" << endl;
            sf::sleep(sf::seconds(4.0f));
            cout << "At our call, hackers, at our call," << endl;
            sf::sleep(sf::seconds(7.0f)); // 62s
            cout << "We'll kick out those dirty licenses" << endl;
            sf::sleep(sf::seconds(4.0f)); // 66s
            cout << "Ever more, hackers, ever more." << endl << endl;
            sf::sleep(sf::seconds(9.0f));
            // 75s
            cout << "Join us now and share the software;" << endl;
            sf::sleep(sf::seconds(6.0f));
            cout << "You'll be free, hackers, you'll be free." << endl;
            sf::sleep(sf::seconds(8.0f));
            cout << "Join us now and share the software;" << endl;
            sf::sleep(sf::seconds(3.0f));
            cout << "You'll be free, hackers, you'll be free." << endl << endl;
            sf::sleep(sf::seconds(9.0f));
            setCCol(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            cout << "*verse une larme*" << endl;
            setCCol(env.txtCol|env.bgCol);
        }else if(env.userName==env.cmd){
            cout << "Bravo, ça c'est ton nom d'utilisateur." << endl;
        // Si toLowerCase!=, "PAS LA PEINE DE GUEULER !" MAIS JE SUIS CALME MOI !
        }else if(env.cmd!="quit"){
            cout << "Layreur ay antre la shez ai mwa." << endl;
        }
    }while(env.cmd!="quit");

    cout << "Quittance..." << endl;
    //SM.say(phrasesFin[rand()%3], F_SM_SYNC);
    SM.sayRand({
        "C'est triste que vous partiez déjà. Gertrude avait fait des patates.",
        "Attention aux poules dans le champ derrière la ferme. Elles n'ont pas été traites.",
        "De toutes façons je vous aimais pas.",
        "Y'a pas le feu à le lac. Ah ben si en fait. Le canard, est pyromane.",
        "Attention au tracteur, il s'entraîne pour le concours de beauté."
    },F_SM_SYNC);

    return 0;
}
