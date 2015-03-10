#include "main.hpp"

// @FIXME IconPro ne semble pas vraiment enregistrer en 8 bpp, ou alors Windaube sait pas lire
// @TODO Mettre iconSmall sur le shell, et le grand en Alt+Tab

int main(int argc, char *argv[]){
    // Main Inits
    Env env;

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


    env.tCol(FOREGROUND_GREEN);
    cout << "kikoOshell 0.3 ";
    // Afficher l'heure et une phrase débile
    { // Scope pour grosse variable temporaire, m'enfin à voir comment c'est mis en mémoire...
        string phrases[]={
            "Sans huile de palme depuis 2015 (mais avec d'autres trucs pires)",
            "Mal au crâne ? Avalez un KShell !",
            "Garanti ou intégralement remboursé !",
            "Cliquez ici pour avoir l'OS en français. Ou là..."
        };
        env.tCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        cout << phrases[rand()%4].c_str() << endl;

    }

    env.tCol(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "Now loading!" << endl;
    env.tCol(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
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
    env.dCol();
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

    env.cwd="|laYgen|" + env.userName + "|maidocs|";
    env.tCol(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    cout << endl << "Bhyaimveunuhe " << env.userName << " !" << endl;
    cout << "Chayl spayssyalysay en kikoOscript v. 0.1" << endl;
    cout << "127.0.0.1 sur localhost" << endl << endl;
    env.dCol();

    do{
        _mainInput();
        // Si la fenêtre a été redimensionnée
        GetConsoleScreenBufferInfo(env.cO, &csbi);
        bufSize=csbi.dwSize;
        winSize=COORD{csbi.srWindow.Right-csbi.srWindow.Left, csbi.srWindow.Bottom-csbi.srWindow.Top};
        winSize.X++; // D'après des observations
        winSize.Y++; // D'après des observations
        stringstream ssTitle;
        ssTitle << "KikooShell - (" << winSize.X << "x" << winSize.Y << ") Propretay : (" << (int)env.dirt << "/" << (int)env.maxDirt << ")";
        SetConsoleTitle(ssTitle.str().c_str());

        if(env.cmd=="cwd"){
            string nCWD=env.args.getS("cwd");
            if(nCWD.size()){
                if(env.addPath(nCWD))
                    env.cwd=nCWD;
                else
                    env.err("Faudrait relire des tutos quand même.");
            }else
                env.err("Koman tahe ooblyay un daussyay !");
            /*if(env.args.size()){
                env.addPath(env.args[0]);
                string nPath(env.args[0]);
                if(nPath.find('/')==string::npos && nPath.find('\\')==string::npos){
                    if(nPath[0]=='|'){
                        env.cwd=nPath + (nPath[nPath.size()-1]=='|'?"":"|");
                    }else{
                        env.cwd+=nPath + (nPath[nPath.size()-1]=='|'?"":"|");
                    }
                    cout << "Jeuh man tap deuh si sa egzeest." << endl;
                    // Quand même gérer à partir du dossier courant... ./ t'insulte, ../ remonte mais pas trop, / root
                    // Voir l'erreur INVALID_HANDLE pour voir l'existence (+LS) https://msdn.microsoft.com/en-us/library/windows/desktop/aa365200(v=vs.85).aspx
                }else{
                    cout << "Sihe ta pahe kaumpree faut maytre | poor lay doçyé." << endl;
                }
            }else{
                cout << "Koman tahe ooblyay un daussyay !" << endl;
            }*/
        }else if(env.cmd=="ls"){
            env.say("Ben alors la machine à vapeur elle devrait traverser l'écran. Sauf que la SNCF est encore en grève. Salauds de pauvres !");
            //env.say("Woufwouwouwouwouwfoufw ah"); On dirait Fak u Gooby
            //env.say("Bien le bonjour les gens.");
        }else if(env.cmd=="sl"){ // Demande le paramètre #leuHtip pour afficher Dossier ou Fichier
            // Faire de l'humour noir quand c'est désert ? Comme ton compte en banque. Comme ta vie sentimentale. J'aime les desserts.
            /*cout << "Des trucs" << endl;
            cout << "Probablement d'autres trucs..." << endl;
            cout << "Et, de sûr, encore d'autres trucs." << endl;*/
            /* Avant env.addPath et tout
            string sPath(env.cwd);
            replace(sPath.begin(), sPath.end(), '|', '\\');
            cout << "Contenu de " << sPath << " :" << endl;
            sPath="..\\root"+sPath+"*";*/
            string sPath(env.args.getS("scheumaim"));
            if(env.getWinPath(sPath)){
            sPath+="*";
            CHAR pathToSearch[MAX_PATH];
            strcpy(pathToSearch, sPath.c_str());
            WIN32_FIND_DATA ffd;
            HANDLE hFind=FindFirstFile(pathToSearch, &ffd);
            LARGE_INTEGER fileSize;
            if(hFind==INVALID_HANDLE_VALUE){
                env.say("J'arrive pas à ouvrir le dossier. Narmol, narmol.");
                cout << "Dossier cherché : " << pathToSearch << endl;
            }else{
                do{
                    if(ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
                        cout << "Dossier : ";
                        if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED)){
                            env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                            cout << ffd.cFileName << endl;
                            env.dCol();
                        }else
                            cout << ffd.cFileName << endl;
                        sf::sleep(sf::milliseconds(50));
                    }else{
                        cout << "Fichier : ";
                        if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED|FILE_ATTRIBUTE_SPARSE_FILE)){
                            env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                            cout << ffd.cFileName;
                            env.dCol();
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
            }
        }else if(env.cmd=="cat"){
            string filePath(env.args.getS("fichyé"));
            if(env.getWinPath(filePath, true)){
                ifstream fileToRead(filePath);
                if(fileToRead){
                    while(!fileToRead.eof()){
                        string str;
                        getline(fileToRead, str);
                        cout << str << endl;
                    }
                }else{
                    env.err("Impossible de trouver " + filePath);
                }
            } // AddPath se charge des erreurs
        }else if(env.cmd=="sleep"){
            env.sayRand({
                "J'me taperais bien une p'tite sieste.",
                "Regardez tous ces gens trop contents !",
                "J'allions me suicider. Parce que pour dormir c'est top."
            });
            env.tCol(FOREGROUND_GREEN | FOREGROUND_RED);
            cout << "Livre dort :" << endl;
            env.dCol();
            cout << "- EKShellent !" << endl << "   Jerry Traifaur" << endl;
            cout << "- Au moins ça plante moins que Windows." << endl << "   Roger Toukompry" << endl;
            cout << "- anph1 hum os adap t o jem naurmo" << endl << "   Jean-Kévin Kikoo" << endl;
            cout << "- Mais K(ikooSh)ell m*rde !" << endl << "   Un rageux." << endl;
        }else if(env.cmd=="kouleur"){
            bool gotGood(false);
            char fColor(0);
            if(env.hasFlag('r') || env.hasFlag("rooj")){
                fColor|=FOREGROUND_RED;
                env.tCol(FOREGROUND_RED|FOREGROUND_INTENSITY);
                env.say("Rouge, c'est la couleur de Gertrude quand elle est en colère.");
                gotGood=true;
            }if(env.hasFlag('v') || env.hasFlag("vair")){
                fColor|=FOREGROUND_GREEN;
                env.tCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                env.say("Vert, ça me rappelle le lait que m'offrent les poules tous les soirs.");
                gotGood=true;
            }if(env.hasFlag('b') || env.hasFlag("bleu")){
                fColor|=FOREGROUND_BLUE;
                env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                env.say("Bleu, ben ça c'est les beaux paturages où y'a Raoul et son tracteur.");
                gotGood=true;
            }if(env.hasFlag('i') || env.hasFlag("himtamse")){
                fColor|=FOREGROUND_INTENSITY;
                env.Col(FOREGROUND_WHITE_INTENSITY);
                env.say("Argh, mes yeux. C'est plus lumineux que dans l'étable.");
                gotGood=true;
            }
            if(gotGood){
                env.stCol(fColor); // Marche plus...
            }else{
                cout << "Clampin, faut mettre ";
                env.tCol(FOREGROUND_RED|FOREGROUND_INTENSITY); cout << "#rooj ";
                env.tCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY); cout << "#vair ";
                env.dCol(); cout << "ou bien ";
                env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY); cout << "#bleu ";
                env.dCol(); cout << "en plus." << endl;
                cout << "Et si t'as pas mal aux yeux, tu peux essayer ";
                env.Col(FOREGROUND_WHITE|BACKGROUND_WHITE_INTENSITY); cout << "#himtamse";
                env.dCol(); cout << " !" << endl;
            }
            /*if(env.args.size()){
                if(env.dirt>env.maxDirt-2){
                    env.say("Désolé, mais c'est trop crade pour mettre de la couleur.");
                }else{
                    if(env.args[0]=="rooj"){
                        env.stCol(FOREGROUND_RED | FOREGROUND_INTENSITY);
                        env.say("Rouge, c'est la couleur de Gertrude quand elle est en colère.");
                    }else if(env.args[0]=="vair"){
                        env.stCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        env.say("Vert, ça me rappelle le lait que m'offrent les poules tous les soirs.");
                    }else if(env.args[0]=="bleu"){
                        env.stCol(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        env.say("Bleu, ben ça c'est les beaux paturages où y'a Raoul et son tracteur.");
                    }else{
                        cout << "Clampin, faut mettre ";
                        env.tCol(FOREGROUND_RED|FOREGROUND_INTENSITY); cout << "rooj ";
                        env.tCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY); cout << "vair ";
                        env.dCol(); cout << "ou bien ";
                        env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY); cout << "bleu ";
                        env.dCol(); cout << "en plus." << endl;
                    }
                }
            }else{
                cout << "Clampin, faut mettre ";
                env.tCol(FOREGROUND_RED|FOREGROUND_INTENSITY); cout << "rooj ";
                env.tCol(FOREGROUND_GREEN|FOREGROUND_INTENSITY); cout << "vair ";
                env.dCol(); cout << "ou bien ";
                env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY); cout << "bleu ";
                env.dCol(); cout << "en plus." << endl;
            }*/
        }else if(env.cmd=="download"){
            string pF(env.args.getS("fichyer")); // Vous ne patherez pas
            if(pF.size() && env.getWinPath(pF,true)){
                //env.download(env.args.getS("aute"), env.args.getS("passe"), pF);
                env.download(env.args.getS("url"), pF);
            }else{
                env.err("Kom c mal fé");
            }
        }else if(env.cmd=="makeclean"){
            env.sayRand({
                "J'ai amené la brosse à dent avec laquelle je nettoie le tracteur.",
                "Ben. Allons dans la salle de. Ben.",
                "Attention ça va faire plein de bubulles !",
                "Le cochon. Il as tout sali avec ses mains sales !"
            }, F_SMS_NODISP|F_SM_SYNC);
            system("CLS");

            if(env.dirt>=env.maxDirt){
                env.say("C'était tellement crade que j'ai paumé la couleur.", F_SM_SYNC | F_SMS_NODISP);
                env.stCol(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
                env.dirt=0;
                if(env.dirt==env.maxDirt){
                    env.stCol(0);
                    env.say("C'est trop crade ! J'arrive pas à récurer. Faudrait changer ou rebooter.", F_SMS_NODISP);
                }else{
                    env.maxDirt--;
                    if(env.dirt==env.maxDirt){
                        env.stCol(FOREGROUND_INTENSITY);
                        env.say("J'ai fait du mieux qu'j'ai pu, mais ça va pas tiendrer longtemps.", F_SMS_NODISP);
                    }else if(env.dirt+5>env.maxDirt){
                        env.darkenTxt();
                    }
                }
            }else{
                env.dirt=0;
                env.maxDirt--;
                if(env.dirt==env.maxDirt){
                    env.stCol(FOREGROUND_INTENSITY);
                    env.say("J'ai fait du mieux qu'j'ai pu, mais ça va pas tiendrer longtemps.", F_SMS_NODISP);
                }else if(env.dirt+5>env.maxDirt){
                    env.darkenTxt();
                }else
                    env.enlightTxt();
            }
        }else if(env.cmd=="reboot"){
            env.sayRand({
                "Surtout regardez pas le code source.",
                "Heu, évitez de le faire MAX_CALL_STACK fois.",
                "Encore un qu'a tout dégueulassé et qui rachète plutôt que de faire le ménage hein !"
            }, F_SM_SYNC);
            system("cls");
            return main(argc, argv);
        }else if(env.cmd=="ping" || env.cmd=="pong"){ // pOng en multi ? Ou param
            // Si on spécifie une IP les raquettes deviennent l'IP. Une adresse est convertie en son IP, si ça marche.
            if(winSize.X<30 || winSize.Y<30){
                env.say("À l'époque de la haute définition, je suggère que vous vous achetiez un écran plus grand pour jouer à des jeux récents et décents.");
            }else{
                cout << "Bob l'éPong" << endl;
                env.say("Veuillez patienter.", F_SM_SYNC);
                SetConsoleTitle("Je compte pas, tu vas perdre.");
                system("CLS");
                sf::sleep(sf::milliseconds(1000+rand()%2000));
                env.say("C'est tellement très le beaucoup bien que ça doit charger longtemps.", F_SMS_NODISP|F_SM_SYNC);
                bool ballX(true), ballY(true);
                unsigned short jH=winSize.Y/6, // Tailles raquette
                    j1S(0), j2S(0); // Scores
                float j1Y((winSize.Y-jH)/2), j2X(winSize.X-2), j2Y((winSize.Y-jH)/2), // Positions des raquettes
                    step((float)winSize.Y/80.0f); // Vitesses balles et raquettes
                sf::Vector2f ballPos(2.0f, (winSize.Y+jH)/2);
                sf::Vector2i bP(2, (winSize.Y+jH)/2);
                //while(getchar!="ESC")

                sf::sleep(sf::seconds(0.5));
                env.say("Profitez bien ! Appuyez sur échap quand vous en aurez marre au canards.", F_SMS_NODISP|F_SM_SYNC);

                while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    system("CLS");

                    // Input
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        j1Y-=step;
                        if(j1Y<0) j1Y=0;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                        j1Y+=step;
                        if(j1Y+jH>winSize.Y-1) j1Y=winSize.Y-jH;
                    }

                    // Compute
                    ballPos.x+=step*(ballX?3:-3);
                    ballPos.y+=step*(ballY?3:-3);

                    bP.x=ballPos.x;
                    bP.y=ballPos.y;
                    if(ballX && bP.x>winSize.X-4){
                        if(bP.x>=winSize.X){ // Un step trop grand et DTC
                            MessageBeep(MB_ICONINFORMATION);
                            // Relance, score...
                            ballX=false;
                            ballPos.x=winSize.X/2;
                        }else if(bP.y>j2Y && bP.y<j2Y+2*jH){
                            MessageBeep(MB_ICONERROR);
                            ballX=false;
                        }
                    }else if(!ballX && bP.x<3){
                        if(bP.x<0){
                            MessageBeep(MB_ICONERROR);
                            ballX=true;
                            ballPos.x=winSize.X/2;
                        }else if(bP.y>j1Y && bP.y<j1Y+jH){
                            MessageBeep(MB_ICONINFORMATION);
                            ballX=true;
                        }
                    }
                    if(ballY && bP.y>=winSize.Y){
                        ballPos.y=winSize.Y-1;
                        ballY=false;
                    }else if(!ballY && bP.y<0){
                        ballPos.y=0;
                        ballY=true;
                    }

                    if(ballX){
                        // Jouer "narmolement"
                        j2X=winSize.X-2;
                        if(j2Y+jH<ballPos.y){
                            j2Y+=3*step;
                        }else{
                            j2Y-=3*step;
                        }
                        if(j2Y<0) j2Y=0;
                        if(j2Y+2*jH>winSize.Y-1) j2Y=winSize.Y-2*jH;

                    }else if(ballPos.x>winSize.X/2){
                        j2X=winSize.X-2;
                    }else{
                        j2X=rand()%(winSize.X/2-2)+winSize.X/2;
                        j2Y=rand()%(winSize.Y-2*jH);
                    }

                    // Output
                    drawVLine(winSize.X/2, 0, winSize.Y, '|');
                    drawVLine(1, j1Y, jH, 'X'); // Surcharger si y'a l'IP.
                    drawVLine(j2X, j2Y, 2*jH, '<'); // Surcharger si y'a l'IP.
                    loc(ballPos.x, ballPos.y); cout << "O";

                    sf::sleep(sf::seconds(1/10)); // J'ai parlé de HD, mais pas de haute fréquence hein.
                }
            }
        }else if(env.cmd=="haylp"){
            if(env.helpnxt==HelpNext::Haylp){
                dispHelp(env);
            }else{
                env.say("Nan en fait faut mettre fomayday !");
                env.helpnxt=HelpNext::Ausekoure;
            }
        }else if(env.cmd=="fomayday"){
            if(env.helpnxt==HelpNext::Fomayday){
                dispHelp(env);
            }else{
                env.say("Je confonds désolé, faut mettre ausekoure");
                env.helpnxt=HelpNext::Haylp;
            }
        }else if(env.cmd=="ausekoure"){
            if(env.helpnxt==HelpNext::Ausekoure){
                dispHelp(env);
            }else{
                env.say("Loupé, c'était haylp !");
                env.helpnxt=HelpNext::Fomayday;
            }
        }else if(env.cmd=="help" || env.cmd=="aide" || env.cmd=="?"){
            env.say("Désolé moi pas comprendre. Toi devoir mettre haylp, fomayday, ou ausekoure.");


        // Trucs qui n'ont rien à voir avec l'OS, mais dans l'esprit
        }else if(env.cmd=="Commande"){
            env.say("L'art, tout ça, c'est la Significiance incarnée.", "Bicool");
        }else if(env.cmd=="faye"){
            launchNav("fayedu39.1s.fr");
        }else if(env.cmd=="wacist"){
            env.setVoice("Zozo");
            env.sayRand({
                "Qu'est-ce t'as t'es raciste sale tête de Javel ?",
                "Tu veux voir ma banane ?",
                "Vas vivre dans la saleté vilain."
            });
            system("color f8");
            env.sbCol(BACKGROUND_WHITE_INTENSITY);
        }else if(env.cmd=="cowsay"){
            string phCow(env.args.getS("fraz"));
            if(phCow.size()){
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
                string cowPhrase("Mais la vache. A dit meuh");
                //for(size_t meuh=0;meuh<env.args.size();meuh++)
                for(size_t meuh=0;meuh<phCow.size()/10;meuh++)
                    cowPhrase+=" "+meuhs[rand()%9]; // Héhé, l'optimisation de s'arrêter à 9, comme ça y'a qu'un seul chiffre !
                cowPhrase+=". En fait ça veut dire \"";
                /*for(size_t mot=0;mot<env.args.size();mot++)
                    cowPhrase+=" " + env.args[mot];*/
                cowPhrase+=phCow+"\". " + comm[rand()%4];
                env.say(cowPhrase.c_str());
            }else{
                env.say("Ben la vache elle a rien à dire en ce moment.");
            }
        }else if(env.cmd=="tlecteur"){
            env.say("Ben y'a beaucoup de choses à dire sur les tracteurs. Parce que les tracteurs, c'est ma passion depuis que je mesure trois pommes virgule deux.");
            string rep;
            do{
                cout << "Quoi qu'tu veux voir ?" << endl;
                env.tCol(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "citation    faidyver    tautologie    nada" << endl;
                env.dCol();
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
                    env.say((LPSTR)cits[cit*2+1].c_str(), F_SMS_NODISP);
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
                    env.say((LPSTR)sGetStr.str().c_str(), F_SMS_NODISP);
                }else if(rep=="tautologie"){
                }else if(rep!="nada"){
                    env.say("Mais t'es un beurdin ! Faut mettre un truc que je te propose quoi...");
                }else{
                    env.say("Dommage, j'avais beaucoup de choses cools sur les tracteurs. Parce que les tracteurs, ayeux pourquoi tu me tapes ?");
                }
            }while(rep!="nada");
        }else if(env.cmd==":hap:"){
            env.say("Onche onche a gauche", F_SMS_NODISP | F_SM_SYNC);
            cout << "\\:hap:\\ ONSH ONSH A GOCH" << endl;
            env.say("Onche onche a droite", F_SMS_NODISP | F_SM_SYNC);
            cout << "/:hap:/ ONSH ONSH A DRWAT" << endl;
            env.say("Onche onche au milieu", F_SMS_NODISP | F_SM_SYNC);
            cout << "|:hap:| ONSH ONSH AU MILYE" << endl;
            env.say("Onche onche en haut", F_SMS_NODISP | F_SM_SYNC);
            cout << "\\:hap:/ ONSH ONSH AN HAU" << endl;
            env.say("Onche onche en bas", F_SMS_NODISP | F_SM_SYNC);
            cout << "/:hap:\\ ONSH ONSH AN BA" << endl;
            env.say("Onche onche et jypsien", F_SMS_NODISP | F_SM_SYNC);
            cout << "7:hap:L ONSH ONSH EGYPTI1" << endl;
            env.say("Onche onche ondulay !", F_SMS_NODISP | F_SM_SYNC);
            cout << "~:hap:~ ONSH ONSH ONDULAY" << endl;
            env.say("Onche onche, tu veux du punch, petit pataponche ? Ce soir, c'est onche onche party !");

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
            //env.say("Une menace, a et T D tec T.", F_SMS_NODISP, "Agnes");
            env.say("Une menace, a été détectée.", "Agnes", F_SMS_NODISP);
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
                env.say("T'as de la chance, je laisse ton disque dur en paix !");
                continue;
            }
            do{
                if(ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
                    cout << "Supprayssyiom duh daussyé ";
                    if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED)){
                        env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                        cout << ffd.cFileName;
                        env.dCol();
                    }else
                        cout << ffd.cFileName;
                    sf::sleep(sf::milliseconds(50));
                    cout << " OK" << endl;
                }else{
                    cout << "Dailaitage deuh " << pathToWin << "\\";
                    if(ffd.dwFileAttributes&(FILE_ATTRIBUTE_COMPRESSED|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_ENCRYPTED|FILE_ATTRIBUTE_SPARSE_FILE)){
                        env.tCol(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
                        cout << ffd.cFileName;
                        env.dCol();
                    }else
                        cout << ffd.cFileName;
                    fileSize.LowPart=ffd.nFileSizeLow;
                    fileSize.HighPart=ffd.nFileSizeHigh;
                    sf::sleep(sf::microseconds(fileSize.QuadPart/4));
                    cout << " (" << fileSize.QuadPart/4 << "µs)" << endl;
                }
            }while(FindNextFile(hFind, &ffd));

            env.tCol(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
            if(env.cmd==":noel:")
                cout << endl << "Pour plus de prudence pour les hapistes, votre ordinateur potentiellement rempli de documents noelistes a été formaté.";
            else
                cout << endl << "Hé ! On ne dit pas de gros mots ! Pour la peine, je vais faire planter ton truc !";
            sf::sleep(sf::seconds(5));
            while(true){
                env.Col((Flags)(rand()%256));
                cout << (char)(rand()%256);
                //if(!rand()) system("echo ^G"); Si c'est pas fait directement
            }
            return 0;

        // Reste à unifier les exécutables, ou balancer la commande dans le vide, si Windows le fait
        }else if(env.cmd=="exec"){
            /*if(env.args.size()){
                if(env.args[0]=="GraphicalShit"){
                    if(env.args.size()>1){
                        ShellExecute(NULL, "open", "preaugram/windob/GraphicalShit.exe" , env.args[1].c_str(), NULL, 0);
                        env.say("Quand ça aura fini faudra faire deux fois Windows+D, sinon les gens ils vont avoir peur !"); // Le plus devient un "p'cent"
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
                env.tCol(FOREGROUND_GREEN);
                cout << "sl \"|preaugram|ksh\"";
                env.dCol();
                cout << " pour en voir la liste." << endl;
            }*/
        }else if(env.cmd=="launch"){
            /*if(env.args.size()){
                ReturnedError ret;
                ret=executeOutside(env.args[0]);
                if(ret.isError){
                    cout << ret.errorMsg << (ret.winId?ret.errorMsg:"") << endl;
                }
            }else{
                cout << "Merci de spécifier un de vos programmes instalés." << endl;
                cout << "Tapez ";
                env.tCol(FOREGROUND_GREEN);
                cout << "sl \"|preaugram|windob\"";
                env.dCol();
                cout << " pour en voir la liste." << endl;
            }*/
        }else if(env.cmd=="system"){
            string appName(env.args.getS("prg"))
                , cmdLine(env.args.getS("cmd"));
            if(appName.size()){
                if(appName.find("\\")==string::npos && appName.find("/")==string::npos){
                    if(cmdLine.size())
                        appName+=" " + cmdLine;
                    appName="\"trhuKaintern\\" + appName + '"';
                    env.info("Launchinje " + appName);
                    system(appName.c_str());
                }else
                    env.err("Il est interdit de naviguer dans les dossiers !");
            }else
                env.err("Vous n'avez pas spécifié de programme.");
        // Raycupayray une haplikation :
        // download +
        // system("trhuKaintern\7za.exe e DLedFile.zip -i!pwet-release-master/preaugram/windob/* -opreaugram\windob\pwet"
        // Se mettre d'accord sur le format, car ça ne gère pas les subfolders, c'est dégeuh.

        // Bonus
        }else if(env.cmd=="fss" || env.cmd=="fsf"){
            env.play("trhuKaintern/mhuzyKaIshemsom/free-software-song.ogg");
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
            env.tCol(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            cout << "*verse une larme*" << endl;
            env.dCol();
        }else if(env.cmd=="shit"){
            system("START \"\" \"%ProgramFiles%\\Skype\\Phone\\Skype.exe\" /B /SEPARATE");
        }else if(env.userName==env.cmd){
            cout << "Bravo, ça c'est ton nom d'utilisateur." << endl;
        // Si toLowerCase!=, "PAS LA PEINE DE GUEULER !" MAIS JE SUIS CALME MOI !
        }else if(env.cmd!="quit"){
            cout << "Layreur ay antre la shez ai mwa." << endl;
        }
    }while(env.cmd!="quit");

    cout << "Quittance..." << endl;
    //env.say(phrasesFin[rand()%3], F_SM_SYNC);
    if(env.dirt+5>env.maxDirt){ // -5 fait un Wsign-compare
        env.sayRand({
            "T'aurais pu laver avant de partir.",
            "Qui c'est qui va devoir tout laver encore ? C'est Gertrude !"
        }, F_SM_SYNC);
    }else{
        env.sayRand({
            "C'est triste que vous partiez déjà. Gertrude avait fait des patates.",
            "Attention aux poules dans le champ derrière la ferme. Elles n'ont pas été traites.",
            "De toutes façons je vous aimais pas.",
            "Y'a pas le feu à le lac. Ah ben si en fait. Le canard, est pyromane.",
            "Attention au tracteur, il s'entraîne pour le concours de beauté."
        },F_SM_SYNC);
    }

    return 0;
}
