#include "svg.h"
#include "paths.h"
#include "Dynamic_list/dynamic_list.h"
#include "Hash/hash.h"
#include "AVL_Tree/AVL.h"
#include "block.h"


void recursive_print_svg(void* root, FILE* original_svg) {

    if(root) {

        void* block_list = get_node_data(root);

        for(void* aux = get_head(block_list); aux; aux = get_next(aux)) {
            void* block = get_list_element(aux);
            fprintf(original_svg, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" id=\"%s\"\n style=\"fill:%s;stroke:%s;stroke-width:%s;fill-opacity:0.5;stroke-opacity:1\" />\n", get_x(block), get_y(block), get_w(block), get_h(block), get_cep(block), get_cfill(block), get_cstroke(block), get_sw(block));
            fprintf(original_svg, "<text x=\"%.2lf\" y=\"%.2lf\">%s</text>\n", get_x(block), get_y(block), get_cep(block));
        }

        recursive_print_svg(get_left(root), original_svg);
        recursive_print_svg(get_right(root), original_svg);

    }

}