#include "svg.h"
#include "paths.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "AVL_Tree/AVL.h"
#include "block.h"
#include "location.h"
#include "person.h"

void print_on_SVG(tree blocks, path paths) {

    FILE* original_svg = fopen(get_path_original_SVG(paths), "w+");
    setvbuf(original_svg, 0, _IONBF, 0);

    void* blocks_root = get_root(blocks);

    fprintf(original_svg, "<!-- Rodrigo Mimura Shimomura -->\n <svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");

    recursive_print_svg(blocks_root, original_svg);

    fprintf(original_svg, "</svg>");

    fclose(original_svg);

}

void recursive_print_svg(void* root, FILE* original_svg) {

    if(root) {

        void* block_list = get_node_data(root);

        for(void* aux = get_head(block_list); aux; aux = get_next(aux)) {
            void* block = get_list_element(aux);
            fprintf(original_svg, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" id=\"%s\"\n style=\"fill:%s;stroke:%s;stroke-width:%.2lf;fill-opacity:0.5;stroke-opacity:1\" />\n", get_x(block), get_y(block), get_w(block), get_h(block), get_cep(block), get_cstroke(block), get_cfill(block), get_sw(block));
            fprintf(original_svg, "<text x=\"%.2lf\" y=\"%.2lf\">%s</text>", get_x(block), get_y(block), get_cep(block));
        }

        recursive_print_svg(get_left(root), original_svg);
        recursive_print_svg(get_right(root), original_svg);

    }

}

void position_cases_character(hash blocks_hash, void* location_data, void* list_of_modifications, char character_to_print){

    void* square = find_item(hash_table_get_register_list(blocks_hash, location_get_cep(location_data)), location_get_cep(location_data), compare_cep);
    char modification[1000];

    switch(location_get_face(location_data)) {

        case 'N':

            sprintf(modification, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + location_get_num(location_data), get_y(square) + get_h(square) - 2, character_to_print);
            
            break;

        case 'S':

            sprintf(modification, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + location_get_num(location_data), get_y(square) + 2, character_to_print);
            
            break;

        case 'L':

            sprintf(modification, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + 2, get_y(square)  + location_get_num(location_data), character_to_print);

            break;

        case 'O':

            sprintf(modification, "<text x=\"%.2lf\" y=\"%.2lf\">%c</text>", get_x(square) + get_w(square) - 2, get_y(square) + location_get_num(location_data), character_to_print);

            break;
    }

    char* command = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(command, modification);
    insert_list(list_of_modifications, command);

}

void position_cases_line(void* old_square, void* new_square, char face, int num, void* person_info, void* list_of_modifications) {

    // (x1,y1) position is going to be the old square
    // (x2,y2) position is going to be the new square
    char mod1[1000], mod2[1000], mod3[1000];
    
    switch(get_person_place_face(person_info)) {

        case 'N':

            switch(face) {
                
                case 'N':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square), get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    break;

                case 'S':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square), get_x(new_square) + (double)num, get_y(new_square) + 2);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square));
                    break;

                case 'L':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square), get_x(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square), get_y(new_square) + (double)num);
                    break;

                case 'O':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square), get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square) + get_h(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    break;
            }

            break;

        case 'S':

            switch(face) {
                
                case 'N':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square), get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    break;

                case 'S':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square), get_x(new_square) + (double)num, get_y(new_square));
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square));
                    break;

                case 'L':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square), get_x(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square), get_y(new_square) + (double)num);
                    break;

                case 'O':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square), get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_person_place_num(person_info), get_y(old_square));
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    break;
            }

            break;

        case 'L':

            switch(face) {
                
                case 'N':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square), get_y(old_square) + (double)num, get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    break;

                case 'S':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square), get_y(old_square) + (double)num, get_x(new_square) + (double)num, get_y(new_square));
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square));
                    break;

                case 'L':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square), get_y(old_square) + (double)num, get_x(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square), get_y(new_square) + (double)num);
                    break;

                case 'O':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square), get_y(old_square) + (double)num, get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    break;
            }

            break;

        case 'O':

            switch(face) {
                
                case 'N':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num, get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square) + get_h(new_square));
                    break;

                case 'S':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num, get_x(new_square) + (double)num, get_y(new_square));
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + (double)num, get_y(new_square));
                    break;

                case 'L':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num, get_x(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square), get_y(new_square) + (double)num);
                    break;

                case 'O':
                    sprintf(mod1, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num, get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    sprintf(mod2, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" fill-opacity = \"1\" />\n", get_x(old_square) + get_w(old_square), get_y(old_square) + (double)num);
                    sprintf(mod3, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" fill-opacity = \"1\" />\n", get_x(new_square) + get_w(new_square), get_y(new_square) + (double)num);
                    break;
            }

            break;


    }

    char* command1 = calloc(strlen(mod1) + 5, sizeof(char));
    strcpy(command1, mod1);
    char* command2 = calloc(strlen(mod2) + 5, sizeof(char));
    strcpy(command2, mod2);
    char* command3 = calloc(strlen(mod3) + 5, sizeof(char));
    strcpy(command3, mod3);
    
    insert_list(list_of_modifications, command1);
    insert_list(list_of_modifications, command2);
    insert_list(list_of_modifications, command3);


}

