#include "projet.h"

/// Définition et initialisation de la variable globale palette
// Les couleurs sont données en hexadécimal (préfixe 0x) avec un octet pour R, V et B
// Exemple : 0XABCDEF correspond à AB pour rouge, CD pour vert, EF pour bleu
t_palette palette =
{
    0, 0,       // position initiale de la palette
    0x000000,   // couleur initiale sélectionnée

                // matrice des couleurs :
    {
        { 0X000000, 0X0000AA, 0X00AA00, 0X00AAAA, 0XAA0000, 0XAA00AA, 0XAAAA00, 0XAAAAAA },
        { 0X000055, 0X0000FF, 0X00AA55, 0X00AAFF, 0XAA0055, 0XAA00FF, 0XAAAA55, 0XAAAAFF },
        { 0X005500, 0X0055AA, 0X00FF00, 0X00FFAA, 0XAA5500, 0XAA55AA, 0XAAFF00, 0XAAFFAA },
        { 0X005555, 0X0055FF, 0X00FF55, 0X00FFFF, 0XAA5555, 0XAA55FF, 0XAAFF55, 0XAAFFFF },
        { 0X550000, 0X5500AA, 0X55AA00, 0X55AAAA, 0XFF0000, 0XFF00AA, 0XFFAA00, 0XFFAAAA },
        { 0X550055, 0X5500FF, 0X55AA55, 0X55AAFF, 0XFF0055, 0XFF00FF, 0XFFAA55, 0XFFAAFF },
        { 0X555500, 0X5555AA, 0X55FF00, 0X55FFAA, 0XFF5500, 0XFF55AA, 0XFFFF00, 0XFFFFAA },
        { 0X555555, 0X5555FF, 0X55FF55, 0X55FFFF, 0XFF5555, 0XFF55FF, 0XFFFF55, 0XFFFFFF }
    }
    ,0,0,0,0
};

// Renvoie la couleur actuellement sélectionnée
int palette_recup_couleur()
{
    return palette.couleur;
}

// A appeler en début de la boucle principale, juste après appel rafraichir_clavier_souris
void palette_gerer()
{
    palette.action_couleur = 0;

    // On enregistre la position souris pour ne pas risquer de disparité
    // (les variables mouse_x et mouse_y peuvent changer à tout moment !)
    // On en profite pour changer de repère (origine et échelle) !
    // On considère l'origine en haut à gauche de la partie matrice
    int xc = (mouse_x-palette.xo)/PAL_TC;
    int yc = (mouse_y-palette.yo)/PAL_TC - PAL_HCDD;

    /// Gestion de la sélection d'une couleur
    // Si clic gauche dans la zone matrice ...
    if ( bouton=='g' && xc>=0 && xc<PAL_LC && yc>=0 && yc<PAL_HC )
    {
        // Enregistrer la couleur correspondante (sélection)
        palette.couleur = palette.matcol[yc][xc];
        palette.action_couleur = 1;
    }


    /// Gestion du drag&drop
    // Si clic gauche dans la zone barre drag&drop, capturer !
    if ( mouse_click&1 && xc>=0 && xc<PAL_LC && yc>=-PAL_HCDD && yc<0 )
    {
        palette.capture = 1;
        palette.xcap = mouse_x-palette.xo;
        palette.ycap = mouse_y-palette.yo;
    }

    // Si la souris est capturée et relâchement clic gauche, relâcher capture !
    if ( palette.capture && mouse_unclick&1 )
        palette.capture = 0;

    // Si la souris est capturée...
    if ( palette.capture )
    {
        // Suivre la position de la souris (au même niveau relatif que la capture)
        palette.xo = mouse_x-palette.xcap;
        palette.yo = mouse_y-palette.ycap;

        // L'alternative suivante pour entraîner avec le déplacement souris est possible
        // mais pose des problèmes sur les bords (testez pour comprendre)
        // palette.xo = palette.xo + mouse_depx;
        // palette.yo = palette.yo + mouse_depy;

        // Contrôle des bords
        if ( palette.xo<0 ) palette.xo = 0;
        if ( palette.xo>FENETRE_LARGEUR-PAL_LC*PAL_TC ) palette.xo = FENETRE_LARGEUR-PAL_LC*PAL_TC;
        if ( palette.yo<0 ) palette.yo = 0;
        if ( palette.yo>FENETRE_HAUTEUR-PAL_HCDD*PAL_TC ) palette.yo = FENETRE_HAUTEUR-PAL_HCDD*PAL_TC;
    }

    /// Dans la zone palette, neutralisation du clic pour les autres éléments de l'interface
    // Si clic quelconque dans la zone palette
    if ( bouton!='\0' && xc>=0 && xc<PAL_LC && yc>=-PAL_HCDD && yc<PAL_HC+PAL_HCBS )
    {
        // "Absorber" le clic pour l'ignorer dans la suite de la boucle interactive
        bouton = '\0';
        mouse_click = 0;
    }
}

// A appeler en fin de la boucle principale, juste avant appel afficher_page
void palette_dessiner()
{
    int xc, yc; // En cases
    int x, y;   // En pixels
    int col;    // Couleur de la case

    // Afficher la barre pour drag&drop
    x = palette.xo;
    y = palette.yo;
    rectfill(page, x, y, x+PAL_LC*PAL_TC, y+PAL_HCDD*PAL_TC, PAL_DD_COUL);
    rect(page, x, y, x+PAL_LC*PAL_TC, y+PAL_HCDD*PAL_TC, PAL_BORDS_COUL);

    // Parcourir et afficher (sur buffer) les cases de la matrice
    for (yc=0; yc<PAL_HC; yc++)
        for (xc=0; xc<PAL_LC; xc++)
        {
            col = palette.matcol[yc][xc];
            x = palette.xo + xc*PAL_TC;
            y = palette.yo + (yc+PAL_HCDD)*PAL_TC;
            rectfill(page, x, y, x+PAL_TC, y+PAL_TC, col);
            rect(page, x, y, x+PAL_TC, y+PAL_TC, PAL_BORDS_COUL);
        }

    // Afficher couleur sélectionnée en dessous de la matrice
    x = palette.xo;
    y = palette.yo + (PAL_HC+PAL_HCDD)*PAL_TC;
    rectfill(page, x, y, x+PAL_LC*PAL_TC, y+PAL_HCBS*PAL_TC, palette.couleur);
    rect(page, x, y, x+PAL_LC*PAL_TC, y+PAL_HCBS*PAL_TC, PAL_BORDS_COUL);
}
