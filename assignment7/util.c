/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "parser.tab.h"
#include "code_generation.h"
#include "emitcode.h"

extern int num_errors;

/* Procedure printToken prints a token 
 * and its lexeme to the file
 */
void printToken( OpKind op, const char* tokenString )
{ 
    switch (op) { 
        case IF:
        case THEN:
        case ELSE:
            printf("reserved word: %s ",tokenString);
            break;
        case ASGN: printf(":= "); break;
        case LT: printf("< "); break;
        case EQ: printf("= "); break;
        case GT: printf("> "); break;
        case LEQ: printf("<= "); break;
        case GEQ: printf(">= "); break;
        case NEQ: printf(">< "); break;
        case COMMA: printf(", "); break;
        case ADDASS: printf("+= "); break;
        case MULASS: printf("*= "); break;
        case SUBASS: printf("-= "); break;
        case DIVASS: printf("/= "); break;
        case LPAREN: printf("( "); break;
        case RPAREN: printf(") "); break;
        case SEMI: printf("; "); break;
        case PLUS: printf("+ "); break;
        case MINUS: printf("- "); break;
        case TIMES: printf("* "); break;
        case INC: printf("++ "); break;
        case DEC: printf("-- "); break;
        case AND: printf("and "); break;
        case OR: printf("or "); break;
        case NOT: printf("not "); break;
        case DIV: printf("/ "); break;
        case MOD: printf("%% "); break;
        case TERNARY: printf("? "); break;
        case CHSIGN: printf("chsign "); break;
        case SIZEOF: printf("sizeof "); break;
        case LBRACKET: printf("[ "); break;
        case NUMBERCONST:
            printf("NUM, val= %s\n",tokenString);
            break;
        case ID:
            printf("ID, name= %s\n",tokenString);
            break;
        /*
        case ERROR:
            printf("ERROR: %s\n",tokenString);
            break;
        */
        default: /* should never happen */
            printf("Unknown token: %d ",op);
    }
}

const char *get_operator(OpKind op) {
    switch (op) {
        case IF: return "if";
        case THEN: return "then";
        case ELSE: return "else";
        case ASGN: return ":=";
        case LT: return "<";
        case EQ: return "=";
        case GT: return ">";
        case LEQ: return "<=";
        case GEQ: return ">=";
        case NEQ: return "><";
        case COMMA: return ",";
        case ADDASS: return "+=";
        case MULASS: return "*=";
        case SUBASS: return "-=";
        case DIVASS: return "/=";
        case LPAREN: return "(";
        case RPAREN: return ")";
        case SEMI: return ";";
        case PLUS: return "+";
        case MINUS: return "-";
        case TIMES: return "*";
        case INC: return "++";
        case DEC: return "--";
        case AND: return "and";
        case OR: return "or";
        case NOT: return "not";
        case DIV: return "/";
        case MOD: return "%";
        case TERNARY: return "?";
        case CHSIGN: return "chsign";
        case SIZEOF: return "sizeof";
        case LBRACKET: return "[";
        default:
            return "Unknown operator";
    }
}

const char *get_type(ExpType type) {
    switch (type) {
        case Void: return "type void";
        case Integer: return "type int";
        case Char: return "type char";
        case CharInt: return "type charint";
        case Boolean: return "type bool";
        case UndefinedType: return "undefined type";
        default:
            return "type Unknown";
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ 
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) {
        printf("Out of memory error at line %d\n",line_num);
    }
    else {
        for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->subkind.stmt = kind;
        t->lineno = line_num;
    }
  
    return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ 
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) {
        printf("Out of memory error at line %d\n",line_num);
    }
    else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->subkind.exp = kind;
        t->lineno = line_num;
        t->type = Void;
    }

    t->oper = 0; /* Hacky for code generation */
  
    return t;
}

/* Function newDeclNode creates a new declaration 
 * node for syntax tree constructioantn
 */
