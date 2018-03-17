#include "projet.h"

void liberer_menu(t_graphMenu* graph)
{
    destroy_bitmap(graph->fond);
    destroy_bitmap(graph->cursor);
    destroy_bitmap(graph->contenu_aide);
    destroy_bitmap(graph->contenu_a_propos);

    destroy_bitmap(graph->img_boutons_off[0]);
    destroy_bitmap(graph->img_boutons_off[1]);
    destroy_bitmap(graph->img_boutons_off[2]);
    destroy_bitmap(graph->img_boutons_off[3]);
    destroy_bitmap(graph->img_boutons_off[4]);
    destroy_bitmap(graph->img_boutons_off[5]);

    destroy_bitmap(graph->img_boutons_on[0]);
    destroy_bitmap(graph->img_boutons_on[1]);
    destroy_bitmap(graph->img_boutons_on[2]);
    destroy_bitmap(graph->img_boutons_on[3]);
    destroy_bitmap(graph->img_boutons_on[4]);
    destroy_bitmap(graph->img_boutons_on[5]);
}

void charger_menu(t_graphMenu* graph)
{
    int i;
    FILE *fpx,*fpy;
    fpx=fopen("boutons_x.txt","r");
    fpy=fopen("boutons_y.txt","r");
    if ((fpx == NULL)|| (fpy==NULL))
    {
        allegro_message("prb ouverture fichiers boutons");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    graph->fond=chargerImage("imgmenu/fond.bmp");
    graph->cursor=chargerImage("imgmenu/cursor.bmp");
    graph->contenu_aide=chargerImage("imgmenu/contenu_aide.bmp");
    graph->contenu_a_propos=chargerImage("imgmenu/contenu_a_propos.bmp");

    graph->img_boutons_off[0]=chargerImage("imgmenu/nouveau0.bmp");
    graph->img_boutons_off[1]=chargerImage("imgmenu/charger0.bmp");
    graph->img_boutons_off[2]=chargerImage("imgmenu/aide0.bmp");
    graph->img_boutons_off[3]=chargerImage("imgmenu/a_propos0.bmp");
    graph->img_boutons_off[4]=chargerImage("imgmenu/quitter0.bmp");
    graph->img_boutons_off[5]=chargerImage("imgmenu/boutonRetour0.bmp");

    graph->img_boutons_on[0]=chargerImage("imgmenu/nouveau1.bmp");
    graph->img_boutons_on[1]=chargerImage("imgmenu/charger1.bmp");
    graph->img_boutons_on[2]=chargerImage("imgmenu/aide1.bmp");
    graph->img_boutons_on[3]=chargerImage("imgmenu/a_propos1.bmp");
    graph->img_boutons_on[4]=chargerImage("imgmenu/quitter1.bmp");
    graph->img_boutons_on[5]=chargerImage("imgmenu/boutonRetour1.bmp");

    for(i=0; i<NB_BOUTONS; i++)
    {
        fscanf(fpx,"%d",&graph->boutons_x[i]);
        fscanf(fpy,"%d",&graph->boutons_y[i]);
    }
    fclose(fpx);
    fclose(fpy);
}

void afficher_menu(t_graphMenu graph)
{
    int mx, my, i;

    while (1) // boucle infinie, qui ne se quitte qu'avec un "break" (voir le fonctionnement du bouton "quitter"
        // en effet on ne veut pas que le programme se quitte avec "echap"
        //sinon quand on quitte l'éditeur avec "echap", ça nous quitte aussi du menu, et donc du programme.
        // alors que là quand on quitte l'éditeur, on revient sur le menu d'accueil, c'est mieux.
    {
        // Mettre à jour les variables touche (clavier) et bouton (souris)
        rafraichir_clavier_souris();

        mx=mouse_x;
        my=mouse_y;

        // Effacer complètement le buffer (tout disparaît)
        effacer_page();

        //AFFICHAGE
        draw_sprite(page, graph.fond, 0,0);

        for (i=0; i<NB_BOUTONS-1; i++)
        {
            if (mx>=graph.boutons_x[i] && mx<=(graph.boutons_x[i]+graph.img_boutons_off[i]->w) && my>=graph.boutons_y[i] && my<=(graph.boutons_y[i]+graph.img_boutons_off[i]->h))
                draw_sprite(page, graph.img_boutons_on[i], graph.boutons_x[i], graph.boutons_y[i]);
            else
                draw_sprite(page, graph.img_boutons_off[i], graph.boutons_x[i], graph.boutons_y[i]);
        }

        draw_sprite(page, graph.cursor, mx, my);
        afficher_page();

        //GESTION DU CLIC
        if (bouton=='g')
        {
            if (mx>=graph.boutons_x[0] && mx<=(graph.boutons_x[0]+graph.img_boutons_off[0]->w) && my>=graph.boutons_y[0] && my<=(graph.boutons_y[0]+graph.img_boutons_off[0]->h))
            {
                //NOUVEAU
                printf("Nouveau\n");
                boucle_jeu(0);

            }
            if (mx>=graph.boutons_x[1] && mx<=(graph.boutons_x[1]+graph.img_boutons_off[1]->w) && my>=graph.boutons_y[1] && my<=(graph.boutons_y[1]+graph.img_boutons_off[1]->h))
            {
                //CHARGER
                printf("Charger\n");
                boucle_jeu(1);
            }
            if (mx>=graph.boutons_x[2] && mx<=(graph.boutons_x[2]+graph.img_boutons_off[2]->w) && my>=graph.boutons_y[2] && my<=(graph.boutons_y[2]+graph.img_boutons_off[2]->h))
            {
                //AIDE
                printf("Aide\n");
                aff_aide(graph);
            }
            if (mx>=graph.boutons_x[3] && mx<=(graph.boutons_x[3]+graph.img_boutons_off[3]->w) && my>=graph.boutons_y[3] && my<=(graph.boutons_y[3]+graph.img_boutons_off[3]->h))
            {
                //A PROPOS
                printf("A propos\n");
                aff_a_propos(graph);
            }
            if (mx>=graph.boutons_x[4] && mx<=(graph.boutons_x[4]+graph.img_boutons_off[4]->w) && my>=graph.boutons_y[4] && my<=(graph.boutons_y[4]+graph.img_boutons_off[4]->h))
            {
                //QUITTER
                break;
            }
        }
        rest(10);
    }
}

void boucle_jeu(int nouveauOuNon)
{
    show_mouse(screen);

    t_editeur* ed;
    ed = editeur_creer_initialiser(nouveauOuNon);

    // Boucle événementielle
    while (!ed->quitter)
    {
        editeur_gerer(ed);
        editeur_afficher(ed);
        rest(10);
    }

    editeur_detruire(ed);
    show_mouse(NULL);
}

void aff_aide(t_graphMenu graph)
{
    int mx;
    int my;
    while(1)
    {
        mx = mouse_x;
        my = mouse_y;

        //AFFICHAGE
        effacer_page();
        draw_sprite(page, graph.contenu_aide, 0, 0);
        if (mx>=graph.boutons_x[NB_BOUTONS-1] && mx<=graph.boutons_x[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->w && my>=graph.boutons_y[NB_BOUTONS-1] && my<=graph.boutons_y[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->h)
            draw_sprite(page, graph.img_boutons_on[NB_BOUTONS-1], graph.boutons_x[NB_BOUTONS-1],graph.boutons_y[NB_BOUTONS-1]);
        else
            draw_sprite(page, graph.img_boutons_off[NB_BOUTONS-1], graph.boutons_x[NB_BOUTONS-1],graph.boutons_y[NB_BOUTONS-1]);

        //CLIC
        if (mx>=graph.boutons_x[NB_BOUTONS-1] && mx<=graph.boutons_x[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->w && my>=graph.boutons_y[NB_BOUTONS-1] && my<=graph.boutons_y[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->h && mouse_b==1)
            break;

        draw_sprite(page, graph.cursor, mx, my);
        afficher_page();
    }
}

void aff_a_propos(t_graphMenu graph)
{
    int mx;
    int my;
    while(1)
    {
        mx = mouse_x;
        my = mouse_y;

        //AFFICHAGE
        effacer_page();
        draw_sprite(page, graph.contenu_a_propos, 0, 0);
        if (mx>=graph.boutons_x[NB_BOUTONS-1] && mx<=graph.boutons_x[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->w && my>=graph.boutons_y[NB_BOUTONS-1] && my<=graph.boutons_y[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->h)
            draw_sprite(page, graph.img_boutons_on[NB_BOUTONS-1], graph.boutons_x[NB_BOUTONS-1],graph.boutons_y[NB_BOUTONS-1]);
        else
            draw_sprite(page, graph.img_boutons_off[NB_BOUTONS-1], graph.boutons_x[NB_BOUTONS-1],graph.boutons_y[NB_BOUTONS-1]);

        //CLIC
        if (mx>=graph.boutons_x[NB_BOUTONS-1] && mx<=graph.boutons_x[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->w && my>=graph.boutons_y[NB_BOUTONS-1] && my<=graph.boutons_y[NB_BOUTONS-1]+graph.img_boutons_off[NB_BOUTONS-1]->h && mouse_b==1)
            break;

        draw_sprite(page, graph.cursor, mx, my);
        afficher_page();
    }
}
