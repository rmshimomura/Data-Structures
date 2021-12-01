#include "svg.h"

#include "AVL_Tree/AVL.h"
#include "Dynamic_list/dynamic_list.h"
#include "Graph/graph.h"
#include "Hash/hash.h"
#include "block.h"
#include "paths.h"
#include "vertex.h"
#include "edge.h"
#include "viewbox.h"

void print_on_SVG(void* connections, void* blocks, void* view_box, path paths) {

    FILE* original_svg = fopen(get_path_original_SVG(paths), "w+");
    setvbuf(original_svg, 0, _IONBF, 0);

    void* blocks_root = get_root(blocks);

    fprintf(original_svg, "<!-- Rodrigo Mimura Shimomura -->\n <svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"%.2lf %.2lf %.2lf %.2lf\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n", get_smallest_x(view_box) - 100, get_smallest_y(view_box) - 100, get_biggest_x(view_box) + 200, get_biggest_y(view_box) + 200);

    recursive_print_svg(blocks_root, original_svg);

    print_graph(connections, original_svg);

    fprintf(original_svg, "</svg>");

    fclose(original_svg);

}

void recursive_print_svg(void* root, FILE* original_svg) {

    if(root) {

        void* block_list = get_node_data(root);

        for(void* aux = get_head(block_list); aux; aux = get_next(aux)) {
            void* block = get_list_element(aux);
            fprintf(original_svg, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" id=\"%s\"\n style=\"fill:%s;stroke:%s;stroke-width:%s;fill-opacity:0.5;stroke-opacity:1\" />\n", get_x(block), get_y(block), get_w(block), get_h(block), get_cep(block), get_cfill(block), get_cstroke(block), get_sw(block));
            fprintf(original_svg, "<text x=\"%.2lf\" y=\"%.2lf\">%s</text>\n", get_x(block), get_y(block) + 10, get_cep(block));
        }

        recursive_print_svg(get_left(root), original_svg);
        recursive_print_svg(get_right(root), original_svg);

    }

}

void print_graph(void* connections, FILE* original_svg) {

    if(connections) {

        for(int i = 0; i < graph_get_size(connections); i++) {

            void* current_vertex = return_vertex_address_by_index(connections, i);

            void* current_vertex_data = vertex_get_data(current_vertex);
            
            fprintf(original_svg, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"2\" id=\"%s\" stroke=\"black\" stroke-width=\"1\" fill=\"black\" fill-opacity = \"0.5\" />\n", vertex_data_get_x(current_vertex_data), vertex_data_get_y(current_vertex_data), vertex_data_get_id(current_vertex_data));

            if(vertex_get_edges(current_vertex)) {

                for(void* edge_runner = get_head(vertex_get_edges(current_vertex)); edge_runner; edge_runner = get_next(edge_runner)) {

                    void* edge = get_list_element(edge_runner);

                    if(edge_get_from(edge) != edge_get_to(edge)) {

                        double x1 = vertex_data_get_x(vertex_get_data(edge_get_from(edge)));
                        double y1 = vertex_data_get_y(vertex_get_data(edge_get_from(edge)));
                        double x2 = vertex_data_get_x(vertex_get_data(edge_get_to(edge)));
                        double y2 = vertex_data_get_y(vertex_get_data(edge_get_to(edge)));

                        double angle = atan2(y2 - y1, x2 - x1);
                        double x3 = x2 - 6 * cos(angle - M_PI / 6);
                        double y3 = y2 - 6 * sin(angle - M_PI / 6);
                        double x4 = x2 - 6 * cos(angle + M_PI / 6);
                        double y4 = y2 - 6 * sin(angle + M_PI / 6);
                        fprintf(original_svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"0.5\" />\n", x1, y1, x2, y2);
                        fprintf(original_svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\".5\" />\n", x2, y2, x3, y3);
                        fprintf(original_svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\".5\" />\n", x2, y2, x4, y4);

                    }

                }

            }

        }


    }

}
