#include "Binary_tree_graph_debug.h"

void Tree_graph_debug(Node* root, const char* output_file_name, void (*Print_tree_data) (const void* data, FILE* file)) {

    FILE* output_file = fopen(output_file_name, "wb+");
    if(!output_file) {

        DEBUG_PRINTF("ERROR: file %s was not opened\n", output_file_name);
        return;
    }

    PRINTOUT("digraph List{\n");
    PRINTOUT("rankdir=TB;\n");
    PRINTOUT("bgcolor=\"#f5cbaf\";\n");
    PRINTOUT("node[fontsize=100, style=filled, fillcolor = \"#f56e31\", fontcolor=\"#000000\", shape=\"none\",style=\"rounded\"];\n");
    PRINTOUT("edge[color=\"#ff05ff\",fontcolor=\"blue\", splines = polylines];\n\n");

    Create_nodes_akinator(root, output_file, Print_tree_data);

    Create_edges_akinator(root, output_file);

    PRINTOUT("\n}\n");

    fclose(output_file);

    if(!System_call(output_file_name))
        DEBUG_PRINTF("ERROR: System_call failed\n");
}

void Create_nodes(Node* root, FILE* output_file, void (*Print_tree_data) (const void* data, FILE* file)) {

    PRINTOUT("node%p[color = \"#ff030f\", fillcolor = \"#f56e31\", style=filled, shape = record,  label = \"{ ", root);
    PRINTOUT("Address: %p | ", root);
    PRINTOUT("Data: ");
    Print_tree_data(&root->node_data, output_file);
    PRINTOUT(" | { <left> Left_node: %p", root->left_node);
    PRINTOUT(" | <right> Right_node: %p }}", root->right_node);
    PRINTOUT("\"];\n");

    if(root->left_node)
        Create_nodes(root->left_node, output_file, Print_tree_data);

    if(root->right_node)
        Create_nodes(root->right_node, output_file, Print_tree_data);

}

void Create_nodes_akinator(Node* root, FILE* output_file, void (*Print_tree_data) (const void* data, FILE* file)) {

    PRINTOUT("node%p[shape=plaintext, color = \"#ff030f\", fillcolor = \"#f56e31\", style=filled,  label =< \n"
    "<TABLE COLOR=\"red\" CELLSPACING=\"2\" CELLPADDING=\"2\" BORDER=\"3\"><TR><TD>", root);
    Print_tree_data(&root->node_data, output_file);
    PRINTOUT("</TD></TR>");
    if(Check_image_existence(&root->node_data)) {

        PRINTOUT("\n<TR><TD><IMG SRC=\"Images\\");
        Print_tree_data(&root->node_data, output_file);
        PRINTOUT(".png\" /></TD></TR>");
    }

    PRINTOUT("</TABLE>>]\n");

    if(root->left_node)
        Create_nodes_akinator(root->left_node, output_file, Print_tree_data);

    if(root->right_node)
        Create_nodes_akinator(root->right_node, output_file, Print_tree_data);

}

bool Check_image_existence(const void* filename_ptr) {

    char* filename = NULL, foldername[] = "Images\\", extension[] = ".png";
    memcpy(&filename, filename_ptr, sizeof(char*));
    char* path = (char*) calloc(strlen(foldername) + strlen(filename) + Calloc_add, sizeof(char));
    if(!path) {

        DEBUG_PRINTF("ERROR: memory was not allocated\n");
        return false;
    }

    memcpy(path, foldername, strlen(foldername));
    memcpy(path + strlen(foldername), filename, strlen(filename));
    memcpy(path + strlen(foldername) + strlen(filename), extension, strlen(extension));
    if(_access(path, 0) == -1) {

        free(path);
        return false;
    }

    else {

        free(path);
        return true;
    }
}

void Create_edges_akinator(Node* root, FILE* output_file) {

    if(root->left_node) {

        PRINTOUT("node%p -> ", root);
        PRINTOUT("node%p[color = \"#ff0505\", splines = polylines, arrowsize = 3, fontsize=70, label = \"NO      \"];\n", root->left_node);
        Create_edges_akinator(root->left_node, output_file);
    }

    if(root->right_node) {

        PRINTOUT("node%p -> ", root);
        PRINTOUT("node%p[color = \"#ff0505\", splines = polylines, arrowsize = 3, fontsize=70, label = \"YES\"];\n", root->right_node);
        Create_edges_akinator(root->right_node, output_file);
    }
}

void Create_edges(Node* root, FILE* output_file) {

    if(root->left_node) {

        PRINTOUT("node%p:left -> ", root);
        PRINTOUT("node%p[color = \"#ff0505\", splines = polylines, fontsize=12];\n", root->left_node);
        Create_edges(root->left_node, output_file);
    }

    if(root->right_node) {

        PRINTOUT("node%p:right -> ", root);
        PRINTOUT("node%p[color = \"#ff0505\", splines = polylines, fontsize=12];\n", root->right_node);
        Create_edges(root->right_node, output_file);
    }
}

bool System_call(const char* output_file_name) {

    char command[] = "dot -Tpng C:\\Users\\mihai\\Documents\\VSCode\\Binary_Trees\\";
    int name_offset = 0;
    char* cmd_buffer = (char*) calloc(strlen(command) + 2 * strlen(output_file_name) + Calloc_add, sizeof(char));
    if(!cmd_buffer) {

        return false;
        DEBUG_PRINTF("ERROR: memory was not allocated\n");
    }

    char* tmp_ptr = strchr(output_file_name, '.');

    if(!tmp_ptr) {

        DEBUG_PRINTF("ERROR: wrong filename format\n");
        return false;
    }

    if(tmp_ptr[1] == '\\') {

        tmp_ptr = strchr(tmp_ptr+1, '.');
        name_offset = 2;
        if(!tmp_ptr) {

            DEBUG_PRINTF("ERROR: wrong filename format\n");
            return false;
        }
    }

    memcpy(command, output_file_name+name_offset, tmp_ptr - output_file_name - name_offset);
    command[tmp_ptr-output_file_name - name_offset] = '\0';

    sprintf(cmd_buffer, "dot -Tpng C:\\Users\\mihai\\Documents\\VSCode\\Binary_Trees\\%s "
    "-o %s.png", output_file_name + name_offset, command);

    DEBUG_PRINTF("cmd_buffer = %s\n", cmd_buffer);
    system(cmd_buffer);

    free(cmd_buffer);

    return true;
}
