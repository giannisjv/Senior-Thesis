#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "../myLibs/colib.h"
#include "../myLibs/functions.h"

#define N 200
#define M 150
#define cores 8

int main(int argc, char const *argv[])
{
    // Defining 3 arrays as pointers for use with malloc
    int **A, **B, **C; //
    int i, j, s, f, c;
    int ARow, ACol, BRow, BCol ,CRow, CCol, stRow, stCol;
    int NN = N * N;
    time_t SeqStart, SeqEnd;
    
    double CPU_time = 0.0;
    double Start = 0.0, Stop =0.0;
    srand(time(NULL));
    
    // Making the Matrices Dynamicly by the user...
/*
        ARow = randomGenInteger(1, 3);
        ACol = randomGenInteger(1, 3);

        BRow = randomGenInteger(1, 3);
        BCol = randomGenInteger(1, 3);
*/

        ARow = N;
        ACol = M;

        BRow = M;
        BCol = N;

        // initiate CRow and CCol
        CRow = ARow * BRow;
        CCol = ACol * BCol;




    //Initiate arrays using malloc!!!
    // A, B
    A = (int **)malloc(ARow * sizeof(int *));
        for(i = 0; i < ARow; i++){
            A[i] = (int *)malloc(ACol * sizeof(int));
        }

    B = (int **)malloc(BRow * sizeof(int *));
        for(i=0; i<BRow; i++){
            B[i] = (int *)malloc(BCol * sizeof(int));
        }

    // C is the product of the multiplication of every single element from A multiplied with B...
     C = (int **)malloc(CRow * sizeof(int *));
        for(i = 0; i < CRow; i++){
            C[i] = (int *)malloc(CCol * sizeof(int)); 
        }


    // Checking if the matrix does not exist
    if(!A){
        printf("\nThe A matrix does not exist\nProbably too big array");
        return -1;
    }

    if(!B){
        printf("\nThe B matrix does not exist\nProbably too big array");
        free(A);
        return -1;
    }


    if(!C){
        printf("\nThe B matrix does not exist\nProbably too big array");
        free(A);
        free(B);
        return -1;
    }


// Filling the matrices with random numbers from -10 to 10
            for (i = 0; i < ARow; i++){
                for (j = 0; j < ACol; j++){
                    A[i][j] = randomGenInteger(-10, 10);
                }
                
            }
            

            for (i = 0; i < BRow; i++){
                for (j = 0; j < BCol; j++){
                    B[i][j] = randomGenInteger(-10, 10);
            }
                }

                SeqStart = clock(); // starting the timer 
                     for(i = 0; i < ARow; i++){ // i from 0 to ROWS cardinality of the first Matrix
                        for (j = 0; j < ACol; j++){ // j from 0 to Columns cardinality of the first Matrix Col
                            stRow = i * BRow; // Matrix C ROW is "i" multiplied by the cardinality of Rows from the second Matrix 
                            stCol = j * BCol; // Matrix C Column is "j" multiplied by the cardinality of Columns from the second Matrix
                                for ( s = 0; s < BRow; s++){ // s from 0 to cardinality of ROWS from the second Matrix
                                     for ( f = 0; f < BCol; f++){ // f from 0 to cardinality of Columns from the second Matrix
                                        C[stRow+s][stCol+f] = (A[i][j]) * (B[s][f]);
                                            // printf("\n\ni %d, j %d, s %d, f %d, Crow %d, Ccol %d",i, j, s, f, CRow+s, CCol+f);
                     }
                          }
                                }
                                    }
            SeqEnd = clock(); 
            CPU_time = SeqEnd - SeqStart;
            printf("\nTime needed for the matrix with (%d*%d) ROWS and (%d*%d) Columns was (%5.6f) sequencialy\n\n",ARow, BRow, ACol, BCol, CPU_time/CLOCKS_PER_SEC);


                for(c = 2; c <= cores; c*=2){
                    Start = omp_get_wtime();
                     #pragma omp parallel for collapse(2) schedule(dynamic, 2) num_threads(c) private(i, j, s, f)
                     for(i = 0; i < ARow; i++){ // i from 0 to ROWS cardinality of the first Matrix
                        for (j = 0; j < ACol; j++){ // j from 0 to Columns cardinality of the first Matrix Col
                            stRow = i * BRow; // Matrix C ROW is "i" multiplied by the cardinality of Rows from the second Matrix 
                            stCol = j * BCol; // Matrix C Column is "j" multiplied by the cardinality of Columns from the second Matrix
                                for ( s = 0; s < BRow; s++){ // s from 0 to cardinality of ROWS from the second Matrix
                                     for ( f = 0; f < BCol; f++){ // f from 0 to cardinality of Columns from the second Matrix
                                        C[stRow+s][stCol+f] = (A[i][j]) * (B[s][f]);
                                            // printf("\n\ni %d, j %d, s %d, f %d, Crow %d, Ccol %d",i, j, s, f, CRow+s, CCol+f);
                     }
                          }
                                }
                                    }
                                    Stop = omp_get_wtime();

            CPU_time = Stop - Start;
            printf("\nTime needed for the matrix with (%d*%d) ROWS and (%d*%d) Columns was (%5.6f) the cores used was (%d) \n\n",ARow, BRow, ACol, BCol, CPU_time, c);
                }
/*
//Display matrix A
printf("\n\n");
printf("Matrix A\n");
        for (i = 0; i < ARow; i++){
            printf("\n");
            for (j = 0; j < ACol; j++){
                    printf("%d\t",A[i][j]);
         }
            } 
      

//Display matrix B
printf("\n\n");
printf("Matrix B\n");
        for (i = 0; i < BRow; i++){
            printf("\n");
            for (j = 0; j < BCol; j++){
                    printf("%d\t",B[i][j]);
         }
            } 



//Display matrix C
printf("\n\n");
printf("Matrix C\n");
        for (i = 0; i < CRow; i++){
            printf("\n"); 
            for (j = 0; j < CCol; j++){
                    printf("%d\t",C[i][j]);
        }
            } 


*/
    free(A);
    free(B);
    free(C);

    return 0;
}
