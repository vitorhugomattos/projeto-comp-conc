#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "timer.h"

typedef struct
{
  long long inicio;
  long long final;
  int eh_thread;
} tArgs;

// declaração das funções
void merge(int vetor_n, long long int inicio, long long int meio, long long int final);
void seq_mergesort(long long int inicio, long long int final);
void *conc_mergesort(void *args);

// variáveis de exclusão mútua
pthread_mutex_t mutex_threads_livres;

// variáveis globais
int threads_livres;
int *vetor_sequencial;
int *vetor_paralelo;

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

  if (dimensao <= 0 || n_threads <= 0)
  {
    fprintf(stderr, "[ERRO] Dimensao do vetor e numero de threads devem ser positivos\n");
    exit(EXIT_FAILURE);
  }

  threads_livres = n_threads;

  // aloca memória para os vetores
  vetor_sequencial = malloc(sizeof(int) * dimensao);
  vetor_paralelo = malloc(sizeof(int) * dimensao);

  // inicializa o gerador de números aleatórios
  srand(time(NULL));

  // gera os números aleatórios para os vetores
  for (long long i = 0; i < dimensao; i++)
  {
    vetor_sequencial[i] = vetor_paralelo[i] = rand() % dimensao;
  }

  // variáveis para contagem de tempo
  double inicio_tempo, final_tempo = 0;

  // verifica o número de threads
  if (n_threads <= 1)
  {
    // ordena o vetor sequencialmente
    GET_TIME(inicio_tempo);
    seq_mergesort(0, dimensao - 1);
    GET_TIME(final_tempo);

    // calcula o tempo de ordenação sequencialmente
    printf("Tempo de ordenação sequencial: %lf\n", final_tempo - inicio_tempo);

    // verifica se o vetor sequencial está ordenado
    for (long long i = 0; i < dimensao - 1; i++)
    {
      if (vetor_sequencial[i] > vetor_sequencial[i + 1])
      {
        fprintf(stderr, "[ERRO] Vetor sequencial não está ordenado.\n");
        exit(EXIT_FAILURE);
      }
    }
  }
  else
  {
    // estrutura para guardar os argumentos para as threads
    tArgs args_merge;

    args_merge.inicio = 0;
    args_merge.final = dimensao - 1;

    tArgs *args_merge_threads = malloc(sizeof(*args_merge_threads));
    *args_merge_threads = args_merge;

    // inicia o timer
    GET_TIME(inicio_tempo);

    // inicializa a variável de exclusão mútua
    pthread_mutex_init(&mutex_threads_livres, NULL);

    // ordena o vetor paralelamente
    (*conc_mergesort)(args_merge_threads);

    // destrói a variável de exclusão mútua
    pthread_mutex_destroy(&mutex_threads_livres);

    // finaliza o timer
    GET_TIME(final_tempo);

    free(args_merge_threads);

    // calcula o tempo de ordenação paralela
    printf("Tempo de ordenação paralela: %lf\n", final_tempo - inicio_tempo);

    // verifica se o vetor paralelo está ordenado
    for (long long int i = 0; i < dimensao - 1; i++)
    {
      if (vetor_paralelo[i] > vetor_paralelo[i + 1])
      {
        fprintf(stderr, "[ERRO] Vetor paralelo não está ordenado.\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  return 0;
}

void merge(int vetor_n, long long int inicio, long long int meio, long long int final)
{
  int *vetor;
  if (vetor_n)
    vetor = vetor_paralelo;
  else
    vetor = vetor_sequencial;

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

void seq_mergesort(long long int inicio, long long int final)
{
  if (inicio >= final)
    return;

  int meio = (inicio + final) / 2;

  seq_mergesort(inicio, meio);
  seq_mergesort(meio + 1, final);

  merge(0, inicio, meio, final);
}

void *conc_mergesort(void *arg)
{
  // definição das variáves
  tArgs *args = (tArgs *)arg;

  long long int inicio = args->inicio;
  long long int final = args->final;
  int eh_thread = args->eh_thread;

  if (inicio >= final)
  {
    if (eh_thread == 0)
      return NULL;

    pthread_mutex_lock(&mutex_threads_livres);
    threads_livres++;
    pthread_mutex_unlock(&mutex_threads_livres);
    pthread_exit(NULL);
  }

  long long meio = (inicio + final) / 2;

  // estrutura para guardar os argumentos para as threads
  tArgs *args_filho = (tArgs *)malloc(sizeof(tArgs) * 2);

  // identificadores das threads
  pthread_t threads_ids[2];
  for (size_t i = 0; i < 2; i++)
    threads_ids[i] = 0;

  for (size_t i = 0; i < 2; i++)
  {
    args_filho[i].inicio = inicio + i * (meio - inicio + 1);
    args_filho[i].final = meio + i * (final - meio);
    args_filho[i].eh_thread = 0;

    // toma o lock do inteiro que representa o número de threads livres
    pthread_mutex_lock(&mutex_threads_livres);

    if (threads_livres > 0)
    {
      threads_livres--;
      // libera o lock do inteiro que representa o número de threads livres
      pthread_mutex_unlock(&mutex_threads_livres);

      args_filho[i].eh_thread = 1;
      if (pthread_create(&threads_ids[i], NULL, conc_mergesort, (void *)&args_filho[i]))
      {
        fprintf(stderr, "[ERRO] pthread_create()\n");
        exit(EXIT_FAILURE);
      }
    }
    else
    {
      // libera o lock do inteiro que representa o número de threads livres
      pthread_mutex_unlock(&mutex_threads_livres);

      (*conc_mergesort)((void *)&args_filho[i]);
    }
  }

  // aguardar o termino das threads
  int i = 0;
  while (threads_ids[i] != 0 && i < 2)
  {
    if (pthread_join(threads_ids[i], NULL))
    {
      fprintf(stderr, "[ERRO] pthread_join()\n");
      exit(EXIT_FAILURE);
    }
    i++;
  }

  free(args_filho);

  merge(1, inicio, meio, final);
}
