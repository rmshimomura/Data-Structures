#include "Dynamic_list/dynamic_list.h"
#include "Graph/graph.h"
#include "checks.h"
#include "dijkstra.h"
#include "edge.h"
#include "libs.h"
#include "paths.h"
#include "system.h"
#include "vertex.h"
#include "kruskal.h"

int main(int argc, char** argv) {
    path paths = create_general_paths();
    flag flags = create_checkers();
    get_arguments(argc, argv, paths, flags);

    show_paths(paths);
    free_paths(paths);

    /*
    void* graph = create_graph(7);
    graph_insert_vertex(graph, new_vertex_data("a", 0.0, 0.0));
    graph_insert_vertex(graph, new_vertex_data("b", 0.0, 0.0));
    graph_insert_vertex(graph, new_vertex_data("c", 0.0, 0.0));
    graph_insert_vertex(graph, new_vertex_data("d", 0.0, 0.0));
    graph_insert_vertex(graph, new_vertex_data("e", 0.0, 0.0));
    graph_insert_vertex(graph, new_vertex_data("f", 0.0, 0.0));
    graph_insert_vertex(graph, new_vertex_data("g", 0.0, 0.0));

    graph_insert_edge(graph, "ab", "a", "b", "-", "-", 0, 1);
    graph_insert_edge(graph, "gf", "g", "f", "-", "-", 1, 1);
    graph_insert_edge(graph, "cd", "c", "d", "-", "-", 2, 1);
    graph_insert_edge(graph, "eb", "e", "b", "-", "-", 3, 1);
    graph_insert_edge(graph, "bd", "b", "d", "-", "-", 4, 1);
    graph_insert_edge(graph, "de", "d", "e", "-", "-", 5, 1);
    graph_insert_edge(graph, "fc", "f", "c", "-", "-", 6, 1);
    graph_insert_edge(graph, "ca", "c", "a", "-", "-", 7, 1);
    graph_insert_edge(graph, "fe", "f", "e", "-", "-", 8, 1);
    graph_insert_edge(graph, "eg", "e", "g", "-", "-", 9, 1);
    graph_insert_edge(graph, "df", "d", "f", "-", "-", 10, 1);

    void* aux = extract_all_edges(graph);
    void* final_result = kruskal(aux);
    free_list(aux, false, NULL);

    void* result = dijkstra(graph, "S", "E", fastest_path);

    for(void* aux = get_head(result); aux ; aux = get_next(aux)) {
        to_string(get_list_element(aux));
        if(get_next(aux)) printf("-> ");
        else puts(".");
    }

    if(get_size(result) == 0) {
        puts("[ ]");
    }

    free_graph(graph);

    */

    // free(flags);
}