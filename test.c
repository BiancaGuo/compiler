#include <stdio.h>
#include <stdlib.h>
#include "SymbolTable.h"
#include "SymbolTree.h"

extern SymbolTableNode *root;

int main()
{
	SymbolNode *temp;
	SymbolTableNode *temp1, *temp2, *temp3;
	createRoot();
	temp1 = createTableNode(root);
	insertSymbol(temp1->header, "absc", 1, 1, 1);
	insertSymbol(root->header, "cccc", 2, 2, 2);
	insertSymbol(temp1->header, "shdjs", 3, 3, 3);
	temp = findSymbolFromTree(temp1, "cccc");
	if (temp == NULL)
		printf("can't find Symbol\n");
	else 
		printf("%s, %d, %d, %d", temp->name, temp->type, temp->dataType, temp->addr);
}