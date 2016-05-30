#include <stdio.h>
#include "ASTtree.h"

int main()
{
	Node *head = mkNode("assign", 2, mkLeaf_int(10), mkNode("aa", 1, mkLeaf_int(20)));
	printAST(head);
}