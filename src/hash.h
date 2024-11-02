#ifndef __HASH_H__
#define __HASH_H__

#include <stdio.h>
#include <math.h>

#define HASH_TABLE_SIZE 11 // Tamanho de cada tabela HASH

// Estrutura de numeros da hash
typedef struct {
    int value; // Valor qualquer (chave)
    unsigned int deleted:1, // Bit de delete
                 started:1; // Bit de numero "iniciado"
} __hash_number;

// Estrutura de dados do tipo HASH
// Tabela Hash do tipo Cuckoo hashing
typedef struct {
    __hash_number h1[HASH_TABLE_SIZE], // Tabela 01 (esquerda)
                  h2[HASH_TABLE_SIZE]; // Tabela 02 (direita)
} Hash_t;

/*
    Cria uma chave para a tabela 01 ou 02 de Hash

    @param  (size_t) key - chave que vai ser indexado
    @return (size_t) chave de indexacao na tabela
*/
size_t h1(int key); // Indexacao do tipo 01 (modulo simples)
size_t h2(int key); // Indexacao do tipo 02 (diferencas de pisos)

/*
    Cria a tabela hash

    @return (Hash_t) - tabela hash criada
*/
Hash_t create_hash_table();

/*
    Procura o valor na tabela hash
    Retorna 0 para nao encontrado
    Retorna 1 para tabela 01
    Retorna 2 para tabela 02

    @param  (size_t) key - chave que vai ser procurado
    @return (int)    qual tabela esta inserido
*/
int search_hash_table(Hash_t t, int k);

/*
    Insere uma chave na tabela HASH
    Insere sempre na T1 da Hash

    @param  (Hash_t) t - tabela hash a ser inserida
    @param  (int)    k - chave a ser inserida
*/
void insert_hash_table(Hash_t *t, int k);

/*
    Deleta uma chave da tebela HASH

    @param  (Hash_t) t - tabela hash a ser mexida
    @param  (int)    k - chave a ser deletada
    @return (int)    Posicao da HASH deletado, ou -1 para nao encontrado
*/
int delete_hash_table(Hash_t *t, int k);


/*
    Imprime de forma ordenado a tabela, da forrma:
    (numero, tabela, posicao)
    (10,T2,4)

    @param  (Hash_t) t - tabela hash a ser impressa
*/
void print_hash_table(Hash_t t);

#endif // __HASH_H__