#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define NB_BOUTONS 6

typedef struct graphMenu // on d�clarera une instance de t_graphMenu dans le main
{
    BITMAP* cursor;
    BITMAP* fond;
    BITMAP* contenu_aide;
    BITMAP* contenu_a_propos;

    BITMAP* img_boutons_on[NB_BOUTONS];
    BITMAP* img_boutons_off[NB_BOUTONS];

    int boutons_x[NB_BOUTONS];
    int boutons_y[NB_BOUTONS];

}t_graphMenu;

// lib�re les bitmaps du menu, � la fin du programme.
void liberer_menu(t_graphMenu* graph);

// charge les informations du menu
void charger_menu(t_graphMenu* graph);

// affiche le menu
void afficher_menu(t_graphMenu graph);

// boucle de jeu
void boucle_jeu(int nouveauOuNon);

// affichage du sous-menu aide
void aff_aide(t_graphMenu graph);

// affichage du sous-menu a propos
void aff_a_propos(t_graphMenu graph);

#endif // MENU_H_INCLUDED
