Bonjour,
Voici le projet de la rainbow table de Jérôme De Groote (42503) et Léopold Mols(53212).

La fonction main se situe dans sha256-main.cpp. On y trouve l'appel generateAllLines(); qui va générer la Rainbow Table et l'appel findAllPsw(); qui va déchiffrer les mots de passe et les mettre dans un fichier texte.
De base, la fonction de déchiffrement se lance après la fonction de création de la RT.
Si vous voulez les exécuter séparement ces méthodes vous pouvez commenter l'un et puis l'autre appel de fonction.

Dans le répertoire du projet doit se trouver le fichier vide ResultTable.txt et le fichier vide HashToUncypher.txt
Lors de la création de la RT, un nouveau fichier sera créé : RainbowTable.txt.
Pour le décryptage des mots de passe, il faut que vous mettiez les hashs à déchiffrer ligne par ligne dans le fichier texte HashToUncypher.txt, et ce, avant d'éxecuter le code de déchiffrement.
Lorsque l'éxecution sera finie, vous trouverez les mots de passe déchiffrés ligne par ligne dans ResultTable.txt.

Bien à vous.



Comment l'exécuter dans le terminal ?

