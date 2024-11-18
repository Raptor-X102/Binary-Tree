#include <TXLib.h>
#include "Tree_funcs.h"
#include "Binary_tree_graph_debug.h"
#include "Check_r_w_flags.h"

Node** Compare_doubles (Node* root, void* search_data, size_t search_data_size);
void Print_double(void* data, FILE* file);

int main(int argc, char* argv[]) {

    file_types files = {};
    if(!Check_r_w_flags(CHECK_W, argv, argc, &files)) {

        DEBUG_PRINTF("ERROR: flags verification failed")
        return 0;
    }

    Node* root_ptr = NULL;
    double root_data = 10;
    Create_new_node(&root_ptr, &root_data, sizeof(double));
    root_data = -666;
    double node1_data = 9;

    Insert_node(root_ptr, &node1_data, sizeof(double), &Compare_doubles);
    node1_data = 11;

    Insert_node(root_ptr, &node1_data, sizeof(double), &Compare_doubles);
    node1_data = 12;

    Insert_node(root_ptr, &node1_data, sizeof(double), &Compare_doubles);
    node1_data = 10.5;

    Insert_node(root_ptr, &node1_data, sizeof(double), &Compare_doubles);
    node1_data = 10.7;

    double new_data = 10.9;
    Replace_node(&root_ptr, &node1_data, &new_data, sizeof(double), &Compare_doubles);

    DEBUG_PRINTF("root_ptr = %p\n", root_ptr);
    DEBUG_PRINTF("root_ptr->root_ptr->left_node = %p\n", root_ptr->left_node);
    DEBUG_PRINTF("root_ptr->root_ptr->right_node = %p\n", root_ptr->right_node);

    node1_data = -666;
    memcpy(&root_data, &root_ptr->node_data, sizeof(double));
    memcpy(&node1_data, &((root_ptr->left_node)->node_data), sizeof(double));

    DEBUG_PRINTF("root_data = %lg\n", root_data);
    DEBUG_PRINTF("node1_data = %lg\n", node1_data);

    Tree_graph_debug(root_ptr, files.write_file, Print_double);

    Tree_Dtor(root_ptr);
}

Node** Compare_doubles (Node* root, void* search_data, size_t search_data_size) {

    double node_data = 0, search_value = 0;
    memcpy(&node_data, &root->node_data, search_data_size);
    memcpy(&search_value, search_data, search_data_size);

    if(search_value < node_data)
        return &root->left_node;

    else
        return &root->right_node;

}

void Print_double(void* data, FILE* file) {

    double tmp_double = 0;
    memcpy(&tmp_double, data, sizeof(double));
    DEBUG_PRINTF("tmp_double = %lf\n", tmp_double);
    fprintf(file, "%lg", tmp_double);
}
