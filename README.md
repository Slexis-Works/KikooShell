# KikooShell alias KSh
##Pr�sentations
Ceci est une parodie d'interface Bash pour Windows, rassemblant les programmes Kikoo.
C'est plus pr�cis�ment la synergie de tas de conneries faites au cours du temps. Pour cette raison, **merci de faire attention au degr� de merdisme incroyablement �lev� de cette chose**.
## Utilisation
Une fois le dossier bin/Release t�l�charg�, il **faut** cr�er un raccourci de bin/Release/root/trhuKaintern/KikooShell.exe dans un endroit plus pratique.
Faites un clic droit sur ce raccourci, et modifiez le champ "D�marrer dans" de sorte � ce que le dossier courant soit root/. Il faut �galement changer la police, celle par d�faut en g�n�ral ne supportant pas les caract�res �tendus. Arrangez vous ausssi pour avoir la fen�tre la plus grande possible. Pour les non-habitu�s : il faut aller dans l'onglet **Disposition**, mettre la fen�tre � l'origine (0;0) et jouer sur la taille de la fen�tre pour que ce qui soit affich� � gauche aie la taille maximale, sans mettre de scroll horizontal.
## Ajouter une commande
Pour ajouter vos propres commandes, il faut se rendre dans le main.cpp. Il y a un endroit o� vous pouvez voir if(env.cmd=="..."). Ins�rez vos commandes avant n'importe quel else if.
Les arguments sont stock�s dans env.args.
Merci de faire en sorte que l'ex�cutable soit toujours � jour, et de ne pas toucher au raccourci, sauf pour am�lioration bien s�r.
## Remerciements et cr�dits
Merci � moi d'avoir fait ce projet.
Merci � [Voxygen](http://voxygen.fr) de proposer une synth�se vocale en exemple.
Merci � la [SFML](http://www.sfml-dev.org) de me permettre d'utiliser cette synth�se vocale.
Je remercie pas [fayedu39](https://github.com/fayedu39) et [Asph�hyre](https://github.com/Asphahyre) de m'avoir donn� des id�es parce que �a me donne du boulot en plus.