void insert_modifications(void* person_data, void* square, char* cpf, void* list_of_modifications){

    char complete_info[200] = "", line[200] = "";
    char* full_addr = get_person_full_address(person_data);

    sprintf(complete_info, "<text x=\"%.2lf\" y=\"-%.2lf\">%s %s - %s %s</text>\n", get_x(square) + 3, 5* get_size(list_of_modifications) + 2.00,get_person_name(person_data), get_person_surname(person_data), cpf, full_addr);

    switch (get_person_place_face(person_data)){
        
        case 'N':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square) + get_person_place_num(person_data), get_y(square) + get_h(square), get_x(square) + get_person_place_num(person_data), 5* get_size(list_of_modifications) + 2.00);
            break;

        case 'S':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square) + get_person_place_num(person_data), get_y(square), get_x(square) + get_person_place_num(person_data), 5* get_size(list_of_modifications) + 2.00);
            break;

        case 'L':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square), get_y(square) + get_person_place_num(person_data), get_x(square), 5* get_size(list_of_modifications) + 2.00);
            break;

        case 'O':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square) + get_w(square), get_y(square) + get_person_place_num(person_data), get_x(square) + get_w(square), 5* get_size(list_of_modifications) + 2.00);

            break;
    }
    
    
    char* last_line = calloc(strlen(line) + 3, sizeof(char));
    strcpy(last_line, line);

    char* text = calloc(strlen(complete_info) + 3, sizeof(char));
    strcpy(text, complete_info);

    free(full_addr);

    insert_list(list_of_modifications, last_line);
    insert_list(list_of_modifications, text);

}

void insert_persons(void* block_data, void* person, char sex, void* list_of_modifications) {

    char modification[200];
    

    switch (get_person_place_face(person)){
        
        case 'N':
            sprintf(modification, "<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"3\" ry=\"6\"\nstyle=\"fill:%s;stroke:black;stroke-width:2\" />\n", get_x(block_data) + get_person_place_num(person), get_y(block_data) + get_h(block_data) - 2, sex == 'M' ? "blue" : "pink");
            break;

        case 'S':
            sprintf(modification, "<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"3\" ry=\"6\"\nstyle=\"fill:%s;stroke:black;stroke-width:2\" />\n", get_x(block_data) + get_person_place_num(person), get_y(block_data) + 2, sex == 'M' ? "blue" : "pink");
            break;

        case 'L':
            sprintf(modification, "<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"3\" ry=\"6\"\nstyle=\"fill:%s;stroke:black;stroke-width:2\" />\n", get_x(block_data) + 2, get_y(block_data) + get_person_place_num(person), sex == 'M' ? "blue" : "pink");
            break;

        case 'O':
            sprintf(modification, "<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"3\" ry=\"6\"\nstyle=\"fill:%s;stroke:black;stroke-width:2\" />\n", get_x(block_data) + get_w(block_data) - 2, get_y(block_data) + get_person_place_num(person), sex == 'M' ? "blue" : "pink");

            break;
    }

    char* command = calloc(strlen(modification) + 5, sizeof(char));

    strcpy(command, modification);

    insert_list(list_of_modifications, command);

}

void insert_location_line(void* location, void* square, void* list_of_modifications){

    char line[300];

    switch (location_get_face(location)){
        
        case 'N':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square) + location_get_num(location), get_y(square) + get_h(square), get_x(square) + location_get_num(location), 5* get_size(list_of_modifications) + 2.00);
            break;

        case 'S':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square) + location_get_num(location), get_y(square), get_x(square) + location_get_num(location), 5* get_size(list_of_modifications) + 2.00);
            break;

        case 'L':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square), get_y(square) + location_get_num(location), get_x(square), 5* get_size(list_of_modifications) + 2.00);
            break;

        case 'O':
            sprintf(line, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"-%.2lf\" style=\"stroke:red;stroke-width:2;\"/>\n", get_x(square) + get_w(square), get_y(square) + location_get_num(location), get_x(square) + get_w(square), 5* get_size(list_of_modifications) + 2.00);

            break;
    }

    char* command = calloc(strlen(line) + 5, sizeof(char));
    strcpy(command, line);

    insert_list(list_of_modifications, command);

}

void position_cases_text(hash blocks_hash, void* location_data, void* list_of_modifications, char* text_to_print){

    void* square = find_item(hash_table_get_register_list(blocks_hash, location_get_cep(location_data)), location_get_cep(location_data), compare_cep);
    char modification[1000] = "";
    switch(location_get_face(location_data)) {

        case 'N':

            sprintf(modification, "<text x=\"%.2lf\" y=\"-%.2lf\">%s</text>", get_x(square) + location_get_num(location_data), 5* get_size(list_of_modifications) + 2.00, text_to_print);
            
            break;

        case 'S':

            sprintf(modification, "<text x=\"%.2lf\" y=\"-%.2lf\">%s</text>", get_x(square) + location_get_num(location_data), 5* get_size(list_of_modifications) + 2.00, text_to_print);
            
            break;

        case 'L':

            sprintf(modification, "<text x=\"%.2lf\" y=\"-%.2lf\">%s</text>", get_x(square) + 2, 5* get_size(list_of_modifications) + 2.00, text_to_print);

            break;

        case 'O':

            sprintf(modification, "<text x=\"%.2lf\" y=\"-%.2lf\">%s</text>", get_x(square) + get_w(square) - 2, 5* get_size(list_of_modifications) + 2.00, text_to_print);

            break;
    }

    char* command = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(command, modification);
    insert_list(list_of_modifications, command);

}