TreeNode * newDeclNode(DeclKind kind)
{ 
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) {
        printf("Out of memory error at line %d\n",line_num);
    }
    else {
        for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = DeclK;
        t->subkind.decl = kind;
        t->lineno = line_num;
        t->type = Void;
    }
  
    return t;
}

/* Function addSibling adds a sibling
 * to a tree node
 */
TreeNode *addSibling(TreeNode *t, TreeNode *s) {
    if (s==NULL && num_errors==0) {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }
    
    if (t!=NULL) {
        TreeNode *tmp;
        tmp = t;
        while (tmp->sibling!=NULL) tmp = tmp->sibling;
            tmp->sibling = s;
            return t;
    }

    return s;
}


/* Function copyString allocates and makes a new
 * copy of an existing string
 */

/*
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}
*/

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno++
#define UNINDENT indentno--

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    printf(".   ");
}

static void print_memory_info(TreeNode * tree) {
    printf("[mem: ");
    if (tree->var_kind == Global) {
        printf("Global ");
    }
    else if (tree->var_kind == Local) {
        printf("Local ");
    }
    else if (tree->var_kind == Parameter) {
        printf("Parameter ");
    }
    else if (tree->var_kind == LocalStatic) {
        printf("LocalStatic ");
    }
    else if (tree->var_kind == None) {
        printf("None ");
    }

    int size = tree->dataword_size;
    int mem_offset = tree->mem_offset;

    if ((tree->nodekind == DeclK && tree->subkind.decl == FuncK) || (tree->nodekind == StmtK && tree->subkind.stmt == CompoundK) || (tree->nodekind == StmtK && tree->subkind.stmt == ForK)) {
        size = size * -1;
    }

    if ((tree->nodekind == DeclK && tree->subkind.decl == VarK) || (tree->nodekind == ExpK && tree->subkind.exp == IdK) || (tree->nodekind == ExpK && tree->subkind.exp == ConstantK) || (tree->nodekind == DeclK && tree->subkind.decl == ParamK)) {
        mem_offset = mem_offset * -1; /* Global and local variable offsets are negative */
    }

    printf("loc: %d size: %d] ", mem_offset, size);
}

