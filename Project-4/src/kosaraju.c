#include "kosaraju.h"
#include "Stack/stack.h"

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

    void* from;
    void* to;
    edge_data* edge_data;
    
} edge;

typedef struct vertex {

    void* edges; //List of edges
    vertex_data* vertex_data; // Data
    int activated;

} vertex;

typedef struct graph {
    
    vertex* vertexes; // Array of vertexes
    int size, next_free_space;

} graph;

