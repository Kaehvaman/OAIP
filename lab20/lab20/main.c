#include <stdio.h>
#include <stdlib.h>

typedef struct tagNODE {
	int data;
	struct tagNODE* next;
} NODE;

NODE* first = NULL;
void addToHead(int value) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if (newNode == NULL) {
		puts("Out of memory");
		exit(EXIT_FAILURE);
	}

	newNode->next = first;
	newNode->data = value;

	first = newNode;
}

void printNodeList() {
	int i = 0;
	printf("first -> ");
	NODE* ptr = first;
	while (ptr != NULL) {
		printf("(%d)[%d] -> ", ptr->data, i);
		ptr = ptr->next;
		i++;
	}
	printf("NULL\n");
}

int popFromHead() {
	if (first == NULL) {
		puts(">>> first is NULL");
		return 0;
	}
	int value = first->data;
	NODE* delNode = first;
	first = first->next;
	free(delNode);
	return value;
}

int popFromIndex(int index) {
	if (first == NULL) {
		puts(">>> first is NULL");
		return 0;
	}

	if (index == 0) {
		return popFromHead();
	}

	NODE* prev_ptr = first;
	NODE* ptr = first->next;
	int i = 1;
	while (ptr != NULL) {
		if (i == index) {
			int value = ptr->data;
			prev_ptr->next = ptr->next;
			free(ptr);

			return value;
		}
		prev_ptr = ptr;
		ptr = ptr->next;
		i++;
	}
	puts(">>> index out of range");
	return 0;
}

int count(int value) {
	NODE* ptr = first;
	int counter = 0;
	while (ptr != NULL) {
		if (ptr->data == value) {
			counter += 1;
		}
		ptr = ptr->next;
	}
	return counter;
}

int evenCount() {
	NODE* ptr = first;
	int counter = 0;
	while (ptr != NULL) {
		if (ptr->data % 2 == 0) {
			counter += 1;
		}
		ptr = ptr->next;
	}
	return counter;
}

void clearNodeList() {
	NODE* delNode;
	while (first != NULL) {
		delNode = first;
		first = first->next;
		free(delNode);
	}
}

int nodeSum() {
	NODE* ptr = first;
	int sum = 0;
	while (ptr != NULL) {
		sum += ptr->data;
		ptr = ptr->next;
	}
	return sum;
}

void test() {
	printNodeList();

	addToHead(10);
	addToHead(10);
	addToHead(20);
	addToHead(30);
	addToHead(10);
	addToHead(20);

	printNodeList();

	printf_s("10 count = %d\n", count(10));
	printf_s("20 count = %d\n", count(20));
	printf_s("30 count = %d\n", count(30));

	printf_s("popped: %d\n", popFromHead());
	printf_s("popped: %d\n", popFromHead());

	printNodeList();

	printf_s("10 count = %d\n", count(10));
	printf_s("20 count = %d\n", count(20));
	printf_s("30 count = %d\n", count(30));
	printf("sum = %d\n", nodeSum());

	clearNodeList();

	printNodeList();
	printf_s("10 count = %d\n", count(10));
	printf_s("20 count = %d\n", count(20));
	printf_s("30 count = %d\n", count(30));

	addToHead(1);
	addToHead(2);
	addToHead(3);
	addToHead(7);
	addToHead(4);
	addToHead(8);
	printNodeList();
	printf_s("even count = %d\n", evenCount());
}

void odds10X() {
	NODE* ptr = first;
	while (ptr != NULL) {
		if (ptr->data % 2 != 0) {
			ptr->data *= 10;
		}
		ptr = ptr->next;
	}
}

void elementIx100(int i) {
	NODE* ptr = first;
	int index = 0;
	while (ptr != NULL) {
		if (index == i) {
			ptr->data *= 100;
		}
		ptr = ptr->next;
		index += 1;
	}
}

void listTemplate() {
	clearNodeList();
	addToHead(1);
	addToHead(2);
	addToHead(3);
	addToHead(7);
	addToHead(4);
	addToHead(8);
}

void task4() {
	printf("\n======  task4  ======\n");
	listTemplate();
	printNodeList();
	odds10X();
	printNodeList();
}

void task5() {
	printf("\n======  task5  ======\n");
	listTemplate();
	printNodeList();
	elementIx100(1);
	elementIx100(2);
	elementIx100(4);
	printNodeList();
}

void leftToIx10(int i) {
	NODE* ptr = first;
	int index = 0;
	while (ptr != NULL) {
		if (index > i) {
			ptr->data *= 10;
		}
		ptr = ptr->next;
		index += 1;
	}
}

void task6() {
	printf("\n======  task6  ======\n");
	listTemplate();
	printNodeList();
	leftToIx10(2);
	printNodeList();
}

void rightToIx10(int i) {
	NODE* ptr = first;
	int index = 0;
	while (ptr != NULL) {
		if (index < i) {
			ptr->data *= 10;
		}
		ptr = ptr->next;
		index += 1;
	}
}

