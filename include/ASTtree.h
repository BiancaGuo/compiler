#ifndef _ASTTREE_H
#define _ASTTREE_H

#include "../common.h"

typedef enum {no_Leaf, int_Leaf, string_Leaf, variable_Leaf, name_Leaf,
	logic_Leaf, NULL_Leaf, this_Leaf, break_Leaf, return_Leaf, Blank_Leaf,
	type_int_Leaf, type_bool_Leaf, type_string_Leaf, type_void_Leaf, 
	syscall_readint, syscall_readline}NodeType;

typedef struct Node{
	NodeType nodeType;
	char *name;		//名称
	int intValue;
	int logicValue;
	char *stringValue;
	struct SymbolTableNode *symbolTableNode;	//对应的符号表结点
	int num;			//子节点个数
	struct Node *node[1];
}Node;

struct Node *mkNode(char *name, int num, ...);
struct Node *mkLeaf_int(int value);
struct Node *mkLeaf_logic(int value);
struct Node *mkLeaf_string(char *value);
struct Node *mkLeaf_name(char *value);
struct Node *mkLeaf_other(NodeType type);
void Check(struct Node *header);
void TypeCheck(struct Node *header);
void SymbolCheck(struct Node *header);
void createTableFromASTtree(struct Node *header);
void updateTable(struct Node *header);
void genTAC(struct Node *header);
void printAST(struct Node *head);
extern unsigned int strlen(char *s);
extern char *strcpy(char* dest, const char *src);

#endif