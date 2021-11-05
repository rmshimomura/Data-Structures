#include "graph.h"
#include "../DynamicList/dynamicList.h"
#include "../edge.h"
#include "../vertex.h"

typedef struct edge {

    void* from;
    void* to;
    void* edge_data;
    
} edge;

typedef struct vertex {

    void* edges; //List of edges
    void* vertex_data; // Data

} vertex;

typedef struct graph {
    
    vertex* vertexes; // Array of vertexes
    int size, next_free_space;

} graph;


void* create_graph(int size) {

    if (!size || size < 0) {

        puts("SIZE NOT VALID!");
        return NULL;

    }

    graph* aux = calloc(1, sizeof(graph));
    aux->vertexes = calloc(size, sizeof(vertex));
    aux->size = size;
    aux->next_free_space = 0;

}

void* create_vertex (char* id, double x, double y) {

    vertex* aux = calloc(1, sizeof(vertex));
    aux->vertex_data = new_vertex_data(id, x, y);
    return aux;

}

void graph_insert_vertex(void* connections, void* vertex_created) {

    graph* aux_graph = connections;

    if(aux_graph->next_free_space == aux_graph->size) {

        puts("No more space available on the graph!");
        return;

    }

    aux_graph->vertexes[aux_graph->next_free_space].vertex_data = vertex_created;
    aux_graph->vertexes[aux_graph->next_free_space].edges = create_list();

    aux_graph->next_free_space++;

}

void* graph_find_vertex(void* connections, char* vertex_id) {

    graph* graph_aux = connections;

    for(int i = 0; i < graph_aux->size; i++) if(!strcmp(vertex_get_id(graph_aux->vertexes[i].vertex_data), vertex_id)) return &(graph_aux->vertexes[i]);

    return NULL;

}

void graph_insert_edge (void* connections, char* name, char* vertex_1, char* vertex_2, char* left_side_square, char* right_side_square, double length, double average_speed) {

    graph* aux_graph = connections;

    vertex* v1 = graph_find_vertex(connections, vertex_1);
    vertex* v2 = graph_find_vertex(connections, vertex_2);

    if(!v1) {
        printf("Vertex 1 with id = %s doesn't exist on graph!\n", vertex_1);
        return;
    }

    if(!v2) {
        printf("Vertex 2 with id = %s doesn't exist on graph!\n", vertex_2);
        return;
    }

    edge* aux_edge = calloc(1, sizeof(edge));
    aux_edge->from = v1;
    aux_edge->to = v2;

    aux_edge->edge_data = new_edge_data(name, left_side_square, right_side_square, length, average_speed, v1->vertex_data, v2->vertex_data);

    insert_list(v1->edges, aux_edge);

}