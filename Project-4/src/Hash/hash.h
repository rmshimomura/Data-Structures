#include "../libs.h"

#ifndef HASH_H
#define HASH_H

void* hash_table_create_table(int size);
int hash_table_create_key(void* HT, char* key);
int hash_table_size(void* HT);
int hash_table_list_exist(void* HT, char* key);
void* hash_table_get_register_list(void* HT, char* key);
void hash_table_insert_data(void* HT, char* key, void* data);
void hash_table_remove_key(void* HT, char* key, void (*free_data)(void*), int (*compare_nodes)(void*, void*), bool remove_elements);
void hash_table_remove_key_special(void* HT, char* key, int (*compare_nodes)(void*, void*));
void hash_table_destroy(void* HT, void (*free_function)(void*), bool remove_elements);
void* hash_table_get_list_by_index(void* HT, int index);
void hash_table_destroy_blocks(void* HT);

#endif