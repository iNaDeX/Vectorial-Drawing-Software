#include "memoire.h"

//===========================================================
/// Booléen pour trace détaillée en console à chaque appel ( non par défaut )
int memoire_tracer = 0;


//===========================================================
/// Bilan allocations/libérations

/// Total des appels malloc
int alloc_nb_malloc = 0;

/// Total des appels free
int alloc_nb_free = 0;

/// Total des appels calloc
int alloc_nb_calloc = 0;

/// Total des appels realloc
int alloc_nb_realloc = 0;

/// Total des appels strdup
int alloc_nb_strdup = 0;

/// Total des octets réels encore réservés en mémoire
size_t alloc_total_bytes = 0;

/// Maximum des octets réels réservés en mémoire
size_t alloc_max_bytes = 0;

/// Affichage bilan allocations/libérations.
void memoire_alloc_bilan()
{
    int totalloc = alloc_nb_malloc + alloc_nb_calloc + alloc_nb_realloc + alloc_nb_strdup;
    int totfree = alloc_nb_free + alloc_nb_realloc;
    printf("\n\n");
    printf("Allocations : %d ( %d allocations, %d liberations)\n",
           totalloc-totfree, totalloc, totfree);
    printf(" allocations : %d malloc, %d calloc, %d strdup, %d realloc\n",
           alloc_nb_malloc, alloc_nb_calloc, alloc_nb_strdup, alloc_nb_realloc);
    printf(" liberations : %d free, %d realloc\n",
           alloc_nb_free, alloc_nb_realloc);
    printf("\nMemoire maximum utilisee: %u\n", alloc_max_bytes);
    printf("Memoire encore reservee : %u\n", alloc_total_bytes);
}


//===========================================================
/// On neutralise les alias sur les fonctions d'allocation pour utiliser les vraies
#undef malloc
#undef free
#undef calloc
#undef realloc
#undef strdup

//===========================================================
/// Wrappers pour les fonctions d'allocation/libération

void total_bytes(int change)
{
    alloc_total_bytes += change;
    if (alloc_total_bytes>alloc_max_bytes)
        alloc_max_bytes = alloc_total_bytes;
}

void *malloc_check(size_t size)
{
    void *mem;
    mem = malloc(size);
    assert( mem!=NULL );
    alloc_nb_malloc++;
    total_bytes(+_msize(mem));
    if (memoire_tracer) printf("@%p <- malloc %d octets (%d reel)\n", mem, size, _msize(mem));
    return mem;
}

void free_check(void *ptr)
{
    assert(ptr!=NULL);
    if (memoire_tracer) printf("@%p -> free %d octets reel\n", ptr, _msize(ptr));
    total_bytes(-_msize(ptr));
    free(ptr);
    alloc_nb_free++;
}

void *calloc_check(size_t nmemb, size_t size)
{
    void *mem;
    mem = calloc(nmemb, size);
    assert( mem!=NULL );
    alloc_nb_calloc++;
    total_bytes(+_msize(mem));
    if (memoire_tracer) printf("@%p <- calloc %d octets (%d reel)\n", mem, nmemb*size, _msize(mem));
    return mem;
}

void *realloc_check(void *ptr, size_t size)
{
    size_t prevsize = _msize(ptr);
    void * prevptr = ptr;
    total_bytes(-_msize(ptr));
    ptr = realloc(ptr, size);
    assert( ptr!=NULL );
    alloc_nb_realloc++;
    total_bytes(+_msize(ptr));
    if (memoire_tracer) printf("@%p -> realloc %d octets reel ...\n", prevptr, prevsize);
    if (memoire_tracer) printf("@%p <- realloc %d octets (%d reel)\n", ptr, size, _msize(ptr));
    return ptr;
}

char *strdup_check(const char *s)
{
    char *dup;
    assert( s!=NULL );
    dup = strdup(s);
    assert( dup!=NULL );
    alloc_nb_strdup++;
    total_bytes(+_msize(dup));
    if (memoire_tracer) printf("@%p <- strdup %d octets (%d reel)\n", dup, strlen(dup)+1, _msize(dup));
    return dup;
}

//===========================================================
/// Ne pas mettre de code ci après (alias allocations neutralisés)

