// --*-c++-*--
#include <omp.h>
#include <math.h>
#include "defs.h"

void ompMM(int N, double **A, double **B, double **C)
{
  // please change the code below to parallel implementation
  int i=0,j=0,k=0,partition=0,tc=getTC();
	omp_set_num_threads(tc);
	//printf("hello");
	partition = (int)(N / tc);
  #pragma omp parallel for schedule(static,partition) private (i,j,k) firstprivate(N,A,B,C)
 for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        C[i][j] = C[i][j] + A[i][k] * B[k][j];
      }
    }
  }

  return;
}
