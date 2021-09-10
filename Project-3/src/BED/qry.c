#include "qry.h"
#include "person.h"
#include "location.h"
#include "paths.h"
#include "Hash/hash.h"
#include "AVL_Tree/AVL.h"
#include "DynamicList/dynamicList.h"
#include "block.h"

void dm_who(hash residents, char* cpf, path paths){

    FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(txt_results, 0, _IONBF, 0);

    if(find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF)){

        void* person_to_print = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);
        
        fprintf(txt_results, "dm?:\n\n");
        print_person_info(person_to_print, txt_results);
        fprintf(txt_results, "====================================================\n");

    }else{
        
        fprintf(txt_results, "dm?:\n\n");
        fprintf(txt_results, "\tSorry, CPF = %s not found...\n\n", cpf);
        fprintf(txt_results, "====================================================\n");

    }

    fclose(txt_results);

}

void mud(hash residents, hash blocks_hash, char* cpf, char* cep, char face, int num, char* compl, path paths) {
    //TODO pergunta evandro
    FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(txt_results, 0, _IONBF, 0);

    if (hash_table_list_exist(residents, cpf)) {

        void* person_to_update = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF); //Find person on hash table of residents

        void* old_square = find_item(hash_table_get_register_list(blocks_hash, get_person_cep(person_to_update)), get_person_cep(person_to_update), compare_cep); //Find new square where this person will live

        void* new_square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep); //Find new square where this person will live

        if (person_to_update) {

            fprintf(txt_results, "mud:\n\n");
            fprintf(txt_results, "BEFORE::\n\n");
            print_person_info(person_to_update, txt_results);

            if(!strcmp(get_person_cep(person_to_update), cep)){  // Check if this person stayed on the same CEP, but wasn't included on the residents list
                
                void** residents = get_residents(new_square);

                int included = 0;

                for(int i = 0; i < get_number_of_persons_living(new_square); i++){
                
                    if(residents[i] == person_to_update){
                        included = 1;
                        break;
                    }

                }

                if(!included){
                    add_resident(new_square, person_to_update);
                }

            }   else   { // This person moved to other CEP, now I need to remove the person from the void* vector of residents of the old block
                
                void** old_residents = get_residents(old_square);

                for(int i = 0; i < get_number_of_persons_living(old_square); i++){
                
                    if(old_residents[i] == person_to_update){
                        
                        old_residents[i] = NULL;
                        break;
                    }

                }

                add_resident(new_square, person_to_update);

            }

            fprintf(txt_results, "AFTER::\n\n");
            update_person(person_to_update, cep, face, num, compl);
            print_person_info(person_to_update, txt_results);
            fprintf(txt_results, "====================================================\n");
            
        }

    } else {
        fprintf(txt_results ,"mud:\n\n\tCouldn't find person with cpf : %s on the hash table.\n\n", cpf);
        fprintf(txt_results, "====================================================\n");
    }

    fclose(txt_results);

}

void oloc(hash locations, hash blocks_hash, char* id, char* cep, char face, int num, char* compl, double ar, double v, path paths){
   
    void* new_location = create_location();
    set_location_properties(new_location, id, cep, face, num, compl, ar, v);
    hash_table_insert_data(locations, cep, new_location);
    void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);
    add_location(square, new_location);

}

void loc(hash residents, hash blocks_hash, hash locations, char* id, char* cpf, path paths) {

    FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(txt_results, 0, _IONBF, 0);

    void* person = find_item(hash_table_get_register_list(residents, cpf), cpf, compare_CPF);
    
    void* location = NULL;

    for(int i = 0; i < hash_table_size(locations); i++){
        location = find_item(hash_table_get_list_by_index(locations, i), id, compare_id);
        if(location) break;
    }

    fprintf(txt_results, "loc:\n\n");

    if(person && location){

        void* old_square = find_item(hash_table_get_register_list(blocks_hash, get_person_cep(person)), get_person_cep(person), compare_cep); //Find new square where this person will live

        void* new_square = find_item(hash_table_get_register_list(blocks_hash, location_get_cep(location)), location_get_cep(location), compare_cep); //Find new square where this person will live

        if(!strcmp(get_person_cep(person), location_get_cep(location))){  // Check if this person stayed on the same CEP, but wasn't included on the residents list
            
            void** residents = get_residents(new_square);

            int included = 0;

            for(int i = 0; i < get_number_of_persons_living(new_square); i++){
            
                if(residents[i] == person){
                    included = 1;
                    break;
                }

            }

            if(!included){
                add_resident(new_square, person);
            }

        }   else   { // This person moved to other CEP, now I need to remove the person from the void* vector of residents of the old block
            
            void** old_residents = get_residents(old_square);

            for(int i = 0; i < get_number_of_persons_living(old_square); i++){
            
                if(old_residents[i] == person){
                    
                    old_residents[i] = NULL;
                    break;
                }

            }

            add_resident(new_square, person);

        }

        update_person(person, location_get_cep(location), location_get_face(location), location_get_num(location), location_get_complement(location));
        location_set_available(location, false);
        location_info(location, txt_results);
        print_person_info(person, txt_results);
        set_person_living_here(location, person);

        fprintf(txt_results, "====================================================\n");
    }

    fclose(txt_results);

}

