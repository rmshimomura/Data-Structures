#include "circle.h"

typedef struct data_c {
    
    double x, y, radius, radiation, nearestDistance, originalX, originalY;
    int insideNShadows;
    char id[100], fill[100], stroke[100];
    void* runTo;
    bool fg;
    bool alive;
    bool markedForDeath;

} data_c;

void* createCircle(){
    data_c *aux = (data_c *) calloc(1, sizeof(data_c));
    return aux;
}

void setCircleX(node current, double x){
    data_c* aux = current;
    aux->x = x;
}

void setCircleY(node current, double y){
    data_c* aux = current;
    aux->y = y;
}

void setCircleId(node current, char* idValue){
    data_c* aux = current;
    strcpy(aux->id, idValue);
}

void setCircleFill(node current, char* fillValue){
    data_c* aux = current;
    strcpy(aux->fill, fillValue);
}

void setCircleStroke(node current, char* strokeValue){
    data_c* aux = current;
    strcpy(aux->stroke, strokeValue);
}

void setCircleRadius(node current, double radius){
    data_c* aux = current;
    aux->radius = radius;
}

double getRadiation(node current){
    data_c* aux = current;
    return aux->radiation;
}

void setRadiation(node current, double newRadiation){
    data_c* aux = current;
    aux->radiation = newRadiation;
}

void setInsideNShadows(node current, int numberOfShadows){
    data_c* aux = current;
    aux->insideNShadows = numberOfShadows;
}

int getInsideNShadows(node current){
    data_c* aux = current;
    return aux->insideNShadows;
}

double getCircleX(node current){
    data_c* aux = current;
    return aux->x;
}

double getCircleY(node current){
    data_c* aux = current;
    return aux->y;
}

char* getCircleId(node current){
    data_c* aux = current;
    return aux->id;
}

char* getCircleFill(node current){
    data_c* aux = current;
    return aux->fill;
}

char* getCircleStroke(node current){
    data_c* aux = current;
    return aux->stroke;
}

double getCircleRadius(node current){
    data_c* aux = current;
    return aux->radius;
}

void* getRunTo(node current){
    data_c* aux = current;
    return aux->runTo;
}

void setRunTo(node current, void* building){
    data_c* aux = current;
    aux->runTo = building;
}

void setNearestDistance(node current, double distance){
    data_c* aux = current;
    aux->nearestDistance = distance;
}   

double getNearestDistance(node current){
    data_c* aux = current;
    return aux->nearestDistance;
}

void setFg(node current, bool state){
    data_c* aux = current;
    aux->fg = state;
}

bool getFg(node current){
    data_c* aux = current;
    return aux->fg;
}

void setCircleOriginalX(node current, double x){
    data_c *aux = current;
    aux->originalX = x;
}

double getCircleOriginalX(node current){
    data_c *aux = current;
    return aux->originalX;
}

void setCircleOriginalY(node current, double y){
    data_c *aux = current;
    aux->originalY = y;
}

double getCircleOriginalY(node current){
    data_c *aux = current;
    return aux->originalY;
}

void setCircleAlive(node current, bool isAlive){
    data_c *aux = current;
    aux->alive = isAlive;
}

bool getCircleAlive(node current){
    data_c *aux = current;
    return aux->alive;
}

void setCircleMarkedForDeath(node current, bool goingToDie){
    data_c *aux = current;
    aux->markedForDeath = goingToDie;
}

bool getCircleMarkedForDeath(node current){
    data_c *aux = current;
    return aux->markedForDeath;
}