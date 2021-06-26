#include "rectangle.h"

typedef struct data {
    
    double x, y, width, height, centerX, centerY;
    char id[100], fill[100], stroke[100];
    void** peopleInside;
    bool vectorOfAddressesStarted;
    int numberOfPeopleInside;

} data_t;

void* createRectangle() {

    data_t* aux = (data_t*)calloc(1, sizeof(data_t));
    return aux;

}

void setRectangleX(node current, double x) {

    data_t* aux = current;
    aux->x = x;

}

void setRectangleY(node current, double y) {

    data_t* aux = current;
    aux->y = y;

}

void setRectangleWidth(node current, double width) {

    data_t* aux = current;
    aux->width = width;

}

void setRectangleHeight(node current, double height) {

    data_t* aux = current;
    aux->height = height;

}

void setRectangleId(node current, char* idValue) {

    data_t* aux = current;
    strcpy(aux->id, idValue);

}

void setRectangleFill(node current, char* fillValue) {

    data_t* aux = current;
    strcpy(aux->fill, fillValue);

}

void setRectangleStroke(node current, char* strokeValue) {

    data_t* aux = current;
    strcpy(aux->stroke, strokeValue);

}

void setRectangleCenterX(node current, double centerX) {

    data_t* aux = current;
    aux->centerX = centerX;

}

void setRectangleCenterY(node current, double centerY) {

    data_t* aux = current;
    aux->centerY = centerY;

}

//===============================================//

double getRectangleX(node current) {

    data_t* aux = current;
    return aux->x;

}

double getRectangleY(node current) {

    data_t* aux = current;
    return aux->y;

}

double getRectangleWidth(node current) {

    data_t* aux = current;
    return aux->width;

}

double getRectangleHeight(node current) {

    data_t* aux = current;
    return aux->height;

}

char* getRectangleId(node current) {

    data_t* aux = current;
    return aux->id;

}

char* getRectangleFill(node current) {

    data_t* aux = current;
    return aux->fill;

}

char* getRectangleStroke(node current) {

    data_t* aux = current;
    return aux->stroke;

}

double getRectangleCenterX(node current) {

    data_t* aux = current;
    return aux->centerX;

}

double getRectangleCenterY(node current) {

    data_t* aux = current;
    return aux->centerY;

}

void setVectorOfPeopleStarted(node current, bool state) {

    data_t* aux = current;
    aux->vectorOfAddressesStarted = state;

}

bool getVectorOfPeopleStarted(node current) {

    data_t* aux = current;
    return aux->vectorOfAddressesStarted;

}

void setNumberOfPeopleInside(node current, int people) {

    data_t* aux = current;
    aux->numberOfPeopleInside = people;

}

int getNumberOfPeopleInside(node current) {

    data_t* aux = current;
    return aux->numberOfPeopleInside;

}

void** getVectorOfPeople(node current) {

    data_t* aux = current;
    return aux->peopleInside;

}

void allocateVectorOfPeople(node current) {

    data_t* aux = current;

    if (!getVectorOfPeople(current) || !aux->numberOfPeopleInside) {

        aux->peopleInside = calloc(1, sizeof(void*));
    
    } else {

        aux->peopleInside = realloc(aux->peopleInside, (aux->numberOfPeopleInside + 1) * sizeof(void*));
    
    }

}

void setAddresses(node current, void* address, int line) {

    data_t* aux = current;
    aux->peopleInside[line] = address;

}

void freeVectorOfPeople(node current) {

    data_t* aux = current;
    
    for (int i = 0; i < getNumberOfPeopleInside(current); i++) {

        aux->peopleInside[i] = NULL;
        free(aux->peopleInside[i]);
    
    }
    free(aux->peopleInside);

}