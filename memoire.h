/// Module de gestion mémoire

/// En mettant partout  #include "memoire.h"   on bénéficie automatiquement
/// d'une "encapsulation" des allocations et libérations mémoires (malloc, free ...)
///
/// -> Avoir une "protection" sur les échecs d'allocation :
///    concrètement une terminaison immédiate du programme, ce n'est
///    pas la solution ultime mais évite un plantage ultérieur...
///
/// -> Comptabiliser précisément le nombre d'allocations et de libérations
///    pour avoir un bilan complet avec alloc_bilan() et vérifier l'absence de fuite mémoire.
///
/// -> Fonctions concernées :   malloc, calloc, realloc, strdup, free

/*      Usage :

   Inclure memoire.h en tête de TOUS les .c du projet
   L'inclusion peut être directe (dans les .c)
   ou indirecte (dans un .h lui même inclus dans le(s) .c)
   Le reste du code est inchangé.


   Appeler   memoire_alloc_bilan();  pour avoir un bilan complet
   Ce bilan peut être fait à n'importe quel moment,
   ou à la fin du programme (juste avant le return 0 du main)


   Mettre la variable globale  memoire_tracer  à 1 pour avoir le détail en console
   Exemple pour étudier précisément ce qui se passe dans "faire des choses" :

    memoire_tracer = 1;

    faire des choses

    memoire_tracer = 0;

*/


#ifndef SERVICES_H_INCLUDED
#define SERVICES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

//===========================================================
/// Booléen pour trace détaillée en console à chaque appel ( non par défaut )
extern int memoire_tracer;


//===========================================================
/// Affichage bilan allocations/libérations.
void memoire_alloc_bilan();


/// Wrappers : NE PAS APPELER DIRECTEMENT
/// VOS APPELS A MALLOC etc... VONT AUTOMATIQUEMENT APPELER CES FONCTIONS
void *malloc_check(size_t size);
void free_check(void *ptr);
void *calloc_check(size_t nmemb, size_t size);
void *realloc_check(void *ptr, size_t size);
char *strdup_check(const char *s);


//===========================================================
/// Déroutage des fonctions mémoire standards vers les fonctions wrappers du module.

#define malloc malloc_check
#define free free_check
#define calloc calloc_check
#define realloc realloc_check
#define strdup strdup_check


#endif // MEMOIRE_H_INCLUDED

