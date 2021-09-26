#include "qry.h"

#include "AVL_Tree/AVL.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "block.h"
#include "location.h"
#include "paths.h"
#include "person.h"
#include "svg.h"

int inside(double x1, double y1, double p1Width, double p1Height, double x2, double y2, double p2Width, double p2Height) {
    if ((x1 >= x2 && x1 <= x2 + p2Width && y1 >= y2 && y1 <= y2 + p2Height && x1 + p1Width <= x2 + p2Width && y1 + p1Height <= y2 + p2Height)) return 1;
    //Fix the search on the p2 and vary on p1
    return 0;
}

void del(tree blocks, hash blocks_hash, hash residents, hash locations, char* cep, FILE* txt_results, void* list_of_modifications) {
    fprintf(txt_results, "del(%s):\n\n", cep);

    void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);

    if (square) {
        void** residents_list = get_residents(square);

        if (residents_list) {
            for (int i = 0; i < get_number_of_persons_living(square); i++) {
                if (residents_list[i]) {
                    print_person_info(residents_list[i], txt_results);

                    hash_table_remove_key(residents, get_cpf(residents_list[i]), free_person, compare_CPF);
                }
            }
        }

        void** locations_list = get_locations(square);

        if (locations_list) {
            for (int i = 0; i < get_number_of_locations_available(square); i++) {
                if (locations_list[i]) {
                    location_info(locations_list[i], txt_results);

                    hash_table_remove_key(locations, location_get_id(locations_list[i]), location_free, compare_id);
                }
            }
        }

    } else {
        fprintf(txt_results, "\tSorry, CEP = %s not found...\n\n", cep);
        fprintf(txt_results, "====================================================\n");
        return;
    }

    void* blocks_root = get_root(blocks);

    blocks_root = delete_node(blocks, blocks_root, square, compare_x, free_single_block);

    fprintf(txt_results, "====================================================\n");
}

void m_who(hash residents, hash blocks_hash, char* cep, FILE* txt_results) {
    
    void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);

    fprintf(txt_results, "m?(%s):\n\n", cep);

    if (square) {
        if (!get_number_of_persons_living(square)) {
            fprintf(txt_results, "\tNobody lives here on cep = %s... \n\n", cep);
            fprintf(txt_results, "====================================================\n");
            return;
        }

        for (int i = 0; i < get_number_of_persons_living(square); i++) {
            if (get_residents(square)[i]) {
                print_person_info(get_residents(square)[i], txt_results);
            }
        }

        fprintf(txt_results, "====================================================\n");

    } else {
        fprintf(txt_results, "\tSorry, CEP = %s not found...\n\n", cep);
        fprintf(txt_results, "====================================================\n");
    }
}

void dm_who(hash residents, char* cpf, FILE* txt_results, void* list_of_modifications) {
    fprintf(txt_results, "dm?(%s):\n\n", cpf);

    if (find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF)) {
        void* person_to_print = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);

        print_person_info(person_to_print, txt_results);
        fprintf(txt_results, "====================================================\n");

    } else {
        fprintf(txt_results, "\tSorry, CPF = %s not found...\n\n", cpf);
        fprintf(txt_results, "====================================================\n");
    }
}

void mud(hash residents, hash blocks_hash, char* cpf, char* cep, char face, int num, char * compl, FILE* txt_results, void* list_of_modifications) {
    //Update September, 14th. mud only makes the person buy a house, so house state = OWN

    if (hash_table_list_exist(residents, cpf)) {

        void* person_to_update = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);  //Find person on hash table of residents

        void* old_square = find_item(hash_table_get_register_list(blocks_hash, get_person_cep(person_to_update)), get_person_cep(person_to_update), compare_cep);  //Find new square where this person will live

        void* new_square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);  //Find new square where this person will live

        if (person_to_update) {  //If the person with cpf passed as argument exists, we're going to update the date

            fprintf(txt_results, "mud(%s, %s, %c, %d, %s):\n\n", cpf, cep, face, num, compl );
            fprintf(txt_results, "BEFORE::\n\n");
            print_person_info(person_to_update, txt_results);

            if (!strcmp(get_person_cep(person_to_update), cep)) {  // Check if this person stayed on the same CEP, but wasn't included on the residents list

                void** residents = get_residents(new_square);

                int included = 0;

                for (int i = 0; i < get_number_of_persons_living(new_square); i++) {

                    if (residents[i] == person_to_update) {

                        included = 1;
                        break;

                    }

                }

                if (!included) {

                    add_resident(new_square, person_to_update);

                }


            } else {  // This person moved to other CEP, now I need to remove the person from the void* vector of residents of the old block
                
                if (old_square) {

                    void** old_residents = get_residents(old_square);

                    for (int i = 0; i < get_number_of_persons_living(old_square); i++) {

                        if (old_residents[i] == person_to_update) {

                            old_residents[i] = NULL;
                            break;

                        }

                    }

                }

                add_resident(new_square, person_to_update);

            }
            position_cases_line(old_square, new_square, face, num, person_to_update, list_of_modifications);
            fprintf(txt_results, "AFTER::\n\n");
            update_person(person_to_update, cep, face, num, compl);
            set_house_state(person_to_update, 0);
            print_person_info(person_to_update, txt_results);

        }

    } else {

        fprintf(txt_results, "mud(%s, %s, %c, %d, %s):\n\n\tCouldn't find person with cpf : %s on the hash table.\n\n", cpf, cep, face, num, compl, cpf);
        
    }

    fprintf(txt_results, "====================================================\n");

}

