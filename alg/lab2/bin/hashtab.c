#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hashtab_hash(char *key) {
    /* Хеш-функция Кернигана–Ричи */
    unsigned int h = 0, hash_mul = 31;
    while (*key) {
        h = h * hash_mul + (unsigned int)*key++;
    }
    return h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab) {
    /*Инициализация хеш-таблицы*/
    int i;
    for (i = 0; i < HASHTAB_SIZE; i++) {
        hashtab[i] = NULL;
    }
}

void hashtab_add(struct listnode **hashtab, char *key, int value) {
    /*Добавление элемента в хеш-таблицу*/
    struct listnode *node;
    int index = hashtab_hash(key);
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key) {
    /*Поиск элемента в хеш-таблице*/
    struct listnode *node;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key) {
    /*Удаление элемента из хеш-таблицы*/
    struct listnode *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            if (prev == NULL) {
                hashtab[index] = node->next;
            }
            else {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
    }
}
