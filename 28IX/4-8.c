#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define N 20
#define menu "1.Input file name\t2.Print\t3.Sort\t4.Find element\t5.Reverse\t6.Exit\n"

typedef struct k {
  int num;
  char str[28];
}key;


typedef struct el {
  key value;
  char line[256];
}TR;

void getLine(FILE *stream, char *str, const int size) {
	int cnt = 0, ch;

	while ((ch = getc(stream)) != '\n' && cnt < size - 1)
		str[cnt++] = ch;

	str[cnt] = '\0';
}

void printTable(const TR *a, const int size){
	int i;

	printf("|__________________________________________________________|\n");
	printf("|   Key   |                     value                      |\n");
	printf("|__________________________________________________________|\n");

	for (i = 0; i < size; i++) {
		printf("|%4s %4d|%s\n", a[i].value.str, a[i].value.num, a[i].line);
    printf("|__________________________________________________________|\n");
  }
}

int cmpr(const key *k1, const key *k2) {
	if (strcmp(k1->str, k2->str) == 0)
		return k1->num <= k2->num;

	return (strcmp(k1->str, k2->str) <= 0) ;
}


bool isEqK(const key *fir, const key *scnd) {
  return (fir->num == scnd->num && (strcmp(fir->str, scnd->str) == 0 ));
}

bool binSearch(const TR *arr, const int size, const key *key) {
	int start = 0, end = size - 1, mid;

	if (size <= 0)
		return false;

	while (start < end) {
		mid = start + (end - start) / 2;

		if (isEqK(&arr[mid].value, key))
			return (mid > -1);
		else if (cmpr(&arr[mid].value, key))
			start = mid + 1;
		else
			end = mid;
	}
  if (isEqK(&arr[end].value, key))
    return (end > -1);

  return false;
}

int cmprBt(const key *k1, const key *k2)
{
	if (strcmp(k1->str, k2->str) == 0) {
    if (k1->num > k2->num) return 1;
    if (k1->num < k2->num) return -1;
    if (k1->num == k2->num) return 0;
  }

	return strcmp(k1->str, k2->str) ;
}

void swap(TR *fir, TR *scnd) {
  TR tmp;
  tmp = *fir;
  *fir = *scnd;
  *scnd = tmp;
}

void shakerSort(TR a[], int n) {
    int p, i;
    for (p = 1; p <= n / 2; p++) {
        for (i = p - 1; i < n - p; i++)
            if (cmprBt(&a[i].value, &a[i+1].value) > 0)
                swap(&a[i], &a[i + 1]);
        for (i = n - p - 1; i >= p; i--)
            if (cmprBt(&a[i].value, &a[i-1].value) < 0)
                swap(&a[i], &a[i - 1]);
    }
}

void reverse (TR *arr, const int size) {
  int i, j;
  for (i = 0, j = size -1; i < j; i++, j -- ) {
    swap(&arr[i], &arr[j]);
  }
}


int main() {
	int i, cnt, a;
	char ch;
  char fName[50];
	TR arr[N];
  bool srtd = false;
  int g = 1;
  while (g == 1){
    printf(menu);
    scanf("%d", &a);

    switch (a) {
      case 1: {// input
        printf("Inpur the file name\n");
        scanf("%s", fName);
        FILE *file = fopen(fName, "r");
        if (file == NULL) {
          printf("Error while reading  file\n");
    		  return 0;
    	   }

    	  i = 0;

    	  while (i < N && fscanf(file, "%s %d", arr[i].value.str, &arr[i].value.num) == 2) {
          fscanf(file, "%c", &ch);
          getLine(file, arr[i].line, sizeof(arr[i].line));
    	    i++;
    	  }

        fclose(file);
    	  cnt = i;
        srtd = false;
        break;
      }

      case 2: {// print tab
        printTable(arr, cnt);
        break;
      }

      case 3: {//sort
        shakerSort(arr, cnt);
        srtd = true;
        break;
      }

      case 4: {//search
        if (srtd)  {
          key key ;
          printf("Input the key: " );
          scanf("%s %d", key.str, &key.num);
          if (binSearch(arr, cnt, &key)) printf("found\n");
          else printf("Not found\n" );
        }

        else printf("The table is not sorted\n");
        break;
      }

      case 5: {//reverse
        if (srtd) reverse(arr, cnt);
        else printf("The table is not sorted\n");
        break;
      }

      case 6: {//exit
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
