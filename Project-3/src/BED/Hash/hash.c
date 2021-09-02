#include "hash.h"
#include "../DynamicList/dynamicList.h"

typedef struct regist {
    dynamic_list list;
}regist_t;

typedef struct hashTable {
    int size;
    regist_t* registers;
}hashTable;

void* hash_table_create_table(int size){ 

    hashTable* new_hash_table = calloc(1, sizeof(hashTable));
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
    hashTable* aux = HT;
    return aux->size;
}

int hash_table_list_exist(void* HT, char* key){
    
    int pos_at_hash_table = hash_table_create_key(HT, key);
    
    hashTable* aux = HT;
    
    return aux->registers[pos_at_hash_table].list ? 1 : 0;

}

void* hash_table_get_register_list(void* HT, char* key){
    
    int pos_at_hash_table = hash_table_create_key(HT, key);
    hashTable* aux = HT;

    return aux->registers[pos_at_hash_table].list;
}

int hash_table_insert_data(void* HT, char* key, void* data){
    
    int pos_at_hash_table = hash_table_create_key(HT, key);
    
    hashTable* aux = HT;

    if(!hash_table_list_exist(HT, key)){

        aux->registers[pos_at_hash_table].list = create_list();
        insert(aux->registers[pos_at_hash_table].list, data);
                
    }else{

        insert(aux->registers[pos_at_hash_table].list, data);
    }

    return 0;

}

void hash_table_remove_key(void* HT, char* key, void (*free_data)(void*)){
    
    if(!hash_table_list_exist(HT, key)){
        return;
    }

    int pos_created_by_the_key = hash_table_create_key(HT, key);

    hashTable* aux = HT;

    if(findItem(aux->registers[pos_created_by_the_key].list, key)){
        remove_node(aux->registers[pos_created_by_the_key].list, findItem(aux->registers[pos_created_by_the_key].list, key), free_data);
    }

}


void hash_table_destroy(void* HT, void (*free_function)(void*)) {
    
    hashTable* aux = HT;

    for(int i = 0; i < aux->size; i++) free_list(aux->registers[i].list, free_function);

    free(aux->registers);
    free(aux);
}