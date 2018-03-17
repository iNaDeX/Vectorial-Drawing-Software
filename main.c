#include "projet.h"

/*
Fonctionnalit�s bonus mis en place (liste non exhaustive):

Titre de la fen�tre (adapt� au fichier charg�)
Menu
Rotation
Lissage
La possibilit� de "Couper" (ctrl+X)
Possibilit� d'ajouter � la selection existante en appuyant sur shift.
Cadre de s�l�ction ajust� � chaque primitive selectionn�e
D�placer la selection avec les touches flechees
Changer couleur des primitives selectionn�s
Supprimer les primitives selectionn�s
chargement/sauvegarde avec explorateur de fichiers
Modifier taille d'une primitive selectionn�e
Selection par CTRL-Clic Gauche dans une primitive (en plus de la selection classique)
Travail sur le .exe : Icone sp�ciale + Nom
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