void oloc(hash locations, hash blocks_hash, char* id, char* cep, char face, int num, char * compl, double ar, double v, FILE* txt_results) {
    void* new_location = create_location();
    set_location_properties(new_location, id, cep, face, num, compl, ar, v);
    hash_table_insert_data(locations, id, new_location);
    void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);
    add_location(square, new_location);
}

void oloc_who(tree blocks, hash block_hash, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {
    
    char modification[1000];

    void* blocks_root = get_root(blocks);

    fprintf(txt_results, "oloc?(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    sprintf(modification, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n style=\"fill:black;stroke:black;stroke-width:2;fill-opacity:0;stroke-opacity:1;stroke-dasharray:5\" />\n", x, y, w, h);

    char* mod1 = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(mod1, modification);
    insert_list(list_of_modifications, mod1);

    oloc_who_search(blocks_root, block_hash, x, y, w, h, txt_results, list_of_modifications);

    fprintf(txt_results, "====================================================\n");
}

void oloc_who_search(void* blocks_root, hash blocks_hash, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {
    
    if (blocks_root) {

        if (get_original_x(blocks_root) >= x) {

            void* list_of_blocks = get_node_data(blocks_root);

            for (void* aux = get_head(list_of_blocks); aux; aux = get_next(aux)) {

                void* element = get_list_element(aux);

                if (inside(get_x(element), get_y(element), get_w(element), get_h(element), x, y, w, h)) {

                    for (int i = 0; i < get_number_of_locations_available(element); i++) {

                        void* location = get_locations(element)[i];

                        if (location) {

                            if (location_get_available(location)) {
                                position_cases_text(blocks_hash, location, list_of_modifications, '*');
                                location_info(location, txt_results);

                            }
                        }
                    }
                }
            }
        }

        if (get_left(blocks_root)) {
            if (get_max_x(get_left(blocks_root)) >= x && get_min_x(get_left(blocks_root)) <= x + w) {
                oloc_who_search(get_left(blocks_root), blocks_hash, x, y, w, h, txt_results, list_of_modifications);
            }
        }

        if (get_right(blocks_root)) {
            if (get_max_x(get_right(blocks_root)) >= x && get_min_x(get_right(blocks_root)) <= x + w) {
                oloc_who_search(get_right(blocks_root), blocks_hash, x, y, w, h, txt_results, list_of_modifications);
            }
        }
    }
}

void loc(hash residents, hash blocks_hash, hash locations, char* id, char* cpf, FILE* txt_results, void* list_of_modifications) {
    
    void* person = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);

    void* location = find_item(hash_table_get_register_list(locations, id), id, compare_id);

    fprintf(txt_results, "loc(%s, %s):\n\n", id, cpf);

    if (person && location) {

        if (!location_get_available(location)) {
            fprintf(txt_results, "\tI'm sorry, couldn't alloc person with cpf = %s to location with id = %s, because this location is not available\n\tor either removed by dloc.\n\n", cpf, id);
            fprintf(txt_results, "====================================================\n");
            return;
        }

        void* old_square = find_item(hash_table_get_register_list(blocks_hash, get_person_cep(person)), get_person_cep(person), compare_cep);  //Find new square where this person will live

        void* new_square = find_item(hash_table_get_register_list(blocks_hash, location_get_cep(location)), location_get_cep(location), compare_cep);  //Find new square where this person will live

        if (!strcmp(get_person_cep(person), location_get_cep(location))) {  // Check if this person stayed on the same CEP, but wasn't included on the residents list

            void** residents = get_residents(new_square);

            int included = 0;

            for (int i = 0; i < get_number_of_persons_living(new_square); i++) {
                if (residents[i] == person) {
                    included = 1;
                    break;
                }
            }

            if (!included) {
                add_resident(new_square, person);
            }

        } else {  // This person moved to other CEP, now I need to remove the person from the void* vector of residents of the old block

            if (old_square) {
                void** old_residents = get_residents(old_square);

                for (int i = 0; i < get_number_of_persons_living(old_square); i++) {
                    if (old_residents[i] == person) {
                        old_residents[i] = NULL;
                        break;
                    }
                }
            }
            add_resident(new_square, person);
        }

        

        

        update_person(person, location_get_cep(location), location_get_face(location), location_get_num(location), location_get_complement(location));
        set_house_state(person, 1);
        location_set_available(location, false);
        location_info(location, txt_results);
        print_person_info(person, txt_results);
        set_person_living_here(location, person);

    } else if (person && !location) {

        fprintf(txt_results, "\tPerson found, but couldn't find the location!\n\n");

    }else if(!person && location) {

        fprintf(txt_results, "\tLocation found, but couldn't find the person!\n\n");

    }else if (!person && !location) {

        fprintf(txt_results, "\tCouldn't find the person and the location!\n\n");

    }

    fprintf(txt_results, "====================================================\n");

}

void loc_who(hash blocks_hash, hash locations, char* id, FILE* txt_results, void* list_of_modifications) {
    
    void* location = find_item(hash_table_get_register_list(locations, id), id, compare_id);

    fprintf(txt_results, "loc?(%s):\n\n", id);

    if (location) {

        if (location_get_ended(location)) {

            fprintf(txt_results, "\tThis location has been ended by dloc!\n");
            location_info(location, txt_results);
            position_cases_text(blocks_hash, location, list_of_modifications, '#');

        } else if (location_get_available(location)) {

            location_info(location, txt_results);
            position_cases_text(blocks_hash, location, list_of_modifications, '$');

        } else {

            location_info(location, txt_results);
            print_person_info(get_person_living_here(location), txt_results);
            position_cases_text(blocks_hash, location, list_of_modifications, '*');

        }

    } else {
        
        fprintf(txt_results, "\tSorry, id = %s not found on hash table...\n\n", id);
        
    }

    fprintf(txt_results, "====================================================\n");
}

void dloc(hash locations, hash blocks_hash, char* id, FILE* txt_results, void* list_of_modifications) {
    fprintf(txt_results, "dloc(%s):\n\n", id);

    void* location = find_item(hash_table_get_register_list(locations, id), id, compare_id);

    if (!get_person_living_here(location)) {  //Nobody lives on target location

        fprintf(txt_results, "\tNobody is living on location with ID = %s...\n\n", id);

        location_info(location, txt_results);

        fprintf(txt_results, "====================================================\n");

        // hash_table_remove_key(locations, id, location_free, compare_id);

        location_set_ended(location, 1); //This flag here is going to be used on svg results printing of loc_who
        location_set_available(location, 0); //Set that this location isn't available anymore

        return;
    }

    if (location) {  //Someone lives on this location and this person exists

        char* cep = location_get_cep(location);  //Gather location's cep to search on the blocks_hash hash table

        void* person_on_this_location = get_person_living_here(location);  //Gather the person's living here info

        print_person_info(person_on_this_location, txt_results);
        update_person(person_on_this_location, " ", ' ', -1, " ");
        set_house_state(person_on_this_location, 2);
        location_info(location, txt_results);

        void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);  //Find the block that this location belongs to

        set_person_living_here(location, NULL);

        for (int i = 0; i < get_number_of_locations_available(square); i++) {
            if (get_locations(square)[i] == location) {  //Find the location data on the locations available on that cep
                get_locations(square)[i] == NULL;
                break;
            }
        }

        // hash_table_remove_key(locations, id, location_free, compare_id);

        location_set_ended(location, 1);
        location_set_available(location, 0);

    } else {
        fprintf(txt_results, "\tSorry, location ID = %s not found...\n\n", id);
    }

    fprintf(txt_results, "====================================================\n");
}

