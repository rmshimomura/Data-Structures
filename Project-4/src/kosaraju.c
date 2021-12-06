#include "kosaraju.h"
#include "Stack/stack.h"
#include "Graph/graph.h"
#include "Dynamic_list/dynamic_list.h"
#include "vertex.h"

typedef struct vertex_data {

    char* id;
    double x;
    double y;

} vertex_data;

typedef struct edge_data {

    char* name;
    char* left_side_square;
    char* right_side_square;
    double length;
    double average_speed;
    char direction[2];

} edge_data;

typedef struct edge {

    struct vertex* from;
    struct vertex* to;
    edge_data* edge_data;
    
} edge;

typedef struct vertex {

    void* edges; //List of edges
    vertex_data* vertex_data; // Data
    int activated;
    int visited;

} vertex;

typedef struct graph {
    
    vertex* vertexes; // Array of vertexes
    int size, next_free_space;

} graph;

void* transform_graph(graph* original_graph, double threshold, void* list_of_modifications) {

    graph* transpose_graph = create_graph(original_graph->size);

    for(int i = 0; i < original_graph->size; i++) {
        
        graph_insert_vertex_transpose(transpose_graph, new_vertex_data(original_graph->vertexes[i].vertex_data->id, original_graph->vertexes[i].vertex_data->x, original_graph->vertexes[i].vertex_data->y));

    }

    for(int i = 0; i < original_graph->size; i++) { 

        for(void* runner = get_head(original_graph->vertexes[i].edges); runner; runner = get_next(runner)) { 
            
            edge* edge_runner = get_list_element(runner);

            if(edge_runner->edge_data->average_speed >= threshold && edge_runner->from != edge_runner->to) {

                graph_insert_edge(
                    transpose_graph,
                    edge_runner->edge_data->name, edge_runner->to->vertex_data->id, edge_runner->from->vertex_data->id,
                    edge_runner->edge_data->left_side_square, edge_runner->edge_data->right_side_square,
                    edge_runner->edge_data->length, edge_runner->edge_data->average_speed
                );

            } else {

                char line[1000] = "";
                sprintf(line, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"8\"/>\n", edge_runner->from->vertex_data->x, edge_runner->from->vertex_data->y, edge_runner->to->vertex_data->x, edge_runner->to->vertex_data->y); 
                char* command = calloc(strlen(line) + 5, sizeof(char));
                strcpy(command, line);
                insert_list(list_of_modifications, command);

            }

        }
    }

    return transpose_graph;

}

void dfs_stacking(void* stack, vertex* current_vertex, double threshold) {

    if(current_vertex->visited)
        return;

    current_vertex->visited = true;

    for(void* runner = get_head(current_vertex->edges); runner; runner = get_next(runner)) {

        edge* analize = get_list_element(runner);

        if(!analize->to->visited && analize->edge_data->average_speed >= threshold) {
            dfs_stacking(stack, analize->to, threshold);
        }

    }

    stack_push(stack, current_vertex);

}

void region_find(vertex* current_vertex, void* region, double threshold, void* list_of_modifications) {

    current_vertex->visited = true;

    for(void* runner = get_head(current_vertex->edges); runner; runner = get_next(runner)) {

        edge* analize = get_list_element(runner);

        if(analize->edge_data->average_speed >= threshold) {

            if(!analize->to->visited) {
                
                region_find(analize->to, region, threshold, list_of_modifications);

            }

        }

    }

    insert_list(region, current_vertex);

}

void** kosaraju(void* connections, double threshold, void* list_of_modifications) { 

    graph* graph_aux = connections;
    void* stack = create_stack();

    for(int i = 0; i < graph_aux->size; i++) {

        dfs_stacking(stack, &graph_aux->vertexes[i], threshold);

    }

    graph* transpose_graph = transform_graph(graph_aux, threshold, list_of_modifications);

    void* list_of_regions = create_list();

    for (vertex* current_stack_vertex = stack_pop(stack); current_stack_vertex; current_stack_vertex = stack_pop(stack)) {

        vertex* current_transpose_vertex = graph_find_vertex(transpose_graph, current_stack_vertex->vertex_data->id);

        if(current_transpose_vertex->visited) {
            continue;
        }

        void* new_region = create_list();

        insert_list(new_region, current_transpose_vertex);
        current_transpose_vertex->visited = true;

        for(void* runner = get_head(current_transpose_vertex->edges); runner; runner = get_next(runner)) {

            edge* aux = get_list_element(runner);

            if(aux->edge_data->average_speed >= threshold) {

                if(!aux->to->visited) {

                    region_find(aux->to, new_region, threshold, list_of_modifications);

                }

            }

        }

        insert_list(list_of_regions, new_region);

    }

    void** package = calloc(2, sizeof(void*));

    package[0] = list_of_regions;
    package[1] = transpose_graph;

    stack_free(stack, false);

    return package;
    
}