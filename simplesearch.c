#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../myLibs/colib.h"
#include "../myLibs/functions.h"

#define N 100000



int main(int argc, char const *argv[]) {
    srand(time(NULL)); 
    time_t start, end;
    double CPU_time;
    int i, j, counter =0, searchNum = randomGenInteger(1, 200);
    int **A;
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
    start = clock();
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(A[i][j] == searchNum){
                counter++;
            }
        }
    }
end = clock();
CPU_time = end - start;

    printf("\nTimes the random number"YEL" %d "RESET" found in plurality of"YEL" %d "RESET" are "YEL" %d"RESET" and the time needed was"GRN" %5.6f"RESET,searchNum, N, counter, CPU_time/CLOCKS_PER_SEC);

    free(A);
        
}