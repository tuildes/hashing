#include "hash.h"

#include <stdio.h>

int main(void) { 

    int n;
    char choose;
    Hash_t myht = create_hash_table();

    while(scanf("%c %d", &choose, &n) != EOF) {
        getchar();
        switch(choose) {
            case 'i':
                insert_hash_table(&myht, n);
                break;
            case 'r':
                delete_hash_table(&myht, n);
                break;
            default:
                print_hash_table(myht);
                return 0;
        }
    }

    print_hash_table(myht);

    return 0; 
}
