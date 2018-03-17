#ifndef CADRE_H_INCLUDED
#define CADRE_H_INCLUDED

typedef struct cadre
{
    int x1;
    int y1;
    int x2;
    int y2;
}t_cadre;

// Crée un cadre
t_cadre* cadre_creer();

//  Dessine un cadre
void cadre_dessiner(t_cadre* c);

// Libère un cadre
void cadre_detruire(t_cadre* c);

#endif // CADRE_H_INCLUDED
