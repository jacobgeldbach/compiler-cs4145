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

#include "ourgetopt.h"  /* ourgetopt() */

extern int yylex();
extern FILE *yyin;
extern int line_num;		/* Error line number from the scanner */
int compound_stmt_saved_line_num[100];
int compound_stmt_saved_line_num_index = 0;
int func_decl_saved_line_num;
char *saved_name;


ExpType saved_exp_type;
extern int num_errors;    	/* Error count */
TreeNode *syntaxTree;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line_num, msg);
    num_errors++;
}

%}

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
%token <token_data> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA COLON SEMI

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
	        | decl { $$ = $1;                       /* first decl, assign to left-hand side */ }
	        ;

decl        : var_decl { $$ = $1; } 
	        | func_decl { $$ = $1; }
	        ;

var_decl    : type_spec var_decl_list SEMI {
                TreeNode * t = $2;
                while (t != NULL) {               /* var_decl_list, so iterate through the list */
                    t->type = $1;                 /* set type_spec terminal type for each var_decl */
                    t = t->sibling;               /* move to next var_decl in the list */
                }
                $$ = $2;                         /* assign the starting tree_node *, front of the list, to left-hand side */
            }
            ;

scoped_var_decl     : STATIC type_spec var_decl_list SEMI {
                        TreeNode * t = $3;
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = $2;                   /* set type_spec terminal type for each var_decl */
                            t->isStatic = true;             /* mark as static */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        $$ = $3;                          /* assign the starting tree_node *, front of the list, to left-hand side */
                    }
		            | type_spec var_decl_list SEMI {
                        TreeNode * t = $2;
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = $1;                   /* set type_spec terminal type for each var_decl */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        $$ = $2;                          /* assign the starting tree_node *, front of the list, to left-hand side */
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
                    }
	                | var_decl_init { $$ = $1; }
	                ;

var_decl_init       : var_decl_id COLON simple_exp { 
                        TreeNode * t = $1;
                        t->child[0] = $3;   /* simple_exp */
                        $$ = t;             /* assign new TreeNode* to left-hand side */
                    }
	                | var_decl_id { $$ = $1; } 
                    ;

var_decl_id         : ID {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->lineno = $1->line_num;  /* set variable declaration line number to that of when the ID was scanned */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    } 
	                | ID LBRACKET NUMBERCONST RBRACKET {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->lineno = $1->line_num;  /* set variable declaration line number to that of when the ID was scanned */
                        t->isArray = true;          /* mark as array */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
	                ;

type_spec           : BOOL { $$ = Boolean; }
	                | CHAR { $$ = Char; }
	                | INT  { $$ = Integer; }
	                ;

func_decl           : type_spec ID LPAREN params RPAREN compound_stmt {
                        TreeNode * t = newDeclNode(FuncK);
                        t->type = $1;                           /* type_spec terminal type */
                        t->attr.name = strdup($2->svalue);              /* ID name comes from token_data_t svalue member */
                        t->lineno = $2->line_num;               /* set function declaration line number to that of when the function name was scanned */
                        t->child[0] = $4;                       /* params */
                        t->child[1] = $6;           /* compound_stmt */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
	                | ID LPAREN params RPAREN compound_stmt {
                        TreeNode * t = newDeclNode(FuncK);
                        t->type = Void;                     /* default to Void type if no type_spec */
                        t->attr.name = strdup($1->svalue);  /* ID name comes from token_data_t svalue member */
                        t->lineno = $1->line_num;           /* set function declaration line number to that of when the function name was scanned */
                        t->child[0] = $3;           /* params */
                        t->child[1] = $5;           /* compound_stmt */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
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
                    | param_type_list { $$ = $1; }
                    ;

param_type_list     : type_spec param_id_list {
                        TreeNode * t = $2;
                        while (t != NULL) {               /* param_id_list, so iterate through the list */
                            t->type = $1;                 /* set type_spec terminal type for each param_id */
                            t = t->sibling;               /* move to next param_id in the list */
                        }
                        $$ = $2;                         /* assign the starting tree_node *, front of the list, to left-hand side */
                    }
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
                    }
                    | param_id { $$ = $1; }
                    ;

param_id            : ID LBRACKET RBRACKET {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->isArray = true;          /* mark as array parameter */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | ID {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
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
                    | SEMI { 
                        $$ = NULL;             /* empty exp_stmt represented by ExpK node with no children */
                    }
                    ;

compound_stmt       : LBRACE local_decls stmt_list RBRACE {
                        TreeNode * t = newStmtNode(CompoundK);
                        t->lineno = $1->line_num;   /* set compound statement line number to that of when the '{' was scanned */
                        t->child[0] = $2;           /* local_decls */
                        t->child[1] = $3;           /* stmt_list */
                        $$ = t;             /* assign new TreeNode to left-hand side */
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
                        t->lineno = $2->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | FOR ID ASGN iter_range DO matched_stmt {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * idNode = newDeclNode(VarK);
                        idNode->attr.name = $2->svalue;  /* ID name comes from token_data_t svalue member */
                        t->child[0] = idNode;            /* loop variable ID and iter_range become siblings */
                        t->child[1] = $4;                /* iter_range */
                        t->child[2] = $6;                /* matched_stmt becomes the first child of the iter_range child */
                        t->lineno = $4->lineno;          /* set for loop line number to that of when the iter_range was scanned */
                        idNode->lineno = $4->lineno;          /* set loop variable ID line number to that of when the iter_range was scanned */
                        $$ = t;                          /* assign new TreeNode to left-hand side */
                    }
                    ;

unmatched_iter_stmt : WHILE simple_exp DO unmatched_stmt {
                        TreeNode * t = newStmtNode(WhileK);
                        t->child[0] = $2;   /* simple_exp */
                        t->child[1] = $4;   /* unmatched_stmt */
                        t->lineno = $2->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | FOR ID ASGN iter_range DO unmatched_stmt {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * idNode = newDeclNode(VarK);
                        idNode->attr.name = $2->svalue;  /* ID name comes from token_data_t svalue member */
                        t->child[0] = idNode;            /* loop variable ID and iter_range become siblings */
                        t->child[1] = $4;                /* iter_range */
                        t->child[2] = $6;                /* unmatched_stmt */
                        t->lineno = $4->lineno;          /* set for loop line number to that of when the iter_range was scanned */
                        idNode->lineno = $4->lineno;     /* set loop variable ID line number to that of when the iter_range was scanned */
                        $$ = t;                          /* assign new TreeNode to left-hand side */
                    }
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
                    ;

return_stmt         : RETURN SEMI {
                        TreeNode * t = newStmtNode(ReturnK);
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | RETURN exp SEMI {
                        TreeNode * t = newStmtNode(ReturnK);
                        t->child[0] = $2;   /* exp */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
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
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | mutable DEC { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = $1;   /* mutable */
                        t->attr.op = DEC;   /* decrement operator */
                        $$ = t;             /* assign new TreeNode to left-hand side */
                    }
                    | simple_exp { $$ = $1; }
                    ;

assign_op           : ASGN   { $$ = ASGN; }
                    | ADDASS { $$ = ADDASS; }
                    | SUBASS { $$ = SUBASS; }
                    | MULASS { $$ = MULASS; }
                    | DIVASS { $$ = DIVASS; }
                    ;

simple_exp          : simple_exp OR and_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = OR;    /* OR operator */
                        t->child[0] = $1;   /* left operand */
                        t->child[1] = $3;   /* right operand */
                        $$ = t;
                    }
                    | and_exp { $$ = $1; }
                    ;

and_exp             : and_exp AND unary_rel_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = AND;   /* AND operator */
                        t->child[0] = $1;   /* left operand */
                        t->child[1] = $3;   /* right operand */
                        $$ = t;
                    }
                    | unary_rel_exp { $$ = $1; }
                    ;

unary_rel_exp       : NOT unary_rel_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = NOT;   /* NOT operator */
                        t->child[0] = $2;   /* operand */
                        $$ = t;
                    }
                    | rel_exp { $$ = $1; }
                    ;

rel_exp             : sum_exp rel_op sum_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = $2;    /* relational operator from rel_op */
                        t->child[0] = $1;   /* left operand */
                        t->child[1] = $3;   /* right operand */
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
                        t->attr.op = $2;    /* sum operator from sum_op */
                        t->child[0] = $1;   /* left operand */
                        t->child[1] = $3;   /* right operand */
                        $$ = t;
                    }
                    | mul_exp { $$ = $1; }
                    ;

sum_op              : PLUS { $$ = PLUS; }
                    | MINUS { $$ = MINUS; }
                    ;

mul_exp             : mul_exp mul_op unary_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = $2;    /* multiplication operator from mul_op */
                        t->child[0] = $1;   /* left operand */
                        t->child[1] = $3;   /* right operand */
                        $$ = t;
                    }
                    | unary_exp { $$ = $1; }
                    ;

mul_op              : TIMES { $$ = TIMES; }
                    | DIV   { $$ = DIV; }
                    | MOD   { $$ = MOD; }
                    ;

unary_exp           : unary_op unary_exp {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = $1;    /* unary operator from unary_op */
                        t->child[0] = $2;   /* operand */
                        $$ = t;
                    }
                    | factor { $$ = $1; }
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
                        t->attr.op = LBRACKET;      /* array access operator */
                        TreeNode * id = newExpNode(IdK);    /* create tree_node for first child */
                        id->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->child[0] = id;           /* ID */
                        t->child[1] = $3;           /* index expression */
                        t->isArray = true;          /* mark as array access */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | ID {
                        TreeNode * t = newExpNode(IdK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    ;

immutable           : LPAREN exp RPAREN { $$ = $2; }
                    | call { $$ = $1; }
                    | constant { $$ = $1; }
                    ;

call                : ID LPAREN args RPAREN {
                        TreeNode * t = newExpNode(CallK);
                        t->attr.name = $1->svalue;  /* ID name comes from token_data_t svalue member */
                        t->child[0] = $3;           /* args */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
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
                    }
                    | exp { $$ = $1; }
                    ;

constant            : NUMBERCONST {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Integer;          /* set type to Integer */
                        t->attr.value = $1->nvalue; /* value from token_data_t nvalue member */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | CHARCONST {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Char;             /* set type to Char */
                        t->attr.cvalue = $1->cvalue; /* value from token_data_t cvalue member */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | STRINGCONST {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = CharInt;               /* set type to String */
                        t->attr.string = $1->svalue;    /* string from token_data_t svalue member */
                        $$ = t;                         /* assign new TreeNode to left-hand side */
                    }
                    | TRUE { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 1;          /* TRUE represented as 1 */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    | FALSE { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 0;          /* FALSE represented as 0 */
                        $$ = t;                     /* assign new TreeNode to left-hand side */
                    }
                    ;

%%

extern int yydebug;
int main(int argc, char *argv[])
{
    char opt;
    char *optstring = "pd"; // Options: a, b (requires an argument), c (requires an argument)
    int printTreeFlag = 0;
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
            case '?':
                fprintf(stderr, "Unknown option -%c.\n", optopt);
                break;
        }
    }

    if (argc-args > 1) {
        if ((yyin = fopen(argv[argc - 1], "r"))) {
            // file open successful
        }
        else {
            // failed to open fie
            printf("ERROR: failed to open \'%s\'\n", argv[argc - 1]);
            exit(1);
        }
    }

    /* Parse */
    num_errors = 0;
    yyparse();
    
    if (printTreeFlag) {
        printTree(syntaxTree); /* Print the syntax tree */
    }

    return 0;
}

/*


*/
