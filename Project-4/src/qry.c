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
#include "kosaraju.h"

typedef struct point {

    double x, y;
    int num;
    char* cep;
    char face;
    void* vertex;
    int valid;

} point;

void catac_search(void* blocks, void* blocks_root, void* blocks_hash, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);
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

bool find_spacial_position(void* blocks_hash, point* aux, char* cep, char face, int num) {

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

        return true;

    } else {

        return false;

    }

}

void* find_position(void* connections, void* blocks_hash, char* cep, char face, int num, FILE* txt_results, void* list_of_modifications) {

    point* aux = calloc(1, sizeof(point));
    aux->cep = calloc(strlen(cep) + 1, sizeof(char));
    strcpy(aux->cep, cep);
    aux->face = face;
    aux->num = num;
    aux->valid = true;

    if(!find_spacial_position(blocks_hash, aux, cep, face, num)) {
        free_point(aux);
        return NULL;
    }

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

void catac(void* connections, void* blocks, void* blocks_hash, double x, double y, double w, double h, void* point_location, FILE* txt_results, void* list_of_modifications) {
    
    fprintf(txt_results, "catac(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    char modification[1000];

    sprintf(modification, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\"\n style=\"fill:#AB37C8;stroke:#AA0044;fill-opacity:0.5;stroke-opacity:0.5\" />\n", x,y,w,h); 

    char* command = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(command, modification);
    insert_list(list_of_modifications, command);

    catac_search(blocks, blocks_root, blocks_hash, x, y, w, h, txt_results, list_of_modifications);

    fprintf(txt_results, "\n");

    if(point_location) { // @o? exists, so we need to check if this specific point was inside catac's rectangle, if so, we set him NULL

        point* aux = point_location;

        if(inside(aux->x, aux->y, 0, 0, x, y, w, h)) {

            fprintf(txt_results, "@o?(%s, %c, %d) is inside catac's rectangle!, removing...\n", aux->cep, aux->face, aux->num);
            aux->valid = false;
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

void catac_search(void* blocks, void* blocks_root, void* blocks_hash, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {

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

                        fprintf(txt_results, "BLOCK WITH CEP = %s REMOVED.\n", get_cep(element));
                        hash_table_remove_key(blocks_hash, get_cep(element), false, compare_cep, false);
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
                catac_search(blocks, get_left(blocks_root), blocks_hash, x, y, w, h, txt_results, list_of_modifications);
            }
        }

        if (get_right(blocks_root)) {
            if (get_max_x(get_right(blocks_root)) >= x && get_min_x(get_right(blocks_root)) <= x + w) {
                catac_search(blocks, get_right(blocks_root), blocks_hash, x, y, w, h, txt_results, list_of_modifications);
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
                    "EDGE = [%s ----> %s]:\nName = %s\nLength = %.2lf\nAverage Speed = %.2lf\nLeft side square ZIP = %s\nRight side square ZIP = %s\n\n",
                    vertex_data_get_id(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_id(vertex_get_data(edge_get_to(edge_element))), 
                    edge_data_get_name(edge_get_data(edge_element)), edge_data_get_length(edge_get_data(edge_element)), edge_data_get_average_speed(edge_get_data(edge_element)),
                    edge_data_get_left_side_square(edge_get_data(edge_element)), edge_data_get_right_side_square(edge_get_data(edge_element))   
                );

            } else {

                if(edge_get_from(edge_element) != edge_get_to(edge_element)) {

                    sprintf(line, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"yellow\" stroke-width=\"5\"/>\n", vertex_data_get_x(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_y(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_x(vertex_get_data(edge_get_to(edge_element))), vertex_data_get_y(vertex_get_data(edge_get_to(edge_element)))); 

                    char* command = calloc(strlen(line) + 5, sizeof(char));
                    strcpy(command, line);
                    insert_list(list_of_modifications, command);

                    fprintf(txt_results,
                    "EDGE = [%s ----> %s]:\nName = %s\nLength = %.2lf\nAverage Speed = %.2lf\nLeft side square ZIP = %s\nRight side square ZIP = %s\n\n",
                    vertex_data_get_id(vertex_get_data(edge_get_from(edge_element))), vertex_data_get_id(vertex_get_data(edge_get_to(edge_element))), 
                    edge_data_get_name(edge_get_data(edge_element)), edge_data_get_length(edge_get_data(edge_element)), edge_data_get_average_speed(edge_get_data(edge_element)),
                    edge_data_get_left_side_square(edge_get_data(edge_element)), edge_data_get_right_side_square(edge_get_data(edge_element))   
                    );

                }

            }

        }

        char modification_root[1000] = "";

        sprintf(modification_root, "<rect x=\"%.2lf\" y=\"%.2lf\" width=\"15\" height=\"15\"\n style=\"fill:red;stroke:red;fill-opacity:1;stroke-opacity:1\"/>\n", vertex_data_get_x(get_package_root(mst_data)) - 7.5, vertex_data_get_y(get_package_root(mst_data)) - 7.5); 

        char* command_root = calloc(strlen(modification_root) + 5, sizeof(char));
        strcpy(command_root, modification_root);
        insert_list(list_of_modifications, command_root);

        free_list(array_of_edges, false, free);

    }

    free_list(list_of_edges, false, free);

    free_list(packaging, true, free_package);

    fprintf(txt_results, "====================================================\n");

}

void cx(void* connections, double threshold, FILE* txt_results, void* list_of_modifications) {

    fprintf(txt_results, "cx(%.2lf):\n\n", threshold);

    char svg_colors[146][50] = {"blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse", "chocolate", "coral", "cornflowerblue", "cornsilk", "crimson", "cyan", "darkblue", "darkcyan", "darkgoldenrod", "darkgray", "darkgreen", "darkgrey", "darkkhaki", "darkmagenta", "darkolivegreen", "darkorange", "darkorchid", "darkred", "darksalmon", "darkseagreen", "darkslateblue", "darkslategray", "darkslategrey", "darkturquoise", "darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue", "firebrick", "floralwhite", "forestgreen", "fuchsia", "gainsboro", "ghostwhite", "gold", "goldenrod", "gray", "grey", "green", "greenyellow", "honeydew", "hotpink", "indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen", "lemonchiffon", "lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen", "lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow", "lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", "mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose", "moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange", "orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred", "papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red", "rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise", "violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen"};

    int region_count = 0;

    int color_count = 0;

    void** kosaraju_return = kosaraju(connections, threshold, list_of_modifications);

    void* regions = kosaraju_return[0];

    for(void* region_runner = get_head(regions); region_runner; region_runner = get_next(region_runner)) {

        void* region = get_list_element(region_runner);

        fprintf(txt_results, "Region %d vertexes:\n\n", region_count + 1);

        for(void* vertex_runner = get_head(region); vertex_runner; vertex_runner = get_next(vertex_runner)) {

            fprintf(txt_results, "Vertex %s (%.2lf, %.2lf)\n", vertex_data_get_id(vertex_get_data(get_list_element(vertex_runner))), vertex_data_get_x(vertex_get_data(get_list_element(vertex_runner))), vertex_data_get_y(vertex_get_data(get_list_element(vertex_runner))));

            char modification_root[1000] = "";

            sprintf(modification_root, "<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"8\" ry=\"10\"\nstyle=\"fill:%s;stroke:black;stroke-width:0.01\" />\n", vertex_data_get_x(vertex_get_data(get_list_element(vertex_runner))), vertex_data_get_y(vertex_get_data(get_list_element(vertex_runner))), svg_colors[color_count]); 

            char* command_root = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(command_root, modification_root);
            insert_list(list_of_modifications, command_root);

        }

        region_count++;
        color_count++;
        if(color_count == 146) color_count = 0;

    }

    for(void* runner = get_head(regions); runner; runner = get_next(runner)) { // List of lists of nodes with vertexes

        void* region = get_list_element(runner); // List of nodes with vertexes

        free_list(region, true, free_vertex);

    }

    free_list(regions, false, free);

    free_graph_vertexes(kosaraju_return[1]);

    free(kosaraju_return);

    fprintf(txt_results, "====================================================\n");

}

void route(void* connections, void* blocks_hash, char* cep, char face, int num, char* cmc, char* cmr, void* departure, FILE* txt_results, void* list_of_modifications) {

    fprintf(txt_results, "p?(%s, %c, %d, %s, %s):\n\n", cep, face, num, cmc, cmr);

    char function_calling[1000];
    sprintf(function_calling, "p?(%s, %c, %d, %s, %s)", cep, face, num, cmc, cmr);

    char* function_calling_F = calloc(strlen(function_calling) + 10, sizeof(char));
    strcpy(function_calling_F, function_calling);
    strcat(function_calling_F, "F");

    char* function_calling_S = calloc(strlen(function_calling) + 10, sizeof(char));
    strcpy(function_calling_S, function_calling);
    strcat(function_calling_S, "S");


    point* starting_point = departure;
    point* end_point = find_position(connections, blocks_hash, cep, face, num, txt_results, list_of_modifications);

    //Shortest path

    char modification_root[1000] = "";

    if(starting_point->valid && end_point) { // Check if the point wasn't inside a catac rectangle

        void* short_path = dijkstra(connections, vertex_data_get_id(vertex_get_data(starting_point->vertex)),
        vertex_data_get_id(vertex_get_data(end_point->vertex)), shortest_path);

        if(!short_path) { // If the point is still valid, but there's no way to go to it

            fprintf(txt_results, "There's no shortest path to this address!\n");
            char problem[1000] = "";

            sprintf(problem, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"8\"\" stroke-dasharray =\"4 1\" />\n", starting_point->x, starting_point->y, end_point->x, end_point->y);

            char* command_not_found = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(command_not_found, modification_root);
            insert_list(list_of_modifications, command_not_found);


        } else {

            sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\"/>\n", vertex_data_get_x(vertex_get_data(starting_point->vertex)), starting_point->y, vertex_data_get_x(vertex_get_data(starting_point->vertex)), vertex_data_get_y(vertex_get_data(starting_point->vertex)), cmc); 

            char* command_root_start_short = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(command_root_start_short, modification_root);
            insert_list(list_of_modifications, command_root_start_short);

            char* animation_motion_shortest_path = calloc(strlen("<path d=\"") + 2, sizeof(char));
            strcpy(animation_motion_shortest_path, "<path d=\"");

            for(void* runner = get_head(short_path); runner; runner = get_next(runner)) {

                void* aux_1 = get_list_element(runner);

                if(get_next(runner)) {

                    void* aux_2 = get_list_element(get_next(runner));

                    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\"/>\n", vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_2))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_2))), cmc); 

                    animation_motion_shortest_path = update_path(animation_motion_shortest_path, vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_2))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_2))));

                    char* line = calloc(strlen(modification_root) + 5, sizeof(char));
                    strcpy(line, modification_root);
                    insert_list(list_of_modifications, line);

                }

            }
            sprintf(modification_root, "\" id = \"%s\"/> \n", function_calling_S);
            animation_motion_shortest_path = realloc(animation_motion_shortest_path, strlen(animation_motion_shortest_path) + strlen(modification_root) + 5);
            strcat(animation_motion_shortest_path, modification_root);

            insert_list(list_of_modifications, animation_motion_shortest_path);

            sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\"/>\n", vertex_data_get_x(vertex_get_data(end_point->vertex)), end_point->y, vertex_data_get_x(vertex_get_data(end_point->vertex)), vertex_data_get_y(vertex_get_data(end_point->vertex)), cmc); 

            char* command_root_end_short = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(command_root_end_short, modification_root);
            insert_list(list_of_modifications, command_root_end_short);

            sprintf(modification_root, "<circle r=\"15\" fill=\"black\">\n\t<animateMotion dur=\"12s\" repeatCount=\"indefinite\">\n\t\t<mpath xlink:href=\"#%s\"/>\n\t</animateMotion>\n</circle>\n", function_calling_S);

            char* motion = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(motion, modification_root);
            insert_list(list_of_modifications, motion);

            free_list(short_path, true, free_helper);

        }

    } else if (!starting_point->valid) { 

        fprintf(txt_results, "@o? point was removed by a catac!\n");

        char problem[1000] = "";

        sprintf(problem, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"8\" stroke-dasharray =\"4 1\" />\n", starting_point->x, starting_point->y, end_point->x, end_point->y);

        char* command_not_found = calloc(strlen(modification_root) + 5, sizeof(char));
        strcpy(command_not_found, modification_root);
        insert_list(list_of_modifications, command_not_found);

    } else if (!end_point) {

        fprintf(txt_results, "Destination is not available for shortest path.\n");

    }

    //========================================================================================================================================================================//

    // Fastest path 

    if(starting_point->valid && end_point) { // Check if the point wasn't inside a catac rectangle

        void* fast_path = dijkstra(connections, vertex_data_get_id(vertex_get_data(starting_point->vertex)),
        vertex_data_get_id(vertex_get_data(end_point->vertex)), fastest_path);

        if(!fast_path) { // If the point is still valid, but there's no way to go to it

            fprintf(txt_results, "There's no fastest path to this address!\n");
            char problem[1000] = "";

            sprintf(problem, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"8\" stroke-dasharray =\"4 1\" />\n", starting_point->x, starting_point->y, end_point->x, end_point->y);

            char* command_not_found = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(command_not_found, modification_root);
            insert_list(list_of_modifications, command_not_found);

        } else {

            sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\"/>\n", vertex_data_get_x(vertex_get_data(starting_point->vertex)), starting_point->y, vertex_data_get_x(vertex_get_data(starting_point->vertex)), vertex_data_get_y(vertex_get_data(starting_point->vertex)), cmr); 

            char* command_root_start_fast = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(command_root_start_fast, modification_root);
            insert_list(list_of_modifications, command_root_start_fast);

            char* animation_motion_fastest_path = calloc(strlen("<path d=\"") + 1, sizeof(char));
            strcpy(animation_motion_fastest_path, "<path d=\"");

            for(void* runner = get_head(fast_path); runner; runner = get_next(runner)) {

                void* aux_1 = get_list_element(runner);

                if(get_next(runner)) {

                    void* aux_2 = get_list_element(get_next(runner));

                    sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\"/>\n", vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_2))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_2))), cmr); 

                    animation_motion_fastest_path = update_path(animation_motion_fastest_path, vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_1))), vertex_data_get_x(vertex_get_data(get_dijkstra_vertex(aux_2))), vertex_data_get_y(vertex_get_data(get_dijkstra_vertex(aux_2))));
        
                    char* line = calloc(strlen(modification_root) + 5, sizeof(char));
                    strcpy(line, modification_root);
                    insert_list(list_of_modifications, line);

                }

            }
            sprintf(modification_root, "\" id = \"%s\"/> \n", function_calling_F);
            animation_motion_fastest_path = realloc(animation_motion_fastest_path, strlen(animation_motion_fastest_path) + strlen(modification_root) + 1);
            strcat(animation_motion_fastest_path, modification_root);

            insert_list(list_of_modifications, animation_motion_fastest_path);

            sprintf(modification_root, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"5\"/>\n", vertex_data_get_x(vertex_get_data(end_point->vertex)), end_point->y, vertex_data_get_x(vertex_get_data(end_point->vertex)), vertex_data_get_y(vertex_get_data(end_point->vertex)), cmr); 

            char* command_root_end_fast = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(command_root_end_fast, modification_root);
            insert_list(list_of_modifications, command_root_end_fast);

            sprintf(modification_root, "<circle r=\"15\" fill=\"black\">\n\t<animateMotion dur=\"12s\" repeatCount=\"indefinite\">\n\t\t<mpath xlink:href=\"#%s\"/>\n\t</animateMotion>\n</circle>\n", function_calling_F);

            char* motion = calloc(strlen(modification_root) + 5, sizeof(char));
            strcpy(motion, modification_root);
            insert_list(list_of_modifications, motion);

            free_list(fast_path, true, free_helper);

        }

    } else if (!starting_point->valid) {

        fprintf(txt_results, "@o? point was removed by a catac!\n");

        char problem[1000] = "";

        sprintf(problem, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"8\" stroke-dasharray =\"4 1\" />\n", starting_point->x, starting_point->y, end_point->x, end_point->y);

        char* command_not_found = calloc(strlen(modification_root) + 5, sizeof(char));
        strcpy(command_not_found, modification_root);
        insert_list(list_of_modifications, command_not_found);

    } else if (!end_point) {

        fprintf(txt_results, "Destination not available for fastest path.\n");

    }

    free_point(end_point);

    free(function_calling_S);
    free(function_calling_F);

    fprintf(txt_results, "====================================================\n");

}

char* update_path(char* path, double x1, double y1, double x2, double y2) {

    char part[1024] = "";

    sprintf(part, " M%.2lf,%.2lf L%.2lf,%.2lf ", x1, y1, x2, y2);
    
    path = realloc(path, strlen(path) + strlen(part) + 1);

    strcat(path, part);

    return path;

}