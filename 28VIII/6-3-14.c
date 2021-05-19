#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXSIZE 8

#define MENU "1.Print list \t2.Input to list \t3.Remove from list \n4.Lenght of list \t5.Do the task \t6.Exit\n"

typedef struct complex{
  int real;
  int imaginary;
} cx;

cx makeNULL (cx cmplx) {
  cmplx.real = INT_MAX;
  cmplx.imaginary = INT_MIN;
}

bool cxIsNull(cx num) {
  return (num.real == INT_MAX && num.imaginary == INT_MIN);
}

cx inptToCX() {
  cx out;
  int a, b;
  scanf("%d %d", &a, &b);
   out.real = a; out.imaginary = b;
  return out;
}

cx printCX(cx num) {
  printf("%d+(%d)i", num.real, num.imaginary);
}

typedef cx ElemType;

typedef struct {
  ElemType value;
  int ptr;
}Component, SLL[MAXSIZE];


bool initList(SLL space) {
  int i;

  for(i = 0; i < MAXSIZE-1; i++){
    space[i].ptr = i + 1;
  }

  space[MAXSIZE-1].ptr = 0;

  return true;
}


int mallocSLL(SLL L) {
  int k;

  k = L[0].ptr;
  L[0].ptr = L[k].ptr;

  return k;

}

int listLength(SLL sl) {
  int k;
  int i = 0;

  k = MAXSIZE - 1;
  k = sl[k].ptr;

  while(k) {
    k = sl[k].ptr;
    i++;
  }

  return i;
}

void printSLL(SLL L) {
  int k, i, m = 0;
  ElemType value;

  k = MAXSIZE - 1;
  i = L[k].ptr;

  while(i != 0) {
    value = L[i].value;
    printf("list element %d: ", ++m);
    printCX(value); printf("\n" );
    i = L[i].ptr;
  }
}


bool insertEl(SLL L, int i, ElemType e){
  int j, k, m;

  k = MAXSIZE - 1;
  if(i > MAXSIZE || i < 1 || L[k].ptr == 0) {
    return false;
  }

  for(j = 0; j <i-1; j++) {
    k = L[k].ptr;
  }

  m = mallocSLL(L);
  L[m].value = e;
  L[m].ptr = L[k].ptr;
  L[k].ptr = m;
  return true;
}


bool deleteEl(SLL L, int i, ElemType *e){
  int j, k, n1, n2;

  k = MAXSIZE - 1;

  if(i > MAXSIZE || i < 1 || L[k].ptr == 0) {
    return false;
  }

 for(j = 0; j < i-1; j++) {
    k = L[k].ptr;
  }

  n1 = k;
  k = L[k].ptr;
  *e = L[k].value;
  n2 = L[k].ptr;
  L[n1].ptr = n2;
  L[k].ptr = L[0].ptr;
  L[0].ptr = k;

  return true;
}


bool getEl(SLL L, int i, ElemType *e){
  int j, k;

  k = MAXSIZE-1;
  if(i > MAXSIZE || i < 1 || L[k].ptr == 0){
    return false;
  }

  for(j = 0; j < i; j++){
    k = L[k].ptr;
  }
  *e = L[k].value;

  return true;
}

void task(SLL sl ) {
  int size =  listLength(sl) ;

  cx tmp;
  for (int i = 1; i < size && i+1 <= size; i += 2) {
    tmp = sl[i].value;
    sl[i].value = sl[i+1].value;
    sl[i+1].value = tmp;
  }
}


int main() {

  cx inpt;
  int listlen, a, index, g = 1;
  SLL sl;

  initList(sl);

  while (g == 1) {
    printf(MENU);
    scanf("%d", &a);

    switch (a) {
      case 1: {//printing list
        printSLL(sl);
        break;
      }
      case 2: {//input to the list

          if (listLength(sl) < (MAXSIZE - 2)) {
            if (! listLength(sl)) {
            printf("\nINPUT A B for (A+Bi):" );
            sl[1].value = inptToCX();
            sl[0].ptr = 2;
            sl[1].ptr = 0;
            sl[MAXSIZE-1].ptr = 1;
            break;
          }
          printf("Input index:");
          scanf("%d", &index);
          printf("\nINPUT A B for (A+Bi):" );
          inpt = inptToCX();
          if (! insertEl(sl, index, inpt)) printf("Impossible to input\n" );
          break;
        }else {
          printf("Impossible to input, the list is full\n" );
          break;
        }
      } break;
      case 3: {// removing from the list
        printf("Input index:" );
        scanf("%d", &index);
        printf("\nINPUT A B for (A+Bi):" );
        inpt = inptToCX();
        if ( !deleteEl(sl, index, &inpt) || index > listLength(sl)) printf("Impossible to delete\n" );
        break;
      }
      case 4: {//printig lengh of the list
        printf("List length :%d\n", listLength(sl));
        break;
      }
      case 5: {// doing the task
        task(sl);
        break;
      }
      case 6: { //quit all of it
        g = 0;
        break;
      }
      default: {
        printf("Your input is wrong");
        break;
      }
    }
  }
  return 0;
}
