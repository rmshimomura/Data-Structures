#include "segments.h"

#include "circle.h"
#include "dynamicList.h"
#include "kdTree.h"
#include "normalTree.h"
#include "rectangle.h"
#include "svg.h"
#include "system.h"

typedef struct point {
    double x, y, angle;
    void* linked_to;
    void* pair;
    char type;
    int quadrant;
    double distance;
    char code[5];
    bool analyzed;

} point_t;

typedef struct segment {
    point_t* point1;
    point_t* point2;

} segment_t;

void* get_P1(void* segment) {
    segment_t* aux = segment;
    return aux->point1;
}

void* get_P2(void* segment) {
    segment_t* aux = segment;
    return aux->point2;
}

void* create_segment() {
    segment_t* aux = calloc(1, sizeof(segment_t));
    return aux;
}

void* create_point() {
    point_t* aux = calloc(1, sizeof(point_t));
    aux->angle = 0;
    aux->linked_to = NULL;
    aux->analyzed = false;
    return aux;
}

void* get_linked_to(void* point) {
    point_t* aux = point;
    return aux->linked_to;
}

int compare_for_qsort(const void* a, const void* b) {
    const point_t* tempA = (point_t*)a;
    const point_t* tempB = (point_t*)b;

    if (tempA->angle > tempB->angle)
        return 1;
    else if (tempA->angle < tempB->angle)
        return -1;
    else if (tempA->distance > tempB->distance)
        return -1;
    else if (tempA->distance < tempB->distance)
        return 1;
    else if (tempA->type == 's' && tempB->type == 'e')
        return -1;
    else if (tempA->type == 'e' && tempB->type == 's')
        return 1;

    return 0;
}

void build_segments(tree rectangleTree, dynamicList segmentsList, void* current_rect) {
    if (current_rect) {
        build_segments(rectangleTree, segmentsList, KD_get_left_node(current_rect));

        if (KD_get_state(current_rect)) {
            segment_t* segment1 = calloc(1, sizeof(segment_t));
            segment1->point1 = calloc(1, sizeof(point_t));
            segment1->point2 = calloc(1, sizeof(point_t));

            segment_t* segment2 = calloc(1, sizeof(segment_t));
            segment2->point1 = calloc(1, sizeof(point_t));
            segment2->point2 = calloc(1, sizeof(point_t));

            segment_t* segment3 = calloc(1, sizeof(segment_t));
            segment3->point1 = calloc(1, sizeof(point_t));
            segment3->point2 = calloc(1, sizeof(point_t));

            segment_t* segment4 = calloc(1, sizeof(segment_t));
            segment4->point1 = calloc(1, sizeof(point_t));
            segment4->point2 = calloc(1, sizeof(point_t));

            segment1->point1->x = get_rectangle_x(KD_get_data(current_rect));
            segment1->point1->y = get_rectangle_y(KD_get_data(current_rect));
            segment1->point2->x = get_rectangle_x(KD_get_data(current_rect)) + get_rectangle_width(KD_get_data(current_rect));
            segment1->point2->y = get_rectangle_y(KD_get_data(current_rect));
            segment1->point1->linked_to = segment1;
            segment1->point2->linked_to = segment1;
            segment1->point1->pair = segment1->point2;
            segment1->point2->pair = segment1->point1;
            strcpy(segment1->point1->code, "ORIG");
            strcpy(segment1->point2->code, "ORIG");

            segment2->point1->x = get_rectangle_x(KD_get_data(current_rect)) + get_rectangle_width(KD_get_data(current_rect));
            segment2->point1->y = get_rectangle_y(KD_get_data(current_rect));
            segment2->point2->x = get_rectangle_x(KD_get_data(current_rect)) + get_rectangle_width(KD_get_data(current_rect));
            segment2->point2->y = get_rectangle_y(KD_get_data(current_rect)) + get_rectangle_height(KD_get_data(current_rect));
            segment2->point1->linked_to = segment2;
            segment2->point2->linked_to = segment2;
            segment2->point1->pair = segment2->point2;
            segment2->point2->pair = segment2->point1;
            strcpy(segment2->point1->code, "ORIG");
            strcpy(segment2->point2->code, "ORIG");

            segment3->point1->x = get_rectangle_x(KD_get_data(current_rect)) + get_rectangle_width(KD_get_data(current_rect));
            segment3->point1->y = get_rectangle_y(KD_get_data(current_rect)) + get_rectangle_height(KD_get_data(current_rect));
            segment3->point2->x = get_rectangle_x(KD_get_data(current_rect));
            segment3->point2->y = get_rectangle_y(KD_get_data(current_rect)) + get_rectangle_height(KD_get_data(current_rect));
            segment3->point1->linked_to = segment3;
            segment3->point2->linked_to = segment3;
            segment3->point1->pair = segment3->point2;
            segment3->point2->pair = segment3->point1;
            strcpy(segment3->point1->code, "ORIG");
            strcpy(segment3->point2->code, "ORIG");

            segment4->point1->x = get_rectangle_x(KD_get_data(current_rect));
            segment4->point1->y = get_rectangle_y(KD_get_data(current_rect)) + get_rectangle_height(KD_get_data(current_rect));
            segment4->point2->x = get_rectangle_x(KD_get_data(current_rect));
            segment4->point2->y = get_rectangle_y(KD_get_data(current_rect));
            segment4->point1->linked_to = segment4;
            segment4->point2->linked_to = segment4;
            segment4->point1->pair = segment4->point2;
            segment4->point2->pair = segment4->point1;
            strcpy(segment4->point1->code, "ORIG");
            strcpy(segment4->point2->code, "ORIG");

            insert(segmentsList, segment1);
            insert(segmentsList, segment2);
            insert(segmentsList, segment3);
            insert(segmentsList, segment4);
        }
        build_segments(rectangleTree, segmentsList, KD_get_right_node(current_rect));
    }
}

