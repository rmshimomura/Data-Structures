#include "bibliotecas.h"
#ifndef CIRCLE_H
#define CIRCLE_H

item createCircle();
void setCircleX(node current, double x);
void setCircleY(node current, double y);
void setCircleId(node current, char* idValue);
void setCircleFill(node current, char* fillValue);
void setCircleStroke(node current, char* strokeValue);
void setCircleRadius(node current, double radius);
double getCircleX(node current);
const char* getCircleIdQSort(const void* current);
double getCircleY(node current);
char* getCircleId(node current);
char* getCircleFill(node current);
char* getCircleStroke(node current);
double getCircleRadius(node current);
void* getRunTo(node current);
void setRunTo(node current, void* building);
void setNearestDistance(node current, double distance);
double getNearestDistance(node current);
void setFg(node current, bool state);
bool getFg(node current);
void setCircleOriginalX(node current, double x);
double getCircleOriginalX(node current);
void setCircleOriginalY(node current, double y);
double getCircleOriginalY(node current);
double getRadiation(node current);
void setRadiation(node current, double newRadiation);
void setInsideNShadows(node current, int numberOfShadows);
int getInsideNShadows(node current);
void setCircleAlive(node current, bool isAlive);
bool getCircleAlive(node current);
void setCircleMarkedForDeath(node current, bool goingToDie);
bool getCircleMarkedForDeath(node current);


#endif