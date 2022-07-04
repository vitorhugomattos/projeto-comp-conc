#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "mergesort.h"
#include "../sequencial/mergesort.h"
#include "../sequencial/merge.h"

void par_mergesort(void *args)
{
  // definição das variáves
  tArgs *args = (tArgs *)args;

  long long int *vetor = args->vetor;
  long long int inicio = args->inicio;
  long long int final = args->final;
  int threads_livres = args->threads_livres;

  if (inicio >= final)
    return;

  long long int meio = (inicio + final) / 2;

  // estrutura para guardar os argumentos para as threads
  tArgs *args_filhos = (tArgs *)malloc(sizeof(tArgs) * 2);

  // identificadores das threads
  pthread_t threads_ids[2];

  for (size_t i = 0; i < 2; i++)
  {
    args_filhos[i].threads_livres = threads_livres - i - 1;
    args_filhos[i].vetor = vetor;
    args_filhos[i].inicio = inicio + i * (meio - inicio + 1);
    args_filhos[i].final = meio + i * (final - meio);

    if (threads_livres > 0)
    {
      if (pthread_create(&threads_ids[i], NULL, par_mergesort, (void *)&args_filhos[i]))
      {
        printf("[ERRO] pthread_create()\n");
        exit(EXIT_FAILURE);
      }
    }
    else
      par_mergesort((void *)&args_filhos[i]);
  }

  merge(vetor, inicio, meio, final);
}