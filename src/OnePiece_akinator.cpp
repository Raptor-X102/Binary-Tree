#include <TXLib.h>
#include "Tree_funcs.h"
#include "Binary_tree_graph_debug.h"
#include "Check_r_w_flags.h"

void Print_strings(const void* data, FILE* file);
Node** Answer_question (Node* root, const void* search_data, size_t search_data_size);

int main(int argc, char* argv[]) {

    char* read_files[1] = {};
    char* write_files[2] = {};
    file_types files = {};
    files.read_files = read_files;
    files.write_files = write_files;
    if(!Check_r_w_flags(CHECK_R_W, argv, argc, &files)) {

        DEBUG_PRINTF("ERROR: flags verification failed")
        return 0;
    }

    DEBUG_PRINTF("%s\n", files.read_files[0]);
    DEBUG_PRINTF("%s\n", files.write_files[0]);
    DEBUG_PRINTF("%s\n", files.write_files[1]);

    Node* root_ptr = NULL;
    char* buffer_ptr = Read_tree_file(&root_ptr, files.read_files[0]);

    char new_question[] = "Is Yonko?";
    char* nq_ptr = new_question;
    char new_answer[] = "Kaido";
    char* na_ptr = new_answer;
    char searching_value[] = "Katakuri";
    char* sv_ptr = searching_value;
    //Replace_node_auto(&root_ptr, &sv_ptr, &nq_ptr, &na_ptr, sizeof(char*), &Answer_question);

    Output_node_definition(root_ptr, "Doflamingo");
    Output_node_definition(root_ptr, "Crocodile");
    Output_node_definition(root_ptr, "Boa Hancock");
    Output_node_definition(root_ptr, "Sanji");
    Output_node_definition(root_ptr, "Zoro");
    Output_node_definition(root_ptr, "Rob Lucci");
    Output_node_definition(root_ptr, "Usopp");

    Tree_graph_debug(root_ptr, files.write_files[0], Print_strings);

    Output_tree(root_ptr, sizeof(char*), files.write_files[1], &Print_strings);

    free(buffer_ptr);
    Tree_Dtor(root_ptr);
}

void Print_strings(const void* data, FILE* file) {

    char* string = NULL;
    memcpy(&string, data, sizeof(char*));
    fprintf(file, "%s", string);
}

Node** Answer_question (Node* root, const void* search_data, size_t search_data_size) {

    char* node_data = NULL, * search_value = NULL;
    int answer = 0, skip_ch = 0;
    memcpy(&node_data, &root->node_data, search_data_size);
    memcpy(&search_value, search_data, search_data_size);

    printf("%s ", node_data);
    printf("(%s)\n", search_value);

    while(tolower(answer) != 'y' && tolower(answer) != 'n')
        answer = getchar();

    while(skip_ch != '\n')
        skip_ch = getchar();

    if(tolower(answer) == 'n')
        return &root->left_node;

    else
        return &root->right_node;

}
