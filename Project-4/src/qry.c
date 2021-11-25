#include "qry.h"

#include "AVL_Tree/AVL.h"
#include "Dynamic_list/dynamic_list.h"
#include "Graph/graph.h"
#include "Hash/hash.h"
#include "block.h"
#include "dijkstra.h"
#include "kruskal.h"
#include "vertex.h"
#include "edge.h"

typedef struct point {

    double x, y;
    int num;
    char* cep;
    char face;
    void* vertex;

} point;

void catac_search(void* blocks, void* blocks_root, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);
void free_list_catac(void* sequence, FILE* txt_results, void (*free_node)(void*));
void* extract_all_edges_inside_rectangle(void* connections, double x, double y, double w, double h);

int inside(double x1, double y1, double p1_width, double p1_height, double x2, double y2, double p2_width, double p2_height) {
    if ((x1 >= x2 && x1 <= x2 + p2_width && y1 >= y2 && y1 <= y2 + p2_height && x1 + p1_width <= x2 + p2_width && y1 + p1_height <= y2 + p2_height)) return 1;
    //Fix the search on the p2 and vary on p1
    return 0;
}

void free_point(void* data) {

    if(!data) return;

    point* aux = data;
    free(aux->cep);
    aux->vertex = NULL;
    free(aux);
}

double distance(double x1, double y1, double x2, double y2) {

    return sqrt(pow(x2-x1, 2.0) + pow(y2 - y1, 2.0));

}

void find_closest_vertex (void* connections, point* aux) {

    for(int i = 0; i < graph_get_size(connections); i++) {

        void* current_vertex = return_vertex_address_by_index(connections, i);

        void* current_vertex_data = vertex_get_data(current_vertex);

        if(aux->vertex) { 
            
            if(distance(aux->x, aux->y, vertex_data_get_x(vertex_get_data(aux->vertex)), vertex_data_get_y(vertex_get_data(aux->vertex))) > distance(aux->x, aux->y, vertex_data_get_x(current_vertex_data), vertex_data_get_y(current_vertex_data))){
                aux->vertex = current_vertex;                
            }

        } else {

            aux->vertex = current_vertex;

        }

    }

}

void find_spacial_position(void* blocks_hash, point* aux, char* cep, char face, int num) {

    void* square = find_element(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);

    if(square) {

        if(face == 'N') {

            aux->x = get_x(square) + num;
            aux->y = get_y(square) + get_h(square);

        } else if (face == 'S') {

            aux->x = get_x(square) + num;
            aux->y = get_y(square);

        } else if (face == 'O') {

            aux->x = get_x(square) + get_w(square);
            aux->y = get_y(square) + num;

        } else if (face == 'L') {

            aux->x = get_x(square);
            aux->y = get_y(square) + num;

        }

    } else {

        puts("ERROR!, square not found!");

    }

}

void* find_position(void* connections, void* blocks_hash, char* cep, char face, int num, FILE* txt_results, void* list_of_modifications) {

    point* aux = calloc(1, sizeof(point));
    aux->cep = calloc(strlen(cep) + 1, sizeof(char));
    strcpy(aux->cep, cep);
    aux->face = face;
    aux->num = num;

    find_spacial_position(blocks_hash, aux, cep, face, num);

    find_closest_vertex(connections, aux);

    char modification_1[1000] = "";
    sprintf(modification_1, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"-50\" stroke=\"black\" stroke-width=\"3\" stroke-dasharray=\"4\" />\n", aux->x, aux->y, aux->x);
    char* command_1 = calloc(strlen(modification_1) + 5, sizeof(char));
    strcpy(command_1, modification_1);
    insert_list(list_of_modifications, command_1);

    char function_parameters[1000] = "";
    sprintf(function_parameters, "@o?(%s, %c, %d)", cep, face, num);
    char* parameters = calloc(strlen(function_parameters) + 2, sizeof(char));
    strcpy(parameters, function_parameters);
    char modification_2[1000] = "";
    sprintf(modification_2, "<text x=\"%.2lf\" y=\"-50\">%s</text>\n", aux->x + 2, parameters);
    char* command_2 = calloc(strlen(modification_2) + 5, sizeof(char));
    strcpy(command_2, modification_2);
    insert_list(list_of_modifications, command_2);

    char modification_3[1000] = "";
    sprintf(modification_3, "<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"3\" stroke=\"black\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", aux->x, aux->y);
    char* command_3 = calloc(strlen(modification_3) + 5, sizeof(char));
    strcpy(command_3, modification_3);
    insert_list(list_of_modifications, command_3);

    free(parameters);
    
    return aux;

}

