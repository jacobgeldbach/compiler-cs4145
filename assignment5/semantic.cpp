/*
 * File: semantic.cpp 
 * Description: Semantic analysis and error detection for the c- compiler
 * Author: Jacob A. Geldbach
 * Date: 9/29/2025
 *
 */

#include "semantic.h"
#include "util.h"
#include "parser.tab.h"
#include <string>

#define MAX_ERROR_MSGS 40
#define MAX_ERROR_MSG_LENGTH 256
#define ERROR_SIMPLE_VAR_CALL           0
#define ERROR_NONARRAY_OPERANDS         1
#define ERROR_WRONG_OPERAND_LHS         2
#define ERROR_WRONG_OPERAND_RHS         3
#define ERROR_NONMATCHING_OPERANDS      4
#define ERROR_ARRAY_INDEX_IS_NOT_INT    5
#define ERROR_ARRAY_INDEX_IS_ARRAY      6
#define ERROR_ARRAY_NOT_ARRAY           7
#define ERROR_CANNOT_RETURN_ARRAY       8
#define ERROR_FUNC_USED_AS_VAR          9
#define ERROR_SYMBOL_ALREADY_DECLARED  10
#define ERROR_SYMBOL_NOT_DECLARED      11
#define ERROR_OP_NOT_ALLOWED_ON_ARRAY  12
#define ERROR_UNARY_REQUIRES_ARRAY     13
#define ERROR_UNARY_WRONG_OPERAND      14
#define ERROR_NO_MAIN_FUNC             15
#define WARNING_VAR_UNUSED             16
#define WARNING_VAR_UNINITIALIZED      17
#define ERROR_BREAK_OUTSIDE_LOOP       18
#define ERROR_ARRAY_IN_TEST_CONDITION  19
#define ERROR_ARRAY_IN_FOR_RANGE       20
#define ERROR_FUNC_PARAM_TYPE_MISMATCH 21
#define ERROR_FOR_RANGE_TYPE_MISMATCH  22
#define ERROR_TEST_CONDITION_NOT_BOOL  23
#define ERROR_EXPECTING_ARRAY_PARAM    24
#define ERROR_RETURN_NOT_VOID          25
#define ERROR_RETURN_VOID              26
#define ERROR_RETURN_TYPE_MISMATCH     27
#define ERROR_INIT_NOT_CONSTANT        28
#define ERROR_INIT_TYPE_MISMATCH       29
#define ERROR_INIT_ARRAY_OPERANDS      30
#define ERROR_UNEXPECTING_ARRAY_PARAM  31
#define ERROR_TOO_FEW_FUNC_PARAMS      32
#define ERROR_TOO_MANY_FUNC_PARAMS     33
#define WARNING_MISSING_RETURN         34
#define WARNING_FUNC_UNUSED            35
#define WARNING_PARAM_UNUSED           36

char *errors_found[1000];
int errors_found_line_num[1000];
int errors_found_idx = 0;
int num_errors = 0;    /* Number of errors */
int num_warnings = 0;  /* Number of warnings */

std::string error_msgs[MAX_ERROR_MSGS] = {
    "ERROR(%d): '%s' is a simple variable and cannot be called.\n",                                             //0
    "ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n",   //1
    "ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n",                                              //2
    "ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n",                                              //3
    "ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n",                        //4
    "ERROR(%d): Array '%s' should be indexed by type int but got %s.\n",                                        //5
    "ERROR(%d): Array index is the unindexed array '%s'.\n",                                                    //6
    "ERROR(%d): Cannot index nonarray '%s'.\n",                                                                 //7
    "ERROR(%d): Cannot return an array.\n",                                                                     //8
    "ERROR(%d): Cannot use function '%s' as a variable.\n",                                                     //9
    "ERROR(%d): Symbol '%s' is already declared at line %d.\n",                                                 //10
    "ERROR(%d): Symbol '%s' is not declared.\n",                                                                //11
    "ERROR(%d): The operation '%s' does not work with arrays.\n",                                               //12
    "ERROR(%d): The operation '%s' only works with arrays.\n",                                                  //13
    "ERROR(%d): Unary '%s' requires an operand of %s but was given %s.\n",                                      //14
    "ERROR(LINKER): A function named 'main()' must be defined.\n",                                              //15
    "WARNING(%d): The variable '%s' seems not to be used.\n",                                                   //16
    "WARNING(%d): Variable '%s' may be uninitialized when used here.\n",                                        //17
    "ERROR(%d): Cannot have a break statement outside of loop.\n",                                              //18 - NEW
    "ERROR(%d): Cannot use array as test condition in %s statement.\n",                                         //19 - NEW
    "ERROR(%d): Cannot use array in position %d in range of for statement.\n",                                  //20 - NEW
    "ERROR(%d): Expecting %s in parameter %i of call to '%s' declared on line %d but got %s.\n",                //21 - NEW
    "ERROR(%d): Expecting %s in position %d in range of for statement but got %s.\n",                           //22 - NEW
    "ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n",                                //23 - NEW
    "ERROR(%d): Expecting array in parameter %i of call to '%s' declared on line %d.\n",                        //24 - NEW
    "ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n",              //25 - NEW
    "ERROR(%d): Function '%s' at line %d is expecting to return %s but return has no value.\n",                 //26 - NEW
    "ERROR(%d): Function '%s' at line %d is expecting to return %s but returns %s.\n",                          //27 - NEW
    "ERROR(%d): Initializer for variable '%s' is not a constant expression.\n",                                 //28 - NEW
    "ERROR(%d): Initializer for variable '%s' of %s is of %s\n",                                                //29 - NEW
    "ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is%s an array and rhs is%s an array.\n", //30 - NEW
    "ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n",                    //31 - NEW
    "ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n",                            //32 - NEW
    "ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n",                           //33 - NEW
    "WARNING(%d): Expecting to return %s but function '%s' has no return statement.\n",                         //34 - NEW
    "WARNING(%d): The function '%s' seems not to be used.\n",                                                   //35 - NEW
    "WARNING(%d): The parameter '%s' seems not to be used.\n"                                                   //36 - NEW
};

