%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "include/ASTtree.h"
	#include "include/SymbolTable.h"
	#include "include/SymbolTree.h"
	int yylex(void);
	void yyerror(char *);
	void test(struct Node *header);
	struct Node *header;
%}

%union {
int intValue;
char *stringValue;
struct Node *node;
};


%type<node> Program
%type<node> ClassDef
%type<node> ClassDefs
%type<node> VariableDef
%type<node> Variable
%type<node> Identifier
%type<node> Type
%type<node> Formals
%type<node> FunctionDef
%type<node> Field
%type<node> StmtBlock
%type<node> Stmts
%type<node> Stmt
%type<node> SimpleStmt
%type<node> LValue
%type<node> Call
%type<node> Actuals
%type<node> ForStmt
%type<node> WhileStmt
%type<node> IfStmt
%type<node> ReturnStmt
%type<node> BreakStmt
%type<node> PrintStmt
%type<node> Exprs
%type<node> BoolExpr
%type<node> Expr
%type<node> Constant

%token MYBOOL MYBREAK MYCLASS MYELSE MYEXTENDS MYFOR MYIF MYINT MYNEW MYNULL MYRETURN MYSTRING MYTHIS MYVOID MYWHILE MYSTATIC MYPRINT MYREADINTEGER MYREADLINE MYINSTANCEOF MYFALSE MYTRUE MYSTRING2 MYIDENTIFIER MYSPACE MYINTEGER MYDEX MYHET MYLET MYEQU MYUEQU MYAND MYOR
%left MYOR 
%left MYAND
%left MYEQU MYUEQU
%left '<' '>' MYHET MYLET
%left '+' '-'
%left '*' '/' '%'
%right '!'
%%
Program:
ClassDefs  {$$ = header = mkNode("Program", 1, $1); }
;

ClassDefs:
ClassDef ';' {$$ = mkNode("ClassDef", 1, $1);}
| ClassDefs ClassDef ';' {$$ = mkNode("ClassDef", 2, $1, $2);}
;

ClassDef:
MYCLASS Identifier MYEXTENDS Identifier '{' Field '}'  {$$ = mkNode("class-extends", 3, $2, $4, $6);}
|MYCLASS Identifier '{' Field '}'  {$$ = mkNode("class", 2, $2, $4);}
;

Field:
FunctionDef {$$ = mkNode("Field", 1, $1);}
| VariableDef {$$ = mkNode("Field", 1, $1);;}
|Field FunctionDef {$$ = mkNode("Field", 2, $1, $2);}
|Field VariableDef {$$ = mkNode("Field", 2, $1, $2);}
;

FunctionDef:
MYSTATIC Type Identifier '(' Formals ')' StmtBlock {$$ = mkNode("Static-function", 4, $2, $3, $5, $7);}
|Type Identifier '(' Formals ')' StmtBlock {$$ = mkNode("function", 4, $1, $2, $4, $6);}
;

VariableDef:
Variable ';' {$$ = mkNode("VariableDef", 1, $1);}
;

Variable:
Type Identifier {$$ = mkNode("Variable", 2, $1, $2);}
;

Identifier:
MYIDENTIFIER {$$ = mkLeaf_name(yylval.stringValue);}

Type:
MYINT {$$ = mkLeaf_other(type_int_Leaf);}
|MYBOOL  {$$ = mkLeaf_other(type_bool_Leaf);}
|MYSTRING {$$ = mkLeaf_other(type_string_Leaf);}
|MYVOID {$$ = mkLeaf_other(type_void_Leaf);}
|MYCLASS Identifier {$$ = mkNode("Type_class", 1, $2);}
|Type '[' ']' {$$ = mkNode("Type_array", 1, $1);}
;

Formals:
Variable {$$ = mkNode("Formal", 1, $1);}
|Formals ',' Variable {$$ = mkNode("Formal", 2, $1, $3);}
| {$$ = mkLeaf_other(Blank_Leaf);}
;

