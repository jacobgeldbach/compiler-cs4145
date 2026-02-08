%{
/*
 * CS-4145 Section 71
 * Assignment 2: C- recognizer + AST builder
 * File: parsey.y - Bison parser file
 * Author: Jacob A. Geldbach
 * Date: 09/16/2025
 */
#include "scanType.h"  /* token_data_t */
#include <stdio.h>
#include <cstring>
#include "globals.h"
#include "util.h"
#include "symbolTable.h"
#include "yyerror.h"
#include "semantic.h"
#include "ourgetopt.h"  /* ourgetopt() */

extern int yylex();
extern FILE *yyin;
extern int line_num;		/* Error line number from the scanner */
extern bool syntax_errors;
int func_decl_saved_line_num;
char *saved_name;

ExpType saved_exp_type;
TreeNode *syntaxTree;

%}
%define parse.error verbose

%union {
    ExpType type;
    token_data_t *token_data;
    TreeNode *tree_node;
    OpKind op;
}

%type <tree_node> program decl_list decl var_decl func_decl var_decl_list params compound_stmt var_decl_init var_decl_id simple_exp and_exp unary_rel_exp rel_exp
%type <tree_node> sum_exp mul_exp unary_exp factor mutable immutable exp args arg_list call constant param_list param_type_list param_id_list param_id
%type <tree_node> stmt matched_stmt unmatched_stmt matched_select_stmt unmatched_select_stmt matched_iter_stmt unmatched_iter_stmt exp_stmt return_stmt break_stmt
%type <tree_node> iter_range local_decls stmt_list scoped_var_decl
%type <op> sum_op mul_op rel_op assign_op unary_op
%type <type> type_spec                                          /* <type> referring to the ExpType type in our union above */
%token <token_data> ID NUMBERCONST CHARCONST STRINGCONST
%token <token_data> BOOL INT CHAR 
%token <token_data> TRUE FALSE STATIC
%token <token_data> IF ELSE THEN RETURN BREAK
%token <token_data> TO BY DO FOR WHILE
%token <token_data> ASGN ADDASS SUBASS MULASS DIVASS INC DEC
%token <token_data> OR AND NOT LT LEQ GT GEQ EQ NEQ
%token <token_data> PLUS MINUS TIMES DIV MOD TERNARY CHSIGN SIZEOF 
%token <token_data> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA COLON SEMI END

%%
program     : decl_list { syntaxTree = $1; }
	        ;

decl_list   : decl_list decl {
                TreeNode * t = $1;

                if (t != NULL) {
                    while (t->sibling != NULL) {    /* decl_list, so iterate to the tail of the list */
                        t = t->sibling;             
                    }
                    t->sibling = $2;                /* append new decl to the end of the list */
                    $$ = $1;                        /* assign the starting tree_node *, front of the list, to left-hand side */
                } else {
                    $$ = $2;                        /* if first decl, assign to left-hand side */
                }
            }
	        | decl { $$ = $1; }                       /* first decl, assign to left-hand side */
	        ;

decl        : var_decl { $$ = $1; } 
	        | func_decl { $$ = $1; }
            | error { $$ = NULL; }
	        ;

var_decl    : type_spec var_decl_list SEMI {
                TreeNode * t = $2;

                while (t != NULL) {               /* var_decl_list, so iterate through the list */
                    t->type = $1;                 /* set type_spec terminal type for each var_decl */
                    t->var_kind = Global;          /* set variable kind to Global */
                    t = t->sibling;               /* move to next var_decl in the list */
                }
                $$ = $2;                         /* assign the starting tree_node *, front of the list, to left-hand side */
                yyerrok;
            }
            | error var_decl_list SEMI { $$ = NULL; yyerrok; }
            | type_spec error SEMI { $$ = NULL; yyerrok; yyerrok; }
            ;

