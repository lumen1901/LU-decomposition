#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[]) {

    int n,i,j;
    int calc;
    double **a;

    FILE* data;

    data = fopen(argv[1], "r");     // open data stream

    fscanf(data, "%d", &n);     // fscanf the dimension of A
    fscanf(data, "%d", &calc);      // fscanf how much b's there are

    a = malloc(n * sizeof(double*));       // allocate memory for one row
    if(NULL == a)
    {
        printf("Kein virtueller RAM mehr vorhanden ... !");
        return EXIT_FAILURE;
    }
    for (i = 0; i<n; i++) {
        a[i] = malloc(n*sizeof(double));   // allocate memory for every column
    }

    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
         fscanf(data, "%lf", &a[i][j]);      // fscanf every entry
      }
    }


    double r[n][n];      // R = A
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
          r[i][j] = a[i][j];
      }
    }

    double l[n][n];

    for (i = 0; i < n; i++) {       // set L as In
      for (j = 0; j < n; j++) {
          l[i][j] = 1;
      }
    }

    for (i = 0; i < n; i++) {       // 0-case
      for (j = 0; j < n; j++) {
          if (j > i) {
             l[i][j] = 0;
          }
      }
    }




    for (i = 0; i < n-1; i++) {     // algorithm for L and R
        for(j = i+1; j < n; j++ ) {

            l[j][i] = r[j][i]/r[i][i];


        for (int k = i; k < n; k++) {
            r[j][k] = r[j][k] - l[j][i] * r[i][k];
        }
        }
    }
    printf("R\n");

    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
         printf(" %lf ", r[i][j]);      // print R
      }
    printf("\n");
    }


printf("L\n");
for (i = 0; i < n; i++) {
  for (j = 0; j < n; j++) {
     printf(" %lf ", l[i][j]);      // print L
  }
printf("\n");
}
printf("\n" );



    double b [calc][n];

    for (i = 0; i < calc; i++  ) {      // fscanf entries for every b and save them into matrix
        for (j = 0; j < n; j++) {
            fscanf(data, "%lf", &b[i][j]);

        }
    }


    double y[calc][n];      // vector(s) yi
    double x[calc][n];      // vector(s) xi

    double summa;       // sum

    for(int count = 0; count < calc; count++) {     // count over the ammount of b's

        for (i = 0; i < n; i++) {

            summa = 0;

            if (i == 0) {       // 0-case
                y[count][i] = b[count][i] / l[i][i];
                continue;
            }
            for (int k = 0; k < i; k++) {

                summa = summa + l[i][k] * y[count][k];      // sum

            }

            y[count][i] = 1/l[i][i] * (b[count][i] - summa);        // algorithm for yi

        }

    }



    for(int count = 0; count < calc; count++) {

        for (i = n-1; i >= 0; i--) {



            if (i == n-1) {
                x[count][n-1] = y[count][n-1] / r[n-1][n-1];        // n-case
                continue;
            }
            summa = 0;

            for (int k = i+1; k < n; k++) {

                summa = summa + r[i][k] * x[count][k];      // sum

            }

            x[count][i] = 1/r[i][i] * (y[count][i] - summa);    // algorithm for xi

        }

    }


    for (int count = 0; count < calc; count ++) {

        for (i = 0; i < n; i++) {
          for (j = 0; j < n; j++) {
             printf(" %lf ", a[i][j]);      // print A
          }
          printf(" * %lfx%i",x[count][i], i+1);
          printf(" = %lf",b[count][i]);
          printf("\n");


        }
        printf("\n");
    }







    fclose(data);       // close data stream


    return 0;
}
