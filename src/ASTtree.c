#include "../common.h"

void error(char *log);

struct Node *mkNode(char *name, int num, ...)
{
	va_list valist;
	int i, nodeSize;
	struct Node *newNode;
	nodeSize = sizeof(struct Node) + (num-1) * sizeof(struct Node *);
	//printf("nodeSize = %d\n", nodeSize);
	if ((newNode = (struct Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = no_Leaf;
	newNode->name = (char *)malloc(strlen(name)+1);
	strcpy(newNode->name, name);
	newNode->num = num;

	va_start(valist, num);
	for (i = 0; i < num; i++)
		newNode->node[i] = va_arg(valist, struct Node *);
	va_end(valist);
	return newNode;
}

struct Node *mkLeaf_int(int value)
{
	int nodeSize;
	struct Node *newNode;
	nodeSize = sizeof(struct Node);
	if ((newNode = (struct Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = int_Leaf;
	newNode->intValue = value;
	newNode->num = 0;
	return newNode;
}

struct Node *mkLeaf_logic(int value)
{
	int nodeSize;
	struct Node *newNode;
	nodeSize = sizeof(struct Node);
	if ((newNode = (struct Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = logic_Leaf;
	newNode->logicValue = value;
	newNode->num = 0;
	return newNode;
}

struct Node *mkLeaf_string(char *value)
{
	int nodeSize;
	struct Node *newNode;
	nodeSize = sizeof(struct Node);
	if ((newNode = (struct Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = string_Leaf;
	newNode->stringValue = (char *)malloc(strlen(value)+1);
	strcpy(newNode->stringValue, value);
	newNode->num = 0;
	return newNode;
}

struct Node *mkLeaf_name(char *value)
{
	int nodeSize;
	struct Node *newNode;
	nodeSize = sizeof(struct Node);
	if ((newNode = (struct Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = name_Leaf;
	newNode->name = (char *)malloc(strlen(value)+1);
	strcpy(newNode->name, value);
	newNode->num = 0;
	return newNode;
}

struct Node *mkLeaf_other(NodeType type)
{
	int nodeSize;
	struct Node *newNode;
	nodeSize = sizeof(struct Node);
	if ((newNode = (struct Node *)malloc(nodeSize)) == NULL)
		printf("out of memory");
	newNode->nodeType = type;
	newNode->num = 0;
	return newNode;
}

void printAST(struct Node *head)
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
		case name_Leaf:
		printf(" %s ", head->name);
		break;
		case variable_Leaf:
		printf(" %s ", head->name);
		break;
		case logic_Leaf:
		printf(" %d ", head->logicValue);
		break;
		case NULL_Leaf:
		printf(" null ");
		break;
		case Blank_Leaf:
		printf(" ");
		break;
		case this_Leaf:
		printf(" this ");
		break;
		case break_Leaf:
		printf(" break ");
		break;
		case return_Leaf:
		printf(" return ");
		break;
		case type_int_Leaf:
		printf(" int ");
		break;
		case type_bool_Leaf:
		printf(" bool ");
		break;
		case type_string_Leaf:
		printf(" string ");
		break;
		case type_void_Leaf:
		printf(" void ");
		break;
		case syscall_readint:
		printf(" readint() ");
		break;
		case syscall_readline:
		printf(" readline() ");
		break;
	}
}

void createTableFromASTtree(struct Node *header)
{
	int i;
	DataType dataType_temp;
	if (header->nodeType != no_Leaf) {return ;}
	if (strcmp(header->name, "Program") == 0) {
		header->symbolTableNode = createRoot();
		header->node[0]->symbolTableNode = header->symbolTableNode;
	}
	else if (strcmp(header->name, "class-extends") == 0){
		if (insertSymbol(header->symbolTableNode->header, header->node[0]->name, Type_class, DataType_noDef, 0) == 0)
			error("identifier defined mutiple or header is null ");
		header->node[0]->symbolTableNode = header->symbolTableNode;
		header->node[1]->symbolTableNode = header->symbolTableNode;
		header->node[2]->symbolTableNode = createTableNode(header->symbolTableNode);
		insertToClassTable(header->node[0]->name, header->node[2]->symbolTableNode);
	}
	else if (strcmp(header->name, "class") == 0){	//
		if (insertSymbol(header->symbolTableNode->header, header->node[0]->name, Type_class, DataType_noDef, 0) == 0)
			error("identifier defined mutiple or header is null ");
		header->node[0]->symbolTableNode = header->symbolTableNode;
		header->node[1]->symbolTableNode = createTableNode(header->symbolTableNode);
		insertToClassTable(header->node[0]->name, header->node[1]->symbolTableNode);
	}
	else if (strcmp(header->name, "Static-function") == 0){	//
		if (insertSymbol(header->symbolTableNode->header, header->node[1]->name, Type_staticFunction, DataType_noDef, 0) == 0)
			error("identifier defined mutiple or header is null ");
		header->node[0]->symbolTableNode = header->symbolTableNode;
		header->node[1]->symbolTableNode = header->symbolTableNode;
		header->node[2]->symbolTableNode = header->node[3]->symbolTableNode = createTableNode(header->symbolTableNode);
	}
	else if (strcmp(header->name, "function") == 0){
		if (insertSymbol(header->symbolTableNode->header, header->node[1]->name, Type_function, DataType_noDef, 0) == 0)
			error("identifier defined mutiple or header is null ");
		header->node[0]->symbolTableNode = header->symbolTableNode;
		header->node[1]->symbolTableNode = header->symbolTableNode;
		header->node[2]->symbolTableNode = header->node[3]->symbolTableNode = createTableNode(header->symbolTableNode);
	}
	else if (strcmp(header->name, "Variable") == 0){	//
		if (header->node[0]->nodeType == type_int_Leaf) dataType_temp = DataType_int;
		else if (header->node[0]->nodeType == type_string_Leaf) dataType_temp = DataType_string;
		else if (header->node[0]->nodeType == type_bool_Leaf) dataType_temp = DataType_bool;
		else if (header->node[0]->nodeType == type_void_Leaf) dataType_temp = DataType_void;
		if (insertSymbol(header->symbolTableNode->header, header->node[1]->name, Type_variable, dataType_temp, 0) == 0)
			error("identifier defined mutiple or header is null ");
		header->node[0]->symbolTableNode = header->symbolTableNode;
		header->node[1]->symbolTableNode = header->symbolTableNode;
	}
	else if (strcmp(header->name, "StmtBlock") == 0){	//
		header->node[0]->symbolTableNode = createTableNode(header->symbolTableNode);
	}
	// else if (strcmp(header->name, "ReturnStmt") == 0){	//
	// 	printTable(header->symbolTableNode);
	// }
	else {
		for (i = 0; i < header->num; i++)
			header->node[i]->symbolTableNode = header->symbolTableNode;
	}
	for (i = 0; i < header->num; i++) {
		createTableFromASTtree(header->node[i]);
	}
}

void updateTable(struct Node *header)
{
	//继承的处理
	int i;
	if (header->num == 0)return ;
	if (strcmp(header->name, "class-extends") == 0){
		header->node[2]->symbolTableNode->parents = findInClassTable(header->node[1]->name);
	}
	for (i = 0; i < header->num; i++) {
		updateTable(header->node[i]);
	}
}

void Check(struct Node *header)
{
	SymbolCheck(header);
	TypeCheck(header);
}
void TypeCheck(struct Node *header)
{

}
void SymbolCheck(struct Node *header)
{

}

void genTAC(struct Node *header)
{
	
}
