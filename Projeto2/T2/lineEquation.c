#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    float slope, intercept;
    float x1, y1, x2, y2;
    float dx, dy;

    scanf("%f", &x1);

    scanf("%f", &y1);

    scanf("%f", &x2);

    scanf("%f", &y2);

    dx = x2 - x1;

    dy = y2 - y1;

    slope = dy / dx;

    // y = mx + c

    // intercept c = y - mx

    intercept = y1 - slope * x1;  // which is same as y2 - slope * x2

    printf("Equation of the line with end points (%.2f, %.2f) and (%.2f, %.2f) : Y = %.2fX %c %.2f\n", x1, y1, x2, y2, slope, (intercept < 0) ? ' ' : '+', intercept);
    
}