#include "projet.h"

t_editeur* editeur_creer_initialiser(int nouveauOuNon)
{
    char chemin[1024];
    char nom[1024];
    char ch[1024];
    int ok;

    t_editeur* ed;
    ed = (t_editeur*) malloc(1*sizeof(t_editeur));

    ed->mode = MODE_AJOUT;
    ed->etape = 0;
    ed->quitter = 0;

    ed->presse_papier = dessin_creer();
    ed->selec = dessin_creer();
    ed->cadre = cadre_creer();

    if (nouveauOuNon == 1) // s'il fallait charger un fichier
    {
        ok = remplit_chemin_chargement(chemin);
        if (ok)
        {
            ed->document= dessin_charger(chemin); // si le choix du fichier a réussi
            recup_nom_fichier(chemin,nom);
            strcpy(ch,"Editeur de Dessin Vectoriel - by G&G || Fichier choisi: ");
            strcat(ch,nom);
            set_window_title(ch);
        }
        else
        {
            printf("vous n'avez pas choisi de fichier, ou alors pas un fichier valide\n");
            printf("j'ai donc cree un document vide a la place.\n");
            ed->document= dessin_creer(); // si le choix du fichier a raté
        }
    }
    if (nouveauOuNon == 0) // s'il ne fallait pas charger de fichier
    {
        ed->document= dessin_creer();
    }

    return ed;
}

void editeur_gerer(t_editeur* ed)
{
    rafraichir_clavier_souris();
    palette_gerer();
    editeur_gerer_quitter(ed);
    editeur_gerer_document(ed);
    editeur_gerer_modes(ed);

    if (ed->mode == MODE_AJOUT)
        editeur_gerer_mode_ajout(ed);
    if (ed->mode == MODE_MANIP)
        editeur_gerer_mode_manip(ed);
}

void editeur_afficher(t_editeur* ed)
{
    effacer_page();
    dessin_dessiner_page(ed->document);
    if (ed->mode == MODE_AJOUT)
        editeur_afficher_mode_ajout(ed);
    if (ed->mode == MODE_MANIP)
        editeur_afficher_mode_manip(ed);
    palette_dessiner();
    afficher_page();
}

void editeur_gerer_quitter(t_editeur* ed)
{
    if(key[KEY_Q])
    {
        ed->quitter = 1;
        set_window_title("Editeur de Dessin Vectoriel - by G&G"); // on remet le titre de la fenetre par défaut en revenant au menu.
    }
}

void editeur_detruire(t_editeur* ed)
{
    cadre_detruire(ed->cadre);
    dessin_dereferencer(ed->selec);
    free(ed->selec);
    dessin_detruire(ed->presse_papier);
    dessin_detruire(ed->document);
    if (ed->etape==1) primitive_detruire(ed->prim_temp);
    free(ed);
}

void editeur_gerer_document(t_editeur* ed)
{
    char chemin[1024];
    char nom[1024];
    char ch[1024];
    int ok;

    // Si la touche s a été pressée...
    if (touche=='s')
    {
        printf("Sauver\n\n");
        ok = remplit_chemin_sauvegarde(chemin);
        if(ok)
        {
            // on peut donc ouvrir ce fichier
            dessin_sauver(ed->document,chemin);
        }
    }

    // Si la touche c a été pressée..
    if (touche=='c')
    {
        printf("Charger\n\n");
        ok = remplit_chemin_chargement(chemin);
        if(ok)
        {
            // on peut donc supprimer le document actuel et charger ce fichier
            if (ed->mode == MODE_AJOUT)
                editeur_sortir_mode_ajout(ed);
            else
                editeur_sortir_mode_manip(ed);
            ed->mode = MODE_AJOUT;
            printf("Bienvenue en mode AJOUT\n");
            dessin_detruire(ed->document);
            ed->document= dessin_charger(chemin);
            recup_nom_fichier(chemin,nom);
            strcpy(ch,"Editeur de Dessin Vectoriel - by G&G || Fichier choisi: ");
            strcat(ch,nom);
            set_window_title(ch);
        }
    }

    // Si la touche v a été pressée..
    if (touche=='v')
    {
        printf("Vider document\n\n");
        dessin_vider(ed->document);
        dessin_dereferencer(ed->selec); // on vide la selection
    }
}

