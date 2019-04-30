#pragma once

#define WORDS_NUMBER 13633
#define WORD_LEN 30

char word[WORDS_NUMBER][WORD_LEN];

int getrand(int min, int max);
double wtime();
void shuffle(char word[WORDS_NUMBER][WORD_LEN], int size);
void swap(char* cur, char* rep);