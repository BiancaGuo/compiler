#include "../include/ClassTable.h"

ClassTable *classTableHeader = NULL;

void insertToClassTable(char *newName, struct SymbolTableNode *newNode)
{
	ClassTable *temp = (ClassTable *)malloc(sizeof(ClassTable));
	temp->name = (char *)malloc(strlen(newName)+1);
	strcpy(temp->name, newName);
	temp->node = newNode;
	temp->next = classTableHeader;
	classTableHeader = temp;
}
struct SymbolTableNode *findInClassTable(char *newName)
{
	ClassTable *temp;
	for (temp = classTableHeader; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->name, newName) == 0)
			return temp->node;
	}
	return NULL;
}
void clearClassTable()
{
	//to clear table;
}
