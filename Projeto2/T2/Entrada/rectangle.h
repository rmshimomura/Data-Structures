#include "bibliotecas.h"
#ifndef RECTANGLE_H
#define RECTANGLE_H

item createRectangle();
void setRectangleX(node current, double x);
void setRectangleY(node current, double y);
void setRectangleWidth(node current, double width);
void setRectangleHeight(node current, double height);
void setRectangleId(node current, char* idValue);
void setRectangleFill(node current, char* fillValue);
void setRectangleStroke(node current, char* strokeValue);
void setRectangleCenterX(node current, double centerX);
void setRectangleCenterY(node current, double centerY);
double getRectangleX(node current);
double getRectangleY(node current);
double getRectangleWidth(node current);
double getRectangleHeight(node current);
char* getRectangleId(node current);
char* getRectangleFill(node current);
char* getRectangleStroke(node current);
double getRectangleCenterX(node current);
double getRectangleCenterY(node current);
void setVectorOfPeopleStarted(node current, bool state);
bool getVectorOfPeopleStarted(node current);
void setNumberOfPeopleInside(node current, int people);
int getNumberOfPeopleInside(node current);
void allocateVectorOfPeople(node current);
void freeVectorOfPeople(node current);
void **getVectorOfPeople(node current);
void tempFreeVectorOfPeople(node current);
void setAddresses(node current, void* address, int line);



#endif