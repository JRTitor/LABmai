#ifndef __passanger_h__
  #define __passanger_h__

  typedef struct{
    char Sername[20];
    char NameInitials[4];
    int number_of_luggage;
    int weight_of_luggage;
    char destination[20];
    char time[7];
    int IsTransfer;
    int child_num;
  } passanger;

  #endif
