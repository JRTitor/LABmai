#include "passanger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  char *par = argv[1];

  if ( strcmp(par, "-f") == 0 ) {
    passanger p;
    FILE * in = fopen(argv[2], "rb");
    int l = sizeof(p);

    printf("IN - initials of the passanger\n");
    printf("LG - amount of the luggage\n");
    printf("LW - the weight of the luggage\n");
    printf("T - number of transfers\n");
    printf("CN - amount of children\n");
    printf("________________________________________________________\n");
    printf("|     name     |IN|LG|LW|   destination   | time |T |CN|\n");
    printf("________________________________________________________\n");

    while (fread(&p, l, 1, in) == 1) {
      printf("|%14s|%2s|%2d|%2d|%17s|%7s|%2d|%2d|\n", p.Sername, p.NameInitials, p.number_of_luggage, p.weight_of_luggage, p.destination, p.time, p.IsTransfer, p.child_num);

    }
    printf("________________________________________________________\n");
    fclose(in);
  }


  else if ( strcmp(par, "-p") == 0) {

    int pr =  atoi(argv[2]);
    passanger p;
    FILE * in = fopen(argv[3], "rb");
    int l = sizeof(p);
    int avgsum = 0;
    int n = 0;

    while( fread(&p, l, 1, in) == 1) {
      if (p.weight_of_luggage != 0) {
        avgsum += ( p.weight_of_luggage / p.number_of_luggage);
      }
      n++;
    }

    int avg = avgsum/ n;
    int avgpass = 0;

    fseek(in, 0, SEEK_SET);

    while( fread(&p, l, 1, in) == 1) {


      if (p.weight_of_luggage != 0) {
        avgpass = ( p.weight_of_luggage / p.number_of_luggage);
      }

      if( abs(avg - avgpass) < pr ){
        printf("%s %s\n", p.Sername, p.NameInitials );
      }

      avgpass = 0;
    }

    fclose(in);
  }
  else {
    printf("Input: ./hand -f <filename>\nTo see full genareted list of passangers\nInput: ./hands -p <number> <filename>\nTo see the job of p in this task \n");
    return 1;
  }



  return 0;
  }