void add_wrap_around_rectangle(tree rectangleTree, tree circleTree, dynamicList segmentsList) {
    segment_t* aux1 = calloc(1, sizeof(segment_t));
    aux1->point1 = calloc(1, sizeof(point_t));
    aux1->point2 = calloc(1, sizeof(point_t));

    segment_t* aux2 = calloc(1, sizeof(segment_t));
    aux2->point1 = calloc(1, sizeof(point_t));
    aux2->point2 = calloc(1, sizeof(point_t));

    segment_t* aux3 = calloc(1, sizeof(segment_t));
    aux3->point1 = calloc(1, sizeof(point_t));
    aux3->point2 = calloc(1, sizeof(point_t));

    segment_t* aux4 = calloc(1, sizeof(segment_t));
    aux4->point1 = calloc(1, sizeof(point_t));
    aux4->point2 = calloc(1, sizeof(point_t));

    aux1->point1->x = -100;
    aux1->point1->y = -100;
    aux1->point2->x = max(get_biggest_x(rectangleTree), get_biggest_x(circleTree)) + 100;
    aux1->point2->y = -100;
    aux1->point1->linked_to = aux1;
    aux1->point2->linked_to = aux1;
    aux1->point1->pair = aux1->point2;
    aux1->point2->pair = aux1->point1;
    strcpy(aux1->point1->code, "RE");
    strcpy(aux1->point2->code, "RE");

    aux2->point1->x = max(get_biggest_x(rectangleTree), get_biggest_x(circleTree)) + 100;
    aux2->point1->y = -100;
    aux2->point2->x = max(get_biggest_x(rectangleTree), get_biggest_x(circleTree)) + 100;
    aux2->point2->y = max(get_biggest_y(rectangleTree), get_biggest_y(circleTree)) + 100;
    aux2->point1->linked_to = aux2;
    aux2->point2->linked_to = aux2;
    aux2->point1->pair = aux2->point2;
    aux2->point2->pair = aux2->point1;
    strcpy(aux2->point1->code, "RE");
    strcpy(aux2->point2->code, "RE");

    aux3->point1->x = max(get_biggest_x(rectangleTree), get_biggest_x(circleTree)) + 100;
    aux3->point1->y = max(get_biggest_y(rectangleTree), get_biggest_y(circleTree)) + 100;
    aux3->point2->x = -100;
    aux3->point2->y = max(get_biggest_y(rectangleTree), get_biggest_y(circleTree)) + 100;
    aux3->point1->linked_to = aux3;
    aux3->point2->linked_to = aux3;
    aux3->point1->pair = aux3->point2;
    aux3->point2->pair = aux3->point1;
    strcpy(aux3->point1->code, "RE");
    strcpy(aux3->point2->code, "RE");

    aux4->point1->x = -100;
    aux4->point1->y = max(get_biggest_y(rectangleTree), get_biggest_y(circleTree)) + 100;
    aux4->point2->x = -100;
    aux4->point2->y = -100;
    aux4->point1->linked_to = aux4;
    aux4->point2->linked_to = aux4;
    aux4->point1->pair = aux4->point2;
    aux4->point2->pair = aux4->point1;
    strcpy(aux4->point1->code, "RE");
    strcpy(aux4->point2->code, "RE");

    insert(segmentsList, aux1);
    insert(segmentsList, aux2);
    insert(segmentsList, aux3);
    insert(segmentsList, aux4);
}