void sort_all_found_errors() {
    
    int i, j;
    for (i = 0; i < errors_found_idx; i++) {
        for (j = 0; j < errors_found_idx - i - 1; j++) {
            if (errors_found_line_num[j] > errors_found_line_num[j + 1]) {
                /* Swap line numbers */
                int temp_line = errors_found_line_num[j];
                errors_found_line_num[j] = errors_found_line_num[j + 1];
                errors_found_line_num[j + 1] = temp_line;

                /* Swap error messages */
                char *temp_msg = errors_found[j];
                errors_found[j] = errors_found[j + 1];
                errors_found[j + 1] = temp_msg;
            }

        }
    }
}

void print_all_found_errors() {

    //sort_all_found_errors();
    //sort_reverse_same_line_order();

    int i;
    for (i = 0; i < errors_found_idx; i++) {
        printf("%s", errors_found[i]);
    }
}

void check_if_used(std::string name, void *ptr) {
    TreeNode *node = (TreeNode *) ptr;
    if (!node->isUsed) {
        if (node->subkind.decl == FuncK) {
            /* Allocated formatted string message */
            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
            errors_found_line_num[errors_found_idx] = node->lineno;
            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_FUNC_UNUSED].c_str(), node->lineno, node->attr.name);
            num_warnings++;
        }
        else if (node->subkind.decl == ParamK) {
            /* Allocated formatted string message */
            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
            errors_found_line_num[errors_found_idx] = node->lineno;
            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_PARAM_UNUSED].c_str(), node->lineno, node->attr.name);
            num_warnings++;
        }
        else
        {
            /* Allocated formatted string message */
            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
            errors_found_line_num[errors_found_idx] = node->lineno;
            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_VAR_UNUSED].c_str(), node->lineno, node->attr.name);
            num_warnings++;
        }
    }
}

void eval_operator_operands(TreeNode *operator_node, SymbolTable *symbol_table) {
    OpKind op = operator_node->attr.op;
    TreeNode *lhs_node = operator_node->child[0];
    TreeNode *rhs_node = operator_node->child[1];
    
    bool error = false;
    bool lhs_warning = false;
    bool rhs_warning = false;
    bool lhs_is_global = false;
    bool rhs_is_global = false;
    /* Binary and Array Operators */
    if (lhs_node != NULL && rhs_node != NULL) {
               
        if (lhs_node->subkind.exp == IdK) {
            /* Update the lhs declaration node as used, check this scope and the Global scope */
            TreeNode *decl_node = (TreeNode *) symbol_table->lookup(lhs_node->attr.name);
            if (decl_node != NULL) {
                decl_node->isUsed = true;
            }
        }

        if (rhs_node->subkind.exp == IdK) {
            /* Update the lhs declaration node as used, check this scope and the Global scope */
            TreeNode *decl_node = (TreeNode *) symbol_table->lookup(rhs_node->attr.name);
            if (decl_node != NULL) {
                decl_node->isUsed = true;
            }
        }


        switch (op) {
            case MINUS:
            case TIMES:
            case DIV:
            case MOD:
            case ADDASS:
            case SUBASS:
            case MULASS:
            case DIVASS:
            case PLUS:
 
                if (lhs_node->type != Integer || rhs_node->type != Integer) {
                    if (lhs_node->type != Integer && lhs_node->type != UndefinedType) {
                        /* Allocated formatted string message memory */
                        errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                        errors_found_line_num[errors_found_idx] = operator_node->lineno;
                        snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_WRONG_OPERAND_LHS].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(lhs_node->type));
                        num_errors++;
                    }
                    if (rhs_node->type != Integer && rhs_node->type != UndefinedType) {     
                        /* Allocated formatted string message memory */
                        errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                        errors_found_line_num[errors_found_idx] = operator_node->lineno;
                        snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_WRONG_OPERAND_RHS].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(rhs_node->type));
                        num_errors++;
                    }
                }

                if (lhs_node->isArray || rhs_node->isArray) {   
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }

                operator_node->type = Integer; /* The result of an arithmetic operation is always Integer */
                operator_node->isConstant = (lhs_node->isConstant && rhs_node->isConstant);
                break;
            case AND:
            case OR:
                if (!(lhs_node->type == Boolean && rhs_node->type == Boolean)) {
                    if (lhs_node->type != Boolean && lhs_node->type != UndefinedType) {                 
                        /* Allocated formatted string message memory */
                        errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                        errors_found_line_num[errors_found_idx] = operator_node->lineno;
                        snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_WRONG_OPERAND_LHS].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(lhs_node->type));
                        num_errors++;
                    }

                    if (rhs_node->type != Boolean && rhs_node->type != UndefinedType) {   
                        /* Allocated formatted string message memory */
                        errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                        errors_found_line_num[errors_found_idx] = operator_node->lineno;
                        snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_WRONG_OPERAND_RHS].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(rhs_node->type));
                        num_errors++;
                    }
                }

                if (lhs_node->isArray || rhs_node->isArray) {         
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }
                operator_node->type = Boolean; /* The result of a logical operation is always Boolean */
                operator_node->isConstant = (lhs_node->isConstant && rhs_node->isConstant);
                break;
            case ASGN:
                if ((lhs_node->type != rhs_node->type) && (lhs_node->type != UndefinedType) && (rhs_node->type != UndefinedType)) {        
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_NONMATCHING_OPERANDS].c_str(), operator_node->lineno, get_operator(op), get_type(lhs_node->type), get_type(rhs_node->type));
                    num_errors++;
                }
                
                if ((lhs_node->isArray && !rhs_node->isArray) || (!lhs_node->isArray && rhs_node->isArray)) {            
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_NONARRAY_OPERANDS].c_str(), operator_node->lineno, get_operator(op), (lhs_node->isArray ? "" : " not"), (rhs_node->isArray ? "" : " not"));
                    num_errors++;
                }

                operator_node->type = lhs_node->type; /* The result of an assignment is the type of the lhs */
                operator_node->isArray = lhs_node->isArray;
                break;
            case EQ:
            case NEQ:
            case LT:
            case GT:
            case LEQ:
            case GEQ:

                if ((lhs_node->type != rhs_node->type) && (lhs_node->type != UndefinedType) && (rhs_node->type != UndefinedType)) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_NONMATCHING_OPERANDS].c_str(), operator_node->lineno, get_operator(op), get_type(lhs_node->type), get_type(rhs_node->type));
                    num_errors++;
                }
                
                if ((lhs_node->isArray && !rhs_node->isArray) || (!lhs_node->isArray && rhs_node->isArray)) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_NONARRAY_OPERANDS].c_str(), operator_node->lineno, get_operator(op), (lhs_node->isArray ? "" : " not"), (rhs_node->isArray ? "" : " not"));
                    num_errors++;
                }

                operator_node->type = Boolean; /* The result of a comparison is always Boolean */
                operator_node->isConstant = true;
                break;
            case LBRACKET:

                //printf("LHS IS ARRAY %d RHS IS ARRAY %d", lhs_node->isArray, rhs_node->isArray);
                
                operator_node->type = lhs_node->type; /* The type of the array access is the type of the array elements */
                operator_node->isArray = false; /* The result of indexing an array is not an array */

                if (!lhs_node->isArray) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_ARRAY_NOT_ARRAY].c_str(), operator_node->lineno, lhs_node->attr.name);
                    num_errors++;
                    error = true;
                } 
                
                if (rhs_node->type != Integer && rhs_node->type != UndefinedType) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_ARRAY_INDEX_IS_NOT_INT].c_str(), operator_node->lineno, lhs_node->attr.name, get_type(rhs_node->type));
                    num_errors++;
                    error = true;
                }
                else {
                    rhs_warning = false;
                }
            
                if (rhs_node->isArray) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_ARRAY_INDEX_IS_ARRAY].c_str(), operator_node->lineno, rhs_node->attr.name);
                    num_errors++;
                    error = true;
                }

                break;
            default:
                break;
        }
