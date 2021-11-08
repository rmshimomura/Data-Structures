#include "dijkstra.h"
#include "edge.h"
#include "vertex.h"
#include "Graph/graph.h"
#include "Priority_queue/priority_queue.h"
#include "Dynamic_list/dynamic_list.h"

typedef struct helper{

    void* vertex;
    void* from;
    double cost;

} helper;

void* new_helper(void* vertex, void* from, double cost) {

    helper* aux = calloc(1, sizeof(helper));
    aux->vertex = vertex;
    aux->from = from;
    aux->cost = cost;

    return aux;

}

void* dijkstra(void* connections, char* start, char* end) {
    
    void* origin = graph_find_vertex(connections, start);
    void* destination = graph_find_vertex(connections, end);

    if(!origin) {
        printf("Vertex 1 with id = %s doesn't exist on graph!\n", start);
        return NULL;
    }

    if(!destination) {
        printf("Vertex 2 with id = %s doesn't exist on graph!\n", end);
        return NULL;
    }

    void* search = origin;
    double search_cost = 0;
    void* back_track = NULL;

    void* prior_queue = create_priority_queue();
    void* visited_vertexes = create_list();

    priority_queue_insert(prior_queue, new_helper(origin, NULL, 0), 0); // S

    while(search != destination) {

        void* search_adjacents = list_of_adjacents_by_address(search);

        for(void* aux = get_head(search_adjacents); aux; aux = get_next(aux)){

            void* edge = get_list_element(aux);

            void* edge_data = edge_get_data(edge);

            void* edge_to = edge_get_to(edge);

            if(edge_to != back_track){ // Prevent self looping

                double cost_until_this_point = ((edge_data_get_length(edge_data)/edge_data_get_average_speed(edge_data)) + search_cost);
                priority_queue_insert(prior_queue, new_helper(edge_to, search, cost_until_this_point), cost_until_this_point);

            }

        }

        insert_list(visited_vertexes, priority_queue_pop(prior_queue, false, free)); // Updated visited vertexes, remove from the priority queue

        helper* aux = priority_queue_get_element(priority_queue_get_head(prior_queue));

        search = aux->vertex; // Go to the next vertex of the priority queue
        search_cost = aux->cost; // Update search cost to the next vertex

    }

    insert_list(visited_vertexes, priority_queue_pop(prior_queue, false, free)); // Remove the destination vertex

    void* optimized_path = create_list(); // List of the vertexes to the optimized path

    for(void* aux = get_end(visited_vertexes); aux; aux = get_previous(aux)) {
        
        helper* builder = get_list_element(aux);

        if(builder->vertex == destination || back_track == builder->vertex) {

            back_track = builder->from;
            insert_list(optimized_path, builder);

        }

    } 

    return optimized_path;

}

void to_string(void* path_node) {

    helper* aux = path_node;

    printf("[%s] ", vertex_data_get_id(vertex_get_data(aux->vertex)));

}