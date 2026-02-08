/*
 * File: code_generation.cpp 
 * Description: Functions for emiting the proper TM three-address codes per tree node types
 * Author: Jacob A. Geldbach
 * Date: 12/1/2025
 *
 */

#include "code_generation.h"
#include "emitcode.h"
#include "globals.h"
#include "semantic.h"
#include <stdio.h>
#include <string.h>

code_generation_linearized_node_t *current_head = NULL;
code_generation_linearized_node_t *function_array_node_list = NULL;
code_generation_linearized_node_t *globals_statics_node_list = NULL;
code_generation_linearized_node_t *last_function_decl_node = NULL;

int last_compound_node_idx = 0;
code_generation_linearized_node_t *last_compound_node[10];

int last_while_node_idx = 0;
code_generation_linearized_node_t *last_while_node[10];

int last_if_node_idx = 0;
code_generation_linearized_node_t *last_if_node[10];

int last_for_node_idx = 0;
code_generation_linearized_node_t *last_for_node[10];

void reset_func_array_node_list() {

    code_generation_linearized_node_t *func_array = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));
    func_array->prev = NULL;
    func_array->next = NULL;
    func_array->action = CG_None;
    func_array->ast_node = NULL;

    function_array_node_list = func_array;
}

void reset_globals_statics_node_list() {

    code_generation_linearized_node_t *globals_statics = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));
    globals_statics->prev = NULL;
    globals_statics->next = NULL;
    globals_statics->action = CG_None;
    globals_statics->ast_node = NULL;

    globals_statics_node_list = globals_statics;
}

code_generation_linearized_node_t *initialize_temp_list() {

    code_generation_linearized_node_t *temp_list = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));

    temp_list->prev = NULL;
    temp_list->next = NULL;
    temp_list->action = CG_None;
    temp_list->ast_node = NULL;

    return temp_list;
}

code_generation_linearized_node_t *initialize_code_generation_list(TreeNode *tree) {

    code_generation_linearized_node_t *head = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));
    code_generation_linearized_node_t *func_array = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));
    code_generation_linearized_node_t *globals_statics = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));
    

    head->prev = NULL;
    head->next = NULL;
    head->action = CG_None;
    head->ast_node = NULL;

    func_array->prev = NULL;
    func_array->next = NULL;
    func_array->action = CG_None;
    func_array->ast_node = NULL;

    globals_statics->prev = NULL;
    globals_statics->next = NULL;
    globals_statics->action = CG_None;
    globals_statics->ast_node = NULL;

    function_array_node_list = func_array;
    globals_statics_node_list = globals_statics;
    current_head = head;

    return head;
}

void append_linearized_node(TreeNode *tree, code_generation_action_t action, code_generation_linearized_node_t *target_list) {

    code_generation_linearized_node_t *new_node = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));

    code_generation_linearized_node_t *current_tail = target_list;

    while(current_tail->next != NULL) {
        current_tail = current_tail->next;
    }

    new_node->ast_node = tree;
    new_node->action = action;
    new_node->prev = current_tail;
    new_node->next = NULL;

    current_tail->next = new_node;
}

void append_comment_node(char *comment, code_generation_linearized_node_t *target_list) {
    code_generation_linearized_node_t *new_node = (code_generation_linearized_node_t *) malloc (sizeof(code_generation_linearized_node_t));

    code_generation_linearized_node_t *current_tail = target_list;

    while(current_tail->next != NULL) {
        current_tail = current_tail->next;
    }
    
    new_node->action = CG_CommentOnly;
    new_node->comment_only_comment = comment;
    new_node->prev = current_tail;
    new_node->next = NULL;

    current_tail->next = new_node;
}

void insert_linearized_node(code_generation_linearized_node_t *node, code_generation_linearized_node_t *target) {
    
    if (target == NULL) {
        printf("ERROR: target node for insertion is NULL\n");
        return;
    }

    code_generation_linearized_node_t *insert_head = node;
    code_generation_linearized_node_t *insert_tail;
    code_generation_linearized_node_t *target_next = target->next;

    insert_tail = insert_head;
    while(insert_tail->next != NULL) {
        insert_tail = insert_tail->next;
    }

    target->next = insert_head;
    insert_head->prev = target;

    insert_tail->next = target_next;
    target_next->prev = insert_tail;
}

code_generation_linearized_node_t *get_current_tail_node(code_generation_linearized_node_t *target_list) {

    code_generation_linearized_node_t *current_tail = target_list;

    while(current_tail->next != NULL) {
        current_tail = current_tail->next;
    }

    return current_tail;
}

void append_globals_on_current_head() {
    
    code_generation_linearized_node_t *current_tail = current_head;

    while(current_tail->next != NULL) {
        current_tail = current_tail->next;
    }

    current_tail->next = globals_statics_node_list;
    globals_statics_node_list->prev = current_tail;

}

int temp_offset = 0;
int temp_offset_saved_stack[100];       /* stack that keeps track of the last foffset before entering a new scope */
int temp_offset_saved_stack_idx = 0;    /* current index for saved_foffset_stack, incremented when a new scope is entered, decremented when exiting a scope */

