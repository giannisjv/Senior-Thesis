#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


#define c 12
#define randomness 2500
int main(int argc, char const *argv[]) {



  srand(time(NULL));
  time_t startSe, StopSe;
  double time_sequ;
  double start = 0.0 , end = 0.0;
  double time_taken = 0.0;



  int i, j, p, l, sum = 0, counter = 0;
  int NA, MA, NB, MB;
  int **A, **B, **C;
  int RowsA, ColumnsA;
  int RowsB, ColumnsB;




 //Inserting the first Matrix
  printf("\n Insert First Matrix's Number of Rows: \n");
  scanf("%d",&NA);

  printf("\n Insert First Matrix's Number of Columns from A \n and Rows from B: \n");

  scanf("%d",&MA);
// Inserting the second Matrix
  NB = MA;

  printf("\nInsert Second Matrix's Number of Columns: \n");

  scanf("%d",&MB);


/* checking if both Matrices Rows from A are equal to Columns from B
and if Rows from B are equal to Columns from A*/

/* checking finished */

/*
MA = NA;
NB = NA;
MB = NA;

if (MA != NB){
  printf("\nM from A and N from B are not equal\n");
  return -1;
}
*/
  RowsA =    NA * sizeof(int *);
  ColumnsA = MA * sizeof(int);

  RowsB =    NB * sizeof(int *);
  ColumnsB = MB * sizeof(int);
  //printf("Here i am Before malloc\n" );

  A = (int **)malloc(RowsA);
      for(i=0;i<NA;i++){
      A[i] = (int *)malloc(ColumnsA);
    }


    if(!A){
      printf("The Matrix is too big\nExiting\n");
      return -1;
    }

    B = (int **)malloc(RowsB);
      for(i=0; i<NB; i++){
        B[i] = (int *)malloc(ColumnsB);
      }

if(!B){
        printf("The Matrix is too big\nFreeing A and Exiting\n");
        free(A);
        return -1;
      }

        C = (int **)malloc(RowsA);
          for(i=0;i<NA;i++){
            C[i] = (int *)malloc(ColumnsB);
          }

if(!C){
        printf("The Matrix is too big\nFreeing A and B\nExiting\n");
        free(A);
        free(B);
        return -1;
          }


          for(i=0; i<NA; i++){
            for (j=0; j<MA; j++) {
            A[i][j] = rand() % randomness + 1;

            }
          }


          for(i=0; i<NB; i++){
            for (j=0; j<MB; j++) {
              B[i][j] = rand() % randomness + 1;

            }
          }

          for(i=0; i<NA; i++){
            for (j=0; j<MB; j++) {
              C[i][j] = 0;

            }
          }

          for(l=1; l<c; l*=2){

            for(i=0; i<NA; i++){
            for (j=0; j<MB; j++) {
              C[i][j] = 0;
              }
            }


      start = omp_get_wtime();
      #pragma omp parallel for collapse(2) schedule(static) num_threads(l) private(i, j, p, sum) shared(A, B, C, NA, MB, MA)
      	 for(i=0; i<NA; i++){
            for (j=0; j<MB; j++) {
              for(p=0; p<MA; p++){

                sum += A[i][p] * B[p][j];


            //  printf("\n\ni = (%d) j= (%d) p = (%d) C = (%d)",i,j,p,C[i][j] );
          }

          #pragma omp nowait
          C[i][j] = sum;
          sum = 0;

          }
        }

end = omp_get_wtime();
time_taken = (end - start);

printf("Number of CPUs used:"YEL" (%d)"RESET" Time tooked "RED"(%5.6f)"RESET" N, M, Number of operations: "CYN"(%d, %d, %d) \n"RESET,l,time_taken, NA, MB,((NB*MA)+((NB*MA -1))));
          }




  //time_taken /= CLOCKS_PER_SEC;

      /*    -------------------------------------
             | print statements for the Matrices |
             -------------------------------------

            printf("\n\nMatrix A\n");
             for(i=0; i<NA; i++){
               printf("\n");
               for (j=0; j<MA; j++) {
                 printf("(%d)\t", A[i][j]);
                              }
             }

             printf("\n\nMatrix B\n");
             for(i=0; i<NB; i++){
               printf("\n");
               for (j=0; j<MB; j++) {
                 printf("(%d)\t", B[i][j]);
                              }
             }

             printf("\n\nMatrix C\n");
             for(i=0; i<NA; i++){
               printf("\n");
               for (j=0; j<MB; j++) {
                 printf("(%d)\t", C[i][j]);
                              }
}
*/


printf("\n");

 startSe = clock();
for(i=0; i<NA; i++){
  for (j=0; j<MB; j++) {
    for(p=0; p<MA; p++){

      sum += A[i][p] * B[p][j];
  //  printf("\n\ni = (%d) j= (%d) p = (%d) C = (%d)",i,j,p,C[i][j] );
}


    if(C[i][j] !=  sum){
      counter++;
    }
     sum = 0;
    //  printf("Wrong at %d,%d,%d\n",i,j,sum );


    }

    }

StopSe = clock();

time_sequ = StopSe - startSe;
time_sequ /= CLOCKS_PER_SEC;


printf("\nTime took Sequencialy: "RED"(%5.6f)"RESET" Wong was found "CYN"(%d)\n"RESET, time_sequ,counter);
printf("\nTime took to run the program: "RED"(%5.6f)"RESET" Time took sequencialy finding pobable errors "GRN"(%5.6f)"RESET" Wrong was: "BLU"%d\n"RESET,time_taken,time_sequ, counter );

             free(A);
             free(B);
             free(C);

  return 0;
}
