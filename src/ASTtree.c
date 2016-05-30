#include "ASTtree.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

Node *mkNode(char *name, int num, ...)
{
	va_list valist;
	int i, nodeSize;
	Node *newNode;
	nodeSize = sizeof(Node) + (num-1) * sizeof(Node *);
	printf("nodeSize = %d\n", nodeSize);
	if ((newNode = (Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = no_Leaf;
	newNode->name = (char *)malloc(strlen(name)+1);
	strcpy(newNode->name, name);
	newNode->num = num;

	va_start(valist, num);
	for (i = 0; i < num; i++)
		newNode->node[i] = va_arg(valist, Node *);
	va_end(valist);
	return newNode;
}

Node *mkLeaf_int(int value)
{
	int nodeSize;
	Node *newNode;
	nodeSize = sizeof(Node);
	if ((newNode = (Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = int_Leaf;
	newNode->intValue = value;
	return newNode;
}

Node *mkLeaf_string(char *value)
{
	int nodeSize;
	Node *newNode;
	nodeSize = sizeof(Node);
	if ((newNode = (Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = int_Leaf;
	newNode->stringValue = (char *)malloc(strlen(value)+1);
	strcpy(newNode->stringValue, value);
	return newNode;
}

Node *mkLeaf_name(char *value)
{
	int nodeSize;
	Node *newNode;
	nodeSize = sizeof(Node);
	if ((newNode = (Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = int_Leaf;
	newNode->name = (char *)malloc(strlen(value)+1);
	strcpy(newNode->name, value);
	return newNode;
}

void printAST(Node *head)
{
	int i;
	switch(head->nodeType)
	{
		case no_Leaf:
		printf("%s:\n", head->name);
		for(i = 0; i < head->num; i++)
			printAST(head->node[i]);
		break;
		case int_Leaf:
		printf(" %d ", head->intValue);
		break;
		case string_Leaf:
		printf(" %s ", head->stringValue);
		break;
		case variable_Leaf:
		printf(" %s ", head->name);
		break;
	}
}