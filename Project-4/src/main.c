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
    // path paths = create_general_paths();
    // flag flags = create_checkers();
    // get_arguments(argc, argv, paths, flags);

    // show_paths(paths);
    // free_paths(paths);

    // void* graph = create_graph(13);
    // graph_insert_vertex(graph, new_vertex_data("S", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("A", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("B", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("C", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("D", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("E", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("F", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("G", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("H", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("I", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("J", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("K", 0, 0));
    // graph_insert_vertex(graph, new_vertex_data("L", 0, 0));

    // graph_insert_edge(graph, "Rua", "S", "A", "esq", "dir", 7, 1);
    // graph_insert_edge(graph, "Rua", "S", "B", "esq", "dir", 2, 1);
    // graph_insert_edge(graph, "Rua", "S", "C", "esq", "dir", 3, 1);
    // graph_insert_edge(graph, "Rua", "A", "B", "esq", "dir", 3, 1);
    // graph_insert_edge(graph, "Rua", "A", "D", "esq", "dir", 4, 1);
    // graph_insert_edge(graph, "Rua", "B", "D", "esq", "dir", 4, 1);
    // graph_insert_edge(graph, "Rua", "B", "H", "esq", "dir", 1, 1);
    // graph_insert_edge(graph, "Rua", "D", "F", "esq", "dir", 5, 1);
    // graph_insert_edge(graph, "Rua", "H", "F", "esq", "dir", 3, 1);
    // graph_insert_edge(graph, "Rua", "H", "G", "esq", "dir", 2, 1);
    // graph_insert_edge(graph, "Rua", "G", "E", "esq", "dir", 2, 1);
    // graph_insert_edge(graph, "Rua", "K", "E", "esq", "dir", 5, 1);
    // graph_insert_edge(graph, "Rua", "I", "K", "esq", "dir", 4, 1);
    // graph_insert_edge(graph, "Rua", "J", "K", "esq", "dir", 4, 1);
    // graph_insert_edge(graph, "Rua", "I", "J", "esq", "dir", 6, 1);
    // graph_insert_edge(graph, "Rua", "L", "I", "esq", "dir", 4, 1);
    // graph_insert_edge(graph, "Rua", "L", "J", "esq", "dir", 4, 1);
    // graph_insert_edge(graph, "Rua", "C", "L", "esq", "dir", 2, 1);

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
    kruskal(aux);
    

    // void* result = dijkstra(graph, "S", "E", fastest_path);

    // for(void* aux = get_head(result); aux ; aux = get_next(aux)) {
    //     to_string(get_list_element(aux));
    //     if(get_next(aux)) printf("-> ");
    //     else puts(".");
    // }

    // if(get_size(result) == 0) {
    //     puts("[ ]");
    // }

    // graph_remove_edge(graph, "S", "A", true);
    // free_list(result, true, free_helper);
    free_graph(graph);

    // free(flags);
}