int function_call_pc = 0;

void increment_temp_offset(int size) {
    temp_offset += size;
}

FILE *code;
int generate_io_library() {
    // Source and destination file names
    const char *io_library_tm_code = "ioLibrary.MYtm";

    // Open the source file for reading
    FILE *sourceFile = fopen(io_library_tm_code, "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return -1;
    }

    // Transfer the contents of the source file to the destination file
    char buffer[1024]; // Buffer for reading chunks of the file
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, code);
    }

    emitSkip(39); // Skip the I/O library code size

    // Close source file
    fclose(sourceFile);

    return 0;
}

int init_code_file(char *filename) {
    // Open the code file for writing
    char new_filename[256];

    snprintf(new_filename, strlen(filename) - 2, "%s", filename);
    sprintf(new_filename, "%s.tm", new_filename); 
    code = fopen(new_filename, "w");
    if (code == NULL) {
        fprintf(stderr, "Error: Could not open file %s for writing.\n", filename);
        return -1;
    }
    fprintf(code, "* C- compiler version C-F23\n");
    fprintf(code, "* File compiled:  %s\n", filename);
    fprintf(code, "* \n");

    if (generate_io_library() != 0) {
        fprintf(stderr, "Error: Could not generate I/O library code.\n");
        return -1;
    }

    emitComment("");

    return 0;
}

void generate_compound_statement_enter(TreeNode *tree, SymbolTable *symbol_table) {
    temp_offset_saved_stack[temp_offset_saved_stack_idx++] = temp_offset; /* Save the current temp_offset on the stack before entering a new scope */
    emitComment("COMPOUND");
    tree->program_counter_address = emitWhereAmI();
    emitComment("TOFF set:", tree->dataword_size * -1);
}

void generate_compound_statement_leave(TreeNode *tree, SymbolTable *symbol_table) {
    temp_offset = temp_offset_saved_stack[--temp_offset_saved_stack_idx]; /* Decrement the temp_offset_stack_idx, and restore the temp_offset value to what it was before entering this scope that is being exited */
    emitComment("TOFF set:", temp_offset * -1);
    emitComment("END COMPOUND");
}

void generate_standard_closing() {
    emitComment("Add standard closing in case there is no return statement");
    emitRM("LDC", FP, 0, AC2, "Set return value to 0");
    emitRM("LD", RT, 1 * -1, GP, "Load return address");
    emitRM("LD", GP, 0, GP, "Adjust fp");
    emitRM("JMP", AC3, 0, RT, "Return");
}

void generate_function_define_enter(TreeNode *tree, SymbolTable *symbol_table) {

    TreeNode *decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);                
    if (decl_node != NULL) {
        decl_node->program_counter_address = emitWhereAmI(); 
    }

    temp_offset = 0; /* Temp offset reset on function definition, stack is reset */
    emitComment("** ** ** ** ** ** ** ** ** ** ** **");
    // Emit a comment indicating the start of the function definition
    emitComment("FUNCTION", tree->attr.name);
    temp_offset += tree->dataword_size;
    emitComment("TOFF set:", temp_offset * -1);

    /* Store function return address in RT register from GP return register offset */
    emitRM("ST", RT, tree->return_address * -1, GP, "Store return address");
}

void generate_function_define_leave(TreeNode *tree, SymbolTable *symbol_table) {

    generate_standard_closing();
    emitComment("END FUNCTION", tree->attr.name);
    emitComment("");
}


void generate_function_call_enter(TreeNode *tree, SymbolTable *symbol_table) {
    temp_offset_saved_stack[temp_offset_saved_stack_idx++] = temp_offset; /* Save the current temp_offset on the stack before entering a new function call scope */
    
    // Emit a comment indicating that a function was called
    emitComment("CALL", tree->attr.name);
    emitRM("ST", GP, temp_offset * -1, GP, "Store fp in ghost frame for", tree->attr.name);
    emitComment("TOFF dec:", (++temp_offset) * -1);
    emitComment("TOFF dec:", (++temp_offset) * -1);
    /* Increment temporary offset by 2 for function fp and return address */
}

void generate_function_call_leave(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("Param end", tree->attr.name);
    temp_offset = temp_offset_saved_stack[--temp_offset_saved_stack_idx]; /* Decrement the temp_offset_stack_idx, and restore the temp_offset value to what it was before entering this function call scope that is being exited */
   
    int function_program_counter_address = 0;
    
    TreeNode *decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);                
    if (decl_node != NULL) {
        function_program_counter_address = decl_node->program_counter_address;
    }

    /* Load direct address to GP register */
    emitRM("LDA", GP, temp_offset * -1, GP, "Ghost frame becomes new active frame");
    emitRM("LDA", RT, 1, AC3, "Return address in ac");
    emitRM("JMP", AC3, (emitWhereAmI() - function_program_counter_address + 1) * -1, AC3, "CALL", tree->attr.name);
    emitRM("LDA", RT, 0, FP, "Save the result in ac");
    emitComment("Call end", tree->attr.name);
    emitComment("TOFF set:", temp_offset * -1);
}

