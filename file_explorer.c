#include "projet.h"

int obtenir_chemin_sauvegarde(char* chemin)
{
    int res;

    TCHAR Buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, Buffer);

    OPENFILENAME ofn;
    TCHAR tmp[1024] ;
    tmp[0]= '\0' ;
    ZeroMemory ( &ofn , sizeof ( OPENFILENAMEW ) );
    ofn.lStructSize = sizeof ( OPENFILENAMEW );
    ofn.lpstrFile = tmp;
    ofn.nMaxFile = 1024;
    ofn.lpstrTitle = _T("Le titre");
    ofn.lpstrFilter = _T("Tous (*.*)\0*.*\0Textes (*.txt)\0*.TXT\0");
    ofn.lpstrInitialDir = _T(Buffer);
    ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER | OFN_OVERWRITEPROMPT;
    res = GetSaveFileName(&ofn);
    if (res==1)
    {
        // si choix du fichier réussi
        strcpy(chemin,ofn.lpstrFile);
        supprimer_contenu_chaine_apres_point(chemin); // obtient un nom de fichier sans extension déjà incluse
        strcat(chemin,".txt"); // on rajoute proprement nous même l'extension
    }
    else printf("Choix du fichier annule\n");

    return res;
}

void supprimer_contenu_chaine_apres_point(char* chemin)
{
    unsigned int i;
    for(i=0;i<strlen(chemin);i++)
    {
        if (chemin[i] == '.')
        {
            chemin[i] = '\0';
            break;
        }
    }
}

int obtenir_chemin_chargement(char* chemin)
{
    int res;

    TCHAR Buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, Buffer);

    OPENFILENAME ofn;
    TCHAR tmp[1024] ;
    tmp[0]= '\0' ;
    ZeroMemory ( &ofn , sizeof ( OPENFILENAMEW ) );
    ofn.lStructSize = sizeof ( OPENFILENAMEW );
    ofn.lpstrFile = tmp;
    ofn.nMaxFile = 1024;
    ofn.lpstrTitle = _T("Le titre");
    ofn.lpstrFilter = _T("Tous (*.*)\0*.*\0Textes (*.txt)\0*.TXT\0");
    ofn.lpstrInitialDir = _T(Buffer);
    ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER;
    res = GetOpenFileName(&ofn);
    if (res==1)
    {
        // si choix du fichier réussi
        strcpy(chemin,ofn.lpstrFile);
    }
    else printf("Choix du fichier annule\n");

    return res;
}

int verif_type_fichier(char* chemin)
{
    int ok;
    char* ext;

    ext = return_extension_blindee(chemin);
    if (strcmp(ext,"txt") == 0)
    {
        ok=1;
        printf("Extension OK\n");
    }
    else
    {
        ok=0;
        printf("Fichier non accepte (extension non reconnue)\n");
    }

    free(ext);

    return ok;
}

char* return_extension_blindee(char* chemin)
{
    int i=0;
    int j=0;
    char* ext;
    ext= (char*) malloc(50*sizeof(char));
    while(chemin[i]!= '.' && chemin[i]!='\0')
    {
        i++;
    }
    i++;
    while(chemin[i]!='\0')
    {
        ext[j]=chemin[i];
        i++;
        j++;
    }
    ext[j]='\0';

    return ext;
}

int remplit_chemin_chargement(char* chemin)
{
    int choix_fini;
    int type_fichier_ok;

    choix_fini = obtenir_chemin_chargement(chemin);
    if(choix_fini)
    {
        type_fichier_ok = verif_type_fichier(chemin);
    }
    if(choix_fini && type_fichier_ok)
    {
        // on est certain qu'un fichier a bien été choisi, et qu'il est bien de type txt
        printf("Chemin: %s\n",chemin);
        return 1;
    }
    else return 0;
}

int remplit_chemin_sauvegarde(char* chemin)
{
    int choix_fini;
    choix_fini = obtenir_chemin_sauvegarde(chemin);
    if(choix_fini)
    {
        // on est certain qu'un fichier a bien été choisi (et qu'il ne dispose pas d'une double extension)
        printf("Chemin: %s\n",chemin);
        return 1;
    }
    else return 0;
}

void recup_nom_fichier(char* chemin, char* nom)
{
    char temp[1024];
    int i= strlen(chemin)-1; // on va parcourir la chaine chemin en partant de la derniere case, d'indice i
    int j= 0;

    while(chemin[i] != '\\') // tant que l'on ne tombe pas sur un "\"
    {
        temp[j] = chemin[i]; // on met dans tmp le caractère analysé
        j++;
        i--;
    }
    temp[j]='\0';
    // on obtient une chaine inversée
    // printf("temp: %s\n",temp);

    j=0;
    for(i=strlen(temp)-1;i>=0;i--) // on réinverse la chaine
    {
        nom[j]=temp[i];
        j++;
    }
    nom[j]='\0';
}
