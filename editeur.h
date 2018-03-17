#ifndef EDITEUR_H_INCLUDED
#define EDITEUR_H_INCLUDED

#define MODE_MANIP 0
#define MODE_AJOUT 1

typedef struct editeur
{
    int mode;
    int etape;
    int quitter;
    t_dessin* document;
    t_dessin* selec;
    t_dessin* presse_papier;
    t_cadre* cadre;
    t_primitive* prim_temp;
}t_editeur;

// D�truit l'�diteur
void editeur_detruire(t_editeur* ed);

// Ajoute les primitives qui sont dans le cadre � la selection
void editeur_remplir_selection(t_editeur* ed);

// Cr�e et initialise une instance d'�diteur
t_editeur* editeur_creer_initialiser(int nouveauOuNon);

// Affiche l'�diteur
void editeur_afficher(t_editeur* ed);

// Affiche les informations li�es � la selection
void editeur_afficher_selec(t_editeur* ed);

// Affiche les informations li�es au mode ajout
void editeur_afficher_mode_ajout(t_editeur* ed);

// Affiche les informations li�es au mode manip
void editeur_afficher_mode_manip(t_editeur* ed);

// G�re la sortie du mode manip
void editeur_sortir_mode_manip(t_editeur* ed);

// G�re la sortie du mode ajout
void editeur_sortir_mode_ajout(t_editeur* ed);

// G�re l'�diteur
void editeur_gerer(t_editeur* ed);

// G�re la sortie de l'�diteur
void editeur_gerer_quitter(t_editeur* ed);

// G�re le document
void editeur_gerer_document(t_editeur* ed);

// G�re le mode d'utilisation
void editeur_gerer_modes(t_editeur* ed);

// G�re le mode ajout
void editeur_gerer_mode_ajout(t_editeur* ed);

// G�re le mode manip
void editeur_gerer_mode_manip(t_editeur* ed);

// G�re la selection
void editeur_gerer_mode_manip_selectionner(t_editeur* ed);

// G�re la selection par clic dans polygone
void editeur_gerer_mode_manip_selectionner_clic(t_editeur* ed);

// G�re la translation
void editeur_gerer_mode_manip_deplacer(t_editeur *ed);

// G�re couper,copier,coller, supprimer..
void editeur_gerer_mode_manip_ccc(t_editeur *ed);

// G�re le changement de couleur
void editeur_gerer_mode_manip_colorer(t_editeur* ed);

// G�re la rotation
void editeur_gerer_mode_manip_rotation(t_editeur *ed);

// G�re le changement de taille
void editeur_gerer_mode_manip_taille(t_editeur *ed);

// G�re le lissage
void editeur_gerer_mode_manip_lisser(t_editeur* ed);

#endif // EDITEUR_H_INCLUDED