int NOT = 287;  /* NOT  */
int CHSIGN = 300;/* CHSIGN  */
int TERNARY = 299; /* TERNARY  */
void generate_load_parameter_constant(TreeNode *tree, SymbolTable *symbol_table) { 
    char *load_comment = NULL;

    int base_register = GP;
    if (tree->var_kind == Global) {
        base_register = 0;
    }

    if (tree->type == Integer) {
        load_comment = "Load integer constant";
    }
    else if (tree->type == Char) {
        if (tree->isArray) {
            emitStrLit(tree->mem_offset * -1, tree->attr.string);
            emitRM("LDA", RT, tree->mem_offset * -1, base_register, "Load address of char array");
            emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");  
            temp_offset += 1;
            emitComment("TOFF dec:", temp_offset * -1);
            return;
        }


        load_comment = "Load char constant";
    }
    else if (tree->type == CharInt) {
        load_comment = "Load charint constant";
    }
    else if (tree->type == Boolean) {
        load_comment = "Load Boolean constant";
    }
    else {
        load_comment = "UnknownType";
    }
    if (tree->oper != 0 && tree->oper != NOT && tree->oper != CHSIGN && tree->oper != TERNARY) {
        /* LHS constant param */
        emitRM("LDC", RT, tree->attr.value, AC2, load_comment);
        emitRM("ST", RT, temp_offset * -1, GP, "Push left side"); 
    }
    else if (tree->oper == NOT) {
        /* LHS constant param with NOT operator */
        emitRM("LDC", RT, tree->attr.value, AC2, load_comment);
        emitRM("LDC", AC, 1, AC2, "Load 1");
        emitRO("XOR", RT, RT, AC, "Op XOR to get logical not");
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
    }
    else if (tree->oper == CHSIGN) {
        emitRM("LDC", RT, tree->attr.value, AC2, load_comment);
        emitRO("NEG", RT, RT, RT, "Op unary -");
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
    }
    else if (tree->oper == TERNARY) {
        /* Ternary operator constant param */
        emitRM("LDC", RT, tree->attr.value, AC2, load_comment);
        emitRO("RND", RT, RT, AC2, "Op ?");
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
    }
    else {
        /* Load Constant immediate, base register doesnt matter */
        emitRM("LDC", RT, tree->attr.value, AC2, load_comment);
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter"); 
    }

    temp_offset += tree->dataword_size;
    emitComment("TOFF dec:", temp_offset * -1);
}

int SIZEOF = 301;           /* SIZEOF  */
void generate_load_parameter_id(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    if (tree->isArray) {
        /* Var param that is an indexed array */
        if (tree->var_kind == Parameter) {
            emitRM("LD", RT, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
        }
        else {
            emitRM("LDA", RT, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
        }

        if (tree->oper == SIZEOF) {
            emitRM("LD", RT, 1, RT, "Load array size", tree->attr.name);
            emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
        }
        else {
            emitRM("ST", RT, temp_offset * -1, GP, "Push left side"); 
        }    
    }
    else if (tree->oper != 0 && tree->oper != NOT && tree->oper != CHSIGN) {
        /* LHS var param */
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "Load variable", tree->attr.name);
        emitRM("ST", RT, temp_offset * -1, GP, "Push left side"); 
    }
    else if (tree->oper == NOT) {
        /* LHS constant param with NOT operator */
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "Load variable", tree->attr.name);
        emitRM("LDC", AC, 1, AC2, "Load 1");
        emitRO("XOR", RT, RT, AC, "Op XOR to get logical not");
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
    }
    else if (tree->oper == CHSIGN) {
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "Load variable", tree->attr.name);
        emitRO("NEG", RT, RT, RT, "Op unary -");
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
    }
    else {
        /* Regular var param */
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "Load variable", tree->attr.name);
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter"); 
    }

    emitComment("TOFF dec:", ++temp_offset * -1);
}

void generate_return_statement(TreeNode *tree, SymbolTable *symbol_table) {
    if (tree->child[0] != NULL) {
        emitRM("LDA", FP, 0, RT, "Copy result to return register");
    }

    emitRM("LD", RT, 1 * -1, GP, "Load return address");
    emitRM("LD", GP, 0, GP, "Adjust fp");
    emitRM("JMP", AC3, 0, RT, "Return");
}

void generate_init_enter(TreeNode *tree, SymbolTable *symbol_table) {
    int final_pc = emitWhereAmI() - 1;
    int goffset = get_goffset();
    emitNewLoc(0); /* Set location to 0 to start emitting init code at beginning of TM code */

    emitRM("JMP", AC3, final_pc, AC3, "Jump to init [backpatch]");
    
    emitSkip(final_pc);

    emitComment("INIT");
    emitRM("LDA", GP, goffset * -1, 0, "set first frame at end of globals");
    emitRM("ST", GP, 0, GP, "store old fp (point to self)");
}

