#ifndef _CLASSTABLE_H
#define _CLASSTABLE_H

#include "../common.h"

typedef struct ClassTable {
	char *name;
	struct SymbolTableNode *node;
	struct ClassTable *next;
}ClassTable;

void insertToClassTable(char *newName, struct SymbolTableNode *newNode);
struct SymbolTableNode *findInClassTable(char *newName);
void clearClassTable();

#endif