void* build_vertex_array(dynamicList segmentsList, double xMeteor, double yMeteor) {
    point_t* aux = calloc(2 * get_size(segmentsList), sizeof(point_t));
    void* pos = get_head(segmentsList);
    for (int i = 0; i < get_size(segmentsList) * 2; i += 2) {
        segment_t* dataAux = get_item(segmentsList, pos);
        pos = get_next(segmentsList, pos);

        if (fabs(xMeteor - dataAux->point1->x) == 0) {
            dataAux->point1->angle = 0;

        } else {
            dataAux->point1->angle = (atan(fabs(yMeteor - dataAux->point1->y) / fabs(xMeteor - dataAux->point1->x))) * (180 / PI);
        }

        dataAux->point1->distance = sqrt(pow(dataAux->point1->x - xMeteor, 2) + pow(dataAux->point1->y - yMeteor, 2));

        if (fabs(xMeteor - dataAux->point2->x) == 0) {
            dataAux->point2->angle = 0;

        } else {
            dataAux->point2->angle = (atan(fabs(yMeteor - dataAux->point2->y) / fabs(xMeteor - dataAux->point2->x))) * (180 / PI);
        }

        dataAux->point2->distance = sqrt(pow(dataAux->point2->x - xMeteor, 2) + pow(dataAux->point2->y - yMeteor, 2));

        if (dataAux->point1->x < xMeteor) {
            if (dataAux->point1->y < yMeteor) {
                //Third quadrant

                dataAux->point1->angle += 180;
                dataAux->point1->quadrant = 3;

            } else if (dataAux->point1->y > yMeteor) {
                //Second quadrant

                dataAux->point1->angle = 180 - dataAux->point1->angle;
                dataAux->point1->quadrant = 2;
            }

        } else if (dataAux->point1->x >= xMeteor) {
            if (dataAux->point1->y < yMeteor) {
                //Fourth quadrant

                dataAux->point1->angle = 360 - dataAux->point1->angle;
                dataAux->point1->quadrant = 4;

            } else if (dataAux->point1->y >= yMeteor) {
                //First quadrant

                dataAux->point1->quadrant = 1;
            }
        }

        if (dataAux->point2->x < xMeteor) {
            if (dataAux->point2->y < yMeteor) {
                //Third quadrant

                dataAux->point2->angle += 180;
                dataAux->point2->quadrant = 3;

            } else if (dataAux->point2->y > yMeteor) {
                //Second quadrant

                dataAux->point2->angle = 180 - dataAux->point2->angle;
                dataAux->point2->quadrant = 2;
            }

        } else if (dataAux->point2->x >= xMeteor) {
            if (dataAux->point2->y < yMeteor) {
                //Fourth quadrant

                dataAux->point2->angle = 360 - dataAux->point2->angle;
                dataAux->point2->quadrant = 4;

            } else if (dataAux->point2->y >= yMeteor) {
                //First quadrant

                dataAux->point2->quadrant = 1;
            }
        }

        switch (dataAux->point1->quadrant) {
            case 1:

                switch (dataAux->point2->quadrant) {
                    case 1:

                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 2:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 3:
                        //Impossible !
                        break;

                    case 4:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;
                }

                break;

            case 2:

                switch (dataAux->point2->quadrant) {
                    case 1:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 2:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 3:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 4:
                        //Impossible !
                        break;
                }

                break;

            case 3:

                switch (dataAux->point2->quadrant) {
                    case 1:
                        //Impossible !
                        break;

                    case 2:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 3:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 4:
                        if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;
                }

                break;

            case 4:

                switch (dataAux->point2->quadrant) {
                    case 1:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 2:
                        //Impossible !
                        break;

                    case 3:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;

                    case 4:
                        if (dataAux->point1->angle > dataAux->point2->angle) {
                            dataAux->point1->type = 'e';
                            dataAux->point2->type = 's';

                        } else if (dataAux->point1->angle < dataAux->point2->angle) {
                            dataAux->point1->type = 's';
                            dataAux->point2->type = 'e';

                        } else if (dataAux->point1->angle == dataAux->point2->angle) {
                            if (dataAux->point1->distance > dataAux->point2->distance) {
                                dataAux->point1->type = 's';
                                dataAux->point2->type = 'e';

                            } else if (dataAux->point1->distance < dataAux->point2->distance) {
                                dataAux->point1->type = 'e';
                                dataAux->point2->type = 's';
                            }
                        }
                        break;
                }

                break;
        }
        //============================================================================

        aux[i] = *(dataAux->point1);
        aux[i + 1] = *(dataAux->point2);
    }

    qsort(aux, 2 * get_size(segmentsList), sizeof(point_t), compare_for_qsort);

    return aux;
}

