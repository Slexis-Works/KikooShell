# KikooShell alias KSh
##Présentations
Ceci est une parodie d'interface Bash pour Windows, rassemblant les programmes Kikoo.
C'est plus précisément la synergie de tas de conneries faites au cours du temps. Pour cette raison, **merci de faire attention au degré de merdisme incroyablement élevé de cette chose**.
## Utilisation
Une fois le dossier bin/Release téléchargé, il **faut** créer un raccourci de bin/Release/root/trhuKaintern/KikooShell.exe dans un endroit plus pratique.
Faites un clic droit sur ce raccourci, et modifiez le champ "Démarrer dans" de sorte à ce que le dossier courant soit root/. Il faut également changer la police, celle par défaut en général ne supportant pas les caractères étendus. Arrangez vous ausssi pour avoir la fenêtre la plus grande possible. Pour les non-habitués : il faut aller dans l'onglet **Disposition**, mettre la fenêtre à l'origine (0;0) et jouer sur la taille de la fenêtre pour que ce qui soit affiché à gauche aie la taille maximale, sans mettre de scroll horizontal.
## Ajouter une commande
Pour ajouter vos propres commandes, il faut se rendre dans le main.cpp. Il y a un endroit où vous pouvez voir if(env.cmd=="..."). Insérez vos commandes avant n'importe quel else if.
Les arguments sont stockés dans env.args.
Merci de faire en sorte que l'exécutable soit toujours à jour, et de ne pas toucher au raccourci, sauf pour amélioration bien sûr.
## Remerciements et crédits
Merci à moi d'avoir fait ce projet.
Merci à [Voxygen](http://voxygen.fr) de proposer une synthèse vocale en exemple.
Merci à la [SFML](http://www.sfml-dev.org) de me permettre d'utiliser cette synthèse vocale.
Je remercie pas [fayedu39](https://github.com/fayedu39) et [Asphähyre](https://github.com/Asphahyre) de m'avoir donné des idées parce que ça me donne du boulot en plus.
