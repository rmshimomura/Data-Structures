#include "qry.h"

#include "AVL_Tree/AVL.h"
#include "DynamicList/dynamicList.h"
#include "Hash/hash.h"
#include "block.h"
#include "location.h"
#include "paths.h"
#include "person.h"

int inside(double x1, double y1, double p1Width, double p1Height, double x2, double y2, double p2Width, double p2Height) {
    if ((x1 >= x2 && x1 <= x2 + p2Width && y1 >= y2 && y1 <= y2 + p2Height && x1 + p1Width <= x2 + p2Width && y1 + p1Height <= y2 + p2Height)) return 1;
    //Fix the search on the p2 and vary on p1
    return 0;
}

void del(tree blocks, hash blocks_hash, hash residents, hash locations, char* cep, FILE* txt_results, FILE* modified_SVG) {
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

                    hash_table_remove_key(locations, location_get_cep(locations_list[i]), location_free, compare_cep);
                }
            }
        }

    } else {
        fprintf(txt_results, "\tSorry, CEP = %s not found...\n\n", cep);
        fprintf(txt_results, "====================================================\n");
        return;
    }

    void* blocks_root = get_root(blocks);

    // blocks_root = delete_node(blocks, blocks_root, square, compare_x, free_block_list);

    fprintf(txt_results, "====================================================\n");
}

void m_who(hash residents, hash blocks_hash, char* cep, FILE* txt_results, FILE* modified_SVG) {
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

void dm_who(hash residents, char* cpf, FILE* txt_results, FILE* modified_SVG) {
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

void mud(hash residents, hash blocks_hash, char* cpf, char* cep, char face, int num, char * compl, FILE* txt_results, FILE* modified_SVG) {
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

            fprintf(txt_results, "AFTER::\n\n");
            update_person(person_to_update, cep, face, num, compl );
            set_house_state(person_to_update, 0);
            print_person_info(person_to_update, txt_results);
            fprintf(txt_results, "====================================================\n");
        }

    } else {
        fprintf(txt_results, "mud(%s, %s, %c, %d, %s):\n\n\tCouldn't find person with cpf : %s on the hash table.\n\n", cpf, cep, face, num, compl, cpf);
        fprintf(txt_results, "====================================================\n");
    }
}

void oloc(hash locations, hash blocks_hash, char* id, char* cep, char face, int num, char * compl, double ar, double v, FILE* txt_results, FILE* modified_SVG) {
    void* new_location = create_location();
    set_location_properties(new_location, id, cep, face, num, compl, ar, v);
    hash_table_insert_data(locations, id, new_location);
    void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);
    add_location(square, new_location);
}

void oloc_who(tree blocks, double x, double y, double w, double h, FILE* txt_results, FILE* modified_SVG) {
    void* blocks_root = get_root(blocks);

    fprintf(txt_results, "oloc?(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    oloc_who_search(blocks_root, x, y, w, h, txt_results);

    fprintf(txt_results, "====================================================\n");
}

void oloc_who_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results) {
    if (blocks_root) {
        if (get_min_x(blocks_root) >= x && get_max_x(blocks_root) <= x + w) {
            void* list_of_blocks = get_node_data(blocks_root);

            for (void* aux = get_head(list_of_blocks); aux; aux = get_next(aux)) {
                void* element = get_list_element(aux);

                if (inside(get_x(element), get_y(element), get_w(element), get_h(element), x, y, w, h)) {
                    for (int i = 0; i < get_number_of_locations_available(element); i++) {
                        void* location = get_locations(element)[i];

                        if (location) {
                            if (location_get_available(location)) {
                                location_info(location, txt_results);
                            }
                        }
                    }
                }
            }
        }

        if (get_left(blocks_root)) {
            if (get_max_x(get_left(blocks_root)) >= x && get_min_x(get_left(blocks_root)) <= x + w) {
                oloc_who_search(get_left(blocks_root), x, y, w, h, txt_results);
            }
        }

        if (get_right(blocks_root)) {
            if (get_max_x(get_right(blocks_root)) >= x && get_min_x(get_right(blocks_root)) <= x + w) {
                oloc_who_search(get_right(blocks_root), x, y, w, h, txt_results);
            }
        }
    }
}

void loc(hash residents, hash blocks_hash, hash locations, char* id, char* cpf, FILE* txt_results, FILE* modified_SVG) {
    void* person = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);

    void* location = find_item(hash_table_get_register_list(locations, id), id, compare_id);

    fprintf(txt_results, "loc(%s, %s):\n\n", id, cpf);

    if (person && location) {
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

        fprintf(txt_results, "====================================================\n");
    }
}

