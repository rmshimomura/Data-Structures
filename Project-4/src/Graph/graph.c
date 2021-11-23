#include "graph.h"
#include "../Dynamic_list/dynamic_list.h"
#include "../edge.h"
#include "../vertex.h"
#include "../qry.h"

typedef struct edge {

    void* from;
    void* to;
    void* edge_data;
    
} edge;

typedef struct vertex {

    void* edges; //List of edges
    void* vertex_data; // Data
    int activated;

} vertex;

typedef struct graph {
    
    vertex* vertexes; // Array of vertexes
    int size, next_free_space;

} graph;

int compare_vertexes(void* data_1, void* data_2) {

    vertex* aux_1 = data_1;
    vertex* aux_2 = data_2;

    return !strcmp(vertex_data_get_id(aux_1->vertex_data), vertex_data_get_id(aux_2->vertex_data));

}

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

void vertex_set_activated(void* v, bool activated) {

    vertex* aux = v;
    aux->activated = activated;

}

void* graph_get_vertexes(void* connections) {
    graph* aux = connections;
    return aux->vertexes;
}

void* return_vertex_address_by_index(void* connections, int index) {

    graph* aux = connections;
    
    if(index > aux->size){
        puts("Index > size!");
        return NULL;
    }
    return &(aux->vertexes[index]);

}

int graph_get_size(void* connections) {
    graph* aux = connections;
    return aux->size;
}

void* vertex_get_data(void* v) {
    return v ? ((vertex*)v)->vertex_data : NULL;
}

void vertex_set_edges(void* v, void* address) {
    ((vertex*)v)->edges = address;
}

void* vertex_get_edges(void* v) {
    return ((vertex*)v)->edges ? ((vertex*)v)->edges : NULL;
}

int vertex_get_activated(void* v) {
    return ((vertex*)v)->activated;
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

void* extract_all_edges_cx(void* connections, double limiar, void* list_of_modifications) {

    graph* aux = connections;

    void* all_edges = create_list();

    for(int i = 0; i < aux->size; i++) {

        if(aux->vertexes[i].activated == true) {

            for(void* temp = get_head(aux->vertexes[i].edges); temp; temp = get_next(temp)) {

                if(edge_data_get_average_speed(edge_get_data(get_list_element(temp))) >= limiar && !find_element_by_edge_name(aux->vertexes[i].edges, temp)) {

                    insert_list(all_edges, get_list_element(temp));

                } else {

                    char line[1000] = "";

                    sprintf(line, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"8\"/>\n", vertex_data_get_x(vertex_get_data(edge_get_from(get_list_element(temp)))), vertex_data_get_y(vertex_get_data(edge_get_from(get_list_element(temp)))), vertex_data_get_x(vertex_get_data(edge_get_to(get_list_element(temp)))), vertex_data_get_y(vertex_get_data(edge_get_to(get_list_element(temp))))); 

                    char* command = calloc(strlen(line) + 5, sizeof(char));
                    strcpy(command, line);
                    insert_list(list_of_modifications, command);

                }

            }

        }

    }

    return all_edges;

}

void* extract_all_edges_inside_rectangle(void* connections, double x, double y, double w, double h) {

    graph* aux = connections;

    void* all_edges = create_list();

    for(int i = 0; i < aux->size; i++) {

        if(inside(vertex_data_get_x(aux->vertexes[i].vertex_data), vertex_data_get_y(aux->vertexes[i].vertex_data), 0, 0, x, y, w, h) && aux->vertexes[i].activated == true) { //Check if the current vertex is inside the given rectangle

            for(void* temp = get_head(aux->vertexes[i].edges); temp; temp = get_next(temp)) { 

                if(inside(vertex_data_get_x(vertex_get_data(edge_get_to(get_list_element(temp)))), vertex_data_get_y(vertex_get_data(edge_get_to(get_list_element(temp)))), 0, 0, x, y, w, h)) {  //Check if the end point of this edge is still inside the rectangle
                    
                    insert_list(all_edges, get_list_element(temp)); // If so, add to the list

                }
            }

        }

    }

    return all_edges;

}

void* extract_all_activated_vertexes_from_list(void* sequence) {

    void* vertex_list = create_list();

    for(void* aux = get_head(sequence); aux; aux = get_next(aux)) {

        if(vertex_get_activated(edge_get_to(get_list_element(aux))) && !find_element_by_vertex_name(vertex_list, vertex_data_get_id(vertex_get_data(edge_get_to(get_list_element(aux)))))) {            
            insert_list(vertex_list, vertex_get_data(edge_get_to(get_list_element(aux))));               
        }
        if(vertex_get_activated(edge_get_from(get_list_element(aux))) && !find_element_by_vertex_name(vertex_list, vertex_data_get_id(vertex_get_data(edge_get_from(get_list_element(aux)))))) {
            insert_list(vertex_list, vertex_get_data(edge_get_from(get_list_element(aux))));               
        }

    }

    return vertex_list;

}

void graph_insert_vertex(void* connections, void* vertex_created) {

    graph* aux_graph = connections;

    if(aux_graph->next_free_space == aux_graph->size) {

        puts("No more space available on the graph!");
        return;

    }

    aux_graph->vertexes[aux_graph->next_free_space].vertex_data = vertex_created;
    aux_graph->vertexes[aux_graph->next_free_space].edges = create_list();
    aux_graph->vertexes[aux_graph->next_free_space].activated = true;

    edge* aux_edge = calloc(1, sizeof(edge));
    aux_edge->from = &(aux_graph->vertexes[aux_graph->next_free_space]);
    aux_edge->to = &(aux_graph->vertexes[aux_graph->next_free_space]);
    char prime_name[512] = "";
    sprintf(prime_name, "%s-%s", vertex_data_get_id(vertex_created), vertex_data_get_id(vertex_created));
    aux_edge->edge_data = new_edge_data(prime_name, "-", "-", 0, 1, vertex_created, vertex_created);

    insert_list(aux_graph->vertexes[aux_graph->next_free_space].edges, aux_edge);

    aux_graph->next_free_space++;

}

void* graph_find_vertex(void* connections, char* vertex_id) {

    graph* graph_aux = connections;

    for(int i = 0; i < graph_aux->size; i++) if(!strcmp(vertex_data_get_id(graph_aux->vertexes[i].vertex_data), vertex_id)) return &graph_aux->vertexes[i];

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

        if(aux->vertexes[i].edges) free_list(aux->vertexes[i].edges, false, free);        

    }

    free(aux->vertexes);
    free(aux);

}

void free_edge(void* edge_) {

    edge* aux = edge_;
    aux->from = NULL;
    aux->to = NULL;
    free_edge_data(aux->edge_data);
    free(aux);

}

void create_graph_with_data(void* connections, FILE* file_roads) {

    char command[512], id[512], ldir[512], lesq[512], nome[512], i[512], j[512];
    double x, y, cmp, vm; 

    while(fscanf(file_roads, "%s", command) != EOF) {

        if(!strcmp(command, "v")){

            fscanf(file_roads, "%s %lf %lf", id, &x, &y);
            graph_insert_vertex(connections, new_vertex_data(id, x, y));

        } else if (!strcmp(command, "e")) { 

            fscanf(file_roads, "%s %s %s %s %lf %lf %s", i, j, ldir, lesq, &cmp, &vm, nome);
            graph_insert_edge(connections, nome, i, j, lesq, ldir, cmp, vm);

        }

    }

} 