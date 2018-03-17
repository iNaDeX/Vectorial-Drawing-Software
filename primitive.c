#include "projet.h"

void primitive_recup_cadre(t_primitive* p,t_cadre* c)
{
    int i, xmin, xmax, ymin, ymax;

    xmin = p->tab[0].x;
    xmax = p->tab[0].x;
    ymin = p->tab[0].y;
    ymax = p->tab[0].y;

        for(i=0; i<p->nb_points_actuel; i++)
        {
            if (p->tab[i].x > xmax)
                xmax= p->tab[i].x;
            if (p->tab[i].x < xmin)
                xmin= p->tab[i].x;
            if (p->tab[i].y > ymax)
                ymax= p->tab[i].y;
            if (p->tab[i].y < ymin)
                ymin= p->tab[i].y;
        }

    c->x1 = xmin;
    c->y1 = ymin;
    c->x2 = xmax;
    c->y2 = ymax;
}

//Lisser une courbe par la methode de Catmull-Rom
void primitive_lisser(t_primitive *p)
{
    int i;
    float t,j;
    int indice=0;
    int i_1=p->nb_points_actuel-1;
    int i1=1;
    int i2=2;
    int nb = (p->nb_points_actuel)*PRECISION;
    if (nb < 500)
    {
        t_point* tab_lissage = (t_point *)malloc(nb*sizeof(t_point));

        if (PRECISION == 0)
        {
            printf("Precision est nul\n");
            exit(-2);
        }

        for (i=0; i<p->nb_points_actuel; i++)
        {
            for (j=0; j<PRECISION; j++)
            {
                t = j/PRECISION;
                tab_lissage[indice].x=((-p->tab[i_1].x*RAIDEUR-p->tab[i].x*(RAIDEUR-2)+p->tab[i1].x*(RAIDEUR-2)+p->tab[i2].x*RAIDEUR)*pow(t,3)+(2*p->tab[i_1].x*RAIDEUR+p->tab[i].x*(RAIDEUR-3)-p->tab[i1].x*(2*RAIDEUR-3)-p->tab[i2].x*RAIDEUR)*pow(t,2)+(p->tab[i1].x*RAIDEUR-p->tab[i_1].x*RAIDEUR)*t+p->tab[i].x);
                tab_lissage[indice].y=((-p->tab[i_1].y*RAIDEUR-p->tab[i].y*(RAIDEUR-2)+p->tab[i1].y*(RAIDEUR-2)+p->tab[i2].y*RAIDEUR)*pow(t,3)+(2*p->tab[i_1].y*RAIDEUR+p->tab[i].y*(RAIDEUR-3)-p->tab[i1].y*(2*RAIDEUR-3)-p->tab[i2].y*RAIDEUR)*pow(t,2)+(p->tab[i1].y*RAIDEUR-p->tab[i_1].y*RAIDEUR)*t+p->tab[i].y);
                indice++;
            }
            i_1=i;
            i1++;
            i2++;
            if (i1>=p->nb_points_actuel) i1=0;
            if (i2>=p->nb_points_actuel) i2=0;
        }
        free(p->tab); // on libère l'ancien tableau de points
        p->nb_points_actuel = nb; // on change le nombre de points de la primitive, car on a créé davantage de points en lissant la primitive
        p->nb_points_max = nb; // on change le nombre de points de la primitive, car on a créé davantage de points en lissant la primitive
        p->tab = tab_lissage; // on accroche le nouveau tableau de points lissés
        printf("Primitive lissee\n");
    }
}

// Grossissement/ Rapetissement d'une primitive
void primitive_modif_taille(t_primitive *p, float k)
{
    double complex a,aa; //point a zoomer et nouveau point
    double complex g; //centre du zoom
    int i=0;
    int xmin = p->tab[0].x;
    int xmax = p->tab[0].x;
    int ymin = p->tab[0].y;
    int ymax = p->tab[0].y;

    for (i=0; i<p->nb_points_actuel; i++)
    {
        if (xmin>p->tab[i].x) xmin = p->tab[i].x;
        if (xmax<p->tab[i].x) xmax = p->tab[i].x;
        if (ymin>p->tab[i].y) ymin = p->tab[i].y;
        if (ymax<p->tab[i].y) ymax = p->tab[i].y;
    }
    g = (xmin+xmax+ymin*I+ymax*I)/2;
    for (i=0; i<p->nb_points_actuel; i++)
    {
        a = p->tab[i].x+p->tab[i].y*I;
        aa = k*(a-g)+g;
        p->tab[i].x = creal(aa);
        p->tab[i].y = cimag(aa);
    }
}

// Fait la rotaton d'angle 1 degre d'un polygone
void primitive_rotation(t_primitive *p, float alpha)
{
    double complex a,aa; //point a tourner et nouveau point
    double complex g; //centre de la rotation
    int i=0;
    int xmin = p->tab[0].x;
    int xmax = p->tab[0].x;
    int ymin = p->tab[0].y;
    int ymax = p->tab[0].y;
    alpha = alpha*2*M_PI/360;


    for (i=0; i<p->nb_points_actuel; i++)
    {
        if (xmin>p->tab[i].x) xmin = p->tab[i].x;
        if (xmax<p->tab[i].x) xmax = p->tab[i].x;
        if (ymin>p->tab[i].y) ymin = p->tab[i].y;
        if (ymax<p->tab[i].y) ymax = p->tab[i].y;
    }
    g = (xmin+xmax+ymin*I+ymax*I)/2;
    for (i=0; i<p->nb_points_actuel; i++)
    {
        a = p->tab[i].x+p->tab[i].y*I;
        aa = (cexp(I*alpha))*(a-g)+g;
        p->tab[i].x = creal(aa);
        p->tab[i].y = cimag(aa);
    }
}

