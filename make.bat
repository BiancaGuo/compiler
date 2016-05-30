flex decaf.lex
bison -d decaf.y
gcc -o decaf lex.yy.c decaf.tab.c
decaf.exe<b.c>a.txt