#include "SymbolTree.h"
#include <stdlib.h>

SymbolTableNode *root;
SymbolTableNode *list;	//用于清空tableTree

void createRoot()
{
	list = NULL;
	root = (SymbolTableNode *)malloc(sizeof(SymbolTableNode));
	root->header = createSymbolTable();
	root->parents = NULL;
}

SymbolTableNode *createTableNode(SymbolTableNode *newParents)
{
	SymbolTableNode *temp;
	temp = (SymbolTableNode *)malloc(sizeof(SymbolTableNode));
	temp->header = createSymbolTable();
	temp->parents = newParents;
	//插入结点的链表便于删除
	temp->next = list;
	list = temp;
}

void clearSymbolTree()
{
	SymbolTableNode *temp, *pretemp;
	temp = list;
	while(temp != NULL) {
		pretemp = temp;
		temp = temp->next;
		clearSymbolTable(&(pretemp->header));
		free(pretemp);
	}
}

SymbolNode *findSymbolFromTree(SymbolTableNode *node, char *symbolName)
{
	SymbolNode *result;
	while(node != NULL)
	{
		result = findSymbol(node->header, symbolName);
		if (result != NULL) return result;
		node = node->parents;
	}
	return NULL;
}