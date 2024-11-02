#include "hash.h"

size_t h1(int key) { 
    if (key < 0) key *= (-1); // Tratamento de negativos
    return (size_t)(key % HASH_TABLE_SIZE); 
}

size_t h2(int key) {
    if (key < 0) key *= (-1); // Tratamento de negativos
    return (size_t)
        floor((HASH_TABLE_SIZE * ((key * 0.9) - floor((key * 0.9)))));
}

Hash_t create_hash_table() {
    Hash_t h;
    for(size_t i=0; i < HASH_TABLE_SIZE; i++) {
        h.h1[i].deleted = 0;
        h.h1[i].started = 0;
        h.h2[i].deleted = 0;
        h.h2[i].started = 0;
    }
    return h;
}

int search_hash_table(Hash_t t, int k) {
    size_t pos = h1(k);

    if((t.h1[pos].started) && (!t.h1[pos].deleted) && (t.h1[pos].value == k))
        return 1;
    if((t.h2[pos].started) && (!t.h2[pos].deleted) && (t.h2[pos].value == k))
        return 2;
        
    return 0;
}

void insert_hash_table(Hash_t *t, int k) {
    
    size_t j, pos = h1(k);

    // Verificar se existe chave na posicao 01
    if((t->h1[pos].started) && (!t->h1[pos].deleted)) {
        // Copiar a T1 para T2
        j = h2(t->h1[pos].value);
        t->h2[j].value = t->h1[pos].value;
        t->h2[j].started = 1;
        t->h2[j].deleted = 0;
    }

    // Inserir a chave na tabella
    t->h1[pos].value = k;
    t->h1[pos].started = 1;
    t->h1[pos].deleted = 0;
}

int delete_hash_table(Hash_t *t, int k) {

    // Deleta primeiro na segunda tabela (se corresponder)
    size_t pos = h2(k);
    if ((t->h2[pos].started) && ((t->h2[pos].value == k))) {
        t->h2[pos].deleted = 1;
        t->h2[pos].value = 0; // Reset de valor
        return (int)pos;
    }

    // Verifica se existe na primeira tabela e deleta
    pos = h1(k);
    if((t->h1[pos].started) && (t->h1[pos].value == k)) {
        t->h1[pos].deleted = 1;
        t->h1[pos].value = 0; // Reset de valor
        return (int)pos; // Sucesso
    }

    return -1; // Nao encontrado
}

void print_hash_table(Hash_t t) {

    // Estrutura de dados temporario para ordenacao
    struct __num_table {
        int value;
        size_t level;
        unsigned int table:1;
    };

    // Acha o tamanho da tabela (nao vazios)
    size_t size = 0; // Quantidade de dados validos
    struct __num_table v[(HASH_TABLE_SIZE << 1)]; // Array de ordenacao
    struct __num_table temp; // Dado temporario para trocas

    // Armazenar dados validos nas tabelas
    for(size_t i=0; i < HASH_TABLE_SIZE; i++) {

        // Conteudo da primeira tabela
        if ((t.h1[i].started) && (!t.h1[i].deleted)) {
            v[size].value = t.h1[i].value;
            v[size].level = i;
            v[size].table = 0;
            size++;
        }
        // Conteudo da segunda tabela
        if ((t.h2[i].started) && (!t.h2[i].deleted)) {
            v[size].value = t.h2[i].value;
            v[size].level = i;
            v[size].table = 1;
            size++;
        }
    }

    // Insertion Sort
    for(size_t i=1; i < size; i++) {
        for(size_t j=i; j > 0; j--) {
            if(v[j].value > v[(j - 1)].value) break;

            temp = v[j];
            v[j] = v[(j - 1)];
            v[(j - 1)] = temp;
        }
    }

    // Imprimir toda as saidas
    // (numero,tabela,posicao)
    for(size_t i=0; i < size; i++)
        printf("%d,T%1hu,%ld\n", v[i].value, (v[i].table + 1) , v[i].level);
}