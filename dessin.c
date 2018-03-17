#include "projet.h"

void dessin_lisser(t_dessin* d)
{
    t_maillon* maillon_actuel = d->p_tete;
    while(maillon_actuel != NULL)
    {
        primitive_lisser(maillon_actuel->prim);
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

void dessin_changer_champ_selected(t_dessin* d, int selected)
{
    t_maillon* maillon_actuel = d->p_tete;
    while(maillon_actuel != NULL)
    {
        maillon_actuel->prim->selected = selected;
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

void dessin_modif_taille(t_dessin* d, float k)
{
    t_maillon* maillon_actuel = d->p_tete;
    while(maillon_actuel != NULL)
    {
        primitive_modif_taille(maillon_actuel->prim,k);
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

void dessin_rotation(t_dessin* d, float alpha)
{
    t_maillon* maillon_actuel = d->p_tete;
    while(maillon_actuel != NULL)
    {
        primitive_rotation(maillon_actuel->prim,alpha);
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

void dessin_supprimer_primitives_selectionnees(t_dessin *d)
{
    t_maillon* p_temp = d->p_tete;
    while (p_temp != NULL)
    {
        if (p_temp->prim->selected == 1)
        {
            if (d->p_queue->p_prec == NULL) // si on est en train de supprimer la seule (dernière) primitive
            {
                d->p_queue = NULL;
                d->p_tete = NULL;
            }
            else if (p_temp->p_suiv == NULL) // si l'élément se trouve en fin de liste
            {
                d->p_queue = p_temp->p_prec;
                d->p_queue->p_suiv = NULL;
            }
            else if (p_temp->p_prec == NULL) // si l'élément se trouve en début de liste
            {
                d->p_tete = p_temp->p_suiv;
                d->p_tete->p_prec = NULL;
            }
            else
            {
                p_temp->p_suiv->p_prec = p_temp->p_prec;
                p_temp->p_prec->p_suiv = p_temp->p_suiv;
            }
            primitive_detruire(p_temp->prim);
            free(p_temp);
            d->longueur--;
            p_temp = p_temp->p_suiv;
        }
        else
        {
            p_temp = p_temp->p_suiv;
        }
    }
}

// copie depart dans arrivee
void dessin_copier(t_dessin* depart,t_dessin* arrivee)
{
    t_maillon* maillon_actuel = depart->p_tete;
    while(maillon_actuel != NULL)
    {
        dessin_ajout_primitive(arrivee,primitive_copier(maillon_actuel->prim));
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

void dessin_changer_couleur(t_dessin* d,int couleur)
{
    t_maillon* maillon_actuel = d->p_tete;
    while(maillon_actuel != NULL)
    {
        primitive_changer_couleur(maillon_actuel->prim,couleur);
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

void dessin_translater(t_dessin* d,int dx,int dy)
{
    t_maillon* maillon_actuel = d->p_tete;
    while(maillon_actuel != NULL)
    {
        primitive_translater(maillon_actuel->prim,dx,dy);
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

/*void dessin_recup_cadre(t_dessin* d,t_cadre* c)
{
    int i, xmin, xmax, ymin, ymax;
    t_maillon* maillon_actuel = d->p_tete;

    xmin = maillon_actuel->prim->tab[0].x;
    xmax = maillon_actuel->prim->tab[0].x;
    ymin = maillon_actuel->prim->tab[0].y;
    ymax = maillon_actuel->prim->tab[0].y;

    while(maillon_actuel != NULL)
    {
        for(i=0; i<maillon_actuel->prim->nb_points_actuel; i++)
        {
            if (maillon_actuel->prim->tab[i].x > xmax)
                xmax= maillon_actuel->prim->tab[i].x;
            if (maillon_actuel->prim->tab[i].x < xmin)
                xmin= maillon_actuel->prim->tab[i].x;
            if (maillon_actuel->prim->tab[i].y > ymax)
                ymax= maillon_actuel->prim->tab[i].y;
            if (maillon_actuel->prim->tab[i].y < ymin)
                ymin= maillon_actuel->prim->tab[i].y;
        }
        maillon_actuel= maillon_actuel->p_suiv;
    }
    c->x1 = xmin;
    c->y1 = ymin;
    c->x2 = xmax;
    c->y2 = ymax;
}*/

void dessin_affich_cadre(t_dessin* d)
{
    t_cadre* c;
    c= cadre_creer();

    t_maillon* maillon_actuel = d->p_tete;

    while(maillon_actuel != NULL)
    {
        primitive_recup_cadre(maillon_actuel->prim,c);
        cadre_dessiner(c);
        maillon_actuel= maillon_actuel->p_suiv;
    }

    free(c);
}

void dessin_dereferencer(t_dessin *d)
{
    while (d->longueur > 0)
    {
        dessin_dereferencer_derniere_primitive(d);
    }
}

void dessin_dereferencer_derniere_primitive(t_dessin *d)
{
    if(d->longueur > 0) // indispensable sinon ca bug si on veut supprimer une primitive inexistante
    {
        t_maillon* p_temp = d->p_queue;

        if (d->p_queue->p_prec == NULL) // si on est en train de supprimer la seule (dernière) primitive
        {
            d->p_queue = NULL;
            d->p_tete = NULL;
        }
        else // si il restera au moins une primitive apres cette suppression
        {
            d->p_queue = d->p_queue->p_prec;
            d->p_queue->p_suiv = NULL;
        }

        free(p_temp); // on free le maillon mais pas la primitive qu'il contient

        d->longueur --;
    }
}

// Constructeur : alloue une instance de dessin initialement vide : 0 primitive dedans
t_dessin * dessin_creer()
{
    t_dessin* document;
    document= (t_dessin*) malloc(1*sizeof(t_dessin));

    document->longueur = 0;
    document->p_tete = NULL;
    document->p_queue = NULL;

    return document;
}

// Détruit les primitives du dessin donné en paramètre, le dessin n'est pas détruit : 0 primitive dedans
void dessin_vider(t_dessin *d)
{
    while (d->longueur > 0)
    {
        dessin_suppression_derniere_primitive(d);
    }
}

// Détruit les primitives du dessin, détruit le dessin
void dessin_detruire(t_dessin *d)
{
    dessin_vider(d);
    free(d);
}

// Ajoute une primitive p (déjà créée) au dessin d
/* il s'agit d'un ajout en queue de liste */
void dessin_ajout_primitive(t_dessin *d, t_primitive *p)
{
    t_maillon* nouv;
    nouv= (t_maillon*) malloc (1*sizeof(t_maillon));
    nouv->prim = p; // on accroche la primitive reçue dans un maillon du dessin
    nouv->p_suiv = NULL;

    if(d->longueur == 0) // équivalent à dessin->p_tete == NULL // équivalent à dessin->p_queue == NULL
    {
        nouv->p_prec = NULL;
        d->p_tete = nouv;
        d->p_queue = nouv;
    }
    else
    {
        d->p_queue->p_suiv = nouv;
        nouv->p_prec = d->p_queue;
        d->p_queue = nouv;
    }

    d->longueur ++;
}

// Enlève et détruit la dernière primitive ajoutée. Facultatif : permet de faire Undo dans l'éditeur
void dessin_suppression_derniere_primitive(t_dessin *d)
{
    if(d->longueur > 0) // indispensable sinon ca bug si on veut supprimer une primitive inexistante
    {
        t_maillon* p_temp = d->p_queue;

        if (d->p_queue->p_prec == NULL) // si on est en train de supprimer la seule (dernière) primitive
        {
            d->p_queue = NULL;
            d->p_tete = NULL;
        }
        else // si il restera au moins une primitive apres cette suppression
        {
            d->p_queue = d->p_queue->p_prec;
            d->p_queue->p_suiv = NULL;
        }

        primitive_detruire(p_temp->prim);
        free(p_temp);

        d->longueur --;
    }
}

// Dessine l'ensemble des primitives contenues dans le dessin d sur le buffer (page)
void dessin_dessiner_page(t_dessin *d)
{
    t_maillon* maillon_actuel = d->p_tete;
    while(maillon_actuel != NULL)
    {
        primitive_dessiner(maillon_actuel->prim);
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

// Ouvre en écriture le fichier dont le nom est passé en paramètre, sauve toutes les primitives
void dessin_sauver(t_dessin *d, char *nom_fichier)
{
    FILE*fp;
    fp= fopen(nom_fichier,"w");
    if (fp==NULL)
    {
        allegro_message("prb ecriture fichier dessin");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    t_maillon* maillon_actuel = d->p_tete;
    fprintf(fp,"%d\n",d->longueur);
    while(maillon_actuel != NULL)
    {
        primitive_sauver(maillon_actuel->prim,fp);
        maillon_actuel= maillon_actuel->p_suiv;
    }
    fclose(fp);
}

// Ouvre en lecture le fichier, créer un nouveau dessin et charge/ajoute toutes les primitives
t_dessin * dessin_charger(char *nom_fichier)
{
    FILE* fp;
    int i,nb_primitives;
    t_primitive* temp;
    t_dessin* document;
    document = dessin_creer();
    fp= fopen(nom_fichier,"r");
    if (fp==NULL)
    {
        allegro_message("prb lecture fichier dessin");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d",&nb_primitives);
    for(i=0; i<nb_primitives; i++)
    {
        temp=primitive_charger(fp);
        dessin_ajout_primitive(document,temp);
    }
    fclose(fp);

    return document;
}