/*
        if (lhs_warning) {
            printf(error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), lhs_node->lineno, lhs_node->attr.name);
        }

        if (rhs_warning) {
            printf(error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), rhs_node->lineno, rhs_node->attr.name);
        }
*/
    } 
    else if (lhs_node != NULL) { /* Unary Operators */
        if (lhs_node->subkind.exp == IdK) {
            /* Update the lhs declaration node as used, check this scope and the Global scope */
            TreeNode *decl_node = (TreeNode *) symbol_table->lookup(lhs_node->attr.name);
            if (decl_node != NULL) {
                decl_node->isUsed = true;
            }
            decl_node = (TreeNode *) symbol_table->lookupGlobal(lhs_node->attr.name);
            if (decl_node != NULL) {
                decl_node->isUsed = true;
                lhs_is_global = true;
            }
        }

        switch (op) {
            case DEC:
            case INC:
            case CHSIGN:
            case TERNARY:
                operator_node->type = Integer; /* The result of these unary operations is always Integer */
                if (lhs_node->type != Integer && lhs_node->type != UndefinedType) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(lhs_node->type));
                    num_errors++;
                }

                if (lhs_node->isArray && lhs_node->type != UndefinedType) {       
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }

                if (op == CHSIGN) {
                    operator_node->isConstant = lhs_node->isConstant;
                }

                break;
            case NOT:
                operator_node->type = Boolean; /* The result of the NOT operation is always Boolean */
                operator_node->isConstant = true;
                if (lhs_node->type != Boolean) {             
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(lhs_node->type));
                    num_errors++;
                }

                if (lhs_node->isArray) {      
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }
                break;
            case SIZEOF:
                operator_node->type = Integer; /* The result of the sizeof operation is always Integer */
                if (!lhs_node->isArray && lhs_node->type != UndefinedType) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_UNARY_REQUIRES_ARRAY].c_str(), operator_node->lineno, get_operator(op), "array", get_type(lhs_node->type));
                    num_errors++;
                }
                break;
            default:
                break;
        }
        /* 
        if (lhs_warning) {
            printf(error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), lhs_node->lineno, lhs_node->attr.name);
        }
        */

    }    
    else if (rhs_node != NULL) { /* Unary Operators */
        if (rhs_node->subkind.exp == IdK) {
            /* Update the rhs declaration node as used, check this scope and the Global scope */
            TreeNode *decl_node = (TreeNode *) symbol_table->lookup(rhs_node->attr.name);
            if (decl_node != NULL) {
                decl_node->isUsed = true;
            }
        }
 
        switch (op) {
            case DEC:
            case INC:
            case CHSIGN:
            case TERNARY:
                operator_node->type = Integer; /* The result of these unary operations is always Integer */
                if (rhs_node->type != Integer && rhs_node->type != UndefinedType) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(rhs_node->type));
                    num_errors++;
                }

                if (rhs_node->isArray && rhs_node->type != UndefinedType) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }

                if (op == CHSIGN) {
                    operator_node->isConstant = rhs_node->isConstant;
                }
                break;
            case NOT:
                operator_node->type = Boolean; /* The result of the NOT operation is always Boolean */
                operator_node->isConstant = true;
                if (rhs_node->type != Boolean) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(rhs_node->type));
                    num_errors++;
                }
                if (rhs_node->isArray) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }

                break;
            case SIZEOF:
                operator_node->type = Integer; /* The result of the sizeof operation is always Integer */
                if (!rhs_node->isArray && rhs_node->type != UndefinedType) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = operator_node->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_UNARY_REQUIRES_ARRAY].c_str(), operator_node->lineno, get_operator(op), "array", get_type(rhs_node->type));
                    num_errors++;
                }
                break;
            default:
                break;
        }

        /*
        if (rhs_warning) {
            printf(error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), rhs_node->lineno, rhs_node->attr.name);
        }
        */

    }




}

