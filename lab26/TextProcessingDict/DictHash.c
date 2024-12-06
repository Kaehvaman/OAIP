//
// Реализация словаря на хэше
// 
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include "Dict.h"
#include "fnvhash_32a.h"
#include "jhash.h"

#ifdef DICT_HASH_C

struct Node {
	char* word;
	struct Node* next;
};

#define FNV_HASH

#if defined VLASENKO_HASH

#define MAX_HASH 13267

// Массив списков
struct Node* first[MAX_HASH];

// Вычисление хэша для строки word
int hash(char* word) {
	unsigned long hash_value = 0;
	int i = 0;
	while (word[i] != '\0') {
		hash_value = 31 * hash_value + ((unsigned)(word[i]));
		i++;
	}
	return hash_value % MAX_HASH;
}

#elif defined JHASH

#define MAX_HASH 16384

// Массив списков
struct Node* first[MAX_HASH];

int hash(char* word) {
	int hash_value = (int)jhash(word, strlen(word) + 1, FNV1_32A_INIT);
	hash_value = hash_value & hashmask(14);
}

#elif defined FNV_HASH
#define MAX_HASH 16384

// Массив списков
struct Node* first[MAX_HASH];

int hash(char* word) {
	int hash_value = (int)fnv_32a_str(word, FNV1_32A_INIT);
	hash_value = TINY_FNV(14, hash_value);
}

#endif

/* INSERT – добавляет элемент в множество.
Множество – содержит только уникальные элементы.
При повторном добавлении элемента в множество, множество не изменяется. 
Нет защиты от двойного включения */
void Insert(char* word) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

	int hash_value = hash(word);

	newNode->next = first[hash_value];
	newNode->word = (char*)calloc(strlen(word) + 1, sizeof(char));
	strcpy(newNode->word, word);
	first[hash_value] = newNode;
}

/* MEMBER – сообщает, является ли указанный элемент членом данного множества или нет. */
int  Member(char* word) {
	int hash_value = hash(word);

	struct Node* ptr = first[hash_value];
	while (ptr != NULL) {
		if (strcmp(ptr->word, word) == 0) {
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

/* CREATE - создает словарь.
Вызывается перед началом использования словаря. */
void Create() {
	for (int i = 0; i < MAX_HASH; i++)
		first[i] = NULL;
}

/* DESTROY - уничтожает словарь.
Вызывается после окончания использования словаря. */
void Destroy() {
	for (int i = 0; i < MAX_HASH; i++) {

		while (first[i] != NULL) {
			struct Node* delNode = first[i];
			first[i] = first[i]->next;

			free(delNode->word);
			free(delNode);
		}
	}
}

#endif
