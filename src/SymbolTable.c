#include "../include/SymbolTable.h"
#include <stdlib.h>
#include <stdio.h>

struct FirstLetter *createSymbolTable()
{
	int i;
	struct FirstLetter *header;
	header = (struct FirstLetter *)malloc(sizeof(struct FirstLetter) * (26*2+1)); //大写小写和_
	for(i = 0; i < 26; i++)
		header[i].letter = 'a'+i;
	for(;i < 52; i++)
		header[i].letter = 'A'+i-26;
	header[i].letter = '_';
	for(i = 0; i < 53; i++)
		header[i].symbolNode = NULL;
	return header;
}

//插入符号信息
int insertSymbol(struct FirstLetter *header, char *newName, Type newType, DataType newDataType, unsigned int newAddr)
{
	struct SymbolNode *temp;
	if (header == NULL) {
		return 0;
	}
	
	temp = (struct SymbolNode *)malloc(sizeof(struct SymbolNode));
	temp->name = (char *)malloc(sizeof(strlen(newName))+1);
	strcpy(temp->name, newName);
	temp->type = newType;
	temp->dataType = newDataType;
	temp->addr = newAddr;
	if (newName[0] >= 'a' && newName[0] <= 'z') {
		temp->next = header[newName[0]-'a'].symbolNode;
		header[newName[0]-'a'].symbolNode = temp;
	}else if (newName[0] >= 'A' && newName[0] <= 'Z') {
		temp->next = header[newName[0]-'A'+26].symbolNode;
		header[newName[0]-'A'+26].symbolNode = temp;
	}else if (newName[0] == '_') {
		temp->next = header[52].symbolNode;
		header[52].symbolNode = temp;
	}
	return 1;
}

//如果查到返回符号信息，否则返回空
struct SymbolNode *findSymbol(struct FirstLetter *header, char *symbolName)
{
	int index;
	struct SymbolNode *temp;
	if (header == NULL) return NULL;
	if (symbolName[0] >= 'a' && symbolName[0] <= 'z')
		index = symbolName[0] - 'a';
	else if (symbolName[0] >= 'A' && symbolName[0] <= 'Z')
		index = symbolName[0] - 'A' + 26;
	else if (symbolName[0] == '_')
		index = 52;
	else return NULL;
	for (temp = header[index].symbolNode; temp != NULL; temp = temp->next) {
		if (strcmp(temp->name, symbolName) == 0)
			return temp;
	}
	return NULL;
}

void clearSymbolTable(struct FirstLetter **header)
{
	int i;
	struct SymbolNode *temp, *pretemp;
	if (header == NULL) return ;
	if (*header == NULL) return ;
	for (i = 0; i < 53; i++) {
		temp = (*header)[i].symbolNode;
		while(temp != NULL) {
			pretemp = temp;
			temp = temp->next;
			free(pretemp);
		}
	}
	free(*header);
	*header = NULL;
}