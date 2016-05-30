#ifndef _ASTTREE_H
#define _ASTTREE_H

typedef enum {no_Leaf, int_Leaf, string_Leaf, variable_Leaf}NodeType;

typedef struct Node{
	NodeType nodeType;
	char *name;		//名称
	int intValue;
	char *stringValue;
	int num;			//子节点个数
	struct Node *node[3];
}Node;

Node *mkNode(char *name, int num, ...);
Node *mkLeaf_int(int value);
Node *mkLeaf_string(char *value);
Node *mkLeaf_name(char *value);
void printAST(Node *head);
extern unsigned int strlen(char *s);
extern char *strcpy(char* dest, const char *src);

#endif