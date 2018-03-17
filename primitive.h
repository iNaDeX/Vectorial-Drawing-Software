#ifndef PRIMITIVE_H_INCLUDED
#define PRIMITIVE_H_INCLUDED

#define NB_POINTS_INIT 10
#define PRECISION 10
#define RAIDEUR 0.5

#include "cadre.h"

typedef struct primitive
{
    t_point* tab;
    int nb_points_max;
    int nb_points_actuel;
    int couleur;
    int selected;
}t_primitive;

/*
Copyright (c) 1970-2003, Wm. Randolph Franklin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimers.
    Redistributions in binary form must reproduce the above copyright notice in the documentation and/or other materials provided with the distribution.
    The name of W. Randolph Franklin may not be used to endorse or promote products derived from this Software without specific prior written permission.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
	 (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}
*/

// Récupère les coordonnées du cadre entourant la primitive
void primitive_recup_cadre(t_primitive* p,t_cadre* c);

//Lisser une courbe par la methode de Catmull-Rom
void primitive_lisser(t_primitive *p);

// remplit deux tableaux de float contenant les coordonnées des poins de la primitive selon x et y
void primitive_remplir_vertx_verty(t_primitive* p,float* vertx, float* verty);

// modifie la taille de la primitive
void primitive_modif_taille(t_primitive *p, float k);

// rotationne la primitive
void primitive_rotation(t_primitive *p, float alpha);

// change la couleur de la primitive
void primitive_changer_couleur(t_primitive* p,int couleur);

// constructeur par copie
t_primitive* primitive_copier(t_primitive* p);

// translate une primitive
void primitive_translater(t_primitive* p,int dx, int dy);

// détermine si oui ou non la primitive considérée est dans le cadre
int primitive_dans_cadre(t_primitive* p, t_cadre* c);

// permet de savoir si la primitive considérée a atteint son maximum de sommets
int primitive_sommet_plein(t_primitive* p);

// ajoute un point à la primitive considérée
void primitive_ajouter_point(t_primitive* p,int x, int y);

// realloue un tableau plus grand pour stocker les sommets d'une primitive
void primitive_realloc_tab_sommets(t_primitive* p);

// Crée un tableau de points (entiers x,y) pour passer à la fonction Allegro "polygon"
t_point_int* primitive_creer_tab_sommets(t_primitive*p);

// Supprime le dernier sommet d'une primitive
void primitive_suppr_sommet(t_primitive* p);

// Constructeur : alloue une instance de primitive et initialise ses données, retourne le pointeur
t_primitive * primitive_creer(int nb_points);

// Destructeur : libère l'instance pointée par p avec free
void primitive_detruire(t_primitive *p);

// Dessine la primitive p sur le buffer (page) avec line ou line_epaisse
void primitive_dessiner(t_primitive *p);

// Sauve la primitive p dans un fichier fp déjà ouvert en écriture
void primitive_sauver(t_primitive *p, FILE *fp);

// Alloue et retourne une primitive avec données chargées depuis un fichier fp déjà ouvert en lecture
t_primitive * primitive_charger(FILE *fp);

int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy);

#endif // PRIMITIVE_H_INCLUDED
