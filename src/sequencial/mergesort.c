#include <stdio.h>

#include "mergesort.h"
#include "merge.h"

void seq_mergesort(long long int *vetor, long long int inicio, long long int final)
{
  if (inicio >= final)
    return;

  int meio = (inicio + final) / 2;

  seq_mergesort(vetor, inicio, meio);
  seq_mergesort(vetor, meio + 1, final);

  merge(vetor, inicio, meio, final);
}