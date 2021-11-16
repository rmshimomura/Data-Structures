#include "AVL_Tree/AVL.h"
#include "Dynamic_list/dynamic_list.h"
#include "Graph/graph.h"
#include "Hash/hash.h"
#include "checks.h"
#include "dijkstra.h"
#include "edge.h"
#include "kruskal.h"
#include "libs.h"
#include "paths.h"
#include "system.h"
#include "vertex.h"

int main(int argc, char** argv) {

    void* paths = create_general_paths();
    void* flags = create_checkers();

    get_arguments(argc, argv, paths, flags);
    int size = structures_size(paths);
    if(size == -1) { 
        puts("Size not inserted!");
        free_paths(paths);
        free(flags);
        return -1;
    }
    void* blocks = create_tree();
    void* blocks_hash = hash_table_create_table(size);
    void* connections = create_graph(size);
    get_data(connections, blocks, blocks_hash, paths, flags);
    
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

    // void* result = dijkstra(graph, "S", "E", fastest_path);

    // for(void* aux = get_head(result); aux ; aux = get_next(aux)) {
    //     to_string(get_list_element(aux));
    //     if(get_next(aux)) printf("-> ");
    //     else puts(".");
    // }

    // if(get_size(result) == 0) {
    //     puts("[ ]");
    // }

    free_graph(graph);

    */

    free_graph(connections);
    hash_table_destroy(blocks_hash, free, false);
    destroy_AVL_tree(blocks, get_root(blocks), free_block_list);
    free(blocks);
    free(flags);
    free_paths(paths);
}