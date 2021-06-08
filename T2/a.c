#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.

int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
    s10_x = p1_x - p0_x;
    s10_y = p1_y - p0_y;
    s32_x = p3_x - p2_x;
    s32_y = p3_y - p2_y;
 
    denom = s10_x * s32_y - s32_x * s10_y;
    if (denom == 0) // parallel or collinear
        return 0; // Collinear
    bool denomPositive = denom > 0;
 
    s02_x = p0_x - p2_x;
    s02_y = p0_y - p2_y;
    s_numer = s10_x * s02_y - s10_y * s02_x;
 if ((s_numer <0) == denomPositive)//The parameter is greater than or equal to 0 and less than or equal to 1, the numerator and denominator must be the same sign and the numerator is less than or equal to the denominator
        return 0; // No collision
 
    t_numer = s32_x * s02_y - s32_y * s02_x;
    if ((t_numer < 0) == denomPositive)
        return 0; // No collision
 
    if (fabs(s_numer) > fabs(denom) || fabs(t_numer) > fabs(denom))
        return 0; // No collision
    // Collision detected
    t = t_numer / denom;
    if (i_x != NULL)
        *i_x = p0_x + (t * s10_x);
    if (i_y != NULL)
        *i_y = p0_y + (t * s10_y);
 
    return 1;

}

int main(){
    
    float posX, posY;
    printf("%s\n", get_line_intersection(1.0, 1.0, 7.0, 7.0, 13.0, 1.0, 1.0, 7.0, &posX,  &posY) ? "Sim" : "Nao");
    printf("Intersec at: (%.2lf, %.2lf)\n", posX, posY);

}