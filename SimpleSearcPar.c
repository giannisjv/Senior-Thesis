#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "../myLibs/colib.h"
#include "../myLibs/functions.h"

//#define N 25000



int main(int argc, char const *argv[]) {
    srand(time(NULL));
    float metrics[40];
    int plurality[40];
    int Cores[40]; 
    
    
    int m=0, p=0, c=0;
    int N = 2000;
    time_t seqStart, Seq_End;
    double CPU_time, CPU_timeSeq;
    double Start = 0.0, Stop =0.0;

    int i, j, counter =0 , counter2 = 0;
    while(N <= 20000){
    int **A;
    int searchNum = randomGenInteger(1, 200);
    //Initiating matrix A with malloc 
    A = (int **)malloc(N * sizeof(int *));
        for(i=0; i<N; i++){
            A[i] = (int *)malloc(N * sizeof(int));
    }

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            A[i][j] = randomGenInteger(1,200);
        }
    }
/*
    printf("\n\n");
    for(i=0; i<N; i++){
        printf("\n");
        for(j=0; j<N; j++){
           printf("\t%d",A[i][j] );
        }
    }
    */

 printf("\n\n");
 printf("======================================");
 printf("\nStarting Sequencial searching with "RED" 1 "RESET" core\n");
    seqStart = clock();
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(A[i][j] == searchNum){
                counter++;
            }
        }
    }
    Seq_End = clock();

CPU_timeSeq = Seq_End - seqStart; 
CPU_timeSeq /= CLOCKS_PER_SEC;
    Cores[c++] = 1;
    plurality[p++] = N; 
    metrics[m++] = CPU_timeSeq;

    printf("Times the random number"YEL" %d "RESET" found in plurality of"YEL" %d "RESET" are "YEL" %d"RESET" and the time needed was"GRN" %5.6f"RESET,searchNum, N, counter, CPU_timeSeq);

   
   for(i=2; i<12; i=i*2){
    
 printf("\n\n");
 printf("======================================");
 printf("\nStarting Sequencial searching parallel with"RED" %d "RESET"cores\n",i);
    Start = omp_get_wtime();
   #pragma omp parallel for collapse(2) schedule(static) num_threads(i) private(counter, searchNum, i, j) shared(A)
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(A[i][j] == searchNum){
                counter++;
            }
        }
    }
    Stop = omp_get_wtime();

CPU_time = Stop - Start;
    Cores[c++] = i;
    plurality[p++] = N; 
    metrics[m++] = CPU_time;
    printf("Times the random number"YEL" %d "RESET" found in plurality of"YEL" %d "RESET" are "YEL" %d"RESET" and the time needed was"GRN" %5.6f"RESET,searchNum, N, counter, CPU_time);
    
}
    free(A);
N += 2000; 
printf("\n\n");
}
 for ( i = 0; i < 40; i++)
 {
     printf(GRN"%2d"RESET"--->Cores "RED"%d"RESET", plurality "YEL"%d"RESET", metrics "MAG"%5.6f"RESET"\n",i+1, Cores[i], plurality[i], metrics[i]);
     counter2++;
     if(counter2 == 4 ){
         printf("\n");
         counter2 = 0;
     }

 }
 printf("\n\n");
return 0;
}