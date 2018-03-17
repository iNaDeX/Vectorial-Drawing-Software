#include "projet.h"

/// Constructeur
t_point * point_creer(int x, int y)
{
    // Pointeur vers la nouvelle instance à créer
    t_point *p;

    // Allocation de l'instance (UNE instance)
    p = (t_point *)malloc(1*sizeof(t_point));

    // Initialisation des attributs de l'instance
    /// INDISPENSABLE : tout initialiser
    /// (à 0 ou NULL ou "" en l'absence de paramètres...)
    p->x = x;
    p->y = y;

    // Retourner l'instance à l'appelant
    return p;
}

/// Destructeur
void point_detruire(t_point *p)
{
    // Libération de la mémoire allouée
    /// ATTENTION autant de free ici
    /// que de malloc dans le constructeur

    free(p);
}

/// Constructeur par copie
t_point * point_copier(t_point *p)
{
    // Pointeur vers la nouvelle instance duplicata
    t_point *pdup;


    // Allouer duplicata : eviter de refaire usage de malloc
    // utiliser le constructeur déjà disponible...
    pdup = point_creer(p->x, p->y);

    /// Ici le constructeur nous a permis de faire
    /// directement un nouvel objet avec les bonnes
    /// valeurs initiales : mais il est souvent nécessaire
    /// d'ajouter des étapes de copie des données
    /// de l'original vers le duplicata !

    // Retourner l'instance dupliquée à l'appelant
    return pdup;
}

/// Saisie de point
void point_saisir(t_point *p)
{
    printf("Abscisse : ");
    scanf("%f", &p->x);
    printf("Ordonnee : ");
    scanf("%f", &p->y);
}

/// Affichage de point
void point_afficher(t_point *p)
{
    printf("(%f, %f)\n", p->x, p->y);
}

/// Translation selon le vecteur vx vy
/// ( exemple de modification de l'objet )
void point_translater(t_point *p, int vx, int vy)
{
    p->x = p->x + vx;
    p->y = p->y + vy;
}

/// Distance entre 2 points
/// ( exemple de fonction qui utilise 2 instances )
int point_distance(t_point *p1, t_point *p2)
{
    // Coord. du vecteur p1 p2
    int vx, vy;

    // Calcul du vecteur p1 p2
    vx = p2->x - p1->x;
    vy = p2->y - p1->y;

    // Retourner la norme du vecteur
    return sqrt( vx*vx + vy*vy );
}