void editeur_gerer_modes(t_editeur* ed)
{
    if (key_press[KEY_F1] && ed->mode == MODE_AJOUT)
        editeur_sortir_mode_ajout(ed);
    if (key_press[KEY_F2] && ed->mode == MODE_MANIP)
        editeur_sortir_mode_manip(ed);
}

void editeur_sortir_mode_manip(t_editeur* ed) // a completer pour sortir proprement du mode actuel
{
    ed->mode = MODE_AJOUT;
    ed->etape = 0;
    dessin_dereferencer(ed->selec); // on vide la selection
    dessin_vider(ed->presse_papier); // on vide le presse papier
    printf("Bienvenue en mode Ajout\n");
}

void editeur_sortir_mode_ajout(t_editeur* ed) // a completer pour sortir proprement du mode actuel
{
    ed->mode = MODE_MANIP;
    if (ed->etape == 1)
    {
        primitive_detruire(ed->prim_temp);
        ed->etape = 0;
    }
    printf("Bienvenue en mode Manip\n");
}

void editeur_afficher_mode_ajout(t_editeur* ed)
{
    // Si un segment est en cours d'édition...
    if ( ed->etape==1 )
        // Dessiner sur le buffer avec cette nouvelle position
        primitive_dessiner(ed->prim_temp);
}

void editeur_gerer_mode_ajout(t_editeur* ed)
{
    // Si la touche Backspace est pressée alors enlever dernier ajout
    // Cas "pas de polygone en cours" : enlever polygone
    if (touche=='\b' && ed->etape==0)
    {
        dessin_suppression_derniere_primitive(ed->document);
    }

    // Cas "polygone en cours" : enlever un sommet
    if (touche=='\b' && ed->etape==1)
    {
        primitive_suppr_sommet(ed->prim_temp);
    }

    // Si le bouton gauche de la souris a été cliqué...
    if ( bouton=='g' )
    {
        // Si aucun polygone en cours d'édition...
        if ( ed->etape==0 )
        {
            // Commencer l'édition d'un nouveau polygone
            ed->etape = 1;
            ed->prim_temp = primitive_creer(NB_POINTS_INIT);

            // Enregistrer couleur
            ed->prim_temp->couleur = palette_recup_couleur();

            // Enregistrer le 1er point
            primitive_ajouter_point(ed->prim_temp,mouse_x,mouse_y);
        }
        // Dans tous les cas on a un nouveau point pour le polygone en cours d'édition
        if (primitive_sommet_plein(ed->prim_temp))
        {
            primitive_realloc_tab_sommets(ed->prim_temp);
            printf("tab de sommets agrandi\n");
        }
        primitive_ajouter_point(ed->prim_temp,mouse_x,mouse_y);
    }

    if ( bouton=='d' && ed->etape==1 )
    {
        // Terminer l'édition du nouveau polygone: l'ajouter au dessin
        ed->etape = 0;
        dessin_ajout_primitive(ed->document,ed->prim_temp);
    }

    // Si un segment est en cours d'édition...
    if ( ed->etape==1 )
    {
        // Mettre à jour la position du dernier sommet
        ed->prim_temp->tab[ed->prim_temp->nb_points_actuel-1].x = mouse_x;
        ed->prim_temp->tab[ed->prim_temp->nb_points_actuel-1].y = mouse_y;
    }

}

void editeur_remplir_selection(t_editeur* ed)
{
    t_maillon* maillon_actuel = ed->document->p_tete;
    while(maillon_actuel != NULL)
    {
        if(primitive_dans_cadre(maillon_actuel->prim,ed->cadre))
        {
            dessin_ajout_primitive(ed->selec,maillon_actuel->prim);
        }
        maillon_actuel= maillon_actuel->p_suiv;
    }
}

