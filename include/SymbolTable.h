#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

typedef enum {DataType_int, DataType_string}DataType;
typedef enum {Type_static, Type_variable, Type_function, Type_class}Type;

typedef struct FirstLetter {
	char letter;
	struct SymbolNode *symbolNode;
}FirstLetter;

typedef struct SymbolNode {
	char *name;
	Type type;
	DataType dataType;
	unsigned int addr;
	struct SymbolNode *next;
}SymbolNode;

FirstLetter *createSymbolTable();
int insertSymbol(FirstLetter *header, char *newName, Type newType, DataType newDataType, unsigned int newAddr);
SymbolNode *findSymbol(FirstLetter *header, char *symbolName);
void clearSymbolTable(FirstLetter **header);
extern unsigned int strlen(char *s);
extern char *strcpy(char* dest, const char *src);
extern int strcmp(const char *s1,const char *s2);

#endif