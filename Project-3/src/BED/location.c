#include "location.h"

typedef struct loction {

    char id[30], cep[20], face, complement[30];
    int num;
    double ar, v;
    bool available;

}location;

void* create_location(){
    
    location* new_location = calloc(1, sizeof(location));
    new_location->available = true;
    return new_location;

}

void set_location_properties(void* location_to_set, char* id, char* cep, char face, int num, char* compl, double ar, double v){
    location* aux = location_to_set;
    strcpy(aux->cep, cep);
    strcpy(aux->id, id);
    strcpy(aux->complement, compl);
    aux->face = face;
    aux->num = num;
    aux->ar = ar;
    aux->v = v;
}

void location_info(void* location_data, FILE* txt_results){

    location* aux = location_data;

    if(aux)        
        fprintf(txt_results, "\tLocation data found: \n\n\tID: %s CEP:%s Face: %c Num: %d Complement: %s\n\tPrice: %.2lf Area: %.2lf\n\tAvailable: %s\n\n", aux->id ,aux->cep, aux->face, aux->num, aux->complement, aux->v, aux->ar, aux->available ? "YES" : "NO");


}

int compare_id(void* current, void* match){

    location* current_node = current;
    

    if(!strcmp(current_node->id, match)) return 1;

    return 0;

}

char* location_get_cep(void* location_data){

    location* aux = location_data;
    return aux->cep; 

}

char location_get_face(void* location_data){

    location* aux = location_data;
    return aux->face; 

}

int location_get_num(void* location_data){

    location* aux = location_data;
    return aux->num; 

}

char* location_get_complement(void* location_data){

    location* aux = location_data;
    return aux->complement; 

}

void location_set_available(void* location_data, bool state){

    location* aux = location_data;
    aux->available = state;
    
}