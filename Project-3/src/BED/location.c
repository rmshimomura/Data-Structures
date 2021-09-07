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

void location_info(void* location_info, FILE* txt_results){

    location* aux = location_info;

    if(aux)        
        fprintf(txt_results, "\tData found: \n\tID: %s CEP:%s Face: %c Num: %d Complement: %s\n\nPrice: %.2lf Area: %.2lf\n\n", aux->id ,aux->cep, aux->face, aux->num, aux->complement, aux->v, aux->ar);


}