#ifndef __HASH_H__
#define __HASH_H__

#define HASH_TABLE_SIZE 11

#include <stdio.h>
#include <math.h>

// Struct de numeros para a hash
typedef struct {
    int value;
    unsigned int deleted:1;
    unsigned int started:1;
} __hash_number;

typedef struct {
    __hash_number h1[HASH_TABLE_SIZE];
    __hash_number h2[HASH_TABLE_SIZE];
} Hash_t;

size_t h1(int key);
size_t h2(int key);

Hash_t create_hash_table();

void insert_hash_table(Hash_t *t, int k);

int delete_hash_table(Hash_t *t, int k);

void print_hash_table(Hash_t t);

#endif // __HASH_H__