/* procedure printTree prints a syntax tree to the 
 *  file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree, bool with_types, bool with_memory_info ) { 
    int i, sibling;
    sibling = 0;
    while (tree != NULL) {
        if (sibling > 0) {
            printSpaces();
            printf("Sibling: %d  ", sibling);
        }

        if (tree->nodekind==StmtK) {
            switch (tree->subkind.stmt) {
                case IfK:
                    printf("If ");
                    break;
                case WhileK:
                    printf("While ");
                    break;
                case CompoundK:
                    printf("Compound ");

                    if (with_memory_info) {    
                        print_memory_info(tree);
                    }   

                    break;
                case BreakK:
                    printf("Break ");
                    break;
                case ForK:
                    printf("For ");
                    if (with_memory_info) {
                        print_memory_info(tree);
                    }   
                    break;
                case ReturnK:
                    printf("Return ");
                    break;
                case RangeK:
                    printf("Range ");
                    break;
                case NullK:
                    printf("Null ");
                    break;
                default:
                    printf("Unknown StmtNode kind\n");
                    break;

            }
        }
        else if (tree->nodekind==ExpK) { 
            switch (tree->subkind.exp) {
                case OpK:
                    printf("Op: ");
                    printToken(tree->attr.op,"\0");
                    
                    if (with_types) {
                        printf("of %s ", get_type(tree->type));
                    }

                    break;
                case ConstantK:
                    if (tree->type == Boolean) {
                        if (tree->attr.value == 0) 
                            printf("Const false ");
                        else 
                            printf("Const true ");
                    }
                    else if (tree->type == Char) {
                        if (tree->isArray) {
                            printf("Const %s is array ", tree->attr.string);
                        }
                        else {
                            printf("Const '%c' ", tree->attr.cvalue);
                        }        
                    }
                    else if (tree->type == CharInt) {
                        printf("Const %s ", tree->attr.string);
                    }
                    else {
                        printf("Const %d ", tree->attr.value);
                    }

                    if (with_types) {
                        printf("of %s ", get_type(tree->type));
                    }
                    
                    /* Only global char arrays get memory allocated in c- */
                    if (tree->type == Char && tree->isArray) {
                        if (with_memory_info) {
                            print_memory_info(tree);
                        }   
                    }

                    break;
                case IdK:
                    printf("Id: %s ", tree->attr.name);
                    
                    if (with_types) {
                        if (tree->isArray) {
                            printf("is%s array of %s ", (tree->isStatic) ? " static" : "", get_type(tree->type));
                        }
                        else {
                            printf("of%s %s ", (tree->isStatic) ? " static" : "", get_type(tree->type));
                        }

                    }

                    if (with_memory_info) {    
                        print_memory_info(tree);
                    }   

                    break;
                case AssignK:
                    printf("Assign: ");
                    printToken(tree->attr.op, "\0");

                    if (tree->isArray) {
                        printf("is array ");
                    }

                    if (with_types) {
                        printf("of %s ", get_type(tree->type));
                    }

                    break;
                case InitK:
                    printf("Init: ");
                    break;
                case CallK:
                    printf("Call: %s ", tree->attr.name);
                    if (with_types) {
                        printf("of %s ", get_type(tree->type));
                    }

                    break;
                default:
                    printf("Unknown ExpNode kind\n");
                break;
            }
        }
        else if (tree->nodekind==DeclK) {
            switch (tree->subkind.decl) {
                case VarK:

                    if (with_types) {
                        if (tree->isArray) {
                            printf("Var: %s is%s array of %s ", tree->attr.name, (tree->isStatic) ? " static" : "", get_type(tree->type));
                        }
                        else {
                            printf("Var: %s of%s %s ", tree->attr.name,(tree->isStatic) ? " static" : "", get_type(tree->type));
                        }
                    }
                    else {
                        printf("Var: %s  ", tree->attr.name);
                    }

                    if (with_memory_info) {
                        print_memory_info(tree);
                    }   

                    break;
                case FuncK:
                    if (with_types) {
                        printf("Func: %s returns %s ", tree->attr.name, get_type(tree->type));
                    }
                    else {
                        printf("Func: %s  ", tree->attr.name);
                    }

                    if (with_memory_info) {
                        print_memory_info(tree);
                    } 
                    
                    break;
                case ParamK:
                    if (with_types) {
                        if (tree->isArray) {
                            printf("Parm: %s is array of %s ", tree->attr.name, get_type(tree->type));
                        }
                        else {
                            printf("Parm: %s of %s ", tree->attr.name, get_type(tree->type));
                        }
                    }
                    else {
                        printf("Parm: %s  ", tree->attr.name);
                    }

                    if (with_memory_info) {
                        print_memory_info(tree);
                    } 
                    break;
                default:
                    printf("Unknown DeclNode kind\n");
                    break;
            }
        }
        else printf("Unknown node kind\n");
    
        printf("[line: %d]\n",tree->lineno);
        for (i=0;i<MAXCHILDREN;i++) {
            if (tree->child[i] != NULL) {
                INDENT;  // Indent deeper for children
                printSpaces();
                /* Only one child and its rhs */
                if (tree->attr.op == TERNARY || tree->attr.op == CHSIGN || tree->attr.op == SIZEOF) {
                    printf("Child: %d  ", 0);    
                }
                else {
                    printf("Child: %d  ", i);
                }
                printTree(tree->child[i], with_types, with_memory_info);  // Recursive printing for children
                UNINDENT;  // Reset indentation
            }
        }
        tree = tree->sibling;
        sibling++;

    }
}

