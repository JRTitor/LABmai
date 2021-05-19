#include <stdio.h>
#include <stdlib.h>
#include "passanger.h"


int passscan(passanger *p, FILE *ff){
    int a = fscanf(ff,"%s %s %d %d %s %s %d %d",
    p->Sername,
    p->NameInitials,
    &p->number_of_luggage,
    &p->weight_of_luggage,
    p->destination,
    p->time,
    &p->IsTransfer,
    &p->child_num
  );
  return a == 8;
}


int main(int argc, char *argv[]) {


  if (argc != 3) {
    printf("Usage:%s program filename\n", argv[0]);
    return 1;
  }

 passanger p;
 FILE *out = fopen(argv[2], "wb");
 FILE *in = fopen(argv[1], "r");
 int l = sizeof(p);
 if ( !out ) {

   perror("Can't open file");
   return 2;
 }

 while ( !feof(in) ){
   passscan(&p, in);
   fwrite(&p, l, 1, out);
 }



fclose(in);
fclose(out);

return 0;
}
