#ifndef _SYMBOLTREE_H
#define _SYMBOLTREE_H

#include "SymbolTable.h"
#include "ASTtree.h"

typedef struct SymbolTableNode{
	struct FirstLetter *header;
	struct SymbolTableNode *parents, *next;
}SymbolTableNode;

struct SymbolTableNode *createRoot();
struct SymbolTableNode *createTableNode(struct SymbolTableNode *newParents);
void clearSymbolTree();
struct SymbolNode *findSymbolFromTree(struct SymbolTableNode *node, char *symbolName);
void printTable(struct SymbolTableNode *node);


#endif