void eval_initializer(TreeNode *tree) {

    TreeNode * init_lhs = tree->param_sibling;
    /* Initializer, need to check if its a constant expression and need to check against what its initializing */
    if (!tree->isConstant) {
        /* Allocated formatted string message memory */
        errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
        errors_found_line_num[errors_found_idx] = tree->lineno;
        snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_INIT_NOT_CONSTANT].c_str(), tree->lineno, init_lhs->attr.name);
        num_errors++;
        /* If error on the initialization of lhs, then make sure lhs is not marked used yet. */
        init_lhs->isUsed = false;
                    
    }
    
    if (init_lhs != NULL) {                
        if (init_lhs->isArray) {                
            if (tree->type != init_lhs->type && tree->type != UndefinedType && init_lhs->type != UndefinedType) {
                /* Allocated formatted string message memory */
                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                errors_found_line_num[errors_found_idx] = tree->lineno;
                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_INIT_TYPE_MISMATCH].c_str(), tree->lineno, init_lhs->attr.name, get_type(init_lhs->type), get_type(tree->type));
                num_errors++;
                /* If error on the initialization of lhs, then make sure lhs is not marked used yet. */
                init_lhs->isUsed = false;                
            }

            if (!tree->isArray) {
                /* Allocated formatted string message memory */
                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                errors_found_line_num[errors_found_idx] = tree->lineno;
                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_INIT_ARRAY_OPERANDS].c_str(), tree->lineno, init_lhs->attr.name, "", " not");
                num_errors++;    
                /* If error on the initialization of lhs, then make sure lhs is not marked used yet. */
                init_lhs->isUsed = false;
            }                    
        }            
        else {                     
            if (tree->type != init_lhs->type && tree->type != UndefinedType && init_lhs->type != UndefinedType) {    
                /* Allocated formatted string message memory */
                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                errors_found_line_num[errors_found_idx] = tree->lineno;
                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_INIT_TYPE_MISMATCH].c_str(), tree->lineno, init_lhs->attr.name, get_type(init_lhs->type), get_type(tree->type));
                num_errors++;
                /* If error on the initialization of lhs, then make sure lhs is not marked used yet. */
                init_lhs->isUsed = false;                
            }

            if (tree->isArray) {     
                /* Allocated formatted string message memory */
                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                errors_found_line_num[errors_found_idx] = tree->lineno;
                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_INIT_ARRAY_OPERANDS].c_str(), tree->lineno, init_lhs->attr.name, " not", "");
                num_errors++;
                /* If error on the initialization of lhs, then make sure lhs is not marked used yet. */
                init_lhs->isUsed = false;                
            }               
        }   
    }
}


TreeNode * search_while_for_if_return(TreeNode * tree) {
 
    if (tree->nodekind == StmtK && tree->subkind.stmt == ReturnK) {
        return tree;
    }

    if (tree->nodekind == StmtK && (tree->subkind.stmt == WhileK || tree->subkind.stmt == ForK || tree->subkind.stmt == IfK)) {
        int i;
        for (i = 0; i < MAXCHILDREN; i++) {
            if (tree->child[i] != NULL) {
                TreeNode * result = search_while_for_if_return(tree->child[i]);
                if (result != NULL) {
                    return result;
                }
            }
        } 
    }
    return NULL;
}



