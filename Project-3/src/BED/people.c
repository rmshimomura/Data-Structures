#include "libs.h"

enum {
    OWN,
    RENT
};

typedef struct livingPlace{
    
    char cep[20];
    char face;
    int num;
    char complement[30];

}livingPlace;

typedef struct people{
    
    char name[50];
    char surname[50];
    char sex;
    char birthDate[11];
    char cpf[15];
    int houseState;
    livingPlace place;

    
}people;