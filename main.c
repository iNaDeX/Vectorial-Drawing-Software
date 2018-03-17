#include "projet.h"

/*
Fonctionnalités bonus mis en place (liste non exhaustive):

Titre de la fenêtre (adapté au fichier chargé)
Menu
Rotation
Lissage
La possibilité de "Couper" (ctrl+X)
Possibilité d'ajouter à la selection existante en appuyant sur shift.
Cadre de séléction ajusté à chaque primitive selectionnée
Déplacer la selection avec les touches flechees
Changer couleur des primitives selectionnés
Supprimer les primitives selectionnés
chargement/sauvegarde avec explorateur de fichiers
Modifier taille d'une primitive selectionnée
Selection par CTRL-Clic Gauche dans une primitive (en plus de la selection classique)
Travail sur le .exe : Icone spéciale + Nom
*/

int main()
{
    initialiser_allegro();

    t_graphMenu graph;

    charger_menu(&graph);
    afficher_menu(graph);

    memoire_alloc_bilan();

    liberer_menu(&graph);
    fermer_allegro();
    return 0;
}
END_OF_MAIN();