void semantic_analysis(TreeNode * tree, SymbolTable * symbol_table) {
    int i, sibling;
    bool scope_entered = false;
    sibling = 0;
    while (tree != NULL) {

        if (tree->nodekind == StmtK && tree->subkind.stmt == CompoundK) {
            symbol_table->enter("Comp_scope" + std::to_string(tree->lineno)); /* Enter into a new Scope for the compound_stmt */
            scope_entered = true;
            
            TreeNode *param_sibling = tree->param_sibling;
            /* Once creating the compound_stmt, traverse backwards looking for parameters incase this is apart of a function decl */
            while ((param_sibling != NULL) && (((param_sibling->nodekind == DeclK) && (param_sibling->subkind.decl == ParamK)) || (param_sibling->nodekind == DeclK && param_sibling->subkind.decl == VarK))) {

                /* Insert the parameters declarations into the symbol table */
                if (symbol_table->insert(param_sibling->attr.name, (void *) param_sibling) == false) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = tree->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), param_sibling->lineno, param_sibling->attr.name, ((TreeNode *) symbol_table->lookup(param_sibling->attr.name))->lineno);
                    num_errors++;
                }
                param_sibling = param_sibling->sibling;
            }


            if (!tree->isLoop) {
            /* Search for break_stmt in this compound_stmt stmt_list as that would be a break_stmt outside of a loop */
            TreeNode *stmt_node = tree->child[1]; /* The stmt_list is child 1 of the compound_stmt */
            while(stmt_node != NULL) {
                if (stmt_node->nodekind == StmtK && stmt_node->subkind.stmt == BreakK) {
                    /* Allocated formatted string message memory */
                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                    errors_found_line_num[errors_found_idx] = tree->lineno;
                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_BREAK_OUTSIDE_LOOP].c_str(), stmt_node->lineno);
                    num_errors++;
                    break; /* Found the break statement */
                }
                
                stmt_node = stmt_node->sibling; 
            }
            }
        }
    
        if (tree->nodekind == StmtK && tree->subkind.stmt == ForK) {
            symbol_table->enter("For_scope" + std::to_string(tree->lineno)); /* Enter into a new Scope for the compound_stmt */
            scope_entered = true;
        }


        if (tree->nodekind == ExpK && tree->subkind.exp == AssignK) {

            TreeNode *rhs = tree->child[1];

            if (rhs != NULL && rhs->attr.op == LBRACKET) {
                /* RHS is an array */
                if (rhs->child[0] != NULL && rhs->child[0]->subkind.exp == IdK) {
                    rhs = rhs->child[0];
                }

            }
        
            if (tree->child[0] != NULL && rhs != NULL) {
                if (tree->child[0]->subkind.exp == IdK && rhs->subkind.exp == IdK) { 
                    if (strcmp(tree->child[0]->attr.name, rhs->attr.name) == 0) {
                        TreeNode *decl_node = (TreeNode *) symbol_table->lookup(rhs->attr.name);
                        if (decl_node != NULL) {
                            if (decl_node->isInitialized == false && decl_node->isInitializedWarningIssued == false && decl_node->subkind.decl != ParamK) {
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), rhs->lineno, rhs->attr.name);
                                


                                decl_node->isInitializedWarningIssued = true;
                                rhs->isInitializedWarningIssued = true; 
                                num_warnings++;
                            } 
                        }
                    }
                }
            }
            
            if (tree->child[0] != NULL) {
                /* These are essentially assigning the lhs to itself so gotta check for initialization */
                if (tree->attr.op == INC || tree->attr.op == DEC) {
                    if (tree->child[0]->subkind.exp == IdK) {
                        TreeNode *decl_node = (TreeNode *) symbol_table->lookup(tree->child[0]->attr.name);
                        if (decl_node != NULL) {
                            if (decl_node->isInitialized == false && decl_node->isInitializedWarningIssued == false && decl_node->subkind.decl != ParamK) {
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), tree->child[0]->lineno,tree->child[0]->attr.name);
                                


                                decl_node->isInitializedWarningIssued = true;
                                tree->child[0]->isInitializedWarningIssued = true; 
                                num_warnings++;
                            } 
                        }
                    }
                }
                else {
                    tree->child[0]->isInitialized = true; /* Mark the lhs variable as initialized */
                }

                if (tree->child[0]->subkind.exp == IdK) {
                    /* Update the lhs declaration node as initialized, check this scope and the Global scope */
                    TreeNode *decl_node = (TreeNode *) symbol_table->lookup(tree->child[0]->attr.name);
                    if (decl_node != NULL) {
                        decl_node->isInitialized = true;
                    }
                }
            }


           
            /* Do the right side first then the left then carry on */
            semantic_analysis(tree->child[0], symbol_table);
            semantic_analysis(tree->child[1], symbol_table);

            eval_operator_operands(tree, symbol_table);

            tree = tree->sibling;
            sibling++;
            continue;
        }

        /* We need to add functions decls first before DF traversal */
        if (tree->nodekind == DeclK && tree->subkind.decl == FuncK) {

            if (tree->attr.name && strcmp(tree->attr.name, "main") == 0) {
                /* Found main function */
                tree->isUsed = true; /* Mark main as used so we dont get unused warning since automatically gets called */
            }


            /* For functions insert it into the global scope */
            if (symbol_table->insertGlobal(tree->attr.name, (void *) tree) == false) {
                /* Allocated formatted string message memory */
                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                errors_found_line_num[errors_found_idx] = tree->lineno;
                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), tree->lineno, tree->attr.name, ((TreeNode *) symbol_table->lookupGlobal(tree->attr.name))->lineno);
                num_errors++;
            }

 
        }
        

        for ( i=0; i < MAXCHILDREN; i++) {
            if (tree->child[i] != NULL) {
                if (tree->isInitialized) {
                    tree->child[i]->isInitialized = true; /* Propagate initialization status to children */
                    if (tree->child[i]->subkind.exp == IdK) {
                        /* Update the lhs declaration node as initialized, check this scope and the Global scope */
                        TreeNode *decl_node = (TreeNode *) symbol_table->lookup(tree->child[i]->attr.name);
                        if (decl_node != NULL) {
                            decl_node->isInitialized = true;
                        }
                    }
                }
                semantic_analysis(tree->child[i], symbol_table);
            }
        }
        
        if (tree->nodekind==StmtK) {
            switch (tree->subkind.stmt) {
                case IfK:
                    
                    if (tree->child[0] != NULL) {
                        if (tree->child[0]->isArray) {
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_ARRAY_IN_TEST_CONDITION].c_str(), tree->lineno, "if");
                            num_errors++;
                        }
                        
                        if (tree->child[0]->type != Boolean && tree->child[0]->type != UndefinedType) {
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_TEST_CONDITION_NOT_BOOL].c_str(), tree->lineno, "if", get_type(tree->child[0]->type));
                            num_errors++;
                        }
                    }


                    break;
                case WhileK:

                   if (tree->child[0] != NULL) {
                        if (tree->child[0]->isArray) {
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_ARRAY_IN_TEST_CONDITION].c_str(), tree->lineno, "while");
                            num_errors++;
                        }
                        
                        if (tree->child[0]->type != Boolean && tree->child[0]->type != UndefinedType) {
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_TEST_CONDITION_NOT_BOOL].c_str(), tree->lineno, "while", get_type(tree->child[0]->type));
                            num_errors++;
                        }
                    }


                    break;
                case CompoundK:
                    //symbol_table->enter("Comp_scope" + std::to_string(tree->lineno)); /* Enter into a new Scope for the compound_stmt */
                    //scope_entered = true;
                    break;
                case BreakK:
                    break;
                case ForK:
                    if (tree->child[2] == NULL) {
                        break;
                    }

                    if (tree->child[0]->subkind.decl == VarK && tree->child[2]->subkind.stmt == CompoundK) {
                        TreeNode *decl_node = (TreeNode *)symbol_table->lookup(tree->child[0]->attr.name);
                        if (decl_node != NULL) {
                            decl_node->isUsed = true;
                        }
                    }

                    break;
                case ReturnK:
                    if (tree->child[0] != NULL) {
                        if (tree->child[0]->isArray) {
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_CANNOT_RETURN_ARRAY].c_str(), tree->lineno);
                            num_errors++;
                        }
                        if (tree->child[0]->subkind.exp == IdK) {
                            TreeNode *return_decl = (TreeNode *)symbol_table->lookup(tree->child[0]->attr.name);
                            if (return_decl != NULL) {
                                return_decl->isUsed = true;
                            }
                        }
                        
                        tree->type = tree->child[0]->type; /* The type of the return statement is the type of its child expression */
                    }

                    break;
                case RangeK:
                
                    int i;
                    for (i = 0; i < MAXCHILDREN; i++) {
                        if (tree->child[i] != NULL) {
                            if (tree->child[i]->type != Integer && tree->child[i]->type != UndefinedType) {
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_FOR_RANGE_TYPE_MISMATCH].c_str(), tree->lineno, get_type(Integer), i + 1, get_type(tree->child[i]->type));
                                num_errors++;
                            }

                            if (tree->child[i]->isArray) {
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_ARRAY_IN_FOR_RANGE].c_str(), tree->lineno, i + 1);
                                num_errors++;
                            }
                        }
                   
                    }


                    break;
                case NullK:
                    break;
                default:
                    break;

            }
        }
        else if (tree->nodekind==ExpK) { 
            switch (tree->subkind.exp) {
                case OpK:
                    eval_operator_operands(tree, symbol_table);

                    if (tree->initializer) {
                        eval_initializer(tree);
                    }
                    break;
                case ConstantK:
                    
                    if (tree->initializer) {
                        eval_initializer(tree);
                    }

                    break;
                case IdK: {
                    TreeNode *decl_node;
                    TreeNode *decl_node_global;
                    bool is_global = false;
                    bool is_param = false;
                       
  
         
                    if (tree->initializer) {
                        eval_initializer(tree);
                    }

                    /* First check if its been declared in the local scope */ 
                    decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);
                    if (decl_node != NULL) {

                        tree->isArray = decl_node->isArray;     /* Propagate array status from declaration to usage */
                        tree->isStatic = decl_node->isStatic; /* Propagate static status from declaration to usage */
                        tree->type = decl_node->type;           /* Propagate type from declaration to usage */
                        tree->isInitialized = decl_node->isInitialized; /* Propagate initialization status from declaration to usage */
                        tree->isInitializedWarningIssued = decl_node->isInitializedWarningIssued; /* Propagate initialization warning status from declaration to usage */

                        if (decl_node->type == UndefinedType) {
                            /* Even though the lookup in this scope has a space holder, if its Undefined we must print not declared error */
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_NOT_DECLARED].c_str(), tree->lineno, tree->attr.name);
                            //decl_node->isUsed = false;
                            num_errors++;

                            break;
                        }   



                        if (decl_node->subkind.decl == FuncK) { /* A function is being used as a variable */
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_FUNC_USED_AS_VAR].c_str(), tree->lineno, tree->attr.name);
                          
                            decl_node->isInitialized = true;
            
                            tree->isArray = decl_node->isArray;     /* Propagate array status from declaration to usage */
                            tree->isStatic = decl_node->isStatic; /* Propagate static status from declaration to usage */
                            tree->type = UndefinedType;
                            tree->isInitialized = decl_node->isInitialized; /* Propagate initialization status from declaration to usage */
                            tree->isInitializedWarningIssued = decl_node->isInitializedWarningIssued; /* Propagate initialization warning status from declaration to usage */ 

                            num_errors++;
                            break;
                        }

                        decl_node->isUsed = true;
                       
                        
                        if (decl_node->subkind.decl == ParamK) {
                            is_param = true;
                        }


                        //break; /* If found in local scope, skip searching global scope */
                    }
                    else {
  
                        /* Not defined so the lookup returns NULL. We MUST insert a space holder in the symbol_table for this scope with type UndefinedType, this way uninitialized warnings only happen once per scop */    
                        if (symbol_table->insert(tree->attr.name, (void *) tree) == false) {
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), tree->lineno, tree->attr.name, ((TreeNode *) symbol_table->lookup(tree->attr.name))->lineno);
                            num_errors++;
                        }

                        decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);
                        decl_node->type = UndefinedType;
                        decl_node->isArray = false; /* Can't be an array if its undefined */
                        decl_node->isUsed = true;

                        /* Allocated formatted string message memory */
                        errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                        errors_found_line_num[errors_found_idx] = tree->lineno;

                        snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_NOT_DECLARED].c_str(), tree->lineno, tree->attr.name);
                        num_errors++;
                        break;
                    }

                    /* Check to make sure decl_node == NULL to not override its non global status  */
                    decl_node_global = (TreeNode *) symbol_table->lookupGlobal(tree->attr.name);
                    if (decl_node_global != NULL && decl_node != NULL) {
                        if (decl_node_global == decl_node) {
                            is_global = true;
                        }
                        else {
                            is_global = false;
                        }
                    }
                    else if (decl_node_global != NULL && decl_node == NULL) {
                        is_global = true;
                    }

                    if (tree->isInitialized == false && tree->isStatic == false && is_global == false && is_param == false) {
                        if(!tree->isInitializedWarningIssued) {
                            /* If this variable is not static and not initialized, then it may be uninitialized */
                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;
                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), tree->lineno, tree->attr.name);
                            
                            tree->isInitializedWarningIssued = true; /* Prevent cascading warnings for this variable in this scope */
                            
                            decl_node->isInitializedWarningIssued = true; /* Prevent cascading warnings for this variable in this scope */
                            num_warnings++;
                        }
                    }

                    break;
                    }
                case AssignK: {
                    break;
                }
                case InitK:
                    break;
                case CallK: 
                    if (tree->initializer) {
                        eval_initializer(tree);
                    }

            if (tree->attr.name && strcmp(tree->attr.name, "main") == 0) {
                /* Found main function */
                tree->isUsed = true; /* Mark main as used so we dont get unused warning since automatically gets called */
            }


                    /* Like function decls, function calls need to be done before their children */
                    if (tree->nodekind == ExpK && tree->subkind.exp == CallK) {
                        /* Function call, check if its been declared */
                        TreeNode *decl_node;
                        TreeNode *p, *q;

                        p = tree->child[0];
                        while (p != NULL) {
                            if (p->subkind.exp == IdK) {
                                p->isInitializedWarningIssued = true; /* Technically its a parameter into a function call I guess? */
                            }

                            if (p->child[0] != NULL && p->child[0]->subkind.exp == IdK) {
                                p->child[0]->isInitializedWarningIssued = true; /* Incase the parameter is an array */
                            }

                            p = p->sibling;
                        }

                        /* Lookup the function, use Global to first fine functions, if NULL look up in regular scope to catch vars being called as function errors */
                        decl_node = (TreeNode *) symbol_table->lookupGlobal(tree->attr.name);
                        /* Nothing in global scope re-lookup in current scope */
                        if (decl_node == NULL) {
                            decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);
                        }

                        if (decl_node != NULL) {
                            decl_node->isUsed = true;

                            if (decl_node->type == UndefinedType) {
                                /* Even though the lookup in this scope has a space holder, if its Undefined we must print not declared error */
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;

                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_NOT_DECLARED].c_str(), tree->lineno, tree->attr.name);
                                num_errors++;

                                /* Symbol is undeclared, do not do param checking */
                                break;
                            }


                            if (decl_node->subkind.decl != FuncK) { /* A var is being called as a function */
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                
                                /* We've found a decl_node for this symbol but its a simple variable, mark this undeclared function call node to a UndefinedType */
                                tree->type = UndefinedType;

                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SIMPLE_VAR_CALL].c_str(), tree->lineno, tree->attr.name);
                                num_errors++;
                                break;
                            }
                       
                            tree->isStatic = decl_node->isStatic; /* Propagate static status from declaration to usage */
                            tree->type = decl_node->type;           /* Propagate type from declaration to usage */
                            tree->isInitialized = decl_node->isInitialized; /* Propagate initialization status from declaration to usage */
                            tree->isInitializedWarningIssued = decl_node->isInitializedWarningIssued; /* Propagate initialization warning status from declaration to usage */

                            /* Check all stuff regarding func decl parameters and those it was called with */
                            p = tree->child[0]; /* Actual call parameters */
                            q = decl_node->child[0]; /* Function declaration parameters */
                            int i_param = 1;
                            while (p != NULL && q != NULL) {

                                if (p->type != q->type && p->type != UndefinedType && q->type != UndefinedType) {
                                    /* Allocated formatted string message memory */
                                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                    errors_found_line_num[errors_found_idx] = tree->lineno;

                                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_FUNC_PARAM_TYPE_MISMATCH].c_str(), tree->lineno, get_type(q->type), i_param, tree->attr.name, decl_node->lineno, get_type(p->type));
                                    num_errors++;
                                }

                                if (!p->isArray && q->isArray) {
                                    /* Allocated formatted string message memory */
                                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                    errors_found_line_num[errors_found_idx] = tree->lineno;

                                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_EXPECTING_ARRAY_PARAM].c_str(), tree->lineno, i_param, decl_node->attr.name, decl_node->lineno);
                                    num_errors++;
                                }

                                if (p->isArray && !q->isArray) {
                                    /* Allocated formatted string message memory */
                                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                    errors_found_line_num[errors_found_idx] = tree->lineno;

                                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_UNEXPECTING_ARRAY_PARAM].c_str(), tree->lineno, i_param, decl_node->attr.name, decl_node->lineno);
                                    num_errors++;
                                }


                                p = p->sibling;
                                q = q->sibling;
                                i_param++;
                            }

                            if (p != NULL && q == NULL) {

                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;

                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_TOO_MANY_FUNC_PARAMS].c_str(), tree->lineno, tree->attr.name, decl_node->lineno);
                                num_errors++;
                            }

                            if (p == NULL && q != NULL) {

                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;

                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_TOO_FEW_FUNC_PARAMS].c_str(), tree->lineno, tree->attr.name, decl_node->lineno);
                                num_errors++;
                            } 
                        }
                        else {


                            /* Not defined so the lookup returns NULL. We MUST insert a space holder in the symbol_table for this scope with type UndefinedType, this way uninitialized warnings only happen once per scop */    
                            if (symbol_table->insert(tree->attr.name, (void *) tree) == false) {
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), tree->lineno, tree->attr.name, ((TreeNode *) symbol_table->lookup(tree->attr.name))->lineno);
                                num_errors++;
                            }

                            decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);
                            decl_node->type = UndefinedType;
                            decl_node->nodekind = DeclK; /* Change the nodekind to DeclK since its a function decl placeholder */
                            decl_node->subkind.decl = FuncK; /* Since undefined call to a function, the undefinedType place holder node needs to be a FuncK */
                            decl_node->isArray = false; /* Can't be an array if its undefined */
                            decl_node->isUsed = false;

                            /* Allocated formatted string message memory */
                            errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                            errors_found_line_num[errors_found_idx] = tree->lineno;

                            snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_NOT_DECLARED].c_str(), tree->lineno, tree->attr.name);
                            num_errors++;
                        }        
                    }

                    break;


                default:
                break;
            }
        }
        else if (tree->nodekind==DeclK) {
            switch (tree->subkind.decl) {
                case FuncK: {
                    /* Find the return_stmt for this function decl from the compound_stmt child */
                    TreeNode *compound_stmt_node = tree->child[1];
                    if (compound_stmt_node != NULL) {

                        TreeNode *all_return_stmts[10];
                        int return_stmt_count = 0;
                        TreeNode *return_stmt_node = compound_stmt_node->child[1]; /* The return statement should be the 2nd child of the compound_stmt */
                        while(return_stmt_node != NULL) {
                            if (return_stmt_node->nodekind == StmtK && return_stmt_node->subkind.stmt == ReturnK) {
                                all_return_stmts[return_stmt_count++] = return_stmt_node;
                                return_stmt_node = return_stmt_node->sibling;
                                continue;
                            }

                            if (return_stmt_node->nodekind == StmtK && (return_stmt_node->subkind.stmt == WhileK || return_stmt_node->subkind.stmt == ForK || return_stmt_node->subkind.stmt == IfK)) {

                                TreeNode * found_return = search_while_for_if_return(return_stmt_node);
                                
                                if (found_return != NULL) {
                                
                                    all_return_stmts[return_stmt_count++] = found_return;
                                    return_stmt_node = return_stmt_node->sibling;
                                    continue;
                                }
                            }

                            return_stmt_node = return_stmt_node->sibling; 
                        }


                        if (return_stmt_count == 0) {

                            if (tree->type != Void) { /* If function is not void and has no return statement, then its an error */
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_MISSING_RETURN].c_str(), tree->lineno, get_type(tree->type), tree->attr.name);
                                num_warnings++;
                                break;
                            }
                        }
                       
                        /* Now check all return statements found */ 
                        int i;
                        for(i = 0; i < return_stmt_count; i++) {
                            return_stmt_node = all_return_stmts[i];
                            /* No return_stmt found */
                            if (return_stmt_node == NULL) {
                                if (tree->type != Void) { /* If function is not void and has no return statement, then its an error */
                                    /* Allocated formatted string message memory */
                                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                    errors_found_line_num[errors_found_idx] = tree->lineno;
                                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[WARNING_MISSING_RETURN].c_str(), tree->lineno, get_type(tree->type), tree->attr.name);
                                    num_warnings++;
                                }
                                continue;
                            }
                       
                            if (return_stmt_node->child[0] == NULL && tree->type != Void) { /* If function is not void and return has no child, then its an error */
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_RETURN_VOID].c_str(), return_stmt_node->lineno, tree->attr.name, tree->lineno, get_type(tree->type));
                                num_errors++;
                                continue;
                            }

                            if (tree->type == Void && (return_stmt_node != NULL && return_stmt_node->child[0] != NULL)) { /* If function is void and return has a child, then its an error */
                                /* Allocated formatted string message memory */
                                errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                errors_found_line_num[errors_found_idx] = tree->lineno;
                                snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_RETURN_NOT_VOID].c_str(), return_stmt_node->lineno, tree->attr.name, tree->lineno);
                                num_errors++;
                                continue;
                            }

                            /* Once return_stmt_node found, we can use it to check the return type vs what the function declared its return type as */
                            if (tree->type != return_stmt_node->type && return_stmt_node->type != UndefinedType) {
                                if (!(tree->type == Void && return_stmt_node->child[0] == NULL)) { /* If function is void and return has no child, then its ok */
                                    /* Allocated formatted string message memory */
                                    errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                                    errors_found_line_num[errors_found_idx] = tree->lineno;
                                    snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_RETURN_TYPE_MISMATCH].c_str(), return_stmt_node->lineno, tree->attr.name, tree->lineno, get_type(tree->type), get_type(return_stmt_node->type));
                                    num_errors++;
                                    continue;
                                }
                            }
                        }

 
                    }



                    break;
                }
                case ParamK:
                    break;
                case VarK:

                    /* Try to insert the variable or parameter into the current scope */    
                    if (symbol_table->insert(tree->attr.name, (void *) tree) == false) {
                        /* Check if insert failed due to undefined place holder */
                        if (((TreeNode *)symbol_table->lookup(tree->attr.name))->type == UndefinedType) {
                            break;
                        }

                        /* Allocated formatted string message */
                        errors_found[errors_found_idx] = (char *)malloc(MAX_ERROR_MSG_LENGTH);
                        errors_found_line_num[errors_found_idx] = tree->lineno;
                        snprintf(errors_found[errors_found_idx++], MAX_ERROR_MSG_LENGTH, error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), tree->lineno, tree->attr.name, ((TreeNode *) symbol_table->lookup(tree->attr.name))->lineno);
                        num_errors++;
                    }
                    break;
                default:
                    printf("Unknown DeclNode kind\n");
                    break;
            }
            
        }
        
        if (scope_entered) {
            /* Before leaving the scope check for any unused variables in this scope */
            symbol_table->applyToAll(check_if_used);

            symbol_table->leave(); /* Leave and terminate the current nodes compound_stmt Scope before moving onto siblings */
            scope_entered = false;
        }

        tree = tree->sibling;
        sibling++;
    }
}


