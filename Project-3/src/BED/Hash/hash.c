#include "hash.h"
#include "../DynamicList/dynamicList.h"

typedef struct regist {
    dynamic_list list;
}regist_t;

typedef struct hashTable {
    int size;
    regist_t* registers;
}hashTable_t;

void* hash_table_create_table(int size){ 

    hashTable_t* new_hash_table = calloc(1, sizeof(hashTable_t));
    new_hash_table->registers = calloc(size, sizeof(regist_t));
    new_hash_table->size = size;

    return new_hash_table;
    
}

int hash_table_create_key(void* HT, char* key){
    
    int pos_at_hash_table = 0;

    for(int i = 0; i < strlen(key); i++) pos_at_hash_table += key[i];

    return pos_at_hash_table % hash_table_size(HT);

}

int hash_table_size(void* HT){
    hashTable_t* aux = HT;
    return aux->size;
}

int hash_table_exist(void* HT, char* key){
    
    int pos_at_hash_table = hash_table_create_key(HT, key);
    hashTable_t* aux = HT;
    
    return aux->registers[pos_at_hash_table].list ? 1 : 0;

}

void* hash_table_get_register_list(void* HT, char* key){
    
    int pos_at_hash_table = hash_table_create_key(HT, key);
    hashTable_t* aux = HT;

    return aux->registers[pos_at_hash_table].list;
}

int hash_table_insert_data(void* HT, char* key, void* data){
    
    int pos_at_hash_table = hash_table_create_key(HT, key);
    hashTable_t* aux = HT;

    if(!hash_table_exist(HT, key)){

        aux->registers[pos_at_hash_table].list = create_list();
        insert(aux->registers[pos_at_hash_table].list, data);

        return 1;
        
    }

    return 0;

}
