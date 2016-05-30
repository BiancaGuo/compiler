%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex(void);
	void yyerror(char *);
%}
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
ClassDef ';'
| Program ClassDef ';'
;
VariableDef:
Variable ';' {printf("\t\t//VariableDef");}
;
Variable:
Type MYIDENTIFIER
;
Type:
MYINT
|MYBOOL
|MYSTRING
|MYVOID
|MYCLASS MYIDENTIFIER
|Type '[' ']'
;
Formals:
Variable
|Formals ',' Variable
|
;
FunctionDef:
MYSTATIC Type MYIDENTIFIER '(' Formals ')' StmtBlock {printf("\t\t//FunctionDef");}
|Type MYIDENTIFIER '(' Formals ')' StmtBlock {printf("\t\t//FunctionDef");}
;
ClassDef:
MYCLASS MYIDENTIFIER MYEXTENDS MYIDENTIFIER '{' Fields '}'  {printf("\t\t//ClassDef");}
|MYCLASS MYIDENTIFIER '{' Fields '}'  {printf("\t\t//ClassDef");}
;
Fields:
Field
|Fields Field
|
;
Field:
FunctionDef
| VariableDef
;
StmtBlock:
'{' Stmts '}'
|'{' '}'
;
Stmts:
Stmt
|Stmt Stmts
;
Stmt:
VariableDef
|SimpleStmt ';'
|IfStmt
|WhileStmt
|ForStmt
|BreakStmt ';'
|ReturnStmt ';'
|PrintStmt ';'
|StmtBlock
;
SimpleStmt:
LValue '=' Expr
|Call
|
;
LValue:
Expr '.' MYIDENTIFIER
|MYIDENTIFIER  
|Expr '[' Expr ']'
;
Call:
Expr '.' MYIDENTIFIER '(' Actuals ')' {printf("\t\t//Call");}
|MYIDENTIFIER '(' Actuals ')' {printf("\t\t//Call");}
;
Actuals:
Expr
|Expr ',' Actuals
|
;
ForStmt:
MYFOR '(' SimpleStmt ';' BoolExpr ';' SimpleStmt ')' Stmt;
;
WhileStmt:
MYWHILE '(' BoolExpr ')' Stmt
;
IfStmt:
MYIF '(' BoolExpr ')' Stmt
|IfStmt MYELSE Stmt
;
ReturnStmt:
MYRETURN 
|MYRETURN Expr
;
BreakStmt:
MYBREAK
;
PrintStmt:
MYPRINT '(' Exprs ')'
;
Exprs:
Expr
|Expr ',' Exprs
|
;
BoolExpr:
Expr
;
Expr:
Constant
|LValue
|MYTHIS
|Call
|'(' Expr ')'
|Expr '+' Expr {printf("Expr '+' Expr")}
|Expr '-' Expr
|Expr '*' Expr
|Expr '/' Expr
|Expr '%' Expr
|'-' Expr
|Expr '<' Expr
|Expr MYLET Expr
|Expr '>' Expr
|Expr MYHET Expr
|Expr MYEQU Expr
|Expr MYUEQU Expr
|Expr MYAND Expr
|Expr MYOR Expr
|'!' Expr
|MYREADINTEGER '(' ')'
|MYREADLINE '(' ')'
|MYNEW MYIDENTIFIER '(' ')'
|MYNEW Type '[' Expr ']'
|MYINSTANCEOF '(' Expr ',' MYIDENTIFIER ')'
|'(' MYCLASS MYIDENTIFIER ')' Expr
;
Constant:
MYINTEGER {printf("%d", yylval);}
|MYDEX {printf("%d", yylval);}
|MYTRUE {printf("true");}
|MYFALSE {printf("false");}
|MYSTRING2
|MYNULL {printf("null");}
;
%%

void yyerror(char *s)
{
	printf("%s\n",s);
}

int main(void)
{
	yyparse();
	return 0;
}








