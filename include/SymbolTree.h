#ifndef _SYMBOLTREE_H
#define _SYMBOLTREE_H

#include "SymbolTable.h"

typedef struct SymbolTableNode{
	FirstLetter *header;
	struct SymbolTableNode *parents, *next;
}SymbolTableNode;

void createRoot();
SymbolTableNode *createTableNode(SymbolTableNode *newParents);
void clearSymbolTree();
SymbolNode *findSymbolFromTree(SymbolTableNode *node, char *symbolName);


#endif