#ifndef CADRE_H_INCLUDED
#define CADRE_H_INCLUDED

typedef struct cadre
{
    int x1;
    int y1;
    int x2;
    int y2;
}t_cadre;

// Cr�e un cadre
t_cadre* cadre_creer();

//  Dessine un cadre
void cadre_dessiner(t_cadre* c);

// Lib�re un cadre
void cadre_detruire(t_cadre* c);

#endif // CADRE_H_INCLUDED
