#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Dict.h"
#include "fnvhash_32a.h"
#include "jhash.h"

#ifdef DICT_HASH_OPEN_ADDRESS_C

#define MAX_HASH 16384
#define TABLE_SIZE (MAX_HASH*2)

// Массив списков
char* hashtable[TABLE_SIZE];

int hash(char* word) {
	int hash_value = (int)fnv_32a_str(word, FNV1_32A_INIT);
	hash_value = TINY_FNV(14, hash_value);
	return hash_value;
}

void Insert(char* word) {
	int hash_value = hash(word);

	while (hashtable[hash_value] != NULL && strcmp(hashtable[hash_value], word) != 0) {
		hash_value++;
		if (hash_value >= TABLE_SIZE) {
			printf("Index out of range\n");
			exit(1);
		}
	}

	hashtable[hash_value] = (char*)calloc(strlen(word) + 1, sizeof(char));
	if (hashtable[hash_value] == NULL) {
		printf("Out of memory\n");
		exit(1);
	}
	strcpy(hashtable[hash_value], word);
}

/* MEMBER – сообщает, является ли указанный элемент членом данного множества или нет. */
int  Member(char* word) {
	int hash_value = hash(word);

	while (hashtable[hash_value] != NULL) {
		if (strcmp(hashtable[hash_value], word) == 0) {
			return 1;
		}
		hash_value++;
		if (hash_value >= TABLE_SIZE) {
			printf("Index out of range\n");
			exit(1);
		}
	}

	return 0;
}

/* CREATE - создает словарь.
Вызывается перед началом использования словаря. */
void Create() {
	for (int i = 0; i < MAX_HASH; i++)
		hashtable[i] = NULL;
}

/* DESTROY - уничтожает словарь.
Вызывается после окончания использования словаря. */
void Destroy() {
	for (int i = 0; i < MAX_HASH; i++) {
		if (hashtable[i] != NULL) {
			free(hashtable[i]);
		}
		hashtable[i] = NULL;
	}
}

#endif