void catac(void* connections, void* blocks, double x, double y, double w, double h, void* point_location, FILE* txt_results, void* list_of_modifications) {
    
    fprintf(txt_results, "catac(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    char modification[1000];

    sprintf(modification, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\"\n style=\"fill:#AB37C8;stroke:#AA0044;fill-opacity:0.5;stroke-opacity:0.5\" />\n", x,y,w,h); 

    char* command = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(command, modification);
    insert_list(list_of_modifications, command);

    catac_search(blocks, blocks_root, x, y, w, h, txt_results, list_of_modifications);

    if(point_location) { // @o? exists, so we need to check if this specific point was inside catac's rectangle, if so, we set him NULL

        point* aux = point_location;

        if(inside(aux->x, aux->y, 0, 0, x, y, w, h)) {

            fprintf(txt_results, "@o?(%s, %c, %d) is inside catac's rectangle!, removing...\n", aux->cep, aux->face, aux->num);
            free_point(aux);
            point_location = NULL;
        }

    }

    for(int i = 0; i < graph_get_size(connections); i++) {

        void* current_vertex = return_vertex_address_by_index(connections, i);

        void* aux_vertex_data = vertex_get_data(current_vertex);

        if(inside(vertex_data_get_x(aux_vertex_data), vertex_data_get_y(aux_vertex_data), 0, 0, x, y, w, h)) {
            
            fprintf(txt_results, "Vertex %s is inside CATAC's rectangle, deactivating...\n", vertex_data_get_id(aux_vertex_data));
            vertex_set_activated(current_vertex, 0);
            free_list_catac(vertex_get_edges(current_vertex), txt_results, free_edge);
            vertex_set_edges(current_vertex, NULL);
            
        }

    }
    
    for(int i = 0; i < graph_get_size(connections); i++) { // Loop through all vertexes

        void* current_vertex = return_vertex_address_by_index(connections, i);

        if(vertex_get_edges(current_vertex)){

            void* aux = get_head(vertex_get_edges(current_vertex));

            if(aux){

                int original_size = get_size(vertex_get_edges(current_vertex));

                for(int j = 0; j < original_size; j++) { // Loop the edges list

                    void* next = get_next(aux);

                    if(!vertex_get_activated(edge_get_to(get_list_element(aux)))) {
                        
                        fprintf(txt_results, "Edge %s -> %s removed because it points to a deactivated vertex!\n", vertex_data_get_id(vertex_get_data(edge_get_to(get_list_element(aux)))), vertex_data_get_id(vertex_get_data(edge_get_from(get_list_element(aux)))));
                        remove_node(vertex_get_edges(current_vertex), get_list_element(aux), free_edge, true);
        
                    }


                    if(next) { 

                        aux = next;

                    } else if (!next) { // If there's no next, we're at the end of the list, or there was only one element and we removed it

                        break;

                    }

                }

            }
        }
    }
    
    fprintf(txt_results, "====================================================\n");

}

void catac_search(void* blocks, void* blocks_root, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {

    if(blocks_root){

        if (get_original_x(blocks_root) >= x) {

            void* list_of_blocks = get_node_data(blocks_root);

            if(list_of_blocks){
                
                void* aux = get_head(list_of_blocks);
                int original_size = get_size(list_of_blocks);

                for (int i = 0; i < original_size; i++) {
                    
                    void* element = get_list_element(aux);
                    if(!element) break;

                    void* temp = get_next(aux);
                    int deletion_happened = 0;

                    if (inside(get_x(element), get_y(element), get_w(element), get_h(element), x, y, w, h)) {
                        
                        blocks_root = delete_node(blocks, blocks_root, element, compare_x, free_single_block, true);
                        deletion_happened = 1;
                    
                    }

                    if(deletion_happened) {
                        if(temp)
                            aux = temp;
                    }else{
                        if(get_next(aux))
                            aux = get_next(aux);
                    }
                }
            }
        }

        if (get_left(blocks_root)) {
            if (get_max_x(get_left(blocks_root)) >= x && get_min_x(get_left(blocks_root)) <= x + w) {
                catac_search(blocks, get_left(blocks_root), x, y, w, h, txt_results, list_of_modifications);
            }
        }

        if (get_right(blocks_root)) {
            if (get_max_x(get_right(blocks_root)) >= x && get_min_x(get_right(blocks_root)) <= x + w) {
                catac_search(blocks, get_right(blocks_root), x, y, w, h, txt_results, list_of_modifications);
            }
        }

    }
}

void rv(void* connections, double x, double y, double w, double h, double f, FILE* txt_results, void* list_of_modifications) {
    
    fprintf(txt_results, "rv(%.2lf, %.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h, f);

    char modification[1000];

    sprintf(modification, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\"\n style=\"fill:white;stroke:black;fill-opacity:0;stroke-opacity:1;stroke-width:7\" stroke-dasharray=\"4 1\"/>\n", x,y,w,h); 

    char* command = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(command, modification);
    insert_list(list_of_modifications, command);

    void* list_of_edges = extract_all_edges_inside_rectangle(connections, x, y, w, h);

    void* packaging = kruskal(list_of_edges);

    for(void* mst = get_head(packaging); mst; mst = get_next(mst)) {

        void* mst_data = get_list_element(mst);

        void** array_of_edges = list_to_array(get_package_list_of_edges(mst_data));

        rv_function_aux(array_of_edges, get_size(get_package_list_of_edges(mst_data)), get_package_root(mst_data), 1, f);

        fprintf(txt_results, "ROOT = %s\n\n", vertex_data_get_id(get_package_root(mst_data)));

        char line[1000] = "";

        for(void* edge_aux = get_head(get_package_list_of_edges(mst_data)); edge_aux; edge_aux = get_next(edge_aux)) {

            void* edge_element = get_list_element(edge_aux);

            if(get_size(get_package_list_of_edges(mst_data)) == 1) {

                fprintf(txt_results,
                    "EDGE = [%s ----> %s]:\nName = %s\nLength = %.2lf\nAverage Speed = %.2lf\nLeft side square ZIP = %s\nRight side ZIP = %s\n\n",
                    vertex_data_get_id(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_id(vertex_get_data(edge_get_to(edge_element))), 
                    edge_data_get_name(edge_get_data(edge_element)), edge_data_get_length(edge_get_data(edge_element)), edge_data_get_average_speed(edge_get_data(edge_element)),
                    edge_data_get_left_side_square(edge_get_data(edge_element)), edge_data_get_right_side_square(edge_get_data(edge_element))   
                );

            } else {

                if(edge_get_from(edge_element) != edge_get_to(edge_element)) {

                    sprintf(line, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"yellow\" stroke-width=\"5\" \" />\n", vertex_data_get_x(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_y(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_x(vertex_get_data(edge_get_to(edge_element))), vertex_data_get_y(vertex_get_data(edge_get_to(edge_element)))); 

                    char* command = calloc(strlen(line) + 5, sizeof(char));
                    strcpy(command, line);
                    insert_list(list_of_modifications, command);

                    fprintf(txt_results,
                    "EDGE = [%s ----> %s]:\nName = %s\nLength = %.2lf\nAverage Speed = %.2lf\nLeft side square ZIP = %s\nRight side ZIP = %s\n\n",
                    vertex_data_get_id(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_id(vertex_get_data(edge_get_to(edge_element))), 
                    edge_data_get_name(edge_get_data(edge_element)), edge_data_get_length(edge_get_data(edge_element)), edge_data_get_average_speed(edge_get_data(edge_element)),
                    edge_data_get_left_side_square(edge_get_data(edge_element)), edge_data_get_right_side_square(edge_get_data(edge_element))   
                    );

                }

            }

        }

        char modification_root[1000] = "";

        sprintf(modification_root, "<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"8\" stroke=\"blue\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", vertex_data_get_x(get_package_root(mst_data)), vertex_data_get_y(get_package_root(mst_data))); 

        char* command_root = calloc(strlen(modification_root) + 5, sizeof(char));
        strcpy(command_root, modification_root);
        insert_list(list_of_modifications, command_root);

        free_list(array_of_edges, false, free);

    }

    free_list(list_of_edges, false, free);

    free_list(packaging, true, free_package);

    fprintf(txt_results, "====================================================\n");

}

void cx(void* connections, double limiar, FILE* txt_results, void* list_of_modifications) {

    fprintf(txt_results, "cx(%.2lf):\n\n", limiar);

    char svg_colors[146][50] = {"blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse", "chocolate", "coral", "cornflowerblue", "cornsilk", "crimson", "cyan", "darkblue", "darkcyan", "darkgoldenrod", "darkgray", "darkgreen", "darkgrey", "darkkhaki", "darkmagenta", "darkolivegreen", "darkorange", "darkorchid", "darkred", "darksalmon", "darkseagreen", "darkslateblue", "darkslategray", "darkslategrey", "darkturquoise", "darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue", "firebrick", "floralwhite", "forestgreen", "fuchsia", "gainsboro", "ghostwhite", "gold", "goldenrod", "gray", "grey", "green", "greenyellow", "honeydew", "hotpink", "indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen", "lemonchiffon", "lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen", "lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow", "lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", "mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose", "moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange", "orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred", "papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red", "rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise", "violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen"};

    void* list_of_edges = extract_all_edges_cx(connections, limiar, list_of_modifications);

    void* packaging = kruskal(list_of_edges);

    int region_count = 0;

    int color_count = 0;

    for(void* mst = get_head(packaging); mst; mst = get_next(mst)) {

        void* mst_data = get_list_element(mst);

        void* vertexes = extract_all_activated_vertexes_from_list(get_package_list_of_edges(mst_data));

        if(get_size(vertexes)) {

            fprintf(txt_results, "Region %d vertexes:\n\n", region_count + 1);
            
            for(void* vertex_runner = get_head(vertexes); vertex_runner; vertex_runner = get_next(vertex_runner)) {

                fprintf(txt_results, "Vertex %s (%.2lf, %.2lf)\n", vertex_data_get_id(get_list_element(vertex_runner)), vertex_data_get_x(get_list_element(vertex_runner)), vertex_data_get_y(get_list_element(vertex_runner)));

                char modification_root[1000] = "";

                sprintf(modification_root, "<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"8\" ry=\"10\"\nstyle=\"fill:%s;stroke:black;stroke-width:0.01\" />\n", vertex_data_get_x(get_list_element(vertex_runner)), vertex_data_get_y(get_list_element(vertex_runner)), svg_colors[color_count]); 

                char* command_root = calloc(strlen(modification_root) + 5, sizeof(char));
                strcpy(command_root, modification_root);
                insert_list(list_of_modifications, command_root);


            }

            fprintf(txt_results, "\n\n");

        }

        free_list(vertexes, false, free);

        region_count++;

        color_count++;

        if(color_count > 146) color_count = 0;

    }

    free_list(list_of_edges, false, free);

    free_list(packaging, true, free_package);

    fprintf(txt_results, "====================================================\n");

}

void route(void* connections, void* blocks_hash, char* cep, char face, int num, char* cmc, char* cmr, void* departure, FILE* txt_results, void* list_of_modifications) {

    fprintf(txt_results, "p?(%s, %c, %d, %s, %s):\n\n", cep, face, num, cmc, cmr);

    if(!departure) {

        fprintf(txt_results, "@o is NOT set or was removed because of catac!\n");

        return;

    }

    point* starting_point = departure;
    point* end_point = find_position(connections, blocks_hash, cep, face, num, txt_results, list_of_modifications);

    char modification_root[1000] = "";

    //Shortest path
    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\"\"/>\n", starting_point->x, starting_point->y, vertex_data_get_x(vertex_get_data(starting_point->vertex)), starting_point->y, cmc); 

    char* command_root_start_short_1 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_start_short_1, modification_root);
    insert_list(list_of_modifications, command_root_start_short_1);

    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\"\"/>\n", vertex_data_get_x(vertex_get_data(starting_point->vertex)), starting_point->y, vertex_data_get_x(vertex_get_data(starting_point->vertex)), vertex_data_get_y(vertex_get_data(starting_point->vertex)), cmc); 

    char* command_root_start_short_2 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_start_short_2, modification_root);
    insert_list(list_of_modifications, command_root_start_short_2);

    void* short_path = dijkstra(connections, vertex_data_get_id(vertex_get_data(starting_point->vertex)),
    vertex_data_get_id(vertex_get_data(end_point->vertex)), shortest_path);

    for(void* runner = get_head(short_path); runner; runner = get_next(runner)) {

        void* aux_1 = get_list_element(runner);

        if(get_next(runner)) {

            void* aux_2 = get_list_element(get_next(runner));

            sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\"\"/>\n", vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_2))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_2))), cmc); 

            char* line = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(line, modification_root);
            insert_list(list_of_modifications, line);

        }

    }

    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\" \" />\n", end_point->x, end_point->y, vertex_data_get_x(vertex_get_data(end_point->vertex)), vertex_data_get_y(vertex_get_data(end_point->vertex)), cmc); 

    char* command_root_end_short_1 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_end_short_1, modification_root);
    insert_list(list_of_modifications, command_root_end_short_1);

    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\"\"/>\n", vertex_data_get_x(vertex_get_data(end_point->vertex)), end_point->y, vertex_data_get_x(vertex_get_data(end_point->vertex)), vertex_data_get_y(vertex_get_data(end_point->vertex)), cmc); 

    char* command_root_end_short_2 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_end_short_2, modification_root);
    insert_list(list_of_modifications, command_root_end_short_2);

    free_list(short_path, true, free_helper);

    //========================================================================================================================================================================//
    
    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\"\"/>\n", starting_point->x, starting_point->y, vertex_data_get_x(vertex_get_data(starting_point->vertex)), starting_point->y, cmr); 

    char* command_root_start_fast_1 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_start_fast_1, modification_root);
    insert_list(list_of_modifications, command_root_start_fast_1);

    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\"\"/>\n", vertex_data_get_x(vertex_get_data(starting_point->vertex)), starting_point->y, vertex_data_get_x(vertex_get_data(starting_point->vertex)), vertex_data_get_y(vertex_get_data(starting_point->vertex)), cmr); 

    char* command_root_start_fast_2 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_start_fast_2, modification_root);
    insert_list(list_of_modifications, command_root_start_fast_2);

    void* fast_path = dijkstra(connections, vertex_data_get_id(vertex_get_data(starting_point->vertex)),
    vertex_data_get_id(vertex_get_data(end_point->vertex)), fastest_path);

    for(void* runner = get_head(fast_path); runner; runner = get_next(runner)) {

        void* aux_1 = get_list_element(runner);

        if(get_next(runner)) {

            void* aux_2 = get_list_element(get_next(runner));

            sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\"\"/>\n", vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_2))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_2))), cmr); 

            char* line = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(line, modification_root);
            insert_list(list_of_modifications, line);

        }

    }

    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\" \" />\n", end_point->x, end_point->y, vertex_data_get_x(vertex_get_data(end_point->vertex)), vertex_data_get_y(vertex_get_data(end_point->vertex)), cmr); 

    char* command_root_end_fast_1 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_end_fast_1, modification_root);
    insert_list(list_of_modifications, command_root_end_fast_1);

    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\"\"/>\n", vertex_data_get_x(vertex_get_data(end_point->vertex)), end_point->y, vertex_data_get_x(vertex_get_data(end_point->vertex)), vertex_data_get_y(vertex_get_data(end_point->vertex)), cmr); 

    char* command_root_end_fast_2 = calloc(strlen(modification_root) + 5, sizeof(char));
    strcpy(command_root_end_fast_2, modification_root);
    insert_list(list_of_modifications, command_root_end_fast_2);

    free_list(fast_path, true, free_helper);

    free_point(end_point);

    fprintf(txt_results, "====================================================\n");

}