void generate_init_leave(TreeNode *tree, SymbolTable *symbol_table) {
    
    TreeNode *main_decl_node = (TreeNode *) symbol_table->lookup("main");

    emitRM("LDA", RT, 1, AC3, "Return address in ac");
    emitRM("JMP", AC3, (emitWhereAmI() - main_decl_node->program_counter_address + 1) * -1, AC3, "Jump to main");
    emitRO("HALT", 0, 0, 0, "DONE!");
    emitComment("END INIT");
}

void generate_globals_statics_enter(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("INIT GLOBALS AND STATICS");
}

void generate_globals_statics_leave(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("END INIT GLOBALS AND STATICS");
}

void generate_load_constant(TreeNode *tree, SymbolTable *symbol_table) {
    char *load_comment = NULL;

    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    if (tree->type == Integer) {
        load_comment = "Load integer constant";
    }
    else if (tree->type == Char) {
        if (tree->isArray) {
            emitStrLit(tree->mem_offset * -1, tree->attr.string);
            emitRM("LDA", RT, tree->mem_offset * -1, base_register, "Load address of char array");
            return;
        }

        load_comment = "Load char constant";
    }
    else if (tree->type == CharInt) {
        load_comment = "Load charint constant";
    }
    else if (tree->type == Boolean) {
        load_comment = "Load Boolean constant";
    }
    else {
        load_comment = "UnknownType";
    }

    /* Load Constant immediate, base register doesnt matter */
    emitRM("LDC", RT, tree->attr.value, AC2, load_comment);
    
    if (tree->oper == CHSIGN) {
        emitRO("NEG", RT, RT, RT, "Op unary -");
    }
}

void generate_load_var(TreeNode *tree, SymbolTable *symbol_table) {
    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    emitRM("LD", RT, tree->mem_offset * -1, base_register, "Load variable", tree->attr.name);
    
    if (tree->oper == NOT) {
        emitRM("LDC", AC, 1, AC2, "Load 1");
        emitRO("XOR", RT, RT, AC, "Op XOR to get logical not");
    }

}

void generate_load_var_indexed(TreeNode *tree, SymbolTable *symbol_table) {
    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    if (tree->var_kind == Parameter) {
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
    }
    else {
        emitRM("LDA", RT, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
    }

    if (tree->oper == SIZEOF) {
        emitRM("LD", RT, 1, RT, "Load array size");
    }
    else {
        emitRM("ST", RT, temp_offset * -1, GP, "Push left side"); 
        emitComment("TOFF dec:", ++temp_offset * -1);
    }

}

void generate_assign_lhs_load(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    if (tree->oper == NOT) {
            emitRM("LDC", AC, 1, AC2, "Load 1");
            emitRO("XOR", RT, RT, AC, "Op XOR to get logical not");
    }

    emitRM("ST", RT, tree->mem_offset * -1, base_register, "Store variable", tree->attr.name);
}

void generate_assign_lhs_push(TreeNode *tree, SymbolTable *symbol_table) {
    emitRM("ST", RT, temp_offset * -1, GP, "Push left side");
    emitComment("TOFF dec:", ++temp_offset * -1);
}

void generate_assign_lhs_load_indexed(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    emitComment("TOFF inc:", (--temp_offset) * -1);
    emitRM("LD", AC, temp_offset * -1, GP, "Pop index");
    
    if (tree->var_kind == Parameter) {
        emitRM("LD", AC1, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
    }
    else {
        emitRM("LDA", AC1, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
    }

    emitRO("SUB", AC1, AC1, AC, "Compute offset of value");
    emitRM("ST", RT, 0, AC1, "Store variable", tree->attr.name);
}

void generate_var_declartion(TreeNode *tree, SymbolTable *symbol_table) {
    TreeNode *decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);

    if (decl_node != NULL) {
        decl_node->program_counter_address = emitWhereAmI(); 
    }

    temp_offset += tree->dataword_size;
}

void generate_var_array_declartion(TreeNode *tree, SymbolTable *symbol_table) {
    TreeNode *decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);
    int base_register = GP;

    if (decl_node != NULL) {
        decl_node->program_counter_address = emitWhereAmI(); 
    }

    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    emitRM("LDC", RT, tree->dataword_size - 1, AC2, "load size of array", tree->attr.name);
    emitRM("ST", RT, (tree->mem_offset - 1) * -1, base_register, "save size of array", tree->attr.name);

    temp_offset += tree->dataword_size;
}

void generate_var_indexed_push(TreeNode *tree, SymbolTable *symbol_table) { 
    emitRM("ST", RT, temp_offset * -1, GP, "Push index");
    emitComment("TOFF dec:", (++temp_offset) * -1);
}

void generate_parameter_push_var_indexed(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global) {
        base_register = 0;
    }

    emitComment("TOFF inc:", (--temp_offset) * -1);
    emitRM("LD", AC, temp_offset * -1, base_register, "Pop left into ac1");
    emitRO("SUB", RT, AC, RT, "compute location from index");
    emitRM("LD", RT, 0, RT, "Load array element");
    if (tree->oper != 0) {
        emitRM("ST", RT, temp_offset * -1, base_register, "Push left side");
    }
    else {
        emitRM("ST", RT, temp_offset * -1, base_register, "Push parameter");
    }
    emitComment("TOFF dec:", (++temp_offset) * -1);
}