void loc_who(hash locations, char* id, path paths){

    FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(txt_results, 0, _IONBF, 0);

    void* location = NULL;

    for(int i = 0; i < hash_table_size(locations); i++){

        location = find_item(hash_table_get_list_by_index(locations, i), id, compare_id);

        if(location) break;

    }

    fprintf(txt_results, "loc?:\n\n");

    if(location){
        if(location_get_available(location)){

            location_info(location, txt_results);
            fprintf(txt_results, "====================================================\n");
        }else{
            location_info(location, txt_results);
            print_person_info(get_person_living_here(location), txt_results);
            fprintf(txt_results, "====================================================\n");
        }
    } else {
        fprintf(txt_results, "\tSorry, id = %s not found on hash table...\n\n", id);
        fprintf(txt_results, "====================================================\n");
    }

    fclose(txt_results);

}

void m_who(hash residents, hash blocks_hash, char* cep, path paths){

    FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(txt_results, 0, _IONBF, 0);

    void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);

    if(square){

        if(!get_number_of_persons_living(square)) {

            fprintf(txt_results, "m?:\n\n");
            fprintf(txt_results, "\tNobody lives here on cep = %s... \n\n", cep);
            fprintf(txt_results, "====================================================\n");
            fclose(txt_results);
            return;

        }

        fprintf(txt_results, "m?:\n\n");

        for(int i = 0; i < get_number_of_persons_living(square); i++){

            if(get_residents(square)[i]){

                print_person_info(get_residents(square)[i], txt_results);

            }

        }

        fprintf(txt_results, "====================================================\n");
        
    }else{

        fprintf(txt_results, "m?:\n\n");
        fprintf(txt_results, "\tSorry, CEP = %s not found...\n\n", cep);
        fprintf(txt_results, "====================================================\n");

    }


    fclose(txt_results);

}

void del(tree blocks, hash blocks_hash, hash residents, hash locations, char* cep, path paths){

    FILE* txt_results = fopen(get_path_TXT_with_qry(paths), "a+");
    setvbuf(txt_results, 0, _IONBF, 0);

    fprintf(txt_results, "del:\n\n");

    void* square = find_item(hash_table_get_register_list(blocks_hash, cep), cep, compare_cep);

    if(square){

        void** residents_list = get_residents(square);

        if(residents_list) {

            // puts("Residents");

            for(int i = 0; i < get_number_of_persons_living(square); i++){

                if(residents_list[i]){

                    print_person_info(residents_list[i], txt_results);
                    
                    hash_table_remove_key(residents, get_cpf(residents_list[i]), free_person, compare_CPF);

                }

            }

            // puts("Residents END\n\n");

        }

        void** locations_list = get_locations(square);

        if(locations_list){

            // puts("Locations");

            for(int i = 0; i < get_number_of_locations_available(square); i++){

                if(locations_list[i]){
                    location_info(locations_list[i], txt_results);
                    
                    hash_table_remove_key(locations, location_get_cep(locations_list[i]), location_free, compare_cep);

                }

            }

            // puts("Locations END\n\n");

        }

    }else   {
        
        fprintf(txt_results, "\tSorry, CEP = %s not found...\n\n", cep);
        fprintf(txt_results, "====================================================\n");

    }

    void* blocks_root = get_root(blocks);

    blocks_root = delete_node(blocks, blocks_root, square, compare_x, free_block_list);

    fclose(txt_results);

}