bool expect_lhs_var = false;
TreeNode *lhs_var_holders[100];
int lhs_var_holder = 0;
int call_params_expected = 0;
int last_param_sibling_num = -1;
bool if_statement_active = false;
int if_child_idx = 0;
void linearize_ast( TreeNode * tree, SymbolTable * symbol_table ) { 
    int i, sibling;
    sibling = 0;
    while (tree != NULL) {        
        if (tree->nodekind==StmtK) {
            switch (tree->subkind.stmt) {
                case IfK:
                    append_linearized_node(tree, CG_EnterIf, current_head);
                    last_if_node[++last_if_node_idx] = get_current_tail_node(current_head);
                    if_statement_active = true;
                    break;
                case WhileK:
                    append_linearized_node(tree, CG_EnterWhile, current_head);
                    last_while_node[++last_while_node_idx] = get_current_tail_node(current_head);
                    break;
                case CompoundK:
                    //generate_compound_statement_enter(tree, symbol_table);
                    append_linearized_node(tree, CG_CompoundStatementEnter, current_head);
                    last_compound_node[last_compound_node_idx++] = get_current_tail_node(current_head);
                    break;
                case BreakK:
                    break;
                case ForK:
                    append_linearized_node(tree, CG_ForEnter, current_head);
                    last_for_node[last_for_node_idx++] = get_current_tail_node(current_head);

                    break;
                case ReturnK:
                    append_comment_node("RETURN", current_head);
                    break;
                case RangeK:
                    append_linearized_node(tree, CG_RangeEnter, current_head);
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
                    
                    if ((tree->attr.op == LEQ || tree->attr.op == GT || tree->attr.op == EQ || tree->attr.op == AND || tree->attr.op == OR || tree->attr.op == LT || tree->attr.op == NOT 
                                || tree->attr.op == GEQ || tree->attr.op == NEQ || tree->attr.op == PLUS || tree->attr.op == MINUS || tree->attr.op == TIMES || tree->attr.op == DIV || tree->attr.op == MOD)
                                        && tree->child[0] != NULL) {
                        tree->child[0]->oper = tree->attr.op;
                    }
                    else if ((tree->attr.op == CHSIGN || tree->attr.op == SIZEOF || tree->attr.op == TERNARY) && tree->child[1] != NULL) {
                        /* Unary chsign only right operand */
                        tree->child[1]->oper = tree->attr.op;
                    }

                    if ((tree->attr.op == TIMES || tree->attr.op == PLUS || tree->attr.op == LT || tree->attr.op == LEQ || tree->attr.op == GT || tree->attr.op == MINUS || tree->attr.op == EQ) && tree->child[0] != NULL) {
                        tree->child[0]->oper = tree->attr.op;
                    }


                    break;
                case ConstantK:
 
                    break;
                case IdK:
                      break;
                case AssignK:
                    if (tree->isParam) {
                        append_comment_node("Param 1", current_head);
                    }
                    else {
                        append_comment_node("EXPRESSION", current_head);
                    }


                    if ((tree->attr.op == ADDASS || tree->attr.op == ASGN || tree->attr.op == INC) && tree->child[0] != NULL) {
                        tree->child[0]->oper = tree->attr.op;
                    }


                    if (tree->isArray) {
                    }
                    
                    expect_lhs_var = true;

                    break;
                case InitK:
                    break;
                case CallK:
                    if (call_params_expected && tree->isParam) {
                        append_comment_node("Param 1", current_head);
                    }
                    else {
                        append_comment_node("EXPRESSION", current_head);
                    }
                    append_linearized_node(tree, CG_FunctionCallEnter, current_head);
                    call_params_expected++;

                    break;
                default:
                break;
            }
        }
        else if (tree->nodekind==DeclK) {
            switch (tree->subkind.decl) {
                case VarK:

                    break;
                case FuncK:
                    append_linearized_node(tree, CG_FunctionDefineEnter, current_head);
                                       
                    break;
                case ParamK:
                    //generate_parameter(tree);
                    
                    break;
                default:
                    break;
            }
        }
    
        code_generation_linearized_node_t *then_part = NULL;
        code_generation_linearized_node_t *else_part = NULL;

        for (i=0;i<MAXCHILDREN;i++) {
            if (tree->child[i] != NULL) {

                       
                if (tree->nodekind == StmtK && tree->subkind.stmt == IfK && if_statement_active) {

                    if (if_statement_active) {
                        switch (i) {
                            case 0: // simple exp skip
                                break;
                            
                            case 1: // then part
                                append_linearized_node(tree, CG_EnterThen, current_head);
                                then_part = get_current_tail_node(current_head);
                                break;
                            case 2: // else part
                                 break;
                            default:
                                break;
                        }
                    }
                }
                
                linearize_ast(tree->child[i], symbol_table);  // Continue down the tree for code generation
                

                if (tree->nodekind == StmtK && tree->subkind.stmt == WhileK) {
                    if (i == 0) {
                        append_linearized_node(tree->child[1], CG_DoWhile, current_head);
                    }
                }
            
                if (tree->nodekind == StmtK && tree->subkind.stmt == IfK && if_statement_active) {

                    if (if_statement_active) {
                        switch (i) {
                            case 0: // simple exp skip
                                break;
                            case 1: // then part
                                append_linearized_node(tree, CG_LeaveThen, current_head);
                                else_part = get_current_tail_node(current_head);

                                break;
                            case 2: // else part
                                append_linearized_node(tree, CG_LeaveElse, current_head);
                                break;
                            default:
                                break;
                        }
                    }
                }
   
                if (tree->nodekind == StmtK && tree->subkind.stmt == RangeK) {
                    switch (i) {
                            case 0: 
                                append_linearized_node(last_for_node[last_for_node_idx - 1]->ast_node, CG_RangeSaveStart, current_head);
                                break;
                             case 1: 
                                append_linearized_node(last_for_node[last_for_node_idx - 1]->ast_node, CG_RangeSaveStop, current_head);
                                break;
                            case 2:
                                append_linearized_node(last_for_node[last_for_node_idx - 1]->ast_node, CG_RangeSaveStep, current_head);
                                break;
                            default:
                                break;
                    }
                }


            }
        }

        /* Post children traversal stuff */
        if (tree->nodekind==StmtK) {
            switch (tree->subkind.stmt) {
                case IfK: {

                    append_comment_node("END IF", current_head);
                    
                    break;
                }
                case WhileK: {
                    code_generation_linearized_node_t *last = last_while_node[last_while_node_idx];
                    code_generation_linearized_node_t *temp_list = initialize_temp_list();
                    code_generation_linearized_node_t *end_while_node;

                    while (last->action != CG_DoWhile) {
                        last = last->next;
                    }
                    
                    end_while_node = last->prev;

                    append_linearized_node(tree, CG_JumpToWhile, temp_list);
                    insert_linearized_node(temp_list, end_while_node);


                    
                    append_linearized_node(last_while_node[last_while_node_idx--]->ast_node, CG_LeaveWhile, current_head);
                    append_comment_node("END WHILE", current_head);

                    break;
                }
                case CompoundK:
                    append_linearized_node(tree, CG_CompoundStatementLeave, current_head);
                    last_compound_node_idx--;
                    //generate_compound_statement_leave(tree, symbol_table);

                    break;
                case BreakK:
                    append_linearized_node(last_compound_node[last_compound_node_idx - 1]->ast_node, CG_BreakStatement, current_head);
                    break;
                case ForK:
                    append_linearized_node(tree, CG_ForLeave, current_head);
                    break;
                case ReturnK:
                    
                    append_linearized_node(tree, CG_ReturnStatement, current_head);
                    //generate_return_statement(tree, symbol_table);
                    break;
                case RangeK:
                    append_linearized_node(last_for_node[last_for_node_idx - 1]->ast_node, CG_RangeLeave, current_head);
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
                    /* For indexed arrays */ 
                    if (tree->attr.op == LBRACKET) {
                        if (tree->child[0] != NULL && tree->child[0]->isParam && call_params_expected && tree->oper == 0) {
                            append_linearized_node(tree, CG_VarIndexParamLoad, current_head);
                            break;
                        }
                        
                        if (lhs_var_holders[lhs_var_holder] == tree->child[0]) {
                            append_linearized_node(tree, CG_VarIndexPush, current_head);
                        }
                        else {
                            append_linearized_node(tree, CG_PopLeftVarIndex, current_head);
                            if (tree->oper == DIV || tree->oper == TIMES || tree->oper == OR || tree->oper == AND || tree->oper == PLUS
                                    || tree->oper == NEQ || tree->oper == EQ || tree->oper == GT || tree->oper == MINUS) {
                                append_linearized_node(tree, CG_AssignLHSPush, current_head);
                            }

                        }
                        
                    }    

                    if (tree->attr.op == PLUS || tree->attr.op == MINUS || tree->attr.op == TIMES || tree->attr.op == DIV || tree->attr.op == MOD) {
                        append_linearized_node(tree, CG_BinaryOp, current_head);
                    }

                    if (tree->attr.op == LEQ || tree->attr.op == GT || tree->attr.op == EQ || tree->attr.op == AND || tree->attr.op == OR || tree->attr.op == LT || tree->attr.op == GEQ || tree->attr.op == NEQ) {
                        if (tree->attr.op == NOT) {
                        }

                        if (tree->child[0] != NULL) {
                            append_linearized_node(tree, CG_VarLHSOpParamLoad, current_head);
                        }
                    }

                    if (tree->attr.op == SIZEOF) {
                        if (tree->oper == TIMES || tree->oper == EQ ) {
                            append_linearized_node(tree, CG_AssignLHSPush, current_head);
                        }
                    }

                    break;
                case ConstantK:
                    if (tree->isParam && call_params_expected) {
                        if (sibling == 0) {
                            append_comment_node("Param 1", current_head);
                        }
                        else {
                            append_comment_node("Param 2", current_head);
                        }

                        append_linearized_node(tree, CG_LoadParameterConstant, current_head);
                        //generate_load_parameter_constant(tree, symbol_table);
                    }
                    else {
                        if (tree->initializer) {
                            if (tree->var_kind == Local) {
                                append_linearized_node(tree, CG_LoadConstant, function_array_node_list);
                                append_linearized_node(tree->param_sibling, CG_AssignLHSLoad, function_array_node_list);
                                break;
                            }
                            else {
                                append_linearized_node(tree, CG_LoadConstant, globals_statics_node_list);
                                append_linearized_node(tree->param_sibling, CG_AssignLHSLoad, globals_statics_node_list);
                                break;
                            }
                        }


                        append_linearized_node(tree, CG_LoadConstant, current_head);
                        if (tree->oper == DIV || tree->oper == TIMES || tree->oper == OR || tree->oper == AND || tree->oper == LT || tree->oper == EQ 
                                || tree->oper == GT || tree->oper == GEQ || tree->oper == LEQ || tree->oper == NEQ || tree->oper == PLUS || tree->oper == MINUS) {
                            append_linearized_node(tree, CG_AssignLHSPush, current_head);
                        }

                        //generate_load_constant(tree, symbol_table);
                    }

                    break;
                case IdK:

                    if (tree->isParam && !expect_lhs_var && call_params_expected) {
                        if (sibling == 0) {
                            append_comment_node("Param 1", current_head);
                        }
                        else {
                            append_comment_node("Param 2", current_head);
                        }

                        append_linearized_node(tree, CG_LoadParameterId, current_head);
                        //generate_load_parameter_id(tree, symbol_table);
                        break;
                    }
                     
                    if (expect_lhs_var) {
                        lhs_var_holders[++lhs_var_holder] = tree;

                        expect_lhs_var = false;

                    }
                    else {
                        
                        if (tree->isArray) {
                            append_linearized_node(tree, CG_VarIndexLoad, current_head);
                        }
                        else {
                            append_linearized_node(tree, CG_LoadVar, current_head);
                            if (tree->oper == DIV || tree->oper == TIMES || tree->oper == OR || tree->oper == AND || tree->oper == PLUS 
                                    || tree->oper == LT || tree->oper == MOD || tree->oper == LEQ || tree->oper == GEQ || tree->oper == GT || tree->oper == MINUS || tree->oper == EQ) {
                                append_linearized_node(tree, CG_AssignLHSPush, current_head);
                            }

                        }
                    }
                    
                    break;
                case AssignK: {

                    TreeNode *lhs_node = NULL;
                    lhs_node = lhs_var_holders[lhs_var_holder--];

                    lhs_node->oper = tree->attr.op;

                    if (lhs_node->isArray) {
                        if (tree->attr.op == ASGN) {
                            append_linearized_node(lhs_node, CG_AssignLHSLoadIndexed, current_head);
                        }
                        else {
                            append_linearized_node(lhs_node, CG_AssignOpLHSLoadIndexed, current_head);
                        }

                    }
                    else {
                        if (tree->attr.op == ASGN) {
                            append_linearized_node(lhs_node, CG_AssignLHSLoad, current_head);
                            if (tree->oper == TIMES || tree->oper == EQ || tree->oper == GT) {
                                append_linearized_node(lhs_node, CG_AssignLHSPush, current_head);
                            }
                        }
                        else {
                            append_linearized_node(lhs_node, CG_AssignOpLHSLoad, current_head);
                        }
                    }

                    if (lhs_node->isParam && lhs_node->var_kind != Parameter) {
                        append_linearized_node(lhs_node, CG_AssignPushParameter, current_head);
                    }

                    break;
                }
                case InitK:
                    break;
                case CallK:
                    append_linearized_node(tree, CG_FunctionCallLeave, current_head);
                    call_params_expected--;
    
                    if (tree->oper == NOT) {
                        append_linearized_node(tree, CG_CallUnaryOp, current_head);
                    }
                    //if (tree->attr.op == SIZEOF || tree->attr.op == MOD || tree->oper == PLUS || tree->oper == MINUS || tree->oper == DIV || tree->oper == TIMES) {
                    else if (tree->oper == TIMES || tree->oper == EQ || tree->oper == PLUS || tree->oper == MINUS || tree->oper == DIV || tree->oper == AND || tree->oper == OR) {
                            append_linearized_node(tree, CG_AssignLHSPush, current_head);
                    }
                    //}
                    else if (call_params_expected && tree->isParam) {
                        /* Produces push parameter ST for this Call that was a parameter */
                        append_linearized_node(tree, CG_AssignPushParameter, current_head);
                    }


                    //emitComment("Param end", tree->attr.name);
                    //generate_function_call_leave(tree, symbol_table);
                    break;
                default:
                break;
            }
        }
        else if (tree->nodekind==DeclK) {
            switch (tree->subkind.decl) {
                case VarK:
                    
                    if (tree->isArray) {
                        if (tree->var_kind == Local) {
                            append_linearized_node(tree, CG_VarArrayDeclaration, function_array_node_list);
                        }
                        else if (tree->var_kind == Global || tree->var_kind == LocalStatic) {
                            append_linearized_node(tree, CG_VarArrayDeclaration, globals_statics_node_list);
                        }
                        //generate_var_array_declartion(tree, symbol_table);
                    }
                    else {
                        append_linearized_node(tree, CG_VarDeclaration, current_head);
                        //generate_var_declartion(tree, symbol_table);
                    }

                    break;
                case ParamK:
                    break;
                case FuncK: {
                    append_comment_node("Compound Body", function_array_node_list); 
                    insert_linearized_node(function_array_node_list, last_compound_node[0]);
                    reset_func_array_node_list();

                    append_linearized_node(tree, CG_FunctionDefineLeave, current_head);
                    //generate_function_define_leave(tree, symbol_table);
                    }
                    break;
                default:
                    break;
            }
        }



        tree = tree->sibling;
        sibling++;

    }
}