void editeur_gerer_mode_manip_selectionner(t_editeur* ed)
{
    /// soit on selectionne via un ctrl+clic
    if ( (key[KEY_LCONTROL] || key[KEY_RCONTROL]) && mouse_click&1 )// Test pour CTRL-Clic Gauche :
    {
        editeur_gerer_mode_manip_selectionner_clic(ed);
    }
    /// soit on selectionne via un drag
    else
    {
        // Si clic gauche : fixer 1er coin du cadre et passer en phase tirage de cadre (etape à 1)
        if (mouse_click&1 && ed->etape==0)
        {
            if (!key[KEY_LSHIFT] && !key[KEY_RSHIFT]) // touche SHIFT pas enfoncée
                dessin_dereferencer(ed->selec); // on vide la selection précedente
            ed->cadre->x1 = mouse_x;
            ed->cadre->y1 = mouse_y;
            ed->etape=1;
        }
        // Si clic gauche relâché appeler sous-prog de détermination des primitives sélectionnées
        if (mouse_unclick&1 && ed->etape==1)
        {
            ed->etape=0;
            editeur_remplir_selection(ed);
        }
        // Si phase tirage de cadre : 2ème coin suit position souris et dessiner cadre
        if (ed->etape==1)
        {
            ed->cadre->x2 = mouse_x;
            ed->cadre->y2 = mouse_y;
        }
    }
}

/*void editeur_afficher_selec(t_editeur* ed)
{
    if (ed->selec->longueur > 0) // si selec pas vide
    {
        dessin_recup_cadre(ed->selec,ed->cadre);
        cadre_dessiner(ed->cadre);
    }
}*/

void editeur_afficher_selec(t_editeur* ed)
{
    if (ed->selec->longueur > 0) // si selec pas vide
    {
        dessin_affich_cadre(ed->selec);
    }
}

void editeur_gerer_mode_manip(t_editeur* ed)
{
    editeur_gerer_mode_manip_selectionner(ed);
    editeur_gerer_mode_manip_deplacer(ed);
    editeur_gerer_mode_manip_ccc(ed);
    editeur_gerer_mode_manip_colorer(ed);
    editeur_gerer_mode_manip_rotation(ed);
    editeur_gerer_mode_manip_taille(ed);
    editeur_gerer_mode_manip_lisser(ed);
}

void editeur_afficher_mode_manip(t_editeur* ed)
{
    if(ed->etape == 1) // on affiche le cadre en cours de tirage
        rect(page, ed->cadre->x1, ed->cadre->y1, ed->cadre->x2, ed->cadre->y2,makecol(255,0,0));
    editeur_afficher_selec(ed); // on affiche les cadres ajustés entourant les primitives sélectionnées
}

void editeur_gerer_mode_manip_deplacer(t_editeur *ed)
{
    if ( mouse_b&2 ) // clic droit actuellement enfoncé
        dessin_translater(ed->selec,mouse_depx,mouse_depy);
    if (key[KEY_LEFT])
        dessin_translater(ed->selec, -1, 0);
    if (key[KEY_RIGHT])
        dessin_translater(ed->selec, +1, 0);
    if (key[KEY_UP])
        dessin_translater(ed->selec, 0, -1);
    if (key[KEY_DOWN])
        dessin_translater(ed->selec, 0, 1);
}

