#include "merge.h"
#include <stdlib.h>

void merge(long long int *vetor, long long int inicio, long long int meio, long long int final)
{
    int *aux = (int *)malloc(sizeof(int) * (final - inicio + 1));
    int indice_primeiro, indice_segundo, indice_interno;

    for (indice_primeiro = inicio, indice_segundo = meio + 1, indice_interno = 0; indice_primeiro <= meio && indice_segundo <= final; indice_interno++)
    {
        if (vetor[indice_primeiro] <= vetor[indice_segundo])
        {
            aux[indice_interno] = vetor[indice_primeiro];
            indice_primeiro++;
        }
        else
        {
            aux[indice_interno] = vetor[indice_segundo];
            indice_segundo++;
        }
    }

    while (indice_primeiro <= meio)
    {
        aux[indice_interno] = vetor[indice_primeiro];
        indice_primeiro++;
        indice_interno++;
    }

    while (indice_segundo <= final)
    {
        aux[indice_interno] = vetor[indice_segundo];
        indice_segundo++;
        indice_interno++;
    }

    for (indice_primeiro = inicio; indice_primeiro <= final; indice_primeiro++)
        vetor[indice_primeiro] = aux[indice_primeiro - inicio];

    free(aux);
}