void loc_who(hash locations, char* id, FILE* txt_results, FILE* modified_SVG) {
    void* location = find_item(hash_table_get_register_list(locations, id), id, compare_id);

    fprintf(txt_results, "loc?(%s):\n\n", id);

    if (location) {
        if (location_get_available(location)) {
            location_info(location, txt_results);
            fprintf(txt_results, "====================================================\n");
        } else {
            location_info(location, txt_results);
            print_person_info(get_person_living_here(location), txt_results);
            fprintf(txt_results, "====================================================\n");
        }
    } else {
        fprintf(txt_results, "\tSorry, id = %s not found on hash table...\n\n", id);
        fprintf(txt_results, "====================================================\n");
    }
}

void dloc(hash locations, hash blocks_hash, char* id, FILE* txt_results, FILE* modified_SVG) {
    fprintf(txt_results, "dloc(%s):\n\n", id);

    void* location = find_item(hash_table_get_register_list(locations, id), id, compare_id);

    if (!get_person_living_here(location)) {  //Nobody lives on target location

        char* cep = location_get_cep(location);  //Gather location's cep to search on the blocks_hash hash table

        fprintf(txt_results, "\tNobody is living on location with ID = %s...\n\n", id);

        location_info(location, txt_results);

        fprintf(txt_results, "====================================================\n");

        hash_table_remove_key(locations, cep, location_free, compare_cep);

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

        hash_table_remove_key(locations, cep, location_free, compare_cep);

    } else {
        fprintf(txt_results, "\tSorry, location ID = %s not found...\n\n", id);
    }

    fprintf(txt_results, "====================================================\n");
}

void hom(tree blocks, double x, double y, double w, double h, FILE* txt_results, FILE* modified_SVG) {
    fprintf(txt_results, "hom(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    hom_search(blocks_root, x, y, w, h, txt_results);

    fprintf(txt_results, "====================================================\n");
}

void hom_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results) {
    if (blocks_root) {
        if (get_min_x(blocks_root) >= x && get_max_x(blocks_root) <= x + w) {
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

void mul(tree blocks, double x, double y, double w, double h, FILE* txt_results, FILE* modified_SVG) {
    fprintf(txt_results, "mul(%.2lf, %.2lf, %.2lf, %.2lf):\n\n", x, y, w, h);

    void* blocks_root = get_root(blocks);

    mul_search(blocks_root, x, y, w, h, txt_results);

    fprintf(txt_results, "====================================================\n");
}

void mul_search(void* blocks_root, double x, double y, double w, double h, FILE* txt_results) {
    if (blocks_root) {
        if (get_min_x(blocks_root) >= x && get_max_x(blocks_root) <= x + w) {
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

    if (get_left(current_node)) {
        fprintf(dot_file, "\t%lf->\t%lf;\n", get_x(get_list_element(get_head(get_node_data(current_node)))), get_x(get_list_element(get_head(get_node_data(get_left(current_node))))));
    }

    if (get_right(current_node)) {
        fprintf(dot_file, "\t%lf->\t%lf;\n", get_x(get_list_element(get_head(get_node_data(current_node)))), get_x(get_list_element(get_head(get_node_data(get_right(current_node))))));
    }

    fprintf(dot_file, "\t%lf[label = \" MIN_X = %lf\tMAX_X = %lf\n\n", get_x(get_list_element(get_head(get_node_data(current_node)))), get_min_x(current_node), get_max_x(current_node));

    void* list_aux = get_node_data(current_node);

    for (void* list_node = get_head(list_aux); list_node; list_node = get_next(list_node)) {
        void* block_data = get_list_element(list_node);

        fprintf(dot_file, "\tCEP: %s\n", get_cep(block_data));
        fprintf(dot_file, "\tX = %.2lf \t Y = %.2lf \t W = %.2lf \t H = %.2lf\n\n", get_x(block_data), get_y(block_data), get_w(block_data), get_h(block_data));
    }

    fprintf(dot_file, "Altura = %d \t\t Fator de balanceamento = %d\n", height(current_node), get_balance(current_node));

    fprintf(dot_file, "\"]\n");

    dmpt_recursive(get_left(current_node), dot_file);
    dmpt_recursive(get_right(current_node), dot_file);
}