/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int line_num; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/


// Kinds of Operators
// these are the token numbers for the operators same as in flex
typedef int OpKind;
// Kinds of Statements
//typedef enum {DeclK, StmtK, ExpK} NodeKind;
enum NodeKind {DeclK, StmtK, ExpK};
// Subkinds of Declarations
enum DeclKind {VarK, FuncK, ParamK};
// Subkinds of Statements
enum StmtKind {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK};
// Subkinds of Expressions
enum ExpKind {OpK, ConstantK, IdK, AssignK, InitK, CallK};
// ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
enum ExpType {Void, Integer, Boolean, Char, CharInt, UndefinedType};
// What kind of scoping is used? (decided during typing)
enum VarKind {None, Local, Global, Parameter, LocalStatic};

#define MAXCHILDREN 3

typedef struct treeNode
{
    // connectivity in the tree
    struct treeNode *child[MAXCHILDREN]; // children of the node
    struct treeNode *sibling; // siblings for the node
    // what kind of node
    int lineno; // linenum relevant to this node
    NodeKind nodekind; // type of this node

    union {
        DeclKind decl; // used when DeclK
        StmtKind stmt; // used when StmtK
        ExpKind exp; // used when ExpK
    } subkind;

    // extra properties about the node depending on type of the node
    union {
        OpKind op; // type of token (same as in bison)
        int value; // used when an integer constant or boolean
        unsigned char cvalue; // used when a character
        char *string; // used when a string constant
        char *name; // used when IdK
    } attr;

    ExpType type; // used when ExpK or DeclK for type checking
    bool isArray; // is this an array
    bool isStatic; // is staticly allocated?
// even more semantic stuff will go here in later assignments.
} TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif
