#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

typedef enum {DataType_noDef, DataType_int, DataType_bool, DataType_string, DataType_void}DataType;
typedef enum {Type_noDef, Type_static, Type_variable, Type_staticVariable, Type_function, Type_staticFunction, Type_class}Type;

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

struct FirstLetter *createSymbolTable();
int insertSymbol(struct FirstLetter *header, char *newName, Type newType, DataType newDataType, unsigned int newAddr);
struct SymbolNode *findSymbol(struct FirstLetter *header, char *symbolName);
void clearSymbolTable(struct FirstLetter **header);
extern unsigned int strlen(char *s);
extern char *strcpy(char* dest, const char *src);
extern int strcmp(const char *s1,const char *s2);

#endif