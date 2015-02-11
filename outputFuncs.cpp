#include "outputFuncs.hpp"

void dispHelp(Env &env){
    env.helpnxt=HelpNext::None;
    setCCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY | env.bgCol);
    cout << "L'aide trop utile de G�rard :" << endl;
    setCCol(env.txtCol | env.bgCol);
    cout << "Liste des commandes :" << endl << "Les ast�risques vous forcent � chercher ce qu'elles remplacent, soit pour le fun, soit parce que c'est un gros mot." << endl;
    cout << "Commande   | Significiance" << endl;
    cout << "cwd        | change le dossier courant (les / ou \\ sont remplac�s par |)" << endl;
    cout << "ls         | liste les fichiers du dossier" << endl;
    cout << "sl         | appelle le train � vapeur (ou c'est peut-�tre l'inverse avec ls...)" << endl;
    cout << "s***p      | affiche le livre d'or" << endl;
    cout << "kouleur    | permet de changer la couleur du texte" << endl;
    cout << "makeclean  | nettoie les salet�s que vous avez foutues sur l'�cran" << endl;
    cout << "reboot     | fait dispara�tre tous les soucis" << endl;
    cout << "*acist     | manifeste votre haine envers l'accent africain" << endl;
    cout << "cowsay     | parce que les vaches ont droit � leur temps de parole !" << endl;
    cout << "tlecteur   | �coutez les histoires pationnantes de G�rard" << endl;
    cout << ":hap:      | promeut le Hapisme" << endl;
    cout << ":n**l:     | c'est interdit, merci" << endl;
    cout << "*********  | entreprise ayant permis le KikooShell avec le Ouin32" << endl;
    cout << "quit       | quittez cette horreur �l�gamment" << endl;
    cout << env.userName << " | vous rappelle que l'�gocentrisme, c'est mal" << endl;

    cout << endl << "Programmes :" << endl;
    cout << "GraphicalShit  | donnez du style � votre �cran" << endl;

    cout << endl << "La l�gende dit que les commandes en cours d'�laboration ne sont pas r�pertori�es. C'est franchement pas cr�dible." << endl;
    // cout << "FarmDraw       | reconstruisez la ferme de G�rard avec des poutres" << endl;
    //cout << "| " << endl;

}