double get_point_x(void* point) {
    point_t* aux = point;
    return aux->x;
}

double get_point_y(void* point) {
    point_t* aux = point;
    return aux->y;
}

char* get_code(void* point) {
    point_t* aux = point;
    return aux->code;
}

char get_point_type(void* point) {
    point_t* aux = point;
    return aux->type;
}

double get_angle(void* point) {
    point_t* aux = point;
    return aux->angle;
}

int get_quadrant(void* point) {
    point_t* aux = point;
    return aux->quadrant;
}

void* get_origin(void* point) {
    point_t* aux = point;
    return aux->linked_to;
}

bool get_analyzed(void* point) {
    point_t* aux = point;
    return aux->analyzed;
}

void* at_pos_array(void* array, int pos) {
    segment_t* aux = array;
    return &aux[pos];
}

void* get_pair(void* point) {
    point_t* aux = point;
    return aux->pair;
}

void set_analyzed(void* point, bool state) {
    point_t* aux = point;
    aux->analyzed = state;
}

void free_points_info(void* segment) {
    if (segment != NULL) {
        segment_t* aux = segment;
        if (aux->point1) {
            free(aux->point1);
        }
        if (aux->point2) {
            free(aux->point2);
        }
    }
}

void destory_segment(void* segment) {
    segment_t* aux = segment;
    free(aux->point1);
    free(aux->point2);
    free(aux);
}

void set_angle(void* point, double angle) {
    point_t* aux = point;
    aux->angle = angle;
}

void free_shadow_polygons_array(void* array) {
    segment_t* aux = array;
    for (int i = 0; i < 3; i++) {
        free(aux[i].point1);
        free(aux[i].point2);
    }
}
