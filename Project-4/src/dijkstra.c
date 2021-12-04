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

void free_helper(void* data) {

    helper* aux = data;
    aux->vertex = NULL;
    aux->from = NULL;
    free(aux);

}

void* get_dijkstra_vertex(void* data){

    helper* aux = data;
    return aux->vertex;

}

int compare(void* a, void* b) {
    helper* aux = a;
    return aux->vertex == b ? 1 : 0;
}

double distance_dijkstra(void* vertex_1, void* vertex_2) {

    return sqrt(pow(vertex_data_get_x(vertex_get_data(vertex_1)) - vertex_data_get_x(vertex_get_data(vertex_2)), 2.0) + pow(vertex_data_get_y(vertex_get_data(vertex_1)) - vertex_data_get_y(vertex_get_data(vertex_2)), 2.0));

}

void* dijkstra(void* connections, char* start, char* end, double (*operation_mode)(void*)) {
    
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

    priority_queue_insert(prior_queue, new_helper(origin, NULL, 0), 0); 

    while(search != destination) {

        void* search_adjacents = list_of_adjacents_by_address(search);

        if(find_element(visited_vertexes, search, compare) == NULL) {

            for(void* aux = get_head(search_adjacents); aux; aux = get_next(aux)){

                void* edge = get_list_element(aux);

                if(edge_get_from(edge) != edge_get_to(edge)) {

                    void* edge_data = edge_get_data(edge);
                    void* edge_to = edge_get_to(edge);

                    double cost_until_this_point = operation_mode(edge_data) + search_cost;
                    
                    void* found = find_element(visited_vertexes, edge_to, compare);

                    if(found == NULL && edge_to != back_track) {

                        priority_queue_insert(prior_queue, new_helper(edge_to, search, cost_until_this_point + distance_dijkstra(edge_to, destination)), cost_until_this_point + distance_dijkstra(edge_to, destination)); // Are we able to use a* ?

                    }

                }
                
            }

        }

        back_track = search; // Update to compare with the next vertex

        helper* top = priority_queue_pop(prior_queue, false, free_helper);

        insert_list(visited_vertexes, top); // Updated visited vertexes, remove from the priority queue

        helper* next_vertex = priority_queue_get_element(priority_queue_get_head(prior_queue));

        if(!next_vertex) break;

        search = next_vertex->vertex;
        search_cost = next_vertex->cost;
        
    }

    insert_list(visited_vertexes, priority_queue_pop(prior_queue, false, free)); // Remove the destination vertex

    free_list(prior_queue, true, free_helper);

    void* optimized_path = create_list(); // List of the vertexes to the optimized path
    void* unused_helpers = create_list();

    if(((helper*)get_list_element(get_end(visited_vertexes)))->vertex == destination) {

        for(void* aux = get_end(visited_vertexes); aux; aux = get_previous(aux)) {

            helper* builder = get_list_element(aux);

            if(builder->vertex == destination || back_track == builder->vertex) {
                back_track = builder->from;
                insert_first(optimized_path, builder);
            } else{
                insert_first(unused_helpers, builder);
            }

        }
    } else { //No path found
        
        free_list(visited_vertexes, true, free_helper);
        free_list(unused_helpers, true, free_helper);
        free_list(optimized_path, true, free);
        return NULL;

    }

    free_list(visited_vertexes, false, free_helper);
    free_list(unused_helpers, true, free_helper);

    return optimized_path;

}

void to_string(void* path_node) {

    helper* aux = path_node;

    printf("[%s] ", vertex_data_get_id(vertex_get_data(aux->vertex)));

}