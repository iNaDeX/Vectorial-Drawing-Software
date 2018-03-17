#ifndef DESSIN_H_INCLUDED
#define DESSIN_H_INCLUDED

typedef struct maillon
{
    t_primitive* prim;
    struct maillon* p_suiv;
    struct maillon* p_prec;
}t_maillon;

typedef struct dessin
{
    int longueur;
    t_maillon* p_tete;
    t_maillon* p_queue;
}t_dessin;

// Lisse les primitives d'un dessin
void dessin_lisser(t_dessin* d);

// modifie la taille des primitives du dessin
void dessin_modif_taille(t_dessin* d, float k);

// rotationne les primitives du dessin
void dessin_rotation(t_dessin* d, float alpha);

// supprime les primitives selectionnées
void dessin_supprimer_primitives_selectionnees(t_dessin *d);

// met à 1 le champ selected des primitives du dessin
void dessin_changer_champ_selected(t_dessin* d, int selected);

// change la couleur de toutes les primitives du dessin
void dessin_changer_couleur(t_dessin* d,int couleur);

// copie depart dans arrivee
void dessin_copier(t_dessin* depart,t_dessin* arrivee);

// translate toutes les primitives du dessin
void dessin_translater(t_dessin* d,int dx,int dy);

// déréférence tout un dessin
void dessin_dereferencer(t_dessin *d);

// déréférence la dernière primitive du dessin
void dessin_dereferencer_derniere_primitive(t_dessin *d);

// affiche un cadre entourant chaque primitive d'un dessin donné
void dessin_affich_cadre(t_dessin* d);

// Constructeur : alloue une instance de dessin initialement vide : 0 primitive dedans
t_dessin * dessin_creer();

// Détruit les primitives du dessin donné en paramètre, le dessin n'est pas détruit : 0 primitive dedans
void dessin_vider(t_dessin *d);

// Détruit les primitives du dessin, détruit le dessin
void dessin_detruire(t_dessin *d);

// Ajoute une primitive p (déjà créée) au dessin d
void dessin_ajout_primitive(t_dessin *d, t_primitive *p);

// Enlève et détruit la dernière primitive ajoutée. Facultatif : permet de faire Undo dans l'éditeur
void dessin_suppression_derniere_primitive(t_dessin *d);

// Dessine l'ensemble des primitives contenues dans le dessin d sur le buffer (page)
void dessin_dessiner_page(t_dessin *d);

// Ouvre en écriture le fichier dont le nom est passé en paramètre, sauve toutes les primitives
void dessin_sauver(t_dessin *d, char *nom_fichier);

// Ouvre en lecture le fichier, créer un nouveau dessin et charge/ajoute toutes les primitives
t_dessin * dessin_charger(char *nom_fichier);


#endif // DESSIN_H_INCLUDED
