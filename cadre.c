#include "projet.h"

// Crée un cadre
t_cadre* cadre_creer()
{
    t_cadre* c;
    c = (t_cadre*) malloc(1*sizeof(t_cadre));

    return c;
}

//  Dessine un cadre
void cadre_dessiner(t_cadre* c)
{
    rect(page,c->x1,c->y1,c->x2,c->y2,makecol(0,0,255));
}

// Libère un cadre
void cadre_detruire(t_cadre* c)
{
    if (c != NULL)
        free(c);
}
