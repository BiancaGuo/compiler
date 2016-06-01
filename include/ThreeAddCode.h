#ifndef _THREEADDCODE_H
#define _THREEADDCODE_H

typedef struct CodeLine {
	char *op;
	unsigned int addr[3];
	struct CodeLine *next;
}CodeLine;

typedef struct ThreeAddCode {
	struct CodeLine *head, *tail; 
}ThreeAddCode;


ThreeAddCode *LinkTAC(ThreeAddCode *code1, ThreeAddCode *code2);
ThreeAddCode *CreateTAC(char *newOp, unsigned int addr1, unsigned int addr2, unsigned int addr3);





#endif