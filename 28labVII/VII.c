#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int cnt3 = 0, cnt2 = 0, cnt1 = 0, cnt = 1;
static int l, c, maxnum;


void fileOpener(FILE * in) {

  int line, coll;

  fscanf(in, "%d %d", &line, &coll);

  float inputf;

  if (line * coll > 3) {
    maxnum = line * coll /3;
  }
  else maxnum = 1;

  l = line;
  c = coll;
  cnt = 1;

}

void theMSprint(FILE * in, int **cip, int **pi, float **ye) {

  *cip = malloc(sizeof(int) * maxnum);
  *pi = malloc(sizeof(int) * maxnum);
  *ye = malloc(sizeof(float) * maxnum);

  int cn2 = 0;
  float inputf;


  putchar('\n');


  for (int i = 0; i < l; i++) {
    for (int j = 0; j < c; j++) {
      if (!fscanf(in,"%f", &inputf)) break;

      if ( inputf != 0 ) {
        (*cip)[cn2] = i;
        (*pi)[cn2] = j;
        (*ye)[cn2] =  inputf;
        cn2 ++;
        printf("%.3f\t", inputf);
      }
      else printf("0\t");

    }
    putchar('\n');
  }
  if (cnt == 1) cnt1 = cn2;
  else if (cnt == 2) cnt2 = cn2;
  cnt ++;

}

void theINprint(float *ye, int *cip, int *pi) {
  putchar('\n');
  putchar('\n');

  int cout;
  if (cnt == 1) cout = cnt1;
  else if (cnt == 2) cout = cnt2;


  printf("ye:\n" );
  for (int i = 0; i < cout; i++ ) {
    printf("%.3f\t", ye[i]);
  }
  putchar('\n');
  printf("cip:\n" );
  for (int i = 0; i < cout; i++ ) {
    printf("%d\t", cip[i]);
  }
  putchar('\n');
  printf("pi:\n" );
  for (int i = 0; i < cout; i++ ) {
    printf("%d\t", pi[i]);
  }
  putchar('\n');
  putchar('\n');
  putchar('\n');
  cnt++;
}

void countSumMX(float *ye1, float *ye2, int *cip1, int *cip2, int *pi1, int *pi2, float *ye3, int *cip3, int *pi3) {

  int a = 0;
  int b = 0;
  int k = 0;

  while ((a < cnt1 || b < cnt2 ) && k < cnt3) {

    if( cip1[a] < cip2[b] && a <= cnt1 && b <= cnt2) {
      cip3[k] = cip1[a];
      pi3[k] = pi1[a];
      ye3[k] = ye1[a];
      k ++;
      a ++;
    }

    else if(cip1[a] == cip2[b]) {

      if (pi1[a] < pi2[b]) {
        cip3[k] = cip1[a];
        pi3[k] = pi1[a];
        ye3[k] = ye1[a];
        k ++;
        a ++;
      }

      else if (pi1[a] ==  pi2[b] ) {

        cip3[k] = cip1[a];
        pi3[k] = pi1[a];
        ye3[k] = ye1[a] + ye2[b];
        k ++;
        a ++;
        b ++;
      }
      else { // pl1[a] > pl2[b]
        cip3[k] = cip2[b];
        pi3[k] = pi2[b];
        ye3[k] = ye2[b];
        k ++;
        b ++;
      }
    }

    else { // cip[a] > cip[b]
      cip3[k] = cip2[b];
      pi3[k] = pi2[b];
      ye3[k] = ye2[b];
      k ++;
      b ++;
    }
  }
}

void theMXsum( int *cip3, int *pi3, float *ye3) {

  printf("Matrix 3:\n");
  int out = 0;
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < c; j++) {
      if (i == cip3[out] && j == pi3[out]) {
        printf("%.3f\t", ye3[out]);
        out ++;
      }
      else printf("0\t");
    }
    putchar('\n');
  }

}