void hom(tree blocks, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {
    fprintf(txt_results, "hom(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    hom_search(blocks_root, x, y, w, h, txt_results);

    fprintf(txt_results, "====================================================\n");
}

void hom_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results) {
    if (blocks_root) {
        if (get_original_x(blocks_root) >= x) {
            void* list_of_blocks = get_node_data(blocks_root);

            for (void* aux = get_head(list_of_blocks); aux; aux = get_next(aux)) {
                void* element = get_list_element(aux);

                if (inside(get_x(element), get_y(element), get_w(element), get_h(element), x, y, w, h)) {
                    for (int i = 0; i < get_number_of_persons_living(element); i++) {
                        void* person = get_residents(element)[i];

                        if (person) {
                            if (get_person_sex(person) == 'M') {
                                print_person_info(person, txt_results);
                            }
                        }
                    }
                }
            }
        }

        if (get_left(blocks_root)) {
            if (get_max_x(get_left(blocks_root)) >= x && get_min_x(get_left(blocks_root)) <= x + w) {
                hom_search(get_left(blocks_root), x, y, w, h, txt_results);
            }
        }

        if (get_right(blocks_root)) {
            if (get_max_x(get_right(blocks_root)) >= x && get_min_x(get_right(blocks_root)) <= x + w) {
                hom_search(get_right(blocks_root), x, y, w, h, txt_results);
            }
        }
    }
}

void mul(tree blocks, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {
    fprintf(txt_results, "mul(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    mul_search(blocks_root, x, y, w, h, txt_results);

    fprintf(txt_results, "====================================================\n");
}

void mul_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results) {
    if (blocks_root) {
        if (get_original_x(blocks_root) >= x) {
            void* list_of_blocks = get_node_data(blocks_root);

            for (void* aux = get_head(list_of_blocks); aux; aux = get_next(aux)) {
                void* element = get_list_element(aux);

                if (inside(get_x(element), get_y(element), get_w(element), get_h(element), x, y, w, h)) {
                    for (int i = 0; i < get_number_of_persons_living(element); i++) {
                        void* person = get_residents(element)[i];

                        if (person) {
                            if (get_person_sex(person) == 'F') {
                                print_person_info(person, txt_results);
                            }
                        }
                    }
                }
            }
        }

        if (get_left(blocks_root)) {
            if (get_max_x(get_left(blocks_root)) >= x && get_min_x(get_left(blocks_root)) <= x + w) {
                mul_search(get_left(blocks_root), x, y, w, h, txt_results);
            }
        }

        if (get_right(blocks_root)) {
            if (get_max_x(get_right(blocks_root)) >= x && get_min_x(get_right(blocks_root)) <= x + w) {
                mul_search(get_right(blocks_root), x, y, w, h, txt_results);
            }
        }
    }
}

void dmpt(tree blocks, char* sfx, path paths) {
    char* temp = calloc(strlen(get_geo_name(paths)) + strlen(sfx) + strlen(get_output_directory(paths)) + 20, sizeof(char));
    sprintf(temp, "%s%s-%s.dot", get_output_directory(paths), get_geo_name(paths), sfx);

    FILE* dot_file = fopen(temp, "w+");
    setvbuf(dot_file, 0, _IONBF, 0);

    void* blocks_root = get_root(blocks);

    fprintf(dot_file, "digraph ARV{\n");
    fprintf(dot_file, "graph [pad=\"0.5\", nodesep=\"2\", ranksep=\"2\"];");

    dmpt_recursive(blocks_root, dot_file);

    fprintf(dot_file, "}\n");
    free(temp);
    fclose(dot_file);
}

void dmpt_recursive(void* current_node, FILE* dot_file) {
    
    if (!current_node) return;

    dmpt_recursive(get_left(current_node), dot_file);
    dmpt_recursive(get_right(current_node), dot_file);

    if (get_left(current_node)) {
        fprintf(dot_file, "\t%lf->%lf;\n", get_original_x(current_node), get_original_x(get_left(current_node)));
        
    }else{
        fprintf(dot_file, "\t%lf->\"NULL_LEFT_%lf\"[style = invis];\n", get_original_x(current_node), get_original_x(current_node));
        fprintf(dot_file, "\t\"NULL_LEFT_%lf\"[shape = doublecircle, label = \"NULL_LEFT_NODE_%lf\", style = invisible]\n", get_original_x(current_node), get_original_x(current_node));
        
    }

    if (get_right(current_node)) {
        fprintf(dot_file, "\t%lf->%lf;\n", get_original_x(current_node), get_original_x(get_right(current_node)));
        
    }else{
        fprintf(dot_file, "\t%lf->\"NULL_RIGHT_%lf\"[style = invis];\n", get_original_x(current_node), get_original_x(current_node));
        fprintf(dot_file, "\t\"NULL_RIGHT_%lf\"[shape = doublecircle, label = \"NULL_RIGHT_NODE_%lf\", style = invisible]\n", get_original_x(current_node),get_original_x(current_node));
        
    }

    void* list_aux = get_node_data(current_node);
    int i = 0;

    fprintf(dot_file, "\t%lf[label = \" MIN_X = %lf\tMAX_X = %lf\n\nLIST SIZE = %d\n\n", get_original_x(current_node), get_min_x(current_node), get_max_x(current_node), get_size(list_aux));

    for (void* list_node = get_head(list_aux); list_node; list_node = get_next(list_node)) {
        if(i == 3) {
            fprintf(dot_file, "\t...\n");
            break;
        }
        void* block_data = get_list_element(list_node);

        fprintf(dot_file, "\tCEP: %s\n", get_cep(block_data));
        fprintf(dot_file, "\tX = %.2lf \t Y = %.2lf \t W = %.2lf \t H = %.2lf\n\n", get_x(block_data), get_y(block_data), get_w(block_data), get_h(block_data));
        i++;
    }

    fprintf(dot_file, "Altura = %d \t\t Fator de balanceamento = %d\n", height(current_node), get_balance(current_node));

    fprintf(dot_file, "\"]\n");

}

void catac(tree blocks, hash residents, hash locations, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {
    
    fprintf(txt_results, "catac(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    char modification[1000];

    sprintf(modification, "\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\"\n style=\"fill:#AB37C8;stroke:#AA0044;fill-opacity:0.5;stroke-opacity:0.5\" />\n", x,y,w,h); 

    char* command = calloc(strlen(modification) + 5, sizeof(char));
    strcpy(command, modification);
    insert_list(list_of_modifications, command);

    catac_search(blocks, blocks_root, residents, locations, x, y, w, h, txt_results, list_of_modifications);

    fprintf(txt_results, "====================================================\n");

}

void catac_search(tree blocks, void* blocks_root, hash residents, hash locations, double x, double y, double w, double h, FILE* txt_results, void* list_of_modifications) {

    if(blocks_root){

        if (get_original_x(blocks_root) >= x) {

            void* list_of_blocks = get_node_data(blocks_root);

            for (void* aux = get_head(list_of_blocks); aux; aux = get_next(aux)) {

                void* element = get_list_element(aux);
                void* temp = get_next(aux);
                int deletion_happened = 0;

                if (inside(get_x(element), get_y(element), get_w(element), get_h(element), x, y, w, h)) {

                    for (int i = 0; i < get_number_of_persons_living(element); i++) {

                        void* person = get_residents(element)[i];

                        if (person) {
                            print_person_info(person, txt_results);
                            hash_table_remove_key(residents, get_cpf(person), free_person, compare_CPF);
                        }
                    }

                    for(int i = 0; i < get_number_of_locations_available(element); i++) {

                        void* location = get_locations(element)[i];

                        if(location) {
                            location_info(location, txt_results);
                            hash_table_remove_key(locations, location_get_id(location), location_free, compare_id);
                        }

                    }
                    
                    blocks_root = delete_node(blocks, blocks_root, element, compare_x, free_single_block);
                    deletion_happened = 1;
                    if(temp) aux = temp;

                    
                }

                if(deletion_happened) aux = get_previous(aux);

            }
        }

        if (get_left(blocks_root)) {
            if (get_max_x(get_left(blocks_root)) >= x && get_min_x(get_left(blocks_root)) <= x + w) {
                catac_search(blocks, get_left(blocks_root), residents, locations, x, y, w, h, txt_results, list_of_modifications);
            }
        }

        if (get_right(blocks_root)) {
            if (get_max_x(get_right(blocks_root)) >= x && get_min_x(get_right(blocks_root)) <= x + w) {
                catac_search(blocks, get_right(blocks_root), residents, locations, x, y, w, h, txt_results, list_of_modifications);
            }
        }

    }
}