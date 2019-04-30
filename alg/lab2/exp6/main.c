#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#define ROWS 13633
#define COLS 30

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main(int argc, char const *argv[]) {

    srand(time(NULL));
    FILE *fp;
    fp = fopen("witcher.txt", "r");
    char words[ROWS][COLS];
    int i;
    for (i = 0; i <= ROWS; ++i) {
        fscanf(fp, "%s ", words[i]);
    }

    struct listnode *elfhashtab[HASHTAB_SIZE];
    struct listnode *krhashtab[HASHTAB_SIZE];
    hashtab_init(elfhashtab, HASHTAB_SIZE);
    hashtab_init(krhashtab, HASHTAB_SIZE);

    KRcounter = 0;
    ELFcounter = 0;
    double lookupTimer = 0, lookupTemp = 0;
    FILE *KRhashtabLookup = fopen("KRhashtabLookup.dat", "w");
    FILE *KRhashtabLookuptime = fopen("KRhashtabLookupTime.dat", "w");
    FILE *ELFhashtabLookup = fopen("ELFhashtabLookup.dat", "w");
    FILE *ELFhashtabLookuptime = fopen("ELFhashtabLookupTime.dat", "w");

    for (i = 1; i <= ROWS; ++i) {
        hashtab_add(elfhashtab, words[i], i, 0);
        if (i % 30 == 0) {
            char *searchKey = words[getrand(0, i)];
            lookupTimer = wtime();
            struct listnode *elfhashNode = hashtab_lookup(elfhashtab, searchKey, 0);
            lookupTemp += wtime() - lookupTimer;
        }
        if (i % 700 == 0) {
            fprintf(ELFhashtabLookup, "%d %d\n", i, ELFcounter);
            fprintf(ELFhashtabLookuptime, "%d %f\n", i, lookupTemp * 60);
            lookupTemp = 0;
        }
    }

    lookupTemp = 0;
    for (i = 1; i <= ROWS; ++i) {
        hashtab_add(krhashtab, words[i], i, 1);
        if (i % 30 == 0) {
            char *searchKey = words[getrand(0, i)];
            lookupTimer = wtime();
            struct listnode *KRhashNode = hashtab_lookup(krhashtab, searchKey, 1);
            lookupTemp += wtime() - lookupTimer;
        }
        if (i % 700 == 0) {
            fprintf(KRhashtabLookup, "%d %d\n", i, KRcounter);
            fprintf(KRhashtabLookuptime, "%d %f\n", i, lookupTemp * 60);
            lookupTemp = 0;
        }
    }

    return 0;
}