#include "include/ASTtree.h"

void test(struct Node *header)
{
	int i;
	if (header->num == 0)return ;
	if (strcmp(header->name, "ReturnStmt") == 0){
		printTable(header->symbolTableNode);
	}
	for (i = 0; i < header->num; i++) {
		test(header->node[i]);
	}
}