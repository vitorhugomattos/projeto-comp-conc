#ifndef MERGE_PARALELO_INCLUIDO
#define MERGE_PARALELO_INCLUIDO

// struct para guardar os argumentos para as threads
typedef struct
{
    int threads_livres;
    long long int *vetor;
    long long int inicio;
    long long int final;
} tArgs;

void par_mergesort(void *args)

#endif
