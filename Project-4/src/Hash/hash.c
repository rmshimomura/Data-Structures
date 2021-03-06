#include "hash.h"
#include "../Dynamic_list/dynamic_list.h"

typedef struct regist {

    void* list;

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

void* hash_table_get_list_by_index(void* HT, int index){
    hashTable* aux = HT;
    return aux->registers[index].list;
}

void hash_table_insert_data(void* HT, char* key, void* data){
    
    int pos_at_hash_table = hash_table_create_key(HT, key);
    
    hashTable* aux = HT;

    if(!hash_table_list_exist(HT, key)){

        aux->registers[pos_at_hash_table].list = create_list();
        insert_list(aux->registers[pos_at_hash_table].list, data);
                
    }else{
        insert_list(aux->registers[pos_at_hash_table].list, data);
    }

}

void hash_table_remove_key(void* HT, char* key, void (*free_data)(void*), int (*compare_nodes)(void*, void*), bool remove_elements){
    
    if(!hash_table_list_exist(HT, key)){
        puts("Key passed does not match any data in the hash table...");
        printf("Key = %s\n", key);
        return;
    }

    int pos_created_by_the_key = hash_table_create_key(HT, key);

    hashTable* aux = HT;

    void* to_remove = find_element(aux->registers[pos_created_by_the_key].list, key, compare_nodes);

    if(to_remove){
        remove_node(aux->registers[pos_created_by_the_key].list, to_remove, free_data, remove_elements);
    }

}

void hash_table_destroy(void* HT, void (*free_function)(void*), bool remove_elements) {
    
    hashTable* aux = HT;

    for(int i = 0; i < aux->size; i++) free_list(aux->registers[i].list, remove_elements, free_function);

    free(aux->registers);
    free(aux);
}