#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include "defs.h"

typedef struct threadInfo{
	int id;
	int Num_Threads;
}ThreadInfo;

typedef struct matrixData{
	int N;
	double **A;
	double **B; 
	double **C;
	ThreadInfo *threaddata;
}MatrixData;

void *computepthreadMM(void* matrixData)
{

ThreadInfo *threadinfo;
int id;
int numThread;
int N;
double **A, **B, **C;
int partition;

int j_lastIndex,j_startIndex;

MatrixData *matrixdata=(MatrixData*) matrixData;
N=matrixdata->N;
A=matrixdata->A;
B=matrixdata->B;
C=matrixdata->C;

id= matrixdata->threaddata->id;
numThread=matrixdata->threaddata->Num_Threads;

partition = (int)ceil(N/(double)numThread);

j_startIndex=id*partition;

if(id==numThread-1)
	j_lastIndex=N;	
else
	j_lastIndex=j_startIndex+partition;

int i = 0, j = 0, k = 0;
  for (i = 0; i < N; i++) {
    for (j = j_startIndex; j < j_lastIndex; j++) {
      for (k = 0; k < N; k++) {
        C[i][j] = C[i][j] + A[i][k] * B[k][j];
      }
    }
  }
}

void pthreadMM(int N, double **A, double **B, double **C)
{
int NUM_THREAD=getTC();
int i;

pthread_t thread[NUM_THREAD];
  for(i=0;i<NUM_THREAD;i++)
	{
		MatrixData *matrixdata=(MatrixData *) malloc(sizeof(MatrixData));
		matrixdata->N=N;
		matrixdata->A=A;
		matrixdata->B=B;
		matrixdata->C=C;		
		ThreadInfo *threadinfo=(ThreadInfo *) malloc(sizeof(ThreadInfo));
		threadinfo->Num_Threads= NUM_THREAD;
		threadinfo->id=i;
		matrixdata->threaddata=threadinfo;
		pthread_create(&thread[i],NULL,computepthreadMM,matrixdata);
	}
	
	for(i=0;i<NUM_THREAD;i++)
	{
		pthread_join(thread[i],NULL);
	}
}
