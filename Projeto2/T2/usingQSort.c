#include <stdio.h>
#include <stdlib.h>

typedef struct data{
    double angle;
}data_t;

typedef struct node{
    char id[10];
    data_t* data;
}node_t;

int comparator(const void* a, const void* b){
    
    const node_t *tempA = (node_t *)a;
    const node_t *tempB = (node_t *)b;
    
    return tempA->data->angle - tempB->data->angle;
    
}

int main(){

    node_t* temp = calloc(10, sizeof(node_t));

    for(int i = 0; i < 10; i++){
        temp[i].data = calloc(1, sizeof(data_t));
        temp[i].data->angle = rand() % 10; 
    }
    
    for(int i = 0; i < 10; i++){
        printf("%.1lf\n", temp[i].data->angle);
    }
    
    puts("=============================");

    qsort(temp, 10, sizeof(node_t), comparator);

    for(int i = 0; i < 10; i++){
        printf("%.1lf\n", temp[i].data->angle);
    }

    for(int i = 0; i < 10; i++){
        free(temp[i].data);
    }
    free(temp);
    
}