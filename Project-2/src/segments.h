#include "bibliotecas.h"
#ifndef SEGMENTS_H
#define SEGMENTS_H

void* create_segment();
void* build_vertex_array(dynamicList segmentsList, double xMeteor, double yMeteor);
void build_segments(tree rectangleTree, dynamicList segmentsList, void* current_rect);
void free_points_info(void* segment);
void* get_origin(void* point);
void* get_linked_to(void* point);
double get_point_x(void* point);
double get_point_y(void* point);
double get_angle(void* point);
void* get_P1(void* segment);
void* get_P2(void* segment);
void* at_pos_array(void* array, int pos);
void set_angle(void* point, double angle);
int get_quadrant(void* point);
char* get_code(void* point);
char get_point_type(void* point);
bool get_analyzed(void* point);
void set_analyzed(void* point, bool state);
void free_shadow_polygons_array(void* array);
void* get_pair(void* point);
void add_wrap_around_rectangle(tree rectangleTree, tree circleTree, dynamicList segmentsList);
void destory_segment(void* segment);

#endif