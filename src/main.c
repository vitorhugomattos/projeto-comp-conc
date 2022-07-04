#include "sequencial/mergesort.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
  // lê o número de elementos do vetor
  int n_threads;
  long long int dimensao;

  // recebe e valida os parametros de entrada (dimensao do vetor)
  if (argc < 2)
  {
    fprintf(stderr, "Digite: %s <dimensao do vetor>\n", argv[0]);
    return 1;
  }
  dimensao = atoll(argv[1]);

  // aloca memória para os vetores
  long long int *vetor = (long long int *)malloc(sizeof(long long int) * dimensao);

  // inicializa o gerador de números aleatórios
  srand(time(NULL));

  // gera os números aleatórios para os vetores
  for (long long int i = 0; i < dimensao; i++)
    vetor[i] = rand() % dimensao;

  // variáveis para contagem de tempo
  double inicio_tempo, final_tempo = 0;

  // ordena o vetor sequencialmente
  GET_TIME(inicio_tempo);
  seq_mergesort(vetor, 0, dimensao - 1);
  GET_TIME(final_tempo);

  // calcula o tempo de ordenação sequencialmente
  printf("Tempo de ordenação sequencial: %lf\n", final_tempo - inicio_tempo);

  // verifica se o vetor sequencial está ordenado
  for (long long int i = 0; i < dimensao - 1; i++)
  {
    if (vetor[i] > vetor[i + 1])
    {
      fprintf(stderr, "[Erro] Vetor sequencial não está ordenado.\n");
      return 1;
    }
  }

  return 0;
}