/* Function for initializing the AST for the Runtime I/O library function calls */
TreeNode * init_io_library_ast() {

    TreeNode *input_func_decl = newDeclNode(FuncK);
    TreeNode *input_b_func_decl = newDeclNode(FuncK);
    TreeNode *input_c_func_decl = newDeclNode(FuncK);
    TreeNode *output_func_decl = newDeclNode(FuncK);
    TreeNode *output_b_func_decl = newDeclNode(FuncK);
    TreeNode *output_c_func_decl = newDeclNode(FuncK);
    TreeNode *output_nl_func_decl = newDeclNode(FuncK);

    TreeNode *output_int_param = newDeclNode(ParamK);
    TreeNode *output_bool_param = newDeclNode(ParamK);
    TreeNode *output_char_param = newDeclNode(ParamK);

    output_int_param->nodekind = DeclK;
    output_int_param->subkind.decl = ParamK;
    output_int_param->lineno = -1;
    output_int_param->type = Integer;
    output_int_param->attr.name = strdup("*dummy*");
    output_int_param->isArray = false;
    output_int_param->isUsed = true; /* Prevent unused warning */
   
    output_bool_param->nodekind = DeclK;
    output_bool_param->subkind.decl = ParamK;
    output_bool_param->lineno = -1;
    output_bool_param->type = Boolean;
    output_bool_param->attr.name = strdup("*dummy*");
    output_bool_param->isArray = false;
    output_bool_param->isUsed = true; /* Prevent unused warning */

    output_char_param->nodekind = DeclK;
    output_char_param->subkind.decl = ParamK;
    output_char_param->lineno = -1;
    output_char_param->type = Char;
    output_char_param->attr.name = strdup("*dummy*");
    output_char_param->isArray = false;
    output_char_param->isUsed = true; /* Prevent unused warning */

    input_func_decl->nodekind = DeclK;
    input_func_decl->subkind.decl = FuncK;
    input_func_decl->lineno = -1;
    input_func_decl->type = Integer;
    input_func_decl->attr.name = strdup("input");
    input_func_decl->isUsed = true; /* Prevent unused warning */

    input_b_func_decl->nodekind = DeclK;
    input_b_func_decl->subkind.decl = FuncK;
    input_b_func_decl->lineno = -1;
    input_b_func_decl->type = Boolean;
    input_b_func_decl->attr.name = strdup("inputb");
    input_b_func_decl->isUsed = true; /* Prevent unused warning */

    input_c_func_decl->nodekind = DeclK;
    input_c_func_decl->subkind.decl = FuncK;
    input_c_func_decl->lineno = -1;
    input_c_func_decl->type = Char;
    input_c_func_decl->attr.name = strdup("inputc");
    input_c_func_decl->isUsed = true; /* Prevent unused warning */

    output_func_decl->nodekind = DeclK;
    output_func_decl->subkind.decl = FuncK;
    output_func_decl->lineno = -1;
    output_func_decl->type = Void;
    output_func_decl->attr.name = strdup("output");
    output_func_decl->child[0] = output_int_param;
    output_func_decl->isUsed = true; /* Prevent unused warning */

    output_b_func_decl->nodekind = DeclK;
    output_b_func_decl->subkind.decl = FuncK;
    output_b_func_decl->lineno = -1;
    output_b_func_decl->type = Void;
    output_b_func_decl->attr.name = strdup("outputb");
    output_b_func_decl->child[0] = output_bool_param;
    output_b_func_decl->isUsed = true; /* Prevent unused warning */

    output_c_func_decl->nodekind = DeclK;
    output_c_func_decl->subkind.decl = FuncK;
    output_c_func_decl->lineno = -1;
    output_c_func_decl->type = Void;
    output_c_func_decl->attr.name = strdup("outputc");
    output_c_func_decl->child[0] = output_char_param;
    output_c_func_decl->isUsed = true; /* Prevent unused warning */

    output_nl_func_decl->nodekind = DeclK;
    output_nl_func_decl->subkind.decl = FuncK;
    output_nl_func_decl->lineno = -1;
    output_nl_func_decl->type = Void;
    output_nl_func_decl->attr.name = strdup("outnl");
    output_nl_func_decl->isUsed = true; /* Prevent unused warning */

    input_func_decl->sibling = input_b_func_decl;
    input_b_func_decl->sibling = input_c_func_decl;
    input_c_func_decl->sibling = output_func_decl;
    output_func_decl->sibling = output_b_func_decl;
    output_b_func_decl->sibling = output_c_func_decl;
    output_c_func_decl->sibling = output_nl_func_decl;

    return input_func_decl; /* Return the head of the linked list of function declarations */

}
