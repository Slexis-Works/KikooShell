# KikooShell
##Présentations
Ceci est une parodie d'interface Bash pour Windows, rassemblant les programmes Kikoo.
## Utilisation
Une fois le dossier bin/Release téléchargé, il suffit de lancer le raccourci pour profiter du programme.
Pour la petit histoire, le raccourci permet de configurer certains paramètres tels que la police que je n'ai pas su faire pour Windows XP.
## Ajouter une commande
Pour ajouter vos propres commandes, il faut se rendre dans le main.cpp. Il y a un endroit où vous pouvez voir if(env.cmd=="..."). Insérez vos commandes avant n'importe quel else if.
Les arguments sont stockés dans env.args.
Merci de faire en sorte que l'exécutable soit toujours à jour, et de ne pas toucher au raccourci, sauf pour amélioration bien sûr.
