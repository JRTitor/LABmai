#include "sort.h"

void QSwap(QQ *queue1, QQ *queue2) {
	QQ tmp;

	tmp = *queue1;
	*queue1 = *queue2;
	*queue2 = tmp;
}

void QSort(QQ *queue) {
	int cap = queueCapacity(queue);
	item max;
	QQ uno;
	QQ dwe;
	QQ tmp;

	if (cap < 2)
		return;

	createQueue(&uno ,cap);
	createQueue(&dwe ,cap);
	createQueue(&tmp, cap);


	max = front(queue);

	dequeue(queue);
	enqueue(&uno, max);

	while (!isEmpty(queue)) {
		if (front(queue).key > max.key) {
			max = front(queue);
			dequeue(queue);
			enqueue(&uno, max);
		}else {
			while (front(&uno).key < front(queue).key) {
				enqueue(&dwe, front(&uno));
				dequeue(&uno);
			}

			enqueue(&dwe, front(queue));
			dequeue(queue);

			while (!isEmpty(&uno)) {
				enqueue(&dwe, front(&uno));
				dequeue(&uno);
			}

			QSwap(&dwe, &uno);
		}
	}

	QSwap(&uno, queue);

	QDestroy(&uno);
	QDestroy(&dwe);
	QDestroy(&tmp);
}
