# KikooShell
##Pr�sentations
Ceci est une parodie d'interface Bash pour Windows, rassemblant les programmes Kikoo.
## Utilisation
Une fois le dossier bin/Release t�l�charg�, il suffit de lancer le raccourci pour profiter du programme.
Pour la petit histoire, le raccourci permet de configurer certains param�tres tels que la police que je n'ai pas su faire pour Windows XP.
## Ajouter une commande
Pour ajouter vos propres commandes, il faut se rendre dans le main.cpp. Il y a un endroit o� vous pouvez voir if(env.cmd=="..."). Ins�rez vos commandes avant n'importe quel else if.
Les arguments sont stock�s dans env.args.
Merci de faire en sorte que l'ex�cutable soit toujours � jour, et de ne pas toucher au raccourci, sauf pour am�lioration bien s�r.
