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

#define MAX_ERROR_MSGS 20
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
#define WARNING_VAR_UNUSED             16
#define WARNING_VAR_UNINITIALIZED      17
#define ERROR_NO_MAIN_FUNC             18

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
    "ERROR(LINKER): A function named 'main()' must be defined.\n"
};

int num_errors;    /* Number of errors */
int num_warnings;  /* Number of warnings */

void check_if_used(std::string name, void *ptr) {
    TreeNode *node = (TreeNode *) ptr;
    if (!node->isUsed) {
        printf(error_msgs[WARNING_VAR_UNUSED].c_str(), node->lineno, node->attr.name);
        num_warnings++;
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
            decl_node = (TreeNode *) symbol_table->lookupGlobal(lhs_node->attr.name);
            if (decl_node != NULL) {
                decl_node->isUsed = true;
                lhs_is_global = true;
            }
        }

        if (rhs_node->subkind.exp == IdK) {
            /* Update the lhs declaration node as used, check this scope and the Global scope */
            TreeNode *decl_node = (TreeNode *) symbol_table->lookup(rhs_node->attr.name);
            if (decl_node != NULL) {
                decl_node->isUsed = true;
            }
            
            decl_node = (TreeNode *) symbol_table->lookupGlobal(rhs_node->attr.name);
            if (decl_node != NULL) {
                rhs_is_global = true;
                decl_node->isUsed = true;
            }
        }

        if (lhs_node->subkind.exp == IdK && op != ASGN && lhs_node->isStatic == false && (lhs_is_global == false)) {
            if (lhs_node->isInitialized == false) {
                lhs_warning = true;
            }
        }

        if (rhs_node->subkind.exp == IdK && rhs_node->isStatic == false && (rhs_is_global == false)) {
            if (rhs_node->isInitialized == false) {
                rhs_warning = true;
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
  
                if (!(lhs_node->type == Integer && rhs_node->type == Integer)) {
                    if (lhs_node->type != Integer) {
                        printf(error_msgs[ERROR_WRONG_OPERAND_LHS].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(lhs_node->type));
                        num_errors++;
                    }
                    if (rhs_node->type != Integer) {
                        printf(error_msgs[ERROR_WRONG_OPERAND_RHS].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(rhs_node->type));
                        num_errors++;
                    }
                }

                if (lhs_node->isArray || rhs_node->isArray) {
                    printf(error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }

                operator_node->type = Integer; /* The result of an arithmetic operation is always Integer */
                break;
            case AND:
            case OR:
                if (!(lhs_node->type == Boolean && rhs_node->type == Boolean)) {
                    if (lhs_node->type != Boolean) {
                        printf(error_msgs[ERROR_WRONG_OPERAND_LHS].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(lhs_node->type));
                        num_errors++;
                    }

                    if (rhs_node->type != Boolean) {
                        printf(error_msgs[ERROR_WRONG_OPERAND_RHS].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(rhs_node->type));
                        num_errors++;
                    }
                }

                if (lhs_node->isArray || rhs_node->isArray) {
                    printf(error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }
                operator_node->type = Boolean; /* The result of a logical operation is always Boolean */
                break;
            case ASGN:
                if ((lhs_node->type != rhs_node->type) && (lhs_node->type != UndefinedType) && (rhs_node->type != UndefinedType)) {
                    printf(error_msgs[ERROR_NONMATCHING_OPERANDS].c_str(), operator_node->lineno, get_operator(op), get_type(lhs_node->type), get_type(rhs_node->type));
                    num_errors++;
                }
                else if ((lhs_node->isArray && !rhs_node->isArray) || (!lhs_node->isArray && rhs_node->isArray)) {
                    printf(error_msgs[ERROR_NONARRAY_OPERANDS].c_str(), operator_node->lineno, get_operator(op), (lhs_node->isArray ? "" : " not"), (rhs_node->isArray ? "" : " not"));
                    num_errors++;
                }

                operator_node->type = lhs_node->type; /* The result of an assignment is the type of the lhs */
                break;
            case EQ:
            case NEQ:
            case LT:
            case GT:
            case LEQ:
            case GEQ:

                if ((lhs_node->type != rhs_node->type) && (lhs_node->type != UndefinedType) && (rhs_node->type != UndefinedType)) {
                    printf(error_msgs[ERROR_NONMATCHING_OPERANDS].c_str(), operator_node->lineno, get_operator(op), get_type(lhs_node->type), get_type(rhs_node->type));
                    num_errors++;
                }
                
                if ((lhs_node->isArray && !rhs_node->isArray) || (!lhs_node->isArray && rhs_node->isArray)) {
                    printf(error_msgs[ERROR_NONARRAY_OPERANDS].c_str(), operator_node->lineno, get_operator(op), (lhs_node->isArray ? "" : " not"), (rhs_node->isArray ? "" : " not"));
                    num_errors++;
                }

                operator_node->type = Boolean; /* The result of a comparison is always Boolean */
                break;
            case LBRACKET:

                //printf("LHS IS ARRAY %d RHS IS ARRAY %d", lhs_node->isArray, rhs_node->isArray);
                
                operator_node->type = lhs_node->type; /* The type of the array access is the type of the array elements */
                operator_node->isArray = false; /* The result of indexing an array is not an array */

                if (lhs_node->subkind.exp == IdK) {
                    // Update the lhs declaration node as initialized, check this scope and the Global scope 
                    TreeNode *decl_node = (TreeNode *) symbol_table->lookup(lhs_node->attr.name);
                    if (decl_node != NULL) {
                        decl_node->isInitialized = true;
                    }
                    else {
                        decl_node = (TreeNode *) symbol_table->lookupGlobal(lhs_node->attr.name);
                        if (decl_node != NULL) {
                            decl_node->isInitialized = true;
                        }
                    }
                }
                
                lhs_node->isInitialized = true; // The array variable is now initialized if it wasn't already
 
                if (!lhs_node->isArray) {
                    printf(error_msgs[ERROR_ARRAY_NOT_ARRAY].c_str(), operator_node->lineno, lhs_node->attr.name);
                    num_errors++;
                    error = true;
                } 
                
                if (rhs_node->type != Integer) {
                    printf(error_msgs[ERROR_ARRAY_INDEX_IS_NOT_INT].c_str(), operator_node->lineno, lhs_node->attr.name, get_type(rhs_node->type));
                    num_errors++;
                    error = true;
                }
                else {
                    rhs_warning = false;
                }
            
                if (rhs_node->isArray) {
                    printf(error_msgs[ERROR_ARRAY_INDEX_IS_ARRAY].c_str(), operator_node->lineno, rhs_node->attr.name);
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

        if (lhs_node->subkind.exp == IdK && lhs_node->isStatic == false && (lhs_is_global == false)) {
            if (lhs_node->isInitialized == false) {
                lhs_warning = true;
            }
        }

        switch (op) {
            case DEC:
            case INC:
            case CHSIGN:
            case TERNARY:
                operator_node->type = Integer; /* The result of these unary operations is always Integer */
                if (lhs_node->type != Integer) {
                    printf(error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(lhs_node->type));
                    num_errors++;
                }

                if (lhs_node->isArray) {
                    printf(error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }
                break;
            case NOT:
                operator_node->type = Boolean; /* The result of the NOT operation is always Boolean */
                if (lhs_node->type != Boolean) {
                    printf(error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(lhs_node->type));
                    num_errors++;
                }

                if (lhs_node->isArray) {
                    printf(error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }
                break;
            case SIZEOF:
                operator_node->type = Integer; /* The result of the sizeof operation is always Integer */
                if (!lhs_node->isArray) {
                    printf(error_msgs[ERROR_UNARY_REQUIRES_ARRAY].c_str(), operator_node->lineno, get_operator(op), "array", get_type(lhs_node->type));
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
            decl_node = (TreeNode *) symbol_table->lookupGlobal(rhs_node->attr.name);
            if (decl_node != NULL) {    
                decl_node->isUsed = true;
                rhs_is_global = true;
            }
        }
 
        if (rhs_node->subkind.exp == IdK && rhs_node->isStatic == false && rhs_is_global == false) {
            if (rhs_node->isInitialized == false) {
                rhs_warning = true;
            }
        }  

        switch (op) {
            case DEC:
            case INC:
            case CHSIGN:
            case TERNARY:
                operator_node->type = Integer; /* The result of these unary operations is always Integer */
                if (rhs_node->type != Integer) {
                    printf(error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Integer), get_type(rhs_node->type));
                    num_errors++;
                }

                if (rhs_node->isArray) {
                    printf(error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }
                break;
            case NOT:
                operator_node->type = Boolean; /* The result of the NOT operation is always Boolean */
                if (rhs_node->type != Boolean) {
                    printf(error_msgs[ERROR_UNARY_WRONG_OPERAND].c_str(), operator_node->lineno, get_operator(op), get_type(Boolean), get_type(rhs_node->type));
                    num_errors++;
                }
                if (rhs_node->isArray) {
                    printf(error_msgs[ERROR_OP_NOT_ALLOWED_ON_ARRAY].c_str(), operator_node->lineno, get_operator(op));
                    num_errors++;
                }

                break;
            case SIZEOF:
                operator_node->type = Integer; /* The result of the sizeof operation is always Integer */
                if (!rhs_node->isArray) {
                    printf(error_msgs[ERROR_UNARY_REQUIRES_ARRAY].c_str(), operator_node->lineno, get_operator(op), "array", get_type(rhs_node->type));
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

void semantic_analysis(TreeNode * tree, SymbolTable * symbol_table) {
    int i, sibling;
    bool scope_entered = false;
    sibling = 0;
    while (tree != NULL) {
        if (sibling > 0) {
        }

        if (tree->nodekind == StmtK && tree->subkind.stmt == CompoundK) {
            symbol_table->enter("Comp_scope" + std::to_string(tree->lineno)); /* Enter into a new Scope for the compound_stmt */
            scope_entered = true;
            
            TreeNode *param_sibling = tree->param_sibling;
            /* Once creating the compound_stmt, traverse backwards looking for parameters incase this is apart of a function decl */
            while ((param_sibling != NULL) && ((param_sibling->nodekind == DeclK) && (param_sibling->subkind.decl == ParamK))) {

                /* Insert the parameters declarations into the symbol table */
                if (symbol_table->insert(param_sibling->attr.name, (void *) param_sibling) == false) {
                    printf(error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), param_sibling->lineno, param_sibling->attr.name, ((TreeNode *) symbol_table->lookup(param_sibling->attr.name))->lineno);
                    num_errors++;
                }
                param_sibling = param_sibling->sibling;
            }

        }
    
        if (tree->nodekind == StmtK && tree->subkind.stmt == ForK) {
            symbol_table->enter("For_scope" + std::to_string(tree->lineno)); /* Enter into a new Scope for the compound_stmt */
            scope_entered = true;
        }

        if (tree->nodekind == StmtK && tree->subkind.stmt == RangeK) {
            /* Not sure why yet but we skip children here */
            tree = tree->sibling;
            sibling++;
            continue;
        }

        if (tree->nodekind == ExpK && tree->subkind.exp == AssignK) {

            TreeNode *find_id_child = tree->child[0];
            while (find_id_child != NULL) {
                // Check if the current node is of subkind `IdK`
                if (find_id_child->subkind.exp == IdK) {
                    break; // Stop traversing since we found the first IdK
                }
                
                // Continue down the left child
                find_id_child = find_id_child->child[0];
            
            }
            
            /* Mark the LHS variable as initialized */    
            if (find_id_child != NULL && find_id_child->subkind.exp == IdK) {
                find_id_child->isInitialized = true;

                
                TreeNode *decl_node = (TreeNode *) symbol_table->lookup(find_id_child->attr.name);
                if (decl_node != NULL) {
                    decl_node->isInitialized = true;
                }
                else {
                    decl_node = (TreeNode *) symbol_table->lookupGlobal(find_id_child->attr.name);
                    if (decl_node != NULL) {
                        decl_node->isInitialized = true;
                    }
                }

                if (tree->child[1] != NULL && tree->child[1]->subkind.exp == IdK) {
                    if (strcmp(find_id_child->attr.name, tree->child[1]->attr.name) == 0) {
                        tree->child[1]->isInitialized = true;
                    }
                }
            }
        }


        /* We need to add functions decls first before DF traversal */
        if (tree->nodekind == DeclK && tree->subkind.decl == FuncK) {
            /* For functions insert it into the global scope */
            if (symbol_table->insertGlobal(tree->attr.name, (void *) tree) == false) {
                printf(error_msgs[10].c_str(), tree->lineno, tree->attr.name, ((TreeNode *) symbol_table->lookupGlobal(tree->attr.name))->lineno);
                num_errors++;
            }
        }

        if (tree->nodekind == ExpK && tree->subkind.exp == AssignK) {
            for ( i=MAXCHILDREN-1; i >= 0; i--) {
                if (tree->child[i] != NULL) {
                    semantic_analysis(tree->child[i], symbol_table);
                }
            }
        }
        else {
            for ( i=0; i < MAXCHILDREN; i++) {
                if (tree->child[i] != NULL) {
                    semantic_analysis(tree->child[i], symbol_table);
                }
            }
        }
        
        if (tree->nodekind==StmtK) {
            switch (tree->subkind.stmt) {
                case IfK:
                    break;
                case WhileK:
                    break;
                case CompoundK:
                    //symbol_table->enter("Comp_scope" + std::to_string(tree->lineno)); /* Enter into a new Scope for the compound_stmt */
                    //scope_entered = true;
                    break;
                case BreakK:
                    break;
                case ForK:
                    break;
                case ReturnK:
                    if (tree->child[0] != NULL) {
                        if (tree->child[0]->isArray) {
                            printf(error_msgs[ERROR_CANNOT_RETURN_ARRAY].c_str(), tree->lineno);
                            num_errors++;
                        }
                        if (tree->child[0]->subkind.exp == IdK) {
                            TreeNode *return_decl = (TreeNode *)symbol_table->lookup(tree->child[0]->attr.name);
                            if (return_decl != NULL) {
                                return_decl->isUsed = true;
                            }
                        }
                    }

                    break;
                case RangeK: 
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
                    break;
                case ConstantK:
                    break;
                case IdK: {
                    TreeNode *decl_node;
                    bool is_global = false;
                    bool is_param = false;

                    /* First check if its been declared in the local scope */ 
                    decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);
                    if (decl_node != NULL) {
                        if (decl_node->subkind.decl == FuncK) { /* A function is being used as a variable */
                            printf(error_msgs[ERROR_FUNC_USED_AS_VAR].c_str(), tree->lineno, tree->attr.name);
                            num_errors++;
                        }
                       
                        tree->isArray = decl_node->isArray;     /* Propagate array status from declaration to usage */
                        tree->isStatic = decl_node->isStatic; /* Propagate static status from declaration to usage */
                        tree->type = decl_node->type;           /* Propagate type from declaration to usage */
                        tree->isInitialized = decl_node->isInitialized; /* Propagate initialization status from declaration to usage */
                        if (decl_node->subkind.decl == ParamK) {
                            is_param = true;
                        }

                        //break; /* If found in local scope, skip searching global scope */
                    }
                    else {
                        printf(error_msgs[ERROR_SYMBOL_NOT_DECLARED].c_str(), tree->lineno, tree->attr.name);
                        num_errors++;
                        tree->type = UndefinedType; /* Set type to undefined to prevent cascading errors */
                   }

                    decl_node = (TreeNode *) symbol_table->lookupGlobal(tree->attr.name);
                    if (decl_node != NULL) {
                        is_global = true;
                        
                        if (decl_node->subkind.decl == ParamK) {
                            is_param = true;
                        }

                    }
                    //    if (decl_node->subkind.decl == FuncK) { /* A function is being used as a variable */
                    //        printf(error_msgs[ERROR_FUNC_USED_AS_VAR].c_str(), tree->lineno, tree->attr.name);
                    //    }
                    //    is_global = true; 
                    //    tree->isArray = decl_node->isArray;     /* Propagate array status from declaration to usage */
                    //    tree->isStatic = decl_node->isStatic; /* Propagate static status from declaration to usage */
                    //    tree->type = decl_node->type;           /* Propagate type from declaration to usage */
                    //   tree->isInitialized = decl_node->isInitialized; /* Propagate initialization status from declaration to usage */
                    //}
                    //else {
                    //    printf(error_msgs[ERROR_SYMBOL_NOT_DECLARED].c_str(), tree->lineno, tree->attr.name);
                    //    tree->type = UndefinedType; /* Set type to undefined to prevent cascading errors */
                   //}

                    if (tree->isInitialized == false && tree->isStatic == false && (is_global == false) && (is_param == false)) {
                        /* If this variable is not static and not initialized, then it may be uninitialized */
                        printf(error_msgs[WARNING_VAR_UNINITIALIZED].c_str(), tree->lineno, tree->attr.name);
                        num_warnings++;
                    }

                    break;
                    }
                case AssignK: {
                    eval_operator_operands(tree, symbol_table);

                    break;
                }
                case InitK:
                    tree->nodekind = DeclK; /* Change the node kind from ExpK to DeclK for insertion into the symbol table */
                    tree->subkind.decl = VarK; /* Change the node kind from InitK to VarK for insertion into the symbol table */
                    tree->isInitialized = true; /* Mark the variable as initialized */
                    /* Try to insert the variable or parameter into the current scope */    
                    if (symbol_table->insert(tree->attr.name, (void *) tree) == false) {
                        printf(error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), tree->lineno, tree->attr.name, ((TreeNode *) symbol_table->lookup(tree->attr.name))->lineno);
                        num_errors++;
                    }
                    break;
                case CallK: {
                    TreeNode *decl_node;
                    TreeNode *p;

                    p = tree->child[0];
                    while (p != NULL) {
                        if (p->subkind.exp == IdK) {
                            TreeNode * lookup = (TreeNode *)symbol_table->lookup(p->attr.name);
                            if (lookup != NULL) {
                                lookup->isUsed = true;
                            }
                        }

                        p = p->sibling;
                    }

                    /* First check if its been declared in the local scope */ 
                    decl_node = (TreeNode *) symbol_table->lookup(tree->attr.name);
                    if (decl_node != NULL){
                        if (decl_node->subkind.decl != FuncK) { /* A var is being called as a function */
                            printf(error_msgs[ERROR_SIMPLE_VAR_CALL].c_str(), tree->lineno, tree->attr.name);
                            num_errors++;
                        }

                        tree->isStatic = decl_node->isStatic; /* Propagate static status from declaration to usage */
                        tree->type = decl_node->type; /* Propagate type from declaration to usage */

                        break; /* If found in local scope, skip searching global scope */
                    }

                    /* Not declared in the local scope so now check if this identifier has been declared in the global scope */
                    decl_node = (TreeNode *) symbol_table->lookupGlobal(tree->attr.name);
                    if (decl_node != NULL) {
                        if (decl_node->subkind.decl != FuncK) { /* A var is being called as a function */
                            printf(error_msgs[ERROR_SIMPLE_VAR_CALL].c_str(), tree->lineno, tree->attr.name);
                            num_errors++;
                        }

                        tree->isStatic = decl_node->isStatic; /* Propagate static status from declaration to usage */
                        tree->type = decl_node->type; /* Propagate type from declaration to usage */
                        
                    }
                    else {
                        printf(error_msgs[ERROR_SYMBOL_NOT_DECLARED].c_str(), tree->lineno, tree->attr.name);
                        num_errors++;
                        tree->type = UndefinedType; /* Set type to undefined to prevent cascading errors */
                    }

                    break;
                    }

                    break;
                default:
                break;
            }
        }
        else if (tree->nodekind==DeclK) {
            
            
            switch (tree->subkind.decl) {
                
                case FuncK:
                    break;
                case ParamK:
                    break;
                case VarK:
                   /* Try to insert the variable or parameter into the current scope */    
                    if (symbol_table->insert(tree->attr.name, (void *) tree) == false) {
                        printf(error_msgs[ERROR_SYMBOL_ALREADY_DECLARED].c_str(), tree->lineno, tree->attr.name, ((TreeNode *) symbol_table->lookup(tree->attr.name))->lineno);
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



