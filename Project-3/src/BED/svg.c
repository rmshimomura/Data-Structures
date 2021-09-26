#include "svg.h"
#include "paths.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "AVL_Tree/AVL.h"
#include "block.h"
#include "location.h"

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

void position_cases_loc_who(hash blocks_hash, void* location_data, FILE* modified_SVG, char character_to_print){

    void* square = find_item(hash_table_get_register_list(blocks_hash, location_get_cep(location_data)), location_get_cep(location_data), compare_cep);

    /*  

        # if ended
        * if not available
        $ if available

    */

    switch(location_get_face(location_data)) {

        case 'N':

            fprintf(modified_SVG, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + location_get_num(location_data), get_y(square) + get_h(square) - 2, character_to_print);

            break;

        case 'S':

            fprintf(modified_SVG, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + location_get_num(location_data), get_y(square) + 2, character_to_print);

            break;

        case 'L':

            fprintf(modified_SVG, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + 2, get_y(square)  + location_get_num(location_data), character_to_print);

            break;

        case 'O':

            fprintf(modified_SVG, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + get_w(location_data) - 2, get_y(square) + location_get_num(location_data), character_to_print);

            break;
    }

}