void theSumInPr( float *ye3, int *cip3, int *pi3 ) {
  putchar('\n');
  putchar('\n');
  printf("ye3:\n");
  for (int i = 0; i < cnt3; i++ ) {
    printf("%.3f\t", ye3[i]);
  }
  putchar('\n');
  printf("cip3:\n");
  for (int i = 0; i < cnt3; i++ ) {
    printf("%d\t", cip3[i]);
  }
  putchar('\n');

  printf("pi3:\n");
  for (int i = 0; i < cnt3; i++ ) {
    printf("%d\t", pi3[i]);
  }
  putchar('\n');
  putchar('\n');
}

void sumSymm(int *cip3, int *pi3, float *ye3) {
  if (l != c) {
    printf("\nNot symmetric matrix \n");
  }
  else {
    int sym = 0;

    for (int i = 0; i < cnt3; i++) {
      if (cip3[i] == pi3[i]) {
        sym ++;
      }
      for (int j = i+1; j < cnt3; j++) {
        if (cip3[i] == pi3[j] && pi3[i] == cip3[j] && ye3[i] == ye3[j]){
          sym +=2;
        }

      }
    }
  if (sym == cnt3) printf("\nSymmetric matrix\n");
  else  printf("\nNot symmetric matrix \n");
  }
}


int main() {


    int a, g = 1;
    char *input;
    int maxnum ;
    int *cip1, *pi1, *cip2, *pi2, *cip3, *pi3;
    float *ye1,  *ye2, *ye3;
    FILE * in;

    cip1 = NULL,  pi1 = NULL, ye1 = NULL, cip2 = NULL, pi2 = NULL, ye2 = NULL, cip3 = NULL, pi3 = NULL, ye3 = NULL;

    while (g == 1) {
      putchar('\n');
      printf("\n1.Open file with matrices \n2.Print two matrices in normal form \n3.Print two matrices in inner form \n4.Conunt the sum of matrices \n5.Print New matrix in normal way \n6.Print new matrix in inner way \n7.Is new matrix symmetric? \n8.Exit\n" );
      scanf("%d", &a);
      putchar('\n');


      switch (a) {

        case 1: {
          if (!in){
            free(cip1);
            free(cip2);
            free(cip3);
            free(pi1);
            free(pi2);
            free(pi3);
            free(ye1);
            free(ye2);
            free(ye3);
      }

        printf("Input the file name :\n");
        scanf("%s", input);
        in = fopen(input, "r");
        fileOpener( in);



      }break;

        case 2:{
          printf("Matrix 1:\n");
          theMSprint(in, &cip1, &pi1, &ye1);
          printf("Matrix 2:\n");
          theMSprint(in, &cip2, &pi2, &ye2);
          cnt3 = cnt1 + cnt2;
          cnt = 1;

          fclose(in);
          //print two massives in normal form
        }break;

        case 3:{
          printf("Matrix 1:\n");
          theINprint( ye1, cip1, pi1);
          printf("Matrix 2:\n");
          theINprint( ye2, cip2, pi2);
          //print two massives inner form
        }break;

        case 4:{//Do the sum only

          for(int i = 0; i < cnt1; i ++) {
            for(int j = 0; j < cnt2; j++) {
              if (cip1[i] == cip2[j] && pi1[i] == pi2[j] ) cnt3 --;

            }
          }
          putchar('\n');
          cip3 = malloc(sizeof(int) * cnt3);
          pi3 = malloc(sizeof(int) * cnt3);
          ye3 = malloc(sizeof(float) * cnt3);

          countSumMX(ye1, ye2, cip1, cip2, pi1, pi2, ye3, cip3, pi3); // Do the sum of two matrices
        }break;

        case 5:
          theMXsum( cip3, pi3, ye3); //Print the New matix in normal way
          break;

        case 6:
          theSumInPr(ye3, cip3, pi3);// print New matrix in inner way
          break;

        case 7:
          sumSymm(cip3, pi3, ye3);// IS matrix symmetric???????????
          break;


        case 8:
          g = 0;
          break;

      }

    }
    return 0;

}
