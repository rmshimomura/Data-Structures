#include "kruskal.h"
#include "Dynamic_list/dynamic_list.h"
#include "Graph/graph.h"
#include "edge.h"
#include "vertex.h"

typedef struct vertex_data {

    char* id;
    double x;
    double y;

} vertex_data;

typedef struct vertex {

    void* edges; //List of edges
    vertex_data* vertex_data; // Data
    int activated;

} vertex;

typedef struct edge_data {

    char* name;
    char* left_side_square;
    char* right_side_square;
    double length;
    double average_speed;
    char direction[2];

} edge_data;

typedef struct edge {

    vertex* from;
    vertex* to;
    edge_data* edge_data;
    
} edge;

typedef struct group {

    void* vertex;
    int parent;
    int rank;

} group;

int compare_edges(void* data_1, void* data_2) {

    if(edge_data_get_length(edge_get_data(data_1)) > edge_data_get_length(edge_get_data(data_2))) {
        return 1;
    } else if (edge_data_get_length(edge_get_data(data_1)) < edge_data_get_length(edge_get_data(data_2))) {
        return -1;
    }

    return 0;

}

int compare_names(void* data_1, void* data_2) {

    return strcmp(vertex_data_get_id(data_1), vertex_data_get_id(data_2));

}

int k_find(group* subsets, int i) {

    if(subsets[i].parent != i)
        subsets[i].parent = k_find(subsets, subsets[i].parent);

    return subsets[i].parent;

}

void k_union(group* subsets, int i, int j) {

    int i_root = k_find(subsets, i);
    int j_root = k_find(subsets, j);

    if(subsets[i_root].rank < subsets[j_root].rank){
        
        subsets[i_root].parent = j_root;

    } else if(subsets[i_root].rank > subsets[j_root].rank) {
        
        subsets[j_root].parent = i_root;
        
    } else {

        subsets[j_root].parent = i_root;
        subsets[i_root].rank++;

    }
    
}

int find_index_kruskal(group* groups, char* id, int iteration_size) {
    for(int i = 0; i < iteration_size; i++) {
        if(!strcmp(vertex_data_get_id(groups[i].vertex), id)) return i;
    }

    return -1;
}

void** kruskal(void* edges_list) {

    list_sort(edges_list, compare_edges);

    void* vertex_list = extract_all_activated_vertexes_from_list(edges_list);

    list_sort(vertex_list, compare_names);

    group* groups = calloc(get_size(vertex_list), sizeof(group));

    void* vertex_list_head = get_head(vertex_list);

    for(int i = 0; i < get_size(vertex_list); i++) {

        groups[i].parent = i;
        groups[i].rank = 0;
        groups[i].vertex = get_list_element(vertex_list_head);
        vertex_list_head = get_next(vertex_list_head);

    }

    void* result = create_list();


    for(void* runner = get_head(edges_list); runner; runner = get_next(runner)) {

        edge* analize = get_list_element(runner);

        int i = k_find(groups, find_index_kruskal(groups, analize->from->vertex_data->id, get_size(vertex_list)));
        int j = k_find(groups, find_index_kruskal(groups, analize->to->vertex_data->id, get_size(vertex_list)));

        if(i != j) {
            insert_list(result, analize);
            k_union(groups, i, j);
        } else if(!strcmp(analize->from->vertex_data->id, analize->to->vertex_data->id)) {
            insert_list(result, analize);
        }

    }

    for(void* aux = get_head(result); aux; aux = get_next(aux)) {
        edge* print = get_list_element(aux);
        printf("%s-%s ", print->from->vertex_data->id, print->to->vertex_data->id);

    }

    puts(" ");

    for(int i = 0; i < get_size(vertex_list); i++) {

        printf("groups[%d].rank = %d vertex = %s\n", i, groups[i].rank, vertex_data_get_id(groups[i].vertex));

    }

    puts(" ");

    return NULL;
}