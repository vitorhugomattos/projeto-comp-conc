#include "sequencial/mergesort.h"

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
    return 1;
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

  // marca inicio do tempo

  // ordena o vetor sequencialmente
  seq_mergesort(vetor_sequencial, 0, dimensao - 1);

  // verifica se o vetor sequencial está ordenado
  for (long long int i = 0; i < dimensao - 1; i++)
  {
    if (vetor_sequencial[i] > vetor_sequencial[i + 1])
    {
      fprintf(stderr, "[Erro] Vetor sequencial não está ordenado.\n");
      return 1;
    }
  }

  // verifica se o vetor paralelo está ordenado
  for (long long int i = 0; i < dimensao - 1; i++)
  {
    if (vetor_paralelo[i] > vetor_paralelo[i + 1])
    {
      fprintf(stderr, "[Erro] Vetor paralelo não está ordenado.\n");
      return 1;
    }
  }

  return 0;
}
