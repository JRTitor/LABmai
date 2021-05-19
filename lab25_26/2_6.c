#include <stdio.h>
#include "sort.h"

#define MAX_CAP 8

int main() {
  QQ queue;
  int a, g = 1;
  item item;

  createQueue(&queue, MAX_CAP);

  while (g == 1) {
    printf("\n1.Create the queue\t2.Input an elment\t3.Delete elment\t4.Size of queue\n5.Sort\t6.Print the queue\t7.Print front\t8.Exit\n");
    scanf("%d", &a);

    switch (a) {
      case 1:{
        createQueue(&queue, MAX_CAP);
        break;
      }

      case 2: {
        printf("\nInput key value:");
        double key;
        int value;
        scanf("%lf %d", &key, &value);
        item.value = value;
        item.key = key;

        if (enqueue(&queue, item)) {
          printf("\nAdded to the queue\n");
        }
        break;
      }

      case 3: {
        if (!isEmpty(&queue)){
        printf("Dequeued: key:%.3lf value:%d ", front(&queue).key, front(&queue).value);
        dequeue(&queue);
      }else printf("The queue is empty\n");

      break;
      }

      case 4: {
        printf("Size:%d\n", Qsize(&queue));
        break;
      }

      case 5: {
        QSort(&queue);
        break;
      }

      case 6: {
        printf("№\tkey\tvalue\n");
        printQQ(&queue);
        break;
      }

      case 7: {
        printf("Front::: key:%.3lf value:%d \n",front(&queue).key, front(&queue).value);
        break;
      }

      case 8: {
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