int OR = 285;   /* OR  */
int AND = 286;  /* AND  */
int LT = 288;   /* LT  */
int LEQ = 289;  /* LEQ  */
int GT = 290;   /* GT  */
int GEQ = 291;  /* GEQ  */
int EQ = 292;   /* EQ  */
int NEQ = 293;  /* NEQ  */

void generate_parameter_push_var_lhs_op(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global) {
        base_register = 0;
    }

    emitComment("TOFF inc:", (--temp_offset) * -1);
    emitRM("LD", AC, temp_offset * -1, base_register, "Pop left into ac1");

    if (tree->attr.op == LEQ) {
        emitRO("TLE", RT, AC, RT, "Op <=");
    }
    else if (tree->attr.op == LT) {
        emitRO("TLT", RT, AC, RT, "Op <");
    }
    else if (tree->attr.op == GEQ) {
        emitRO("TGE", RT, AC, RT, "Op >=");
    }
    else if (tree->attr.op == GT) {
        emitRO("TGT", RT, AC, RT, "Op >");
    }
    else if (tree->attr.op == EQ) {
        emitRO("TEQ", RT, AC, RT, "Op =");
    }
    else if (tree->attr.op == NEQ) {
        emitRO("TNE", RT, AC, RT, "Op ><");
    }
    else if (tree->attr.op == AND) {
        emitRO("AND", RT, AC, RT, "Op AND");
    }
    else if (tree->attr.op == OR) {
        emitRO("OR", RT, AC, RT, "Op OR");
    }

    if (tree->isParam && tree->oper == 0) {
        emitRM("ST", RT, temp_offset * -1, base_register, "Push parameter");
        emitComment("TOFF dec:", (++temp_offset) * -1);
    }
    else if (tree->oper != 0) {
        if (tree->oper == NOT) {
            emitRM("LDC", AC, 1, AC2, "Load 1");
            emitRO("XOR", RT, RT, AC, "Op XOR to get logical not");
        }

        emitRM("ST", RT, temp_offset * -1, base_register, "Push left side");
        emitComment("TOFF dec:", (++temp_offset) * -1);
    }

}



void generate_pop_left_var_indexed(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global) {
        base_register = 0;
    }

    emitComment("TOFF inc:", (--temp_offset) * -1);
    emitRM("LD", AC, temp_offset * -1, base_register, "Pop left into ac1");
    emitRO("SUB", RT, AC, RT, "compute location from index");
    emitRM("LD", RT, 0, RT, "Load array element");
}

int ADDASS = 279;
int SUBASS = 280;                  /* SUBASS  */
int MULASS = 281;                  /* MULASS  */
int DIVASS = 282;                  /* DIVASS  */
int INC = 283;                      /* INC  */
int DEC = 284;                      /* DEC  */

