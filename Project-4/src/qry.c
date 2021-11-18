#include "qry.h"
#include "AVL_Tree/AVL.h"
#include "block.h"
#include "Graph/graph.h"
#include "vertex.h"
#include "Dynamic_list/dynamic_list.h"

void catac_search(void* blocks, void* blocks_root, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications);
void free_list_catac(void* sequence, FILE* txt_results, void (*free_node)(void*));

int inside(double x1, double y1, double p1Width, double p1Height, double x2, double y2, double p2Width, double p2Height) {
    if ((x1 >= x2 && x1 <= x2 + p2Width && y1 >= y2 && y1 <= y2 + p2Height && x1 + p1Width <= x2 + p2Width && y1 + p1Height <= y2 + p2Height)) return 1;
    //Fix the search on the p2 and vary on p1
    return 0;
}


void catac(void* connections, void* blocks, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {
    
    fprintf(txt_results, "catac(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    char modification[1000];

    sprintf(modification, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\"\n style=\"fill:#AB37C8;stroke:#AA0044;fill-opacity:0.5;stroke-opacity:0.5\" />\n", x,y,w,h); 

    char* command = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(command, modification);
    insert_list(list_of_modifications, command);

    catac_search(blocks, blocks_root, x, y, w, h, txt_results, list_of_modifications);

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