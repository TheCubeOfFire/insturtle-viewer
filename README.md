# Description
Un programme qui affiche le résultat de l'interprétation du langage obtenu après avoir interprété le langage Turtle, un langage inventé dans le cadre du projet d'analyse syntaxique à l'Université de Franche-Comté.
Ce programme vise à être un clone open-source du programme turtle-viewer, fourni avec la description du projet par Julien Bernard. Le nom du programme vient de la contraction de « instant » et du nom du programme originel : il dessine instantanément ceque turtle-viewer affiche pas à pas. Ce programme n'a pas pour objectif d'être plus performant, il propose une version différente du résultat.
Le code source est très fortement inspiré de l'exemple d'utilisation du [Gamedev Framework](http://gamedevframework.github.io/)

# Installation
Vous aurez besoin :
* du Gamedev Framework, ainsi que de ses dépendances
* de CMake
* d'un compilateur C++14
* et, évidemment, de Git

Pour compiler, clonez ce dépôt et placez-vous dans le dossier créé. Ensuite, utilisez par exemple ces commandes avec Bash :
```
mkdir build
cd build
cmake ..
make
```

# Utilisation
Lancez le programme résultant de la compilation, en lui fournissant les commandes à exécuter sur l'entrée standard. Par exemple, si le fichier `turtle.txt` contient vos commandes, vous pouvez faire :
```
./insturtle-viewer < turtle.txt
```

Une fois le résultat affiché, vous pouvez changer l'épaisseur des traits avec les flèches du clavier.
