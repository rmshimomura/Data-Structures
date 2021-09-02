#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* hash_table_create_table(int size);
int hash_table_create_key(void* HT, char* key);
int hash_table_size(void* HT);
int hash_table_exist(void* HT, char* key);
void* hash_table_get_register(void* HT, char* key);
int hash_table_insert_data(void* HT, char* key, void* data);