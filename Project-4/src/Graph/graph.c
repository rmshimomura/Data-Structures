#include "graph.h"
#include "../DynamicList/dynamicList.h"

typedef struct edge {

    char* name;
    void* from;
    void* to;
    char* left_side_square;
    char* right_side_square;
    double lenght;
    double average_speed;

} edge;

typedef struct vertex {

    char* id;
    void* edges;
    double x;
    double y;

} vertex;

typedef struct graph {
    
    vertex* vertexes;
    int size;

} graph;


void* create_graph(int size) {

    if (!size || size < 0) {

        puts("SIZE NOT VALID!");
        return NULL;

    }

}

void* graph_find_vertex(void* connections, char* vertex_name) {

    graph* graph_aux = connections;

    for(int i = 0; i < graph_aux->size; i++) if(!strcmp(graph_aux->vertexes[i].id, vertex_name)) return &(graph_aux->vertexes[i]);

    return NULL;

}

void graph_insert_edge(void* connections, char* vertex_1, char* vertex_2) {

    vertex* v1 = graph_find_vertex(connections, vertex_1);
    vertex* v2 = graph_find_vertex(connections, vertex_2);

    if (!v1) {
        printf("Vertex 1 with id = %s doesn't exists on the graph!\n", vertex_1);
        return;
    }

    if (!v2) {
        printf("Vertex 2 with id = %s doesn't exists on the graph!\n", vertex_2);
        return;
    }

    if(!v1->edges) v1->edges = create_list();




}