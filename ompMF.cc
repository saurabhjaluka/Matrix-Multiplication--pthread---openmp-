#include<omp.h>
#include "defs.h"

int ompMF(int ld, double** matrix)
{ 
  double diag;
  int error = 0,i,j,k;
omp_set_num_threads(getTC());
#pragma omp parallel firstprivate(ld,matrix) private(i,j,k,diag)
{
		
  for (k=0; k<ld; k++)  {
    if (matrix[k][k] == 0.0) {
      error=1;
	break;
    }

    diag = 1.0 / matrix[k][k];
	#pragma omp for schedule(static)
    for (i=k+1; i < ld; i++) {
      matrix[k][i] = diag * matrix[k][i];
    }
	
	#pragma omp for schedule(static)
    for (i=k+1; i<ld; i++) {
      for (j=k+1; j<ld; j++) {
        matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j];
      }
    }
	
}
}	
  return error;
}
