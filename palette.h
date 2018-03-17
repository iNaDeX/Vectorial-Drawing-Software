#ifndef PALETTE_H_INCLUDED
#define PALETTE_H_INCLUDED

#include "compalleg.h"

/// Géométrie de la palette

// ATTENTION : pour toute modification du nombre de cases,
// modifier également l'initialisation de palette dans palette.c
// Nombre de cases en largeur matrice couleur
#define PAL_LC 8
// Nombre de cases en hauteur matrice couleur
#define PAL_HC 8

// Taille des cases matrice (en pixel)
#define PAL_TC 20

// Hauteur barre pour drag&drop (en nombre de cases)
#define PAL_HCDD 1

// Hauteur boite de couleur sélectionnée (en nombre de cases)
#define PAL_HCBS 3

/// Couleurs de la palette
#define PAL_BORDS_COUL makecol(0,0,0)
#define PAL_DD_COUL makecol(180,180,200)

/// Structure regroupant les infos de gestion de palette

typedef struct palette {
    int xo, yo;                 // xo yo position de la palette
    int couleur;                // couleur sélectionnée
    int matcol[PAL_HC][PAL_LC]; // matrice des couleurs
    int capture;                // booléen "la souris est capturée pour drag&drop"
    int xcap, ycap;             // coordonnées de capture (repère palette)
    int action_couleur;
} t_palette;


/// Une variable globale palette : LA palette

extern t_palette palette;


/// Prototypes

// Renvoie la couleur actuellement sélectionnée
int palette_recup_couleur();

// A appeler en début de la boucle principale, juste après appel rafraichir_clavier_souris
void palette_gerer();

// A appeler en fin de la boucle principale, juste avant appel afficher_page
void palette_dessiner();


#endif // PALETTE_H_INCLUDED
