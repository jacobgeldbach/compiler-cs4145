/*
 * File: code_generation.h
 *
 *
 *
 *
 */

#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_

#include "globals.h"
#include "symbolTable.h"

typedef enum {
    CG_None,
    CG_CommentOnly,
    CG_FunctionDefineEnter,
    CG_FunctionDefineLeave,
    CG_FunctionCallEnter,
    CG_FunctionCallLeave,
    CG_CompoundStatementEnter,
    CG_CompoundStatementLeave,
    CG_LoadParameterConstant,
    CG_LoadParameterId,
    CG_LoadParameterLHS,
    CG_LoadConstant,
    CG_LoadVar,
    CG_ReturnStatement,
    CG_InitEnter,
    CG_InitLeave,
    CG_GlobalsStaticsEnter,
    CG_GlobalsStaticsLeave,
    CG_AssignLHSLoad,
    CG_AssignLHSLoadIndexed,
    CG_AssignLHSPush,
    CG_VarDeclaration,
    CG_VarArrayDeclaration,
    CG_VarIndexPush,
    CG_VarIndexParamLoad,
    CG_VarIndexLoad,
    CG_PopLeftVarIndex,
    CG_AssignOpLHSLoadIndexed,
    CG_AssignOpLHSLoad,
    CG_BinaryOp,
    CG_VarLHSOpParamLoad,
    CG_AssignPushParameter,
    CG_JumpToWhile,
    CG_EnterWhile,
    CG_LeaveWhile,
    CG_EnterIf,
    CG_EnterThen,
    CG_EnterElse,
    CG_LeaveThen,
    CG_LeaveElse,
    CG_BreakStatement,
    CG_GlobalsEnter,
    CG_GlobalsLeave,
    CG_DoWhile,
    CG_ForEnter,
    CG_RangeSaveStart,
    CG_RangeSaveStop,
    CG_RangeSaveStep,
    CG_RangeLeave,
    CG_ForLeave,
    CG_RangeEnter,
    CG_CallUnaryOp,

} code_generation_action_t;

typedef struct code_generation_linearized_node {

    code_generation_action_t action;
    TreeNode *ast_node;
    code_generation_linearized_node *prev;
    code_generation_linearized_node *next;

    char *comment_only_comment;
    
    /* function decl stuff */
    code_generation_linearized_node *array_decl;
    code_generation_linearized_node *static_globals_decl;
    int compound_node_idx;

    /* While node stuff */
    code_generation_linearized_node *while_do_part_node;

} code_generation_linearized_node_t;

extern code_generation_linearized_node_t *current_head;
extern code_generation_linearized_node_t *function_array_node_list;
extern code_generation_linearized_node_t *globals_statics_node_list;

extern code_generation_linearized_node_t *last_function_decl_node;

extern int last_compound_node_idx;
extern code_generation_linearized_node_t *last_compound_node[10];

extern int last_while_node_idx;
extern code_generation_linearized_node_t *last_while_node[10];

extern int last_if_node_idx;
extern code_generation_linearized_node_t *last_if_node[10];

extern int last_for_node_idx;
extern code_generation_linearized_node_t *last_for_node[10];

code_generation_linearized_node_t *initialize_temp_list();
code_generation_linearized_node_t *initialize_code_generation_list(TreeNode *tree);
void append_linearized_node(TreeNode *tree, code_generation_action_t action, code_generation_linearized_node_t *target_list);
void append_comment_node(char *comment, code_generation_linearized_node_t *target_list);
void insert_linearized_node(code_generation_linearized_node_t *node, code_generation_linearized_node_t *target);
code_generation_linearized_node_t *get_current_tail_node(code_generation_linearized_node_t *target_list);
void generate_code(code_generation_linearized_node_t *head, SymbolTable *symbol_table);
void reset_func_array_node_list();
void reset_globals_statics_node_list();
void append_globals_on_current_head();

void increment_temp_offset(int size);
int init_code_file(char *filename);
void generate_function_define_enter(TreeNode *tree, SymbolTable *symbol_table);
void generate_function_define_leave(TreeNode *tree, SymbolTable *symbol_table);
void generate_function_call_enter(TreeNode *tree, SymbolTable *symbol_table);
void generate_function_call_leave(TreeNode *tree, SymbolTable *symbol_table);
void generate_compound_statement_enter(TreeNode *tree, SymbolTable *symbol_table);
void generate_compound_statement_leave(TreeNode *tree, SymbolTable *symbol_table);
void generate_load_parameter_constant(TreeNode *tree, SymbolTable *symbol_table);
void generate_load_parameter_id(TreeNode *tree, SymbolTable *symbol_table);
void generate_load_constant(TreeNode *tree, SymbolTable *symbol_table);
void generate_load_var(TreeNode *tree, SymbolTable *symbol_table);
void generate_return_statement(TreeNode *tree, SymbolTable *symbol_table);
void generate_init_enter(TreeNode *tree, SymbolTable *symbol_table);
void generate_init_leave(TreeNode *tree, SymbolTable *symbol_table);
void generate_globals_statics_enter(TreeNode *tree, SymbolTable *symbol_table);
void generate_globals_statics_leave(TreeNode *tree, SymbolTable *symbol_table);
void generate_assign_lhs_load(TreeNode *tree, SymbolTable *symbol_table);
void generate_assign_lhs_load_indexed(TreeNode *tree, SymbolTable *symbol_table);
void generate_var_declartion(TreeNode *tree, SymbolTable *symbol_table);
void generate_var_array_declartion(TreeNode *tree, SymbolTable *symbol_table);
void generate_var_indexed_push(TreeNode *tree, SymbolTable *symbol_table);
void generate_parameter_push_var_indexed(TreeNode *tree, SymbolTable *symbol_table);

#endif
