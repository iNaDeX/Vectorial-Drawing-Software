#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

/// Structure principale du module

typedef struct point
{
    float x;
    float y;
} t_point;

typedef struct point_int
{
    int x;
    int y;
}t_point_int;

/// Prototypes des sous-programmes

// Constructeur
t_point * point_creer(int x, int y);

// Destructeur
void point_detruire(t_point *p);

// Constructeur par copie
t_point * point_copier(t_point *p);

// Saisie de point
void point_saisir(t_point *p);

// Affichage de point
void point_afficher(t_point *p);

// Translation selon le vecteur vx vy
// ( exemple de modification de l'objet )
void point_translater(t_point *p, int vx, int vy);

// Distance entre 2 points
// ( exemple de fonction qui utilise 2 instances )
int point_distance(t_point *p1, t_point *p2);

#endif // POINT_H_INCLUDED