scoped_var_decl     : STATIC type_spec var_decl_list SEMI {
                        TreeNode * t = $3;
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = $2;                   /* set type_spec terminal type for each var_decl */
                            t->isStatic = true;             /* mark as static */
                            t->var_kind = LocalStatic;      /* set variable kind to LocalStatic */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        $$ = $3;                          /* assign the starting tree_node *, front of the list, to left-hand side */
                        yyerrok;
                    }
		            | type_spec var_decl_list SEMI {
                        TreeNode * t = $2;
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = $1;                   /* set type_spec terminal type for each var_decl */
                            t->var_kind = Local;            /* mark as Local reference type */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        $$ = $2;                          /* assign the starting tree_node *, front of the list, to left-hand side */
                        yyerrok;
                    }
		            ;

var_decl_list       : var_decl_list COMMA var_decl_init {
                        TreeNode * t = $1;

                        if (t != NULL) {
                            while (t->sibling != NULL) {        /* var_decl_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = $3;                    /* append new var_decl_init to the end of the list */   
                            $$ = $1;                            /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            $$ = $3;                            /* if first var_decl_init, assign to left-hand side */
                        }
                        yyerrok;
                    }
	                | var_decl_init { $$ = $1; }
                    | var_decl_list COMMA error { $$ = NULL; }
                    | error                     { $$ = NULL; }
	                ;

var_decl_init       : var_decl_id COLON simple_exp { 
                        TreeNode * t = $1;
                        TreeNode * init = $3;
                        
                        init->initializer = true;
                        if ($3->subkind.exp == ConstantK) {
                            /* If the initializer is a constant, set the variable's isInitializedWithConstant flag to true */
                            init->isConstant = true;
                        }
                        
                        if (t != NULL) {
                            t->isInitialized = true;        /* mark as initialized */
                            t->child[0] = init;             /* simple_exp */
                        }

                        init->param_sibling = t;        /* tie the initializer to the variable it is initiallizing */
                        $$ = t;                         /* assign new TreeNode* to left-hand side */
                    }
                    | error ':' simple_exp  { $$ = NULL; yyerrok; }
	                | var_decl_id           { $$ = $1; }
                    ;

var_decl_id         : ID {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->lineno = $1->line_num;   /* set variable declaration line number to that of when the ID was scanned */
                        t->dataword_size = 1;       /* default dataword size to 1 */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    } 
	                | ID LBRACKET NUMBERCONST RBRACKET {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = $1->svalue;          /* ID name comes from token_data_t svalue member */
                        t->isArray = true;                  /* mark as array variable */
                        t->lineno = $1->line_num;           /* set variable declaration line number to that of when the ID was scanned */
                        t->dataword_size = $3->nvalue + 1;  /* set dataword size to the size specified by the NUMBERCONST + 1 as arrays first dataword will be the size of the array itself */
                        $$ = t;                             /* assign new TreeNode to left-hand side */
                    }
                    | ID LBRACKET error         { $$ = NULL; }
                    | error RBRACKET            { $$ = NULL; yyerrok; }
	                ;

type_spec           : BOOL { $$ = Boolean; }
	                | CHAR { $$ = Char; }
	                | INT  { $$ = Integer; }
	                ;

func_decl           : type_spec ID LPAREN params RPAREN compound_stmt {
                        TreeNode * t = newDeclNode(FuncK);
                        t->type = $1;                               /* type_spec terminal type */
                        t->attr.name = strdup($2->svalue);          /* ID name comes from token_data_t svalue member */
                        t->lineno = $2->line_num;                   /* set function declaration line number to that of when the function name was scanned */
                        t->child[0] = $4;                           /* params */
                        t->child[1] = $6;                           /* compound_stmt */
                        t->child[1]->param_sibling = t->child[0];   /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */

                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
	                | ID LPAREN params RPAREN compound_stmt {
                        TreeNode * t = newDeclNode(FuncK);
                        t->type = Void;                     /* default to Void type if no type_spec */
                        t->attr.name = strdup($1->svalue);  /* ID name comes from token_data_t svalue member */
                        t->lineno = $1->line_num;           /* set function declaration line number to that of when the function name was scanned */
                        t->child[0] = $3;           /* params */
                        t->child[1] = $5;           /* compound_stmt */
                        t->child[1]->param_sibling = t->child[0];   /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        $$ = t;                     /* assign new TreeNode to left-hand side */

                    }
                    | type_spec error                               { $$ = NULL; }
                    | type_spec ID LPAREN error                     { $$ = NULL; }
                    | ID LPAREN error                               { $$ = NULL; }
                    | ID LPAREN params RPAREN error                 { $$ = NULL; }
	                ;

params              : param_list { $$ = $1; }
	                | { $$ = NULL; } /* Empty, representing ε in our grammar, nullify this leaf of the tree */
                    ;

param_list          : param_list SEMI param_type_list {
                        TreeNode * t = $1;

                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* param_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = $3;                /* append new param_type_list to the end of the list */ 
                            $$ = $1;                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            $$ = $3;                        /* if first param_type_list, assign to left-hand side */
                        }
                    }
                    | param_type_list           { $$ = $1; }
                    | param_list SEMI error     { $$ = NULL; }
                    | error                     { $$ = NULL; }
                    ;

param_type_list     : type_spec param_id_list {
                        TreeNode * t = $2;
                        while (t != NULL) {               /* param_id_list, so iterate through the list */
                            t->type = $1;                 /* set type_spec terminal type for each param_id */
                            t = t->sibling;               /* move to next param_id in the list */
                        }
                        $$ = $2;                         /* assign the starting tree_node *, front of the list, to left-hand side */
                    }
                    | type_spec error           { $$ = NULL; }
                    ;

param_id_list       : param_id_list COMMA param_id {
                        TreeNode * t = $1;

                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* param_id_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = $3;                /* append new param_id to the end of the list */
                            $$ = $1;                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            $$ = $3;                        /* if first param_id, assign to left-hand side */
                        }
                        yyerrok;
                    }
                    | param_id                      { $$ = $1; }
                    | param_id_list COMMA error     { $$ = NULL; }
                    | error                         { $$ = NULL; }
                    ;