void task7() {
	printf("\n======  task7  ======\n");
	listTemplate();
	printNodeList();
	rightToIx10(3);
	printNodeList();
}

void task8() {
	printf("\n======  task8  ======\n");
	listTemplate();
	printNodeList();
	printf("popped: %d\n", popFromIndex(3));
	printNodeList();

	clearNodeList();
	addToHead(10);
	addToHead(20);
	addToHead(30);
	addToHead(40);
	addToHead(50);

	printNodeList();
	printf("popped: %d\n", popFromIndex(-1));
	printNodeList();
}

void reversePrint(NODE* ptr) {
	if (ptr == NULL) {
		printf("NULL <- ");
		return;
	}
	reversePrint(ptr->next);
	printf("(%d) <- ", ptr->data);
}

void task9() {
	printf("\n======  task9  ======\n");
	listTemplate();
	printNodeList();
	
	reversePrint(first);
	printf("first");
}

void detectRepeats() {
	NODE* ptr = first;
	while (ptr != NULL) {
		if (count(ptr->data) > 1) {
			printf("repeats detected!\n");
			return;
		}
		ptr = ptr->next;
	}
	printf("no repeats\n");
}

void task10() {
	printf("\n======  task10  ======\n");
	listTemplate();
	printNodeList();
	detectRepeats();
	addToHead(1);
	printNodeList();
	detectRepeats();
}

void swap_by_next(int i, int j) {
	if (first == NULL) {
		puts("first == NULL, no swap happened");
		return;
	}
	if (first->next == NULL) {
		puts("first->next == NULL, no swap happened");
		return;
	}
	NODE* prev_ptr = first;
	NODE* ptr = first->next;

	NODE* i_prev = first;
	NODE* i_ptr = first;
	NODE* j_prev = first;
	NODE* j_ptr = first->next;
	
	int index = 1;
	while (ptr != NULL) {
		if (index == i) {
			i_prev = prev_ptr;
			i_ptr = ptr;
			break;
		}
		prev_ptr = ptr;
		ptr = ptr->next;
		index++;
	}
	prev_ptr = first;
	ptr = first->next;
	index = 1;
	while (ptr != NULL) {
		if (index == j) {
			j_prev = prev_ptr;
			j_ptr = ptr;
			break;
		}
		prev_ptr = ptr;
		ptr = ptr->next;
		index++;
	}
	if (i == 0) {
		first = j_ptr;
	}
	else {
		i_prev->next = j_ptr;
	}
	j_prev->next = i_ptr;
	NODE* tmp = i_ptr->next;
	i_ptr->next = j_ptr->next;
	j_ptr->next = tmp;
}

void swap_by_data(int i, int j) {
	NODE* ptr = first;
	int i_data = 0, j_data = 0;
	int index = 0;
	while (ptr != NULL) {
		if (index == i) {
			i_data = ptr->data;
		}
		if (index == j) {
			j_data = ptr->data;
		}
		ptr = ptr->next;
		index++;
	}
	ptr = first;
	index = 0;
	while (ptr != NULL) {
		if (index == i) {
			ptr->data = j_data;
		}
		if (index == j) {
			ptr->data = i_data;
		}
		ptr = ptr->next;
		index++;
	}
}

NODE* getNode(int index) {
	NODE* ptr = first;
	int i = 0;
	while (ptr != NULL) {
		if (i == index) {
			return ptr;
		}
		ptr = ptr->next;
		i++;
	}
	puts("Node not found");
	return NULL;
}

void bubbleSort_by_next() {
	NODE* ptri = first;
	int i = 0;
	while (ptri->next != NULL) {
		int j = 0;
		NODE* ptrj = first;
		while (ptrj->next != NULL) {
			if (ptrj->data > ptrj->next->data) {
				swap_by_next(j, j + 1);
			}
			j++;
			ptrj = getNode(j);
		}
		i++;
		ptri = getNode(i);
	}
}

void bubbleSort_by_data() {
	NODE* ptri = first;
	int i = 0;
	while (ptri->next != NULL) {
		NODE* ptrj = first;
		int j = 0;
		while (ptrj->next != NULL) {
			if (ptrj->data > ptrj->next->data) {
				swap_by_data(j, j + 1);
			}
			j++;
			ptrj = ptrj->next;
		}
		i++;
		ptri = ptri->next;
	}
}

void task12() {
	printf("\n======  task12  ======\n");
	listTemplate();
	printNodeList();
	swap_by_next(0, 2);
	swap_by_next(3, 5);
	printNodeList();
}

void task13() {
	printf("\n======  task13  ======\n");
	listTemplate();
	printNodeList();
	bubbleSort_by_next();
	printNodeList();
}

int main() {
	test();

	task4();
	task5();
	task6();
	task7();
	task8();
	task9();
	task10();
	task12();
	task13();

	return 0;
}