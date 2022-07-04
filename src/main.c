#include "sequencial/mergesort.h"
#include "paralelo/mergesort.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
  // lê o número de elementos do vetor
  int n_threads;
  long long int dimensao;

  // recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
  if (argc < 3)
  {
    fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  dimensao = atoll(argv[1]);
  n_threads = atoi(argv[2]);

  // aloca memória para os vetores
  long long int *vetor_sequencial = (long long int *)malloc(sizeof(long long int) * dimensao);
  long long int *vetor_paralelo = (long long int *)malloc(sizeof(long long int) * dimensao);

  // inicializa o gerador de números aleatórios
  srand(time(NULL));

  // gera os números aleatórios para os vetores
  for (long long int i = 0; i < dimensao; i++)
    vetor_sequencial[i] = vetor_paralelo[i] = rand() % dimensao;

  // variáveis para contagem de tempo
  double inicio_tempo, final_tempo, diferenca_tempo;

  // verifica o número de threads
  if (n_threads <= 1)
  {
    // ordena o vetor sequencialmente
    GET_TIME(inicio_tempo);
    seq_mergesort(vetor_sequencial, 0, dimensao - 1);
    GET_TIME(final_tempo);

    // calcula o tempo de ordenação sequencialmente
    diferenca_tempo = final_tempo - inicio_tempo;
    printf("Tempo de ordenação sequencial: %e\n", diferenca_tempo);

    // verifica se o vetor sequencial está ordenado
    for (long long int i = 0; i < dimensao - 1; i++)
    {
      if (vetor_sequencial[i] > vetor_sequencial[i + 1])
      {
        fprintf(stderr, "[Erro] Vetor sequencial não está ordenado.\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  else
  {
    // estrutura para guardar os argumentos para as threads
    tArgs *args_merge = (tArgs *)malloc(sizeof(tArgs) * 2);

    args_merge->threads_livres = n_threads;
    args_merge->vetor = vetor_paralelo;
    args_merge->inicio = 0;
    args_merge->final = dimensao - 1;

    // ordena o vetor paralelamente
    GET_TIME(inicio_tempo);
    par_mergesort((void *)&args_merge);
    GET_TIME(final_tempo);

    // calcula o tempo de ordenação paralela
    diferenca_tempo = final_tempo - inicio_tempo;
    printf("Tempo de ordenação paralela: %e\n", diferenca_tempo);

    // verifica se o vetor paralelo está ordenado
    for (long long int i = 0; i < dimensao - 1; i++)
    {
      if (vetor_paralelo[i] > vetor_paralelo[i + 1])
      {
        fprintf(stderr, "[Erro] Vetor paralelo não está ordenado.\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  return 0;
}
