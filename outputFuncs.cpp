#include "outputFuncs.hpp"

void dispHelp(Env &env){
    env.helpnxt=HelpNext::None;
    setCCol(FOREGROUND_GREEN | FOREGROUND_INTENSITY | env.bgCol);
    cout << "L'aide trop utile de Gérard :" << endl;
    setCCol(env.txtCol | env.bgCol);
    cout << "Liste des commandes :" << endl << "Les astérisques vous forcent à chercher ce qu'elles remplacent, soit pour le fun, soit parce que c'est un gros mot." << endl;
    cout << "Commande   | Significiance" << endl;
    cout << "cwd        | change le dossier courant (les / ou \\ sont à remplacer par |)" << endl;
    cout << "ls         | liste les fichiers du dossier" << endl;
    cout << "sl         | appelle le train à vapeur (ou c'est peut-être l'inverse avec ls...)" << endl;
    cout << "s***p      | affiche le livre d'or" << endl;
    cout << "kouleur    | permet de changer la couleur du texte" << endl;
    cout << "makeclean  | nettoie les saletés que vous avez foutues sur l'écran" << endl;
    cout << "reboot     | fait disparaître tous les soucis" << endl;
    cout << "*acist     | manifeste votre haine envers l'accent africain" << endl;
    cout << "cowsay     | parce que les vaches ont droit à leur temps de parole !" << endl;
    cout << "tlecteur   | écoutez les histoires pationnantes de Gérard" << endl;
    cout << ":hap:      | promeut le Hapisme" << endl;
    cout << ":n**l:     | c'est interdit, merci" << endl;
    cout << "*********  | entreprise ayant permis le KikooShell avec le Ouin32" << endl;
    cout << "quit       | quittez cette horreur élégamment" << endl;
    cout << env.userName << " | vous rappelle que l'égocentrisme, c'est mal" << endl;

    cout << endl << "Programmes internes/externes :" << endl;
    cout << "exec                                           | lance un programme du dossier |preaugram|ksh au sein du KSh" << endl;
    cout << "kshprog                                        | affiche l'aide de tous les programmes pour exec" << endl;
    cout << "launch                                         | lance un programme du dossier |preaugram|windob dans Windows" << endl;
    cout << "loseprog                                       | affiche l'aide de tous les programmes pour launch" << endl;
    cout << "raycupayraYunEhapplicassyoMdeupwYaimternait    | télécharge l'application spécifiée depuis internet" << endl;
    cout << "yAkwAkoMtruKkoul                               | télécharge et affiche la liste des applications récupérables avec raycupayraYunEhapplicassyoMdeupwYaimternait" << endl;
    //cout << "GraphicalShit  | donnez du style à votre écran" << endl;
    //cout << "PlaySound      | petit utilitaire pour cracher des sons périodiques"
    // cout << "FarmDraw       | reconstruisez la ferme de Gérard avec des poutres" << endl;

    cout << endl << "La légende dit que les commandes en cours d'élaboration ne sont pas répertoriées. C'est franchement pas crédible." << endl;
    //cout << "| " << endl;

}
