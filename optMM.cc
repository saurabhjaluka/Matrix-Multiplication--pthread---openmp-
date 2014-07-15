int min(int x,int y){
	if(x<y)
		return x;
	else
		return y;
}

void optMM(int N, double **A, double **B, double **C)
{
  // make the code below optimized matrix multiplation routine

  // you should modify or tweak some/all these to get the better performance
  int nrolls = 8;
  int blocksize = 512;
double tmp=0,boundaryCondition=0,ifBoundary;
  int i = 0, j = 0, k = 0;
int iB=0,jB=0,kB=0;
	for(iB=0;iB<N;iB+=blocksize) {
		for(jB=0;jB<N;jB+=blocksize) {
			for(kB=0;kB<N;kB+=blocksize) {
  				for (i = iB; i < min(N,iB+blocksize); i++) {
					for (j = jB; j < min(N,jB+blocksize); j++) {
						tmp=C[i][j];
						boundaryCondition=min(kB+blocksize,N);
						ifBoundary=boundaryCondition-nrolls;
						for (k = kB; k <= ifBoundary ; k+=nrolls) {
							tmp += A[i][k] * B[k][j];
							tmp += A[i][k+1] * B[k+1][j];
							tmp += A[i][k+2] * B[k+2][j];
							tmp += A[i][k+3] * B[k+3][j];
							tmp += A[i][k+4] * B[k+4][j];
							tmp += A[i][k+5] * B[k+5][j];
							tmp += A[i][k+6] * B[k+6][j];
							tmp += A[i][k+7] * B[k+7][j];
					      	}
						if(k!=boundaryCondition)
						{
							for(;k<boundaryCondition;k++)
							{tmp+=A[i][k]*B[k][j];}
						}	
						C[i][j]=tmp;
    					}
  				}
			}
		}
	}
  return;
}

