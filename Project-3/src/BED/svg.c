#include "svg.h"
#include "paths.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "AVL_Tree/AVL.h"
#include "block.h"


void print_on_SVG(tree blocks, path paths) {

    FILE* original_svg = fopen(get_path_original_SVG(paths), "w+");
    setvbuf(original_svg, 0, _IONBF, 0);

    void* blocks_root = get_root(blocks);

    fprintf(original_svg, "<!-- Rodrigo Mimura Shimomura -->\n <svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");

    recursive_print_svg(blocks_root, original_svg);

    fclose(original_svg);

}


void recursive_print_svg(void* root, FILE* original_svg) {

    if(root) {

        void* block_list = get_node_data(root);

        for(void* aux = get_head(block_list); aux; aux = get_next(aux)) {
            void* block = get_list_element(aux);
            fprintf(original_svg, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" id=\"%s\"\n style=\"fill:%s;stroke:%s;stroke-width:%.2lf;fill-opacity:0.5;stroke-opacity:1\" />\n", get_x(block), get_y(block), get_w(block), get_h(block), get_cep(block), get_cstroke(block), get_cfill(block), get_sw(block));
        }

        recursive_print_svg(get_left(root), original_svg);
        recursive_print_svg(get_right(root), original_svg);

    }

}