param_id            : ID LBRACKET RBRACKET {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->isArray = true;          /* mark as array parameter */
                        t->var_kind = Parameter;
                        t->dataword_size = 1;      /* all param dataword_size will be 1 since pass by reference */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | ID {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->var_kind = Parameter;
                        t->dataword_size = 1;      /* all param dataword_size will be 1 since pass by reference */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    ;

stmt                : matched_stmt { $$ = $1; }
                    | unmatched_stmt { $$ = $1; }
                    ;

matched_stmt        : matched_iter_stmt { $$ = $1; }
                    | matched_select_stmt { $$ = $1; }
                    | compound_stmt { $$ = $1; }
                    | exp_stmt { $$ = $1; }
                    | return_stmt { $$ = $1; }
                    | break_stmt { $$ = $1; }
                    ;

unmatched_stmt      : unmatched_iter_stmt { $$ = $1; }
                    | unmatched_select_stmt { $$ = $1; }
                    ;

matched_select_stmt : IF simple_exp THEN matched_stmt ELSE matched_stmt {
                        TreeNode * t = newStmtNode(IfK);
                        t->child[0] = $2;   /* simple_exp */
                        t->child[1] = $4;   /* matched_stmt for THEN */
                        t->child[2] = $6;   /* matched_stmt for ELSE */
                        t->lineno = $2->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | IF error                                          { $$ = NULL; }
                    | IF error ELSE matched_stmt                        { $$ = NULL; yyerrok; }
                    | IF error THEN matched_stmt ELSE matched_stmt      { $$ = NULL; yyerrok; }
                    ;

unmatched_select_stmt   : IF simple_exp THEN stmt {
                            TreeNode * t = newStmtNode(IfK);
                            t->child[0] = $2;   /* simple_exp */
                            t->child[1] = $4;   /* matched_stmt for THEN */
                            t->lineno = $2->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                            $$ = t;             /* assign new TreeNode to left-hand side */
                        }
                        | IF simple_exp THEN matched_stmt ELSE unmatched_stmt {
                            TreeNode * t = newStmtNode(IfK);
                            t->child[0] = $2;   /* simple_exp */
                            t->child[1] = $4;   /* matched_stmt for THEN */
                            t->child[2] = $6;   /* unmatched_stmt for ELSE */
                            t->lineno = $2->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                            $$ = t;             /* assign new TreeNode to left-hand side */
                        }
                        ;

exp_stmt            : exp SEMI { $$ = $1; }
                    | SEMI { $$ = NULL; }
                    | error SEMI { $$ = NULL; yyerrok; }
                    ;

compound_stmt       : LBRACE local_decls stmt_list RBRACE {
                        TreeNode * t = newStmtNode(CompoundK);
                        t->lineno = $1->line_num;   /* set compound statement line number to that of when the '{' was scanned */
                        t->child[0] = $2;           /* local_decls */
                        t->child[1] = $3;           /* stmt_list */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                        yyerrok;
                    }
                    ;

local_decls         : local_decls scoped_var_decl { 
                        TreeNode * t = $1;

                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* local_decls, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = $2;                /* append new scoped_var_decl to the end of the list */
                            $$ = $1;                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            $$ = $2;                        /* if first scoped_var_decl, assign to left-hand side */    
                        }
                    }
                    | {$$ = NULL; } /* Empty, representing ε in our grammar, nullify this leaf of the tree */
                    ;

stmt_list           : stmt_list stmt {
                        TreeNode * t = $1;

                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* stmt_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = $2;                /* append new stmt to the end of the list */
                            $$ = $1;                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            $$ = $2;                        /* if first stmt, assign to left-hand side */
                        }
                    }
                    | { $$ = NULL; } /* Empty, representing ε in our grammar, nullify this leaf of the tree */
                    ;


matched_iter_stmt   : WHILE simple_exp DO matched_stmt {
                        TreeNode * t = newStmtNode(WhileK);
                        t->child[0] = $2;   /* simple_exp */
                        t->child[1] = $4;   /* matched_stmt */
                        
                        if (t->child[1] != NULL) {
                            t->child[1]->isLoop = true;
                        }

                        if ($2 != NULL) {
                            t->lineno = $2->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        }

                        if ($4 != NULL) {
                            t->child[1]->param_sibling = t->child[0]; /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        }

                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | FOR ID ASGN iter_range DO matched_stmt {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * init = newDeclNode(VarK);
                        init->isInitialized = true;      /* loop variable is initialized by the iter_range */
                        init->attr.name = $2->svalue;    /* ID name comes from token_data_t svalue member */
                        init->type = Integer;
                        init->var_kind = Local;
                        init->dataword_size = 1;
                        t->var_kind = None;
                        t->child[0] = init;              /* loop variable ID and iter_range become siblings */
                        t->child[1] = $4;                /* iter_range */
                        t->child[2] = $6;                /* matched_stmt becomes the first child of the iter_range child */
                        if (t->child[2] != NULL) {
                            t->child[2]->isLoop = true;
                        }

                        if ($6 != NULL) {
                            t->child[2]->param_sibling = t->child[0]; /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        }
                        
                        t->lineno = $1->line_num;          /* set for loop line number to that of when the iter_range was scanned */
                        init->lineno = $2->line_num;     /* set loop variable ID line number to that of when the iter_range was scanned */
                        $$ = t;                          /* assign new TreeNode to left-hand side */
                    }
                    | WHILE error DO matched_stmt           { $$ = NULL; yyerrok; }
                    | WHILE error                           { $$ = NULL; }
                    | FOR ID ASGN error DO matched_stmt     { $$ = NULL; yyerrok; }
                    | FOR error                             { $$ = NULL; }
                    ;

unmatched_iter_stmt : WHILE simple_exp DO unmatched_stmt {
                        TreeNode * t = newStmtNode(WhileK);
                        t->child[0] = $2;   /* simple_exp */
                        t->child[1] = $4;   /* unmatched_stmt */
                        t->lineno = $1->line_num;  /* set while loop line number to that of when the simple_exp was scanned */
                        
                        if ($2 != NULL) {
                            t->lineno = $2->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        }

                        if (t->child[1] != NULL) {
                            t->child[1]->isLoop = true;
                        }

                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | FOR ID ASGN iter_range DO unmatched_stmt {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * init = newDeclNode(VarK);
                        init->isInitialized = true;      /* loop variable is initialized by the iter_range */
                        init->attr.name = $2->svalue;  /* ID name comes from token_data_t svalue member */
                        init->type = Integer;
                        init->var_kind = Local;
                        init->dataword_size = 1;

                        t->var_kind = None;
                        t->child[0] = init;            /* loop variable ID and iter_range become siblings */
                        t->child[1] = $4;                /* iter_range */
                        t->child[2] = $6;                /* unmatched_stmt */
                        t->child[2]->param_sibling = t->child[0]; /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        t->lineno = $1->line_num;          /* set for loop line number to that of when the iter_range was scanned */
                        init->lineno = $2->line_num;     /* set loop variable ID line number to that of when the iter_range was scanned */
                        
                        if (t->child[2] != NULL) {
                            t->child[2]->isLoop = true;
                        }

                        $$ = t;                          /* assign new TreeNode to left-hand side */
                    }
                    | IF error THEN unmatched_stmt                      { $$ = NULL; yyerrok; }
                    | IF error THEN matched_stmt ELSE unmatched_stmt    { $$ = NULL; yyerrok; }
                    ;
                    
iter_range          : simple_exp TO simple_exp {
                        TreeNode * t = newStmtNode(RangeK);
                        t->child[0] = $1;   /* start expression */
                        t->child[1] = $3;   /* end expression */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | simple_exp TO simple_exp BY simple_exp {
                        TreeNode * t = newStmtNode(RangeK);
                        t->child[0] = $1;   /* start expression */
                        t->child[1] = $3;   /* end expression */
                        t->child[2] = $5;   /* step expression */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | simple_exp TO error               { $$ = NULL; }
                    | error BY error                    { $$ = NULL; yyerrok; }
                    | simple_exp TO simple_exp BY error { $$ = NULL; } 
                    ;

return_stmt         : RETURN SEMI {
                        TreeNode * t = newStmtNode(ReturnK);
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | RETURN exp SEMI {
                        TreeNode * t = newStmtNode(ReturnK);
                        t->child[0] = $2;   /* exp */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                        yyerrok;
                    }
                    | RETURN error SEMI { $$ = NULL; yyerrok; }
                    ;

break_stmt          : BREAK SEMI {
                        TreeNode * t = newStmtNode(BreakK);
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    ;

exp                 : mutable assign_op exp { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = $1;   /* mutable */
                        t->child[1] = $3;   /* exp */
                        t->attr.op = $2;    /* assignment operator from assign_op */
                        
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | mutable INC { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = $1;   /* mutable */
                        t->attr.op = INC;   /* increment operator */
                        t->type = Integer;  /* set type to Integer for increment operator */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | mutable DEC { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = $1;   /* mutable */
                        t->attr.op = DEC;   /* decrement operator */
                        t->type = Integer;  /* set type to Integer for decrement operator */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | simple_exp { $$ = $1; }                    
                    | error assign_op exp       { $$ = NULL; yyerrok; }
                    | mutable assign_op error   { $$ = NULL; }
                    | error DEC                 { $$ = NULL; yyerrok; }
                    | error INC                 { $$ = NULL; yyerrok; }
                    ;

assign_op           : ASGN   { $$ = ASGN; }
                    | ADDASS { $$ = ADDASS; }
                    | SUBASS { $$ = SUBASS; }
                    | MULASS { $$ = MULASS; }
                    | DIVASS { $$ = DIVASS; }
                    ;

simple_exp          : simple_exp OR and_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = OR;        /* OR operator */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = $1;       /* left operand */
                        t->child[1] = $3;       /* right operand */
                        $$ = t;
                    }
                    | and_exp { $$ = $1; }
                    | simple_exp OR error { $$ = NULL; }
                    ;

and_exp             : and_exp AND unary_rel_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = AND;       /* AND operator */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = $1;       /* left operand */
                        t->child[1] = $3;       /* right operand */
                        $$ = t;
                    }
                    | unary_rel_exp { $$ = $1; }
                    | and_exp AND error { $$ = NULL; }
                    ;

unary_rel_exp       : NOT unary_rel_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = NOT;   /* NOT operator */
                        t->child[0] = $2;   /* operand */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        $$ = t;
                    }
                    | rel_exp           { $$ = $1; }
                    | NOT error         { $$ = NULL; }
                    ;

rel_exp             : sum_exp rel_op sum_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = $2;        /* relational operator from rel_op */
                        t->child[0] = $1;       /* left operand */
                        t->child[1] = $3;       /* right operand */
                        $$ = t;
                    }
                    | sum_exp { $$ = $1; }
                    ;

rel_op              : LT    { $$ = LT; }
                    | LEQ   { $$ = LEQ; }
                    | GT    { $$ = GT; }
                    | GEQ   { $$ = GEQ; }
                    | EQ    { $$ = EQ; }
                    | NEQ   { $$ = NEQ; }
                    ;

sum_exp             : sum_exp sum_op mul_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = $2;        /* sum operator from sum_op */
                        t->type = UndefinedType;
                        t->child[0] = $1;       /* left operand */
                        t->child[1] = $3;       /* right operand */
                        $$ = t;
                    }
                    | mul_exp { $$ = $1; }
                    | sum_exp sum_op error { $$ = NULL; }
                    ;

sum_op              : PLUS { $$ = PLUS; }
                    | MINUS { $$ = MINUS; }
                    ;

mul_exp             : mul_exp mul_op unary_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = $2;            /* multiplication operator from mul_op */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = $1;           /* left operand */
                        t->child[1] = $3;           /* right operand */
                        $$ = t;
                    }
                    | unary_exp { $$ = $1; }
                    | mul_exp mul_op error { $$ = NULL; }
                    ;

mul_op              : TIMES { $$ = TIMES; }
                    | DIV   { $$ = DIV; }
                    | MOD   { $$ = MOD; }
                    ;

unary_exp           : unary_op unary_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = $1;            /* unary operator from unary_op */
                        t->type = UndefinedType;
                        t->child[0] = NULL;         /* unary operator has no left operand */
                        t->child[1] = $2;           /* operand */
                        $$ = t;
                    }
                    | factor { $$ = $1; }
                    | unary_op error { $$ = NULL; }
                    ;

unary_op            : MINUS     { $$ = CHSIGN; }
                    | TIMES     { $$ = SIZEOF; }
                    | TERNARY   { $$ = TERNARY; }
                    ;

factor              : mutable   { $$ = $1; }
                    | immutable { $$ = $1; }
                    ;

mutable             : ID LBRACKET exp RBRACKET {
                        TreeNode * t = newExpNode(OpK);
                        TreeNode * id = newExpNode(IdK);    /* create tree_node for first child */
                        id->attr.name = $1->svalue;     /* ID name comes from token_data_t svalue member */
                        t->attr.op = LBRACKET;          /* array access operator */
                        t->child[0] = id;               
                        t->child[1] = $3;               /* index expression */
                        t->type = UndefinedType;             /* set type to that of the lhs */
                        $$ = t;                         /* assign new TreeNode to left-hand side */
                    }
                    | ID {
                        TreeNode * t = newExpNode(IdK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    ;

immutable           : LPAREN exp RPAREN { $$ = $2; yyerrok; }
                    | call { $$ = $1; }
                    | constant { $$ = $1; }
                    | LPAREN error { $$ = NULL; }
                    ;

call                : ID LPAREN args RPAREN {
                        TreeNode * t = newExpNode(CallK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->child[0] = $3;           /* args */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | error LPAREN          { $$ = NULL; yyerrok; }
                    ;

args                : arg_list { $$ = $1; }
                    | { $$ = NULL; }                 /* Empty, representing ε in our grammar, nullify the left handside and this leaf of the tree */
                    ;

arg_list            : arg_list COMMA exp {
                        TreeNode * t = $1;

                        if (t != NULL) {
                            while (t->sibling != NULL) {
                                t = t->sibling;
                            }
                            t->sibling = $3;
                            $$ = $1; 
                        } else {
                            $$ = $3;
                        }
                        yyerrok;
                    }
                    | exp { $$ = $1; }
                    | arg_list COMMA error { $$ = NULL; }
                    ;

constant            : NUMBERCONST {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Integer;          /* set type to Integer */
                        t->attr.value = $1->nvalue; /* value from token_data_t nvalue member */
                        t->isConstant = true;
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | CHARCONST {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Char;             /* set type to Char */
                        t->attr.cvalue = $1->cvalue; /* value from token_data_t cvalue member */
                        t->isConstant = true;
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | STRINGCONST {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Char;                 /* set type to String */
                        t->isArray = true;            /* mark as array to represent string */
                        t->attr.string = $1->svalue;    /* string from token_data_t svalue member */
                        t->isConstant = true;
                        $$ = t;                         /* assign new TreeNode to left-hand side */
                    }
                    | TRUE { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 1;          /* TRUE represented as 1 */
                        t->isConstant = true;
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | FALSE { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 0;          /* FALSE represented as 0 */
                        t->isConstant = true;
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    ;

%%

extern int yydebug;
int main(int argc, char *argv[])
{
    char opt;
    char *optstring = "pdPDM"; // Options: a, b (requires an argument), c (requires an argument)
    int printTreeFlag = 0;
    int printTreeTypeFlag = 0;
    int symbolDebugFlag = 0;
    int printTreeMemoryFlag = 0;
    int args = 0;
    while ((opt = ourGetopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'p':
                printTreeFlag = 1;
                args++;
                break;
            case 'd':
                yydebug = 1;
                args++;
                break;
            case 'P':
                printTreeTypeFlag = 1;
                args++;
                break;
            case 'D':
                symbolDebugFlag = 1;
                args++;
                break;
            case 'M':
                printTreeMemoryFlag = 1;
                args++;
                break;
            case '?':
                fprintf(stderr, "Unknown option -%c.\n", optopt);
                break;
        }
    }
    
    num_errors = 0;
    num_warnings = 0;

    initErrorProcessing();

    if (argc-args > 1) {
        if ((yyin = fopen(argv[argc - 1], "r"))) {
            // file open successful
        }
        else {
            // failed to open fie
            printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[argc - 1]);
            
            num_errors++;
            printf("Number of warnings: %d\n", num_warnings);
            printf("Number of errors: %d\n", num_errors);
            return 1;
        }
    }

    /* Parse */
    yyparse();

    if (syntax_errors == false) {
        SymbolTable *symbol_table = new SymbolTable();              /* Create the symbol table */ 
    
        TreeNode * io_library_ast = new TreeNode();                 /* Create a dummy root node for the I/O library AST */
        io_library_ast = init_io_library_ast();                        /* Initialize the I/O library AST and populate the symbol table with I/O functions */
    
        semantic_analysis(io_library_ast, symbol_table);            /* Perform semantic analysis on the I/O library AST to populate the symbol table with this libraries function decls */

        /* This also default enters us into the Global scope */
        if (symbolDebugFlag) {
            symbol_table->debug(true);                              /* Enable debug mode for the symbol table */
        }

        semantic_analysis(syntaxTree, symbol_table);                /* Perform semantic analysis and build the symbol table */
            
        /* Check for unused functions in the global scope */
        symbol_table->applyToAll(check_if_used);

        print_all_found_errors();

        TreeNode * main_func_node = (TreeNode *) symbol_table->lookupGlobal("main");
    
        if (main_func_node != NULL) {
            if (main_func_node->nodekind == DeclK && main_func_node->subkind.decl == FuncK) {    
                /* Main function found, can't have params */
                if (main_func_node->child[0] != NULL) {
                    printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
                    num_errors++;
                }
            }
            else {
                printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
                num_errors++;
            }
        }
        else {
            printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
            num_errors++;
        }
    }
    
    if (num_errors == 0 && syntax_errors == false) {
        if (printTreeFlag) {
            printTree(syntaxTree, false, false); /* Print the syntax tree */
        }

        if (printTreeTypeFlag) {
            printTree(syntaxTree, true, false); /* Print the syntax tree with types no memory usage*/
        }

        if (printTreeMemoryFlag) {
            printTree(syntaxTree, true, true); /* Print the syntax tree memory usage and types */
        }

        print_goffset();
    }


    printf("Number of warnings: %d\n", num_warnings);
    printf("Number of errors: %d\n", num_errors);   
    
    return 0;
}

/*


*/