void primitive_changer_couleur(t_primitive* p,int couleur)
{
    p->couleur = couleur;
}

t_primitive* primitive_copier(t_primitive* p)
{
    int i;
    t_primitive* nouv;
    nouv = (t_primitive*) malloc(1*sizeof(t_primitive));

    nouv->tab = (t_point*) malloc(p->nb_points_max *sizeof(t_point));
    nouv->nb_points_max = p->nb_points_max;
    nouv->nb_points_actuel = p->nb_points_actuel;
    nouv->couleur = p->couleur;

    for(i=0; i<p->nb_points_actuel; i++)
    {
        nouv->tab[i].x = p->tab[i].x;
        nouv->tab[i].y = p->tab[i].y;
    }

    return nouv;
}

void primitive_translater(t_primitive* p,int dx,int dy)
{
    int i;
    for(i=0; i<p->nb_points_actuel; i++)
    {
        p->tab[i].x = dx + p->tab[i].x;
        p->tab[i].y = dy + p->tab[i].y;
    }
}

int primitive_dans_cadre(t_primitive* p, t_cadre* c)
{
    int dedans = 1;
    int i;
    int x1,y1,x2,y2;

    if (c->x1 <= c->x2)
    {
        x1 = c->x1;
        x2 = c->x2;
    }
    else
    {
        x1 = c->x2;
        x2 = c->x1;
    }

    if (c->y1 <= c->y2)
    {
        y1 = c->y1;
        y2 = c->y2;
    }
    else
    {
        y1 = c->y2;
        y2 = c->y1;
    }

    for(i=0; i<p->nb_points_actuel; i++)
    {
        if(!((p->tab[i].x >= x1) && (p->tab[i].x <= x2) && (p->tab[i].y >= y1) && (p->tab[i].y <= y2)))
        {
            dedans=0;
            break;
        }
    }

    return dedans;
}

// Constructeur : alloue une instance de primitive et initialise ses données, retourne le pointeur
t_primitive * primitive_creer(int nb_points)
{
    t_primitive* nouv;
    nouv = (t_primitive*) malloc(1*sizeof(t_primitive));
    nouv->tab = (t_point*) malloc(nb_points*sizeof(t_point));
    nouv->nb_points_max = nb_points;
    nouv->nb_points_actuel = 0;
    nouv->couleur = 0;

    return nouv;
}

void primitive_realloc_tab_sommets(t_primitive* p)
{
    p->nb_points_max = 3*p->nb_points_max/2;
    p->tab = realloc(p->tab,p->nb_points_max*sizeof(t_point));
}

t_point_int* primitive_creer_tab_sommets(t_primitive*p)
{
    int i;
    t_point_int* tab = (t_point_int*) malloc(p->nb_points_actuel*sizeof(t_point_int));
    for(i=0; i<p->nb_points_actuel; i++)
    {
        tab[i].x = (int) p->tab[i].x;
        tab[i].y = (int) p->tab[i].y;
    }
    return tab;
}

// Dessine la primitive p sur le buffer (page) avec line ou line_epaisse
void primitive_dessiner(t_primitive *p)
{
    t_point_int* tab_special;
    tab_special = primitive_creer_tab_sommets(p);
    polygon(page, p->nb_points_actuel, (int *)tab_special, p->couleur);
    free(tab_special);
}

// Sauve la primitive p dans un fichier fp déjà ouvert en écriture
void primitive_sauver(t_primitive *p, FILE *fp)
{
    int i;
    fprintf(fp,"%d ",p->nb_points_actuel);
    fprintf(fp,"%d ",p->couleur);
    for(i=0; i<p->nb_points_actuel; i++)
    {
        fprintf(fp,"%f %f ",p->tab[i].x,p->tab[i].y);
    }
    fprintf(fp,"\n");
}

void primitive_suppr_sommet(t_primitive* p)
{
    if (p->nb_points_actuel > 2)
    {
        p->nb_points_actuel --;
    }
}

// Alloue et retourne une primitive avec données chargées depuis un fichier fp déjà ouvert en lecture
t_primitive * primitive_charger(FILE *fp)
{
    int i, nb_points;
    t_primitive* nouv;
    fscanf(fp,"%d",&nb_points);

    nouv= primitive_creer(nb_points);
    nouv->nb_points_actuel = nb_points;
    fscanf(fp,"%d",&nouv->couleur);
    for(i=0; i<nouv->nb_points_actuel; i++)
    {
        fscanf(fp,"%f %f ",&nouv->tab[i].x,&nouv->tab[i].y);
    }

    return nouv;
}

int primitive_sommet_plein(t_primitive* p)
{
    if (p->nb_points_actuel == p->nb_points_max) return 1;
    else return 0;
}

void primitive_ajouter_point(t_primitive* p,int x, int y)
{
    p->tab[p->nb_points_actuel].x = x;
    p->tab[p->nb_points_actuel].y = y;
    p->nb_points_actuel ++;
}

// Destructeur : libère l'instance pointée par p avec free
void primitive_detruire(t_primitive *p)
{
    free(p->tab);
    free(p);
}

void primitive_remplir_vertx_verty(t_primitive* p,float* vertx, float* verty)
{
    int i;

    for(i=0; i<p->nb_points_actuel; i++)
    {
        vertx[i]= p->tab[i].x;
        verty[i]= p->tab[i].y;
    }
}

int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++)
    {
        if ( ((verty[i]>testy) != (verty[j]>testy)) && (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
            c = !c;
    }
    return c;
}