void generate_assign_op_lhs_load(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    char *op_string = NULL;

    if (tree->oper == ADDASS) {
        emitRM("LD", AC, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
        op_string = "op +=";
        emitRO("ADD", RT, AC, RT, op_string);
    }
    else if (tree->oper == SUBASS) {
        emitRM("LD", AC, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
        op_string = "op -=";
        emitRO("SUB", RT, AC, RT, op_string);
    }
    else if (tree->oper == DIVASS) {
        emitRM("LD", AC, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
        op_string = "op /=";
        emitRO("DIV", RT, AC, RT, op_string);
    }
    else if (tree->oper == MULASS) {
        emitRM("LD", AC, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
        op_string = "op *=";
        emitRO("MUL", RT, AC, RT, op_string);
    }
    else if (tree->oper == INC) {
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
        emitRM("LDA", RT, 1, RT, "increment value of", tree->attr.name);
    }
    else if (tree->oper == DEC) {
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
        emitRM("LDA", RT, -1, RT, "decrement value of", tree->attr.name);
    }

    else {
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
    }

    emitRM("ST", RT, tree->mem_offset * -1, base_register, "Store variable", tree->attr.name);
}

void generate_assign_op_lhs_load_indexed(TreeNode *tree, SymbolTable *symbol_table) {

    int base_register = GP;
    if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
        base_register = 0;
    }

    char *op_string = NULL;

    
    //op_string = "op *=";
    //op_string = "op /=";


    emitComment("TOFF inc:", (--temp_offset) * -1);
    emitRM("LD", AC, temp_offset * -1, GP, "Pop index");
    
    if (tree->var_kind == Parameter) {
        emitRM("LD", AC1, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
    }
    else {
        emitRM("LDA", AC1, tree->mem_offset * -1, base_register, "Load address of base of array", tree->attr.name);
    }

    emitRO("SUB", AC1, AC1, AC, "Compute offset of value");

    emitRM("LD", AC, 0, AC1, "load lhs variable", tree->attr.name);
    if (tree->oper == ADDASS) {
        op_string = "op +=";
        emitRO("ADD", RT, AC, RT, op_string);
    }
    else if (tree->oper == INC) {
        emitRM("LD", RT, tree->mem_offset * -1, base_register, "load lhs variable", tree->attr.name);
        emitRM("LDA", RT, 1, RT, "increment value of", tree->attr.name);
    }

    else if (tree->oper == SUBASS) {
        op_string = "op -=";
        emitRO("SUB", RT, AC, RT, op_string);
    }

    emitRM("ST", RT, 0, AC1, "Store variable", tree->attr.name);
}


int PLUS = 294; /* Bison PLUS  */
int MINUS = 295; /* Bison MINUS  */
int TIMES = 296; /* Bison TIMES  */
int DIV = 297;  /* Bison DIV  */
int MOD = 298;  /* Bison MOD  */

void generate_binary_op(TreeNode *tree, SymbolTable *symbol_table) {
     
    emitComment("TOFF inc:", (--temp_offset) * -1);
    emitRM("LD", AC, temp_offset * -1, GP, "Pop left into ac1");
    

    if (tree->attr.op == PLUS) {
        emitRO("ADD", RT, AC, RT, "Op +");
    } 
    else if (tree->attr.op == MINUS) {
        emitRO("SUB", RT, AC, RT, "Op -");
    }
    else if (tree->attr.op == TIMES) {  
        emitRO("MUL", RT, AC, RT, "Op *");
    }
    else if (tree->attr.op == DIV) {
        emitRO("DIV", RT, AC, RT, "Op /");
    }
    else if (tree->attr.op == MOD) {
        emitRO("MOD", RT, AC, RT, "Op %");
    }

    if (tree->isParam && tree->oper == 0) {
        emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
        emitComment("TOFF dec:", (++temp_offset) * -1);
    }
    else if (tree->oper != 0) {
        emitRM("ST", RT, temp_offset * -1, GP, "Push left side");
        emitComment("TOFF dec:", (++temp_offset) * -1);
    }

}

void generate_assign_push_parameter(TreeNode *tree, SymbolTable *symbol_table) {
    emitRM("ST", RT, temp_offset * -1, GP, "Push parameter");
    emitComment("TOFF dec:", (++temp_offset) * -1);
}

void generate_jump_to_while(TreeNode *tree, SymbolTable *symbol_table) {
    emitRM("JNZ", RT, 1, AC3, "Jump to while part");
    emitSkip(1);
}

void generate_while_statement_enter(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("WHILE");
    tree->program_counter_address = emitSkip(0);
}

void generate_while_do(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("DO");
    tree->program_counter_address = emitSkip(0);
}

void generate_while_statement_leave(TreeNode *tree, SymbolTable *symbol_table) {
    emitRM("JMP", AC3, (emitWhereAmI() - tree->program_counter_address + 1) * -1, AC3, "go to beginning of loop");
    
    int compound_address = 0;
    if (tree->child[1] != NULL) {
        compound_address = tree->child[1]->program_counter_address;
    }

    int jump_back = emitWhereAmI() - compound_address;

    emitNewLoc(compound_address - 1);
    emitRM("JMP", AC3, jump_back, AC3, "Jump past loop [backpatch]");

    emitSkip(jump_back);
}

void generate_if_statement_enter(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("IF");
    tree->program_counter_address = emitWhereAmI();
}

void generate_if_then_enter(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("THEN");
    tree->l1_patch = emitSkip(1);
}

void generate_if_else_enter(TreeNode *tree, SymbolTable *symbol_table) {
    tree->l2_patch = emitSkip(1);
}

void generate_if_then_leave(TreeNode *tree, SymbolTable *symbol_table) {

    
    if (tree->child[2] != NULL) {
        tree->l2_patch = emitSkip(1);
    }

    backPatchAJumpToHere("JZR", RT, tree->l1_patch, "Jump around the THEN if false [backpatch]");
    
    if (tree->child[2] != NULL) {
        emitComment("ELSE");
    }
    //emitNewLoc(then_pc);
    //emitRM("JZR", RT, jump_past, AC3, "Jump around the THEN if false [backpatch]");
    //emitSkip(jump_past + 1);
}


void generate_if_else_leave(TreeNode *tree, SymbolTable *symbol_table) {


    backPatchAJumpToHere(tree->l2_patch, "Jump around the ELSE [backpatch]");
    //emitNewLoc(else_pc);
    //emitRM("JMP", AC3, jump_past, AC3, "Jump around the ELSE [backpatch]");
    //emitSkip(jump_past);
}

void generate_break_statement(TreeNode *tree, SymbolTable *symbol_table) {
    
    emitComment("BREAK");
    int jump_back = emitWhereAmI() - (tree->program_counter_address - 2);

    emitRM("JMP", AC3, jump_back * -1, AC3, "break");

}

void generate_globals_enter(TreeNode *tree, SymbolTable *symbol_table) { 
    emitComment("INIT GLOBALS AND STATICS");
}

void generate_globals_leave(TreeNode *tree, SymbolTable *symbol_table) { 
    emitComment("END INIT GLOBALS AND STATICS");
}

void generate_for_statement_enter(TreeNode *tree, SymbolTable *symbol_table) {
    temp_offset = tree->dataword_size; 
    temp_offset_saved_stack[temp_offset_saved_stack_idx++] = temp_offset; /* Save the current temp_offset on the stack before entering a new scope */
    emitComment("TOFF set:", temp_offset * -1);
    emitComment("FOR");    
}

void generate_for_statement_leave(TreeNode *tree, SymbolTable *symbol_table) {
    emitComment("Bottom of loop increment and jump");

    TreeNode *id_node = tree->child[0];
    TreeNode *range_node = tree->child[1];
    TreeNode *compound_node = tree->child[2];


    emitRM("LD", RT, (id_node->mem_offset) * -1, GP, "Load index");
    emitRM("LD", AC1, (id_node->mem_offset + 2)* -1, GP, "Load step");
    emitRO("ADD", RT, 3, AC1, "increment");
    emitRM("ST", RT, (id_node->mem_offset) * -1, GP, "store back to index");
    

    emitGotoAbs(tree->l1_patch, "go to beginning of loop");
    backPatchAJumpToHere(tree->l2_patch, "Jump past loop [backpatch]");
    temp_offset = temp_offset_saved_stack[--temp_offset_saved_stack_idx]; /* Decrement the temp_offset_stack_idx, and restore the temp_offset value to what it was before entering this scope that is being exited */
    emitComment("END LOOP");
}

void generate_range_statement_enter(TreeNode *tree, SymbolTable *symbol_table) {
    tree->program_counter_address = emitWhereAmI();
}

void generate_range_statement_save_start(TreeNode *tree, SymbolTable *symbol_table) { 
    TreeNode *id_node = tree->child[0];
    TreeNode *range_node = tree->child[1];

    emitRM("ST", RT, id_node->mem_offset * -1, GP, "save starting value in index variable");
}

void generate_range_statement_save_stop(TreeNode *tree, SymbolTable *symbol_table) {
    TreeNode *id_node = tree->child[0];
    TreeNode *range_node = tree->child[1];

    emitRM("ST", RT, (id_node->mem_offset + 1) * -1, GP, "save stop value"); 
    
}

void generate_range_statement_save_step(TreeNode *tree, SymbolTable *symbol_table) {
    TreeNode *id_node = tree->child[0];
    TreeNode *range_node = tree->child[1];

    emitRM("ST", RT, (id_node->mem_offset + 2) * -1, GP, "save step value"); 
    tree->l1_patch = emitSkip(0);
}

void generate_range_statement_leave(TreeNode *tree, SymbolTable *symbol_table) {

    TreeNode *id_node = tree->child[0];
    TreeNode *range_node = tree->child[1];

    if (range_node->child[2] == NULL) {
        emitRM("LDC", RT, 1, AC2, "default increment by 1");
        emitRM("ST", RT, (id_node->mem_offset + 2) * -1, GP, "save step value");
        tree->l1_patch = emitSkip(0);
    }

    temp_offset--; //Variable i for loop does not affect temp_offset

    emitRM("LD", AC, (id_node->mem_offset) * -1, GP, "loop index");
    emitRM("LD", AC1, (id_node->mem_offset + 1) * -1, GP, "stop value");
    emitRM("LD", RT, (id_node->mem_offset + 2)* -1, GP, "step value");

    emitRO("SLT", RT, AC, AC1, "Op <");
    emitRM("JNZ", RT, 1, AC3, "Jump to loop body");
    
    tree->l2_patch = emitSkip(1);
}

void generate_call_unary_op(TreeNode *tree, SymbolTable *symbol_table) {
    // Unary op call
    if (tree->oper == NOT) {
            emitRM("LDC", AC, 1, AC2, "Load 1");
            emitRO("XOR", RT, RT, AC, "Op XOR to get logical not");
    }
}

void generate_code(code_generation_linearized_node_t *head, SymbolTable *symbol_table) {

    while (head != NULL) {
        switch (head->action) {
            case CG_FunctionDefineEnter:
                generate_function_define_enter(head->ast_node, symbol_table);
                break;
            case CG_FunctionDefineLeave:
                generate_function_define_leave(head->ast_node, symbol_table);
                break;
            case CG_FunctionCallEnter:
                generate_function_call_enter(head->ast_node, symbol_table);
                break;
            case CG_FunctionCallLeave:
                generate_function_call_leave(head->ast_node, symbol_table);
                break;
            case CG_CompoundStatementEnter:
                generate_compound_statement_enter(head->ast_node, symbol_table);
                break;
            case CG_CompoundStatementLeave:
                generate_compound_statement_leave(head->ast_node, symbol_table);
                break;
            case CG_LoadParameterConstant:
                generate_load_parameter_constant(head->ast_node, symbol_table);
                break;
            case CG_LoadParameterId:
                generate_load_parameter_id(head->ast_node, symbol_table);
                break;
            case CG_LoadConstant:
                generate_load_constant(head->ast_node, symbol_table);
                break;
            case CG_LoadVar:
                generate_load_var(head->ast_node, symbol_table);
                break;
            case CG_ReturnStatement:
                generate_return_statement(head->ast_node, symbol_table);
                break;
            case CG_InitEnter:
                generate_init_enter(head->ast_node, symbol_table);
                break;
            case CG_InitLeave:
                generate_init_leave(head->ast_node, symbol_table);
                break;
            case CG_GlobalsStaticsEnter:
                generate_globals_statics_enter(head->ast_node, symbol_table);
                break;
            case CG_GlobalsStaticsLeave:
                generate_globals_statics_leave(head->ast_node, symbol_table);
                break;
            case CG_AssignLHSLoad:
                generate_assign_lhs_load(head->ast_node, symbol_table);
                break;
            case CG_AssignLHSLoadIndexed:
                generate_assign_lhs_load_indexed(head->ast_node, symbol_table);
                break;
            case CG_AssignLHSPush:
                generate_assign_lhs_push(head->ast_node, symbol_table);
                break;
            case CG_VarDeclaration:
                generate_var_declartion(head->ast_node, symbol_table);
                break;
            case CG_VarArrayDeclaration:
                generate_var_array_declartion(head->ast_node, symbol_table);
                break;
            case CG_VarIndexPush:
                generate_var_indexed_push(head->ast_node, symbol_table);
                break;
            case CG_VarIndexParamLoad:
                generate_parameter_push_var_indexed(head->ast_node, symbol_table);
                break;
            case CG_VarLHSOpParamLoad:
                generate_parameter_push_var_lhs_op(head->ast_node, symbol_table);
                break;
            case CG_VarIndexLoad:
                generate_load_var_indexed(head->ast_node, symbol_table);
                break;
            case CG_PopLeftVarIndex:
                generate_pop_left_var_indexed(head->ast_node, symbol_table);
                break;
            case CG_AssignOpLHSLoadIndexed:
                generate_assign_op_lhs_load_indexed(head->ast_node, symbol_table);
                break;
            case CG_AssignOpLHSLoad:
                generate_assign_op_lhs_load(head->ast_node, symbol_table);
                break;
            case CG_BinaryOp:
                generate_binary_op(head->ast_node, symbol_table);
                break;
            case CG_AssignPushParameter:
                generate_assign_push_parameter(head->ast_node, symbol_table);
                break;
            case CG_JumpToWhile:
                generate_jump_to_while(head->ast_node, symbol_table);
                break;
            case CG_EnterWhile:
                generate_while_statement_enter(head->ast_node, symbol_table);
                break;
            case CG_LeaveWhile:
                generate_while_statement_leave(head->ast_node, symbol_table);
                break;
            case CG_DoWhile:
                generate_while_do(head->ast_node, symbol_table);
                break;
            case CG_EnterIf:
                generate_if_statement_enter(head->ast_node, symbol_table);
                break;
            case CG_EnterThen:
                generate_if_then_enter(head->ast_node, symbol_table);
                break;
            case CG_EnterElse:
                generate_if_else_enter(head->ast_node, symbol_table);
                break;
            case CG_LeaveThen:
                generate_if_then_leave(head->ast_node, symbol_table);
                break;
            case CG_LeaveElse:
                generate_if_else_leave(head->ast_node, symbol_table);
                break;
            case CG_BreakStatement:
                generate_break_statement(head->ast_node, symbol_table);
                break;
            case CG_GlobalsEnter:
                generate_globals_enter(head->ast_node, symbol_table);
                break;
            case CG_GlobalsLeave:
                generate_globals_leave(head->ast_node, symbol_table);
                break;
            case CG_ForEnter:
                generate_for_statement_enter(head->ast_node, symbol_table);
                break;
            case CG_ForLeave:
                generate_for_statement_leave(head->ast_node, symbol_table);
                break;
            case CG_RangeEnter:
                generate_range_statement_enter(head->ast_node, symbol_table);
                break;
            case CG_RangeSaveStart:
                generate_range_statement_save_start(head->ast_node, symbol_table);
                break;
            case CG_RangeSaveStop:
                generate_range_statement_save_stop(head->ast_node, symbol_table);
                break;
            case CG_RangeSaveStep:
                generate_range_statement_save_step(head->ast_node, symbol_table);
                break;
            case CG_RangeLeave:
                generate_range_statement_leave(head->ast_node, symbol_table);
                break;
            case CG_CallUnaryOp:
                generate_call_unary_op(head->ast_node, symbol_table);
                break;
            case CG_CommentOnly:
                if (head->comment_only_comment != NULL) {
                    emitComment(head->comment_only_comment);
                }
            default:
                break;
        }

        head = head->next;
    }



}

