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

typedef struct package {

    void* list_of_edges;
    void* root;

} package;

void* get_package_list_of_edges (void* data) {

    return data ? ((package*)data)->list_of_edges : NULL;

}

void* get_package_root (void* data) {

    return data ? ((package*)data)->root : NULL;

}

void* new_package(void* original_root) {

    package* aux = calloc(1, sizeof(package));
    aux->list_of_edges = create_list();
    aux->root = original_root;
    return aux;

}

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

void rv_function_aux(void* edges[], int num_of_edges, void* root, int height, double factor){

    for(int i = 0; i < num_of_edges; i++) {

        edge* aux = edges[i];

        if(aux){

            if(!strcmp(vertex_data_get_id(vertex_get_data(aux->from)), vertex_data_get_id(root))) {

                if(factor * height < 1) {

                    edge_data_set_average_speed(aux->edge_data, edge_data_get_average_speed(aux->edge_data) - (edge_data_get_average_speed(aux->edge_data) * (factor * height)));

                } else {

                    edge_data_set_average_speed(aux->edge_data, edge_data_get_average_speed(aux->edge_data) * (0.01));

                }

                void* other_one = aux->to;

                edges[i] = NULL;

                rv_function_aux(edges, num_of_edges, vertex_get_data(other_one), height + 1, factor);


            } else if (!strcmp(vertex_data_get_id(vertex_get_data(aux->to)), vertex_data_get_id(root))) {

                if(factor * height < 1) {

                    edge_data_set_average_speed(aux->edge_data, edge_data_get_average_speed(aux->edge_data) - (edge_data_get_average_speed(aux->edge_data) * (factor * height)));

                } else {

                    edge_data_set_average_speed(aux->edge_data, edge_data_get_average_speed(aux->edge_data) * (0.01));

                }

                void* other_one = aux->from;

                edges[i] = NULL;

                rv_function_aux(edges, num_of_edges, vertex_get_data(other_one), height + 1, factor);

            }

        }

    }

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
        
        if(analize->to != analize->from) {
            

            int i = k_find(groups, find_index_kruskal(groups, analize->from->vertex_data->id, get_size(vertex_list)));
            int j = k_find(groups, find_index_kruskal(groups, analize->to->vertex_data->id, get_size(vertex_list)));

            if(i != j) {

                insert_list(result, analize);
                k_union(groups, i, j);
                
            } else if(!strcmp(analize->from->vertex_data->id, analize->to->vertex_data->id)) {
                
                insert_list(result, analize);
                
            }

        } else {

            insert_list(result, analize);

        }
    }

    void* packaging = create_list();

    for(void* edge_aux = get_head(result); edge_aux; edge_aux = get_next(edge_aux)) { // For each edge of the result list, we'll pack them sorted by root

        edge* analize = get_list_element(edge_aux);

        void* origin_root_from = groups[k_find(groups, find_index_kruskal(groups, analize->from->vertex_data->id, get_size(vertex_list)))].vertex;

        bool found = false;

        for(void* package_runner = get_head(packaging); package_runner; package_runner = get_next(package_runner)){ // Check if the root of the current element already exists on the packaging list

            package* look = get_list_element(package_runner);

            if(look->root == origin_root_from){

                insert_list(look->list_of_edges, analize);
                found = true;
                break;

            }

        }

        if(!found){

            insert_list(packaging, new_package(origin_root_from));

            package* look = get_list_element(get_end(packaging));

            insert_list(look->list_of_edges, analize);

            look->root = origin_root_from;

        }

    }

    free(groups);
    free_list(result, false, NULL);
    free_list(vertex_list, false, NULL);

    return packaging;
}

void free_package(void* pack) {

    if(!pack) return;
    
    package* aux = pack;
    free_list(aux->list_of_edges, false, free);
    aux->root = NULL;
    free(aux);

}