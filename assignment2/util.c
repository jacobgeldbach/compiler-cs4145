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

/* Procedure printToken prints a token 
 * and its lexeme to the file
 */
void printToken( OpKind op, const char* tokenString )
{ switch (op)
  { case IF:
    case THEN:
    case ELSE:
      printf(
         "reserved word: %s ",tokenString);
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
      printf(
          "NUM, val= %s\n",tokenString);
      break;
    case ID:
      printf(
          "ID, name= %s\n",tokenString);
      break;
      /*
    case ERROR:
      printf(
          "ERROR: %s\n",tokenString);
      break;
      */
    default: /* should never happen */
      printf("Unknown token: %d ",op);
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error at line %d\n",line_num);
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
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error at line %d\n",line_num);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->subkind.exp = kind;
    t->lineno = line_num;
    t->type = Void;
  }
  return t;
}

/* Function newDeclNode creates a new declaration 
 * node for syntax tree constructioantn
 */
TreeNode * newDeclNode(DeclKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error at line %d\n",line_num);
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

/* procedure printTree prints a syntax tree to the 
 *  file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree ) { 
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
                    break;
                case BreakK:
                    printf("Break ");
                    break;
                case ForK:
                    printf("For ");
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
                    break;
                case ConstantK:
                    if (tree->type == Boolean) {
                        if (tree->attr.value == 0) 
                            printf("Const false ");
                        else 
                            printf("Const true ");
                    }
                    else if (tree->type == Char) {
                        printf("Const '%c' ", tree->attr.cvalue);
                    }
                    else if (tree->type == CharInt) {
                        printf("Const %s ", tree->attr.string);
                    }
                    else {
                        printf("Const %d ", tree->attr.value);
                    }
                    break;
                case IdK:
                    printf("Id: %s ", tree->attr.name);
                    break;
                case AssignK:
                    printf("Assign: ");
                    printToken(tree->attr.op, "\0");
                    break;
                case InitK:
                    printf("Init: ");
                    break;
                case CallK:
                    printf("Call: %s ", tree->attr.name);
                    break;
                default:
                    printf("Unknown ExpNode kind\n");
                break;
            }
        }
        else if (tree->nodekind==DeclK) {
            switch (tree->subkind.decl) {
                case VarK:
                    printf("Var: %s  ", tree->attr.name);
                    break;
                case FuncK:
                    printf("Func: %s  ", tree->attr.name);
                    break;
                case ParamK:
                    printf("Parm: %s  ", tree->attr.name);
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
                printf("Child: %d  ", i);
                printTree(tree->child[i]);  // Recursive printing for children
                UNINDENT;  // Reset indentation
            }
        }
        tree = tree->sibling;
        sibling++;

    }
}