StmtBlock:
'{' Stmts '}' {$$ = mkNode("StmtBlock", 1, $2);}
|'{' '}' {$$ = mkLeaf_other(Blank_Leaf);}
;
Stmts:
Stmt {$$ = mkNode("Stmts", 1, $1);}
|Stmt Stmts {$$ = mkNode("Stmts", 2, $1, $2);}
;
Stmt:
VariableDef {$$ = mkNode("Stmt", 1, $1);}
|SimpleStmt ';' {$$ = mkNode("Stmt", 1, $1);}
|IfStmt {$$ = mkNode("Stmt", 1, $1);}
|WhileStmt {$$ = mkNode("Stmt", 1, $1);}
|ForStmt {$$ = mkNode("Stmt", 1, $1);}
|BreakStmt ';' {$$ = mkNode("Stmt", 1, $1);}
|ReturnStmt ';' {$$ = mkNode("Stmt", 1, $1);}
|PrintStmt ';' {$$ = mkNode("Stmt", 1, $1);}
|StmtBlock {$$ = mkNode("Stmt", 1, $1);}
;
SimpleStmt:
LValue '=' Expr {$$ = mkNode("=", 2, $1, $3);}
|Call {$$ = mkNode("SimpleStmt", 1, $1);}
;
LValue:
Expr '.' Identifier {$$ = mkNode(".", 2, $1, $3);} 
|Identifier  {$$ = mkNode("LValue", 1, $1);} 
|Expr '[' Expr ']' {$$ = mkNode("Array", 2, $1, $3);}
;
Call:
Expr '.' Identifier '(' Actuals ')' {$$ = mkNode("ClassCall", 3, $1, $3, $5);}
|Identifier '(' Actuals ')' {$$ = mkNode("Call", 2, $1, $3);}
;
Actuals:
Expr {$$ = mkNode("Actuals", 1, $1);}
|Expr ',' Actuals {$$ = mkNode("Actuals", 2, $1, $3);}
| {$$ = mkLeaf_other(Blank_Leaf);}
;
ForStmt:
MYFOR '(' SimpleStmt ';' BoolExpr ';' SimpleStmt ')' StmtBlock {$$ = mkNode("ForStmt", 4, $3, $5, $7, $9);}
;
WhileStmt:
MYWHILE '(' BoolExpr ')' StmtBlock {$$ = mkNode("WhileStmt", 2, $3, $5);}
;
IfStmt:
MYIF '(' BoolExpr ')' StmtBlock {$$ = mkNode("IfStmt", 2, $3, $5);}
|IfStmt MYELSE StmtBlock {$$ = mkNode("If-else", 2, $1, $3);}
;
ReturnStmt:
MYRETURN {$$ = mkNode("ReturnStmt", 0);}
|MYRETURN Expr {$$ = mkNode("ReturnStmt", 1, $2);}
;
BreakStmt:
MYBREAK {$$ = mkLeaf_other(break_Leaf);}
;
PrintStmt:
MYPRINT '(' Exprs ')' {$$ = mkNode("PrintStmt", 1, $3);}
;
Exprs:
Expr {$$ = mkNode("Exprs", 1, $1);}
|Expr ',' Exprs {$$ = mkNode("Exprs", 2, $1, $3);}
| {$$ = mkLeaf_other(Blank_Leaf);}
;
BoolExpr:
Expr {$$ = mkNode("Expr", 1, $1);}
;
Expr:
Constant {$$ = mkNode("Constant", 1, $1);}
|LValue {$$ = mkNode("Expr", 1, $1);}
|MYTHIS {$$ = mkLeaf_other(this_Leaf);}
|Call {$$ = mkNode("Expr", 1, $1);}
|'(' Expr ')' {$$ = mkNode("Expr", 1, $2);}
|Expr '+' Expr {$$ = mkNode("+", 2, $1, $3);}
|Expr '-' Expr {$$ = mkNode("-", 2, $1, $3);}
|Expr '*' Expr {$$ = mkNode("*", 2, $1, $3);}
|Expr '/' Expr {$$ = mkNode("/", 2, $1, $3);}
|Expr '%' Expr {$$ = mkNode("%", 2, $1, $3);}
|'-' Expr {$$ = mkNode("-", 1, $2);}
|Expr '<' Expr {$$ = mkNode("<", 2, $1, $3);}
|Expr MYLET Expr {$$ = mkNode("<=", 2, $1, $3);}
|Expr '>' Expr {$$ = mkNode(">", 2, $1, $3);}
|Expr MYHET Expr {$$ = mkNode(">=", 2, $1, $3);}
|Expr MYEQU Expr {$$ = mkNode("==", 2, $1, $3);}
|Expr MYUEQU Expr {$$ = mkNode("!=", 2, $1, $3);}
|Expr MYAND Expr {$$ = mkNode("&&", 2, $1, $3);}
|Expr MYOR Expr {$$ = mkNode("||", 2, $1, $3);}
|'!' Expr {$$ = mkNode("!", 1, $2);}
|MYREADINTEGER '(' ')' {$$ = mkLeaf_other(syscall_readint);}
|MYREADLINE '(' ')' {$$ = mkLeaf_other(syscall_readline);}
|MYNEW Identifier '(' ')' {$$ = mkNode("new_class", 1, $2);}
|MYNEW Type '[' Expr ']' {$$ = mkNode("new_array", 2, $2, $4);}
|MYINSTANCEOF '(' Expr ',' Identifier ')' {$$ = mkNode("instanceof", 2, $3, $5);}
;
Constant:
MYINTEGER {$$ = mkLeaf_int(yylval.intValue);}
|MYDEX {$$ = mkLeaf_int(yylval.intValue);}
|MYTRUE {$$ = mkLeaf_logic(1);}
|MYFALSE {$$ = mkLeaf_logic(0);}
|MYSTRING2 {$$ = mkLeaf_string(yylval.stringValue);}
|MYNULL {$$ = mkLeaf_other(NULL_Leaf);}
;
%%

void yyerror(char *s)
{
	printf("%s\n",s);
}

int main(void)
{
	yyparse();
	createTableFromASTtree(header);
	updateTable(header);
	test(header);
	return 0;
}








