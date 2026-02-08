%{
/*
 * CS-4145 Section 71
 * Assignment 1: Flex Scanner + Bison Parser
 * File: parsey.y - Bison parser file
 * Author: Jacob A. Geldbach
 * Date: 09/01/2025
 */

#include "scanType.h"  /* token_data_t */
#include <stdio.h>
#include <cstring>
double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line_num;		/* Error line number from the scanner */
extern int num_errors;    	/* Error count */

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line_num, msg);
    num_errors++;
}

void print_token(token_data_t *token_data);
%}

/* This is included in the generated bison generated tab.h file, therefore scanType.h must be included before the tab.h file */
%union {
    token_data_t *token_data;
}

%token  <token_data> ID NUMBER CHAR STRING BOOL OPERATOR DELIMITER KEYWORD QUIT

/* Current parse/grammar tree is pretty simple, this will expand and most likely change once passed Assignment1 */
%%
token_list : token_list token
	   | token
	   | '\n'	       { /* ignore newlines */ }
	   ;

token     : ID                  { print_token($1); }
	  | NUMBER              { print_token($1); }
	  | CHAR                { print_token($1); }
	  | STRING              { print_token($1); }
	  | BOOL                { print_token($1); }
	  | OPERATOR            { print_token($1); }
	  | DELIMITER           { print_token($1); }
	  | KEYWORD             { print_token($1); }
	  | QUIT                { exit(0); }
	  ;
%%

/* I assume this will be refactored out once passed Assignment1, we will be doing more in this compiler than printing the lexemes */
void print_token(token_data_t *token_data) {
    
    switch (token_data->token_class) {
	case ID:
	    printf("Line %d Token: ID Value: %s\n", token_data->line_num, token_data->svalue);
	    break;
	case NUMBER:
	    printf("Line %d Token: NUMCONST Value: %d  Input: %s\n", token_data->line_num, token_data->nvalue, token_data->token_str);
	    break;
	case CHAR:
	    printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n", token_data->line_num, token_data->cvalue, token_data->token_str);
	    break;
	case STRING:
	    printf("Line %d Token: STRINGCONST Value: %s  Len: %d  Input: %s\n", token_data->line_num, token_data->svalue, strlen(token_data->svalue) - 2, token_data->token_str);
	    break;
	case BOOL:
	    printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n", token_data->line_num, token_data->nvalue, token_data->token_str);
	    break;
	case OPERATOR:
	    if (strcmp(token_data->svalue, "><") == 0) {
	    	printf("Line %d Token: NEQ\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "<=") == 0) {
	    	printf("Line %d Token: LEQ\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, ">=") == 0) {
	    	printf("Line %d Token: GEQ\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "&&") == 0) {
	    	printf("Line %d Token: AND\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "||") == 0) {
	    	printf("Line %d Token: OR\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "++") == 0) {
	    	printf("Line %d Token: INC\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "--") == 0) {
	    	printf("Line %d Token: DEC\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "+=") == 0) {
		printf("Line %d Token: ADDASS\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "and") == 0) {
		printf("Line %d Token: AND\n", token_data->line_num);
	    } 
	    else if (strcmp(token_data->svalue, "or") == 0) {
		printf("Line %d Token: OR\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "not") == 0) {
		printf("Line %d Token: NOT\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, ":=") == 0) {
		printf("Line %d Token: ASGN\n", token_data->line_num);
	    }
	    else {
	    	printf("Line %d Token: %c\n", token_data->line_num, token_data->svalue[0]);
	    }
	    break;
	case DELIMITER:
	    printf("Line %d Token: %c\n", token_data->line_num, token_data->cvalue);
	    break;
	case KEYWORD:
	    if (strcmp(token_data->svalue, "if") == 0) {
		printf("Line %d Token: IF\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "else") == 0) {
		printf("Line %d Token: ELSE\n", token_data->line_num);
	    } 
	    else if (strcmp(token_data->svalue, "while") == 0) {
		printf("Line %d Token: WHILE\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "return") == 0) {
		printf("Line %d Token: RETURN\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "int") == 0) {
		printf("Line %d Token: INT\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "char") == 0) {
		printf("Line %d Token: CHAR\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "string") == 0) {
		printf("Line %d Token: STRING\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "bool") == 0) {
		printf("Line %d Token: BOOL\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "void") == 0) {
		printf("Line %d Token: VOID\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "case") == 0) {
		printf("Line %d Token: CASE\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "switch") == 0) {
		printf("Line %d Token: SWITCH\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "default") == 0) {
		printf("Line %d Token: DEFAULT\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "break") == 0) {
		printf("Line %d Token: BREAK\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "for") == 0) {
		printf("Line %d Token: FOR\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "do") == 0) {
		printf("Line %d Token: DO\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "double") == 0) {
		printf("Line %d Token: DOUBLE\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "float") == 0) {
		printf("Line %d Token: FLOAT\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "continue") == 0) {
		printf("Line %d Token: CONTINUE\n", token_data->line_num); 
	    }
	    else if (strcmp(token_data->svalue, "static") == 0) {
		printf("Line %d Token: STATIC\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "to") == 0) {
		printf("Line %d Token: TO\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "by") == 0) {
		printf("Line %d Token: BY\n", token_data->line_num);
	    }
	    else if (strcmp(token_data->svalue, "then") == 0) {
		printf("Line %d Token: THEN\n", token_data->line_num);
	    }

	    break;
	case QUIT:
	    break;
	default:
	    printf("UNKNOWN Token CLASS: %d\n", token_data->token_class);
    }
}


extern int yydebug;
int main(int argc, char *argv[])
{
    if (argc > 1) {
        if ((yyin = fopen(argv[1], "r"))) {
            // file open successful
        }
        else {
            // failed to open fie
            printf("ERROR: failed to open \'%s\'\n", argv[1]);
            exit(1);
        }
    }

    /* Parse */
    num_errors = 0;
    yyparse();

    return 0;
}
