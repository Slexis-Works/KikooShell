#include "main.hpp"

int main(int argc, char *argv[]){

    // Main Inits
    Env env;
    SoundManager SM;

    env.dirt=0;
    env.maxDirt=15; // 10 pour bien faire c
    env.txtCol=FOREGROUND_WHITE | FOREGROUND_INTENSITY;

    // Win32 inits
    env.cI=GetStdHandle(STD_INPUT_HANDLE);
    env.cO=GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(env.cO, &csbi);
    COORD bufSize(csbi.dwSize), winSize{csbi.srWindow.Right-csbi.srWindow.Left, csbi.srWindow.Bottom-csbi.srWindow.Top};

    /*SMALL_RECT consRect;
    consRect.Top=0; consRect.Left=0;
    consRect.Right=csbi.dwMaximumWindowSize.X*14/9-12; // Calcul estrange li� � la police, faut voir la vraie taille max
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
    cout << "kikoOshell 0.3 ";
    // Afficher l'heure et une phrase d�bile
    { // Scope pour grosse variable temporaire, m'enfin � voir comment c'est mis en m�moire...
        string phrases[]={
            "Sans huile de palme depuis 2015 (mais avec d'autres trucs pires)",
            "Mal au cr�ne ? Avalez un KShell !",
            "Garanti ou int�gralement rembours� !",
            "Cliquez ici pour avoir l'OS en fran�ais. Ou l�..."
        };
        setCCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        cout << phrases[rand()%4].c_str() << endl;

    }

    setCCol(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "Now loading!" << endl;
    setCCol(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "For your pleasure!" << endl;
    for(unsigned char nbM=0;nbM<10;nbM++){
        COORD matrixPos; // FIXME Pas forc�ment 3 suivant les dimensions de la fen�tre
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
    cout << "Automaticly switched language to: Frrem��h" << endl << endl;
    setCCol(env.txtCol);
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
            cout << "Ce p�gu n'existe pas." << endl;
            env.userName.clear();
        }
    }while(env.userName.empty());

    env.cwd="|laYgen|" + env.userName + "|maidocs";
    setCCol(3 | FOREGROUND_INTENSITY);
    cout << endl << "Bhyaimveunuhe " << env.userName << " !" << endl;
    cout << "Chayl spayssyalysay en kikoOscript v. 0.1" << endl;
    cout << "127.0.0.1 sur localhost" << endl << endl;
    setCCol(env.txtCol);

    do{
        _mainInput();
        // Si la fen�tre a �t� redimensionn�e
        GetConsoleScreenBufferInfo(env.cO, &csbi);
        bufSize=csbi.dwSize;
        winSize=COORD{csbi.srWindow.Right-csbi.srWindow.Left, csbi.srWindow.Bottom-csbi.srWindow.Top};
        stringstream ssTitle;
        ssTitle << "KikooShell - (" << bufSize.X << "x" << bufSize.Y << ") Propretay : (" << (int)env.dirt << "/" << (int)env.maxDirt << ")";
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
                    // Quand m�me g�rer � partir du dossier courant... ./ t'insulte, ../ remonte mais pas trop, / root
                    // Voir l'erreur INVALID_HANDLE pour voir l'existence (+LS) https://msdn.microsoft.com/en-us/library/windows/desktop/aa365200(v=vs.85).aspx
                }else{
                    cout << "Sihe ta pahe kaumpree faut maytre | poor lay do�y�." << endl;
                }
            }else{
                cout << "Koman tahe ooblyay un daussyay !" << endl;
            }
        }else if(env.cmd=="ls"){
            SM.say("Ben alors la machine � vapeur elle devrait traverser l'�cran. Sauf que la SNCF est encore en gr�ve. Salauds de pauvres !");
            //SM.say("Woufwouwouwouwouwfoufw ah"); On dirait Fak u Gooby
            //SM.say("Bien le bonjour les gens.");
        }else if(env.cmd=="sl"){
            cout << "Des trucs" << endl;
            cout << "Probablement d'autres trucs..." << endl;
            cout << "Et, de s�r, encore d'autres trucs." << endl;
        }else if(env.cmd=="sleep"){
            SM.sayRand({
                "J'me taperais bien une p'tite sieste.",
                "Regardez tous ces gens trop contents !",
                "J'allions me suicider. Parce que pour dormir c'est top."
            });
            setCCol(FOREGROUND_GREEN | FOREGROUND_RED);
            cout << "Livre dort :" << endl;
            setCCol(env.txtCol);
            cout << "- EKShellent !" << endl << "   Jerry Traifaur" << endl;
            cout << "- Au moins �a plante moins que Windows." << endl << "   Roger Toukompry" << endl;
            cout << "- anph1 hum os adap t o jem naurmo" << endl << "   Jean-K�vin Kikoo" << endl;
            cout << "- Mais K(ikooSh)ell m*rde !" << endl << "   Un rageux." << endl;
        }else if(env.cmd=="kouleur"){
            if(env.args.size()){
                if(env.dirt>env.maxDirt-2){
                    SM.say("D�sol�, mais c'est trop crade pour mettre de la couleur.");
                }else{
                    if(env.args[0]=="rooj"){
                        env.txtCol=FOREGROUND_RED | FOREGROUND_INTENSITY;
                        setCCol(FOREGROUND_RED | FOREGROUND_INTENSITY);
                        SM.say("Rouge, c'est la couleur de Gertrude quand elle est en col�re.");
                    }else if(env.args[0]=="vair"){
                        env.txtCol=FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                        setCCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        SM.say("Vert, �a me rappelle le lait que m'offrent les poules tous les soirs.");
                    }else if(env.args[0]=="bleu"){
                        env.txtCol=FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                        setCCol(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        SM.say("Bleu, ben �a c'est les beaux paturages o� y'a Raoul et son tracteur.");
                    }else{
                        cout << "Clampin, faut mettre ";
                        setCCol(FOREGROUND_RED|FOREGROUND_INTENSITY); cout << "rooj ";
                        setCCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY); cout << "vair ";
                        setCCol(env.txtCol); cout << "ou bien ";
                        setCCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY); cout << "bleu ";
                        setCCol(env.txtCol); cout << "en plus." << endl;
                    }
                }
            }else{
                cout << "Clampin, faut mettre ";
                setCCol(FOREGROUND_RED|FOREGROUND_INTENSITY); cout << "rooj ";
                setCCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY); cout << "vair ";
                setCCol(env.txtCol); cout << "ou bien ";
                setCCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY); cout << "bleu ";
                setCCol(env.txtCol); cout << "en plus." << endl;
            }
        }else if(env.cmd=="makeclean"){
            SM.sayRand({
                "J'ai amen� la brosse � dent avec laquelle je nettoie le tracteur.",
                "Ben. Allons dans la salle de. Ben.",
                "Attention �a va faire plein de bubulles !",
                "Le cochon. Il as tout sali avec ses mains sales !"
            }, F_SMS_NODISP|F_SM_SYNC);
            system("CLS");

            if(env.dirt>=env.maxDirt){
                SM.say("C'�tait tellement crade que j'ai paum� la couleur.", F_SM_SYNC | F_SMS_NODISP);
                env.txtCol=FOREGROUND_WHITE | FOREGROUND_INTENSITY;
                env.dirt=0;
                if(env.dirt==env.maxDirt){
                    env.txtCol=0;
                    SM.say("C'est trop crade ! J'arrive pas � r�curer. Faudrait changer ou rebooter.", F_SMS_NODISP);
                }else{
                    env.maxDirt--;
                    if(env.dirt==env.maxDirt){
                        env.txtCol=FOREGROUND_INTENSITY;
                        SM.say("J'ai fait du mieux qu'j'ai pu, mais �a va pas tiendrer longtemps.", F_SMS_NODISP);
                    }else if(env.dirt>env.maxDirt-5){
                        env.txtCol&=~FOREGROUND_INTENSITY;
                    }
                }
            }else{
                env.dirt=0;
                env.maxDirt--;
                if(env.dirt==env.maxDirt){
                    env.txtCol=FOREGROUND_INTENSITY;
                    SM.say("J'ai fait du mieux qu'j'ai pu, mais �a va pas tiendrer longtemps.", F_SMS_NODISP);
                }else if(env.dirt>env.maxDirt-5){
                    env.txtCol&=~FOREGROUND_INTENSITY;
                }else
                    env.txtCol|=FOREGROUND_INTENSITY;
            }
        }else if(env.cmd=="reboot"){
            SM.sayRand({
                "Surtout regardez pas le code source.",
                "Heu, �vitez de le faire MAX_CALL_STACK fois.",
                "Encore un qu'a tout d�gueulass� et qui rach�te plut�t que de faire le m�nage hein !"
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

        // Trucs qui n'ont rien � voir avec l'OS, mais dans l'esprit
        }else if(env.cmd=="cowsay"){
            if(env.args.size()){
                string meuhs[]={ // Syst�me probabiliste hautes performances
                    "meuh", "meuh", "meuh",
                    "",
                    "meeeeuh", "meeeeuh",
                    "mooouh",
                    "b���h", "MEUH"
                }, comm[]={
                    "Des fois elle est plus bavarde.",
                    "Je l'aime tellement que je crois qu'elle va remplacer Gertrude.",
                    "Je l'ai jamais vue autant causer !",
                    "C'est du patois charollais, vous pouvez pas comprendre."
                };
                string cowPhrase("Mais la vache. A dit");
                for(size_t meuh=0;meuh<env.args.size();meuh++)
                    cowPhrase+=" "+meuhs[rand()%9]; // H�h�, l'optimisation de s'arr�ter � 9, comme �a y'a qu'un seul chiffre !
                cowPhrase+=". En fait �a veut dire \"";
                for(size_t mot=0;mot<env.args.size();mot++)
                    cowPhrase+=" " + env.args[mot];
                cowPhrase+=" \" " + comm[rand()%4];
                SM.say(cowPhrase.c_str());
            }else{
                SM.say("Ben la vache elle a rien � dire en ce moment.");
            }
        }else if(env.cmd=="tlecteur"){
            SM.say("Ben y'a beaucoup de choses � dire sur les tracteurs. Parce que les tracteurs, c'est ma passion depuis que je mesure trois pommes virgule deux.");
            string rep;
            do{
                cout << "Quoi qu'tu veux voir ?" << endl;
                setCCol(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "citation    faidyver    tautologie    nada" << endl;
                setCCol(env.txtCol);
                rep=basicInput();
                if(rep=="citation"){
                    string cits[]={
                        "\"Un tracteur, dans un garage, n'est qu'un objet technique ; quand il est au labour, et s'incline dans le sillon pendant que la terre se verse, il peut �tre per�u comme beau.\" --Gilbert Simondon",
                        "Un tracteur, dans un garage, n'est qu'un objet technique. Quand il est au labour, et s'incline dans le sillon pendant que la terre se verse, il peut �tre per�u comme beau. Magnifique citation de Gilbert Simondon",
                        "\"Le forceps doit �tre pr�f�rable au tracteur lorsqu'il s'agit de rectifier la position de la t�te et de diminuer son diam�tre transverse ; cependant il est possible d'employer le tracteur � ces op�rations et avec plus d'avantages qu'on n'est peut-�tre port� � le croire au premier abord.\" -- Neil Arnott",
                        "Le forceps doit �tre pr�f�rable au tracteur lorsqu'il s'agit de rectifier la position de la t�te et de diminuer son diam�tre transverse. Cependant il est possible d'employer le tracteur a ces op�rations et avec plus d'avantages qu'on n'est peut-�tre port� � le croire au premier abord. Un chouette cours de m�canique traditionnelle de Neil Arnott."
                    };
                    int cit=rand()%2;
                    cout << cits[cit*2] << endl;
                    SM.say((LPSTR)cits[cit*2+1].c_str(), F_SMS_NODISP);
                }else if(rep=="faidyver"){
                    stringstream sDispStr, sGetStr;
                    sDispStr << "Le tracteur a ";
                    sGetStr << "Le tracteur. A ";
                    string actions[]={
                        "viol�",
                        "�cras�",
                        "brul�",
                        "mang�",
                        "pouss�",
                    }, persos[]={
                        "la poule", "la vache", "le canard",
                        "le cheval", "le chien", "le cochon",
                        "le corbeau", "le mouton", "l'ours",
                        "le tracteur", "le tigre en papier", "la Gertrude",
                        "Emmanuel Daubert", "le KikooShell", "Raoul le cultivateur"
                    }, lieux[]={
                        "l'entrep�t � ma�s",
                        "la for�t",
                        "l'�glise",
                        "la voiture � l'autre G�rard",
                        "le champ derri�re la ferme"
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
            SM.say("Onche onche, tu veux du punch, petit pataponche. Ce soir, c'est onche onche party !");

            // Trow gentil ! Mais m�rit�.
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
            CHAR pathToWin[MAX_PATH]; //, pathToFiles[MAX_PATH];
            GetWindowsDirectory(pathToWin, MAX_PATH);
            for(unsigned char i=0;i<3;i++){
                MessageBeep(MB_ICONERROR);
                sf::sleep(sf::seconds(0.5));
            }
            //SM.say("Une menace, a et T D tec T.", F_SMS_NODISP, "Agnes");
            SM.say("Une menace, a �t� d�tect�e.", F_SMS_NODISP, "Agnes");
            for(unsigned char i=0;i<150;i++){
                //sf::Uint64 fakeFile((rand()<<32) + rand());
                cout << "Suppression de " << pathToWin << "\\" <<  rand() << ".sys" << endl;
                sf::sleep(sf::milliseconds(rand()%30));
            }/*
            for(unsigned char i=0;i<100;i++){
                sf::Int64 fakeFile(rand()<<32 + rand());
                cout << "Suppression de " << pathToFiles << fakeFile << ".exe";
                sf::sleep(sf::milliseconds(rand()%50));
            }*/
            setCCol(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
            if(env.cmd==":noel:")
                cout << endl << "Pour plus de prudence pour les hapistes, votre ordinateur potentiellement rempli de documents noelistes a �t� format�.";
            else
                cout << endl << "H� ! On ne dit pas de gros mots ! Pour la peine, je vais faire planter ton truc !";
            sf::sleep(sf::seconds(5));
            while(true){
                setCCol(rand()%256);
                cout << (char)(rand()%256);
                //if(!rand()) system("echo ^G"); Si c'est pas fait directement
            }
            return 0;
        // Reste � unifier les ex�cutables, ou balancer la commande dans le vide, si Windows le fait
        }else if(env.cmd=="GraphicalShit"){
            if(env.args.size()){
                ShellExecute(NULL, "open", "preaugram/windob/GraphicalShit.exe" , env.args[0].c_str(), NULL, 0);
                SM.say("Quand �a aura fini faudra faire deux fois Windows+D, sinon les gens ils vont avoir peur !"); // Le plus devient un "p'cent"
            }else{
                ShellExecute(NULL, "open", "preaugram/windob/GraphicalShit.exe" , NULL, NULL, 0);
                cout << "Sp�cifiez un nombre pour plus de fun !" << endl;
            }
        }else if(env.userName==env.cmd){
            cout << "Bravo, �a c'est ton nom d'utilisateur." << endl;
        // Si toLowerCase!=, "PAS LA PEINE DE GUEULER !" MAIS JE SUIS CALME MOI !
        }else if(env.cmd!="quit"){
            cout << "Layreur ay antre la shez ai mwa." << endl;
        }
    }while(env.cmd!="quit");

    cout << "Quittance..." << endl;
    //SM.say(phrasesFin[rand()%3], F_SM_SYNC);
    SM.sayRand({
        "C'est triste que vous partiez d�j�. Gertrude avait fait des patates.",
        "Attention aux poules dans le champ derri�re la ferme. Elles n'ont pas �t� traites.",
        "De toutes fa�ons je vous aimais pas.",
        "Y'a pas le feu � le lac. Ah ben si en fait. Le canard, est pyromane.",
        "Attention au tracteur, il s'entra�ne pour le concours de beaut�."
    },F_SM_SYNC);

    return 0;
}
