/*
 * File: Semantic.h
 *
 *
 *
 *
 */

#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
#include "globals.h"
#include "symbolTable.h"
#include "yyerror.h"

void semantic_analysis(TreeNode * syntax_tree, SymbolTable * symbol_table);
void check_if_used(std::string name, void *ptr);
void print_all_found_errors();
void print_goffset();
int get_goffset();

TreeNode * init_io_library_ast();

#endif
