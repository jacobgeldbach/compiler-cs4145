/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_
#include "scanType.h"
#include "symbolTable.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( OpKind op, const char* );

TreeNode *newDeclNode(DeclKind kind);

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode *newStmtNode(StmtKind kind); 

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode *newExpNode(ExpKind kind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree, bool with_types, bool with_memory_info );

const char *get_operator(OpKind op);

const char *get_type(ExpType type);

void linearize_ast(TreeNode * syntax_tree, SymbolTable * symbol_table);

#endif
