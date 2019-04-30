#include "main.h"
#include "bstree.h"
#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int main() 
{
    srand(time(NULL));
    FILE *fp;
    fp = fopen("words/witcher.txt", "r");
    if (fp == NULL) {
        printf("Opening error\n");
        return -1;
    }

    for (int i = 0; i <= WORDS_NUMBER; i++) {
        fscanf(fp, "%s ", word[i]);
    }

    struct bstree *tree = bstree_create(word[0], 0);
    struct listnode *hashtab[HASHTAB_SIZE];
    double addTimer = 0, lookupTimer = 0, lookupTemp = 0, addTemp = 0;
    hashtab_init(hashtab);

    FILE *bstreeLookup = fopen("dat/bstreeLookup.dat", "w");
    FILE *hashtabLookup = fopen("dat/hashtabLookup.dat", "w");
    FILE *bstreeAdd = fopen("dat/bstreeAdd.dat", "w");
    FILE *hashtabAdd = fopen("dat/hashtabAdd.dat", "w");

    // Поиск и добавление элементов в бинарное дерево
    addTimer = wtime();
    for (int i = 1; i <= WORDS_NUMBER; i++) {
        bstree_add(tree, word[i], i);
        if (i % 30 == 0) {
            char *searchKey = word[getrand(0, i)];
            lookupTimer = wtime();
            struct bstree *treeNode = bstree_lookup(tree, searchKey);
            lookupTemp += wtime() - lookupTimer;
            addTemp += wtime() - addTimer;
        }
        if (i % 700 == 0) {
            fprintf(bstreeAdd, "%d %f\n", i, addTemp * 60);
            fprintf(bstreeLookup, "%d %f\n", i, lookupTemp * 60);
            addTemp = 0;
            lookupTemp = 0;
        }
    }

    lookupTemp = 0;
    addTemp = 0;
    // Поиск и добавление элементов в хеш-таблицу
    addTimer = wtime();
    for (int i = 1; i <= WORDS_NUMBER; i++) {
        hashtab_add(hashtab, word[i], i);
        if (i % 30 == 0) {
            char *searchKey = word[getrand(0, i)];
            lookupTimer = wtime();
            struct listnode *hashNode = hashtab_lookup(hashtab, searchKey);
            lookupTemp += wtime() - lookupTimer;
            addTemp += wtime() - addTimer;
        }
        if (i % 700 == 0) {
            fprintf(hashtabAdd, "%d %f\n", i, addTemp * 60);
            fprintf(hashtabLookup, "%d %f\n", i, lookupTemp * 60);
            addTemp = 0;
            lookupTemp = 0;
        }
    }


    return 0;
}

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void shuffle(char word[WORDS_NUMBER][WORD_LEN], int size) {
    for (size_t i = 0; i < size - 1; i++) {
        swap(word[i], word[rand() % size]);
    }
}

void swap(char* cur, char* rep)
{
    char temp[WORD_LEN];
    strcpy(temp, cur);
    strcpy(cur, rep);
    strcpy(rep, temp);
}
