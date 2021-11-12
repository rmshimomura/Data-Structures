#include "graph.h"
#include "../Dynamic_list/dynamic_list.h"
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

    return aux;

}

void* create_vertex (char* id, double x, double y) {

    vertex* aux = calloc(1, sizeof(vertex));
    aux->vertex_data = new_vertex_data(id, x, y);
    return aux;

}

void* vertex_get_data(void* v) {
    return v ? ((vertex*)v)->vertex_data : NULL;
}

void* vertex_get_edges(void* v) {
    return ((vertex*)v)->edges;
}

void* edge_get_data(void* e) {
    return ((edge*)e)->edge_data;
}

void* edge_get_from(void* e) {
    return ((edge*)e)->from;
}

void* edge_get_to(void* e) {
    return ((edge*)e)->to;
}

void* extract_all_edges(void* connections) {

    graph* aux = connections;

    void* all_edges = create_list();

    for(int i = 0; i < aux->size; i++) {

        for(void* temp = get_head(aux->vertexes[i].edges); temp; temp = get_next(temp))
            insert_list(all_edges, get_list_element(temp));

    }

    return all_edges;

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

    for(int i = 0; i < graph_aux->size; i++) if(!strcmp(vertex_data_get_id(graph_aux->vertexes[i].vertex_data), vertex_id)) return &(graph_aux->vertexes[i]);

    return NULL;

}

void graph_insert_edge (void* connections, char* name, char* vertex_1, char* vertex_2, char* left_side_square, char* right_side_square, double length, double average_speed) {

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

void graph_remove_edge(void* connections, char* vertex_1, char* vertex_2, bool remove_vertexes) {

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

    edge* aux = get_list_element(find_edge(v1->edges, v2));

    if(aux) {
        remove_node(v1->edges, aux, free_edge, remove_vertexes);
        free(aux);
    } else {
        printf("There's no edge linking %s and %s!\n", vertex_1, vertex_2);
    }

}

void* find_edge(void* v1_edges, void* v2){

    if(!v1_edges) {
        puts("There's no edges on this vertex!");
        return NULL;
    }

    void* list_node = get_head(v1_edges);
    edge* list_element = get_list_element(list_node);

    for(int i = 0; i < get_size(v1_edges); i++) {

        if(list_element->to == v2) return list_node;

        list_node = get_next(list_node);
        list_element = get_list_element(list_node);

    }

    return NULL;

}

int adjacent(void* connections, char* vertex_1, char* vertex_2) {

    vertex* v1 = graph_find_vertex(connections, vertex_1);
    vertex* v2 = graph_find_vertex(connections, vertex_2);

    if(!v1) {
        printf("Vertex 1 with id = %s doesn't exist on graph!\n", vertex_1);
        return -1;
    }

    if(!v2) {
        printf("Vertex 2 with id = %s doesn't exist on graph!\n", vertex_2);
        return -1;
    }

    edge* aux = find_edge(v1->edges, v2);

    return aux ? 1 : 0;

}

void* list_of_adjacents_by_name(void* connections, char* vertex_1) {

    vertex* v1 = graph_find_vertex(connections, vertex_1);

    if(!v1) {
        printf("Vertex 1 with id = %s doesn't exist on graph!\n", vertex_1);
        return NULL;
    }

    return v1->edges;

}

void* list_of_adjacents_by_address(void* vertex_1) {

    return vertex_1 ? ((vertex*)vertex_1)->edges : NULL;

}

void free_graph(void* connections) {

    graph* aux = connections;

    for(int i = 0; i < aux->size; i++) {

        if(aux->vertexes[i].vertex_data) free_vertex_data(aux->vertexes[i].vertex_data);

        for(void* runner = get_head(aux->vertexes[i].edges); runner; runner = get_next(runner)){

            free_edge(get_list_element(runner));

        }

        free_list(aux->vertexes[i].edges, true, free);

    }

    free(aux->vertexes);
    free(aux);

}

void free_edge(void* edge_) {

    edge* aux = edge_;
    aux->from = NULL;
    aux->to = NULL;
    free_edge_data(aux->edge_data);

}