void editeur_gerer_mode_manip_ccc(t_editeur *ed)
{
    t_maillon* maillon_actuel;
    t_primitive* p_temp;

    // Test pour ctrl-C :
    if ( (key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key_press[KEY_C] )
    {
        dessin_vider(ed->presse_papier); // on vide le presse papier actuel
        dessin_copier(ed->selec,ed->presse_papier);
    }

    // Test pour ctrl-V :
    if ( (key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key_press[KEY_V] )
    {
        dessin_dereferencer(ed->selec); // on vide la selection

        maillon_actuel = ed->presse_papier->p_tete;
        while(maillon_actuel != NULL) // tant qu'il y a des primitives dans le presse papier
        {
            p_temp = primitive_copier(maillon_actuel->prim); // on duplique la primitive
            dessin_ajout_primitive(ed->selec,p_temp); // on l'ajoute à la selection
            dessin_ajout_primitive(ed->document,p_temp); // on l'ajoute au document

            maillon_actuel= maillon_actuel->p_suiv; // on passe au maillon suivant
        }
    }

    // Test pour ctrl-X :
    if ( (key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key_press[KEY_X] )
    {
        dessin_vider(ed->presse_papier); // on vide le presse papier actuel
        dessin_copier(ed->selec,ed->presse_papier);// on copie la selection dans le presse papier
        dessin_changer_champ_selected(ed->document,0); // on met selected à 0 pour toutes les primitives du document
        dessin_changer_champ_selected(ed->selec,1); // on met selected à 1 pour toutes les primitives selectionnées
        dessin_dereferencer(ed->selec); // on vide la selection
        dessin_supprimer_primitives_selectionnees(ed->document); // on supprime dans le document les primitives sélectionnées

    }

    // Test pour "Suppr" (delete):
    if ( key_press[KEY_DEL] || key_press[KEY_BACKSPACE])
    {
        dessin_changer_champ_selected(ed->document,0); // on met selected à 0 pour toutes les primitives du document
        dessin_changer_champ_selected(ed->selec,1); // on met selected à 1 pour toutes les primitives selectionnées
        dessin_dereferencer(ed->selec); // on vide la selection
        dessin_supprimer_primitives_selectionnees(ed->document); //  on supprime les primitives séléctionnées
    }

}

void editeur_gerer_mode_manip_colorer(t_editeur* ed)
{
    if (palette.action_couleur)
    {
        dessin_changer_couleur(ed->selec,palette_recup_couleur());
    }
}

void editeur_gerer_mode_manip_rotation(t_editeur *ed)
{
    if ( (key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_R] ) // si CTRL-R
    {
        dessin_rotation(ed->selec,1);
    }
    if ( (key[KEY_LSHIFT] || key[KEY_RSHIFT]) && key[KEY_R] ) // si SHIFT-R
    {
        dessin_rotation(ed->selec,-1);
    }
}

void editeur_gerer_mode_manip_taille(t_editeur *ed)
{
    if (key[KEY_I])
        dessin_modif_taille(ed->selec,1.01);
    if (key[KEY_O])
        dessin_modif_taille(ed->selec,1/1.01);
}

void editeur_gerer_mode_manip_selectionner_clic(t_editeur* ed)
{
    t_maillon* maillon_actuel;
    float *vertx = NULL;
    float *verty = NULL;

    if (!key[KEY_LSHIFT] && !key[KEY_RSHIFT]) // touche SHIFT pas enfoncée
        dessin_dereferencer(ed->selec); // on vide la selection
    maillon_actuel = ed->document->p_tete;

    while(maillon_actuel != NULL) // tant qu'il y a des primitives dans le document
    {
        vertx = (float*) malloc(maillon_actuel->prim->nb_points_actuel*sizeof(float));
        verty = (float*) malloc(maillon_actuel->prim->nb_points_actuel*sizeof(float));
        primitive_remplir_vertx_verty(maillon_actuel->prim,vertx,verty);

        if (pnpoly(maillon_actuel->prim->nb_points_actuel,vertx,verty,(float)mouse_x,(float)mouse_y))
        {
            dessin_ajout_primitive(ed->selec,maillon_actuel->prim); // on l'ajoute à la selection
        }
        free(vertx);
        free(verty);
        maillon_actuel= maillon_actuel->p_suiv; // on passe au maillon suivant
    }
}

void editeur_gerer_mode_manip_lisser(t_editeur* ed)
{
    if (key_press[KEY_L])
       dessin_lisser(ed->selec);
}
