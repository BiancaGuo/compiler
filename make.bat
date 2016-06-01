flex decaf.lex
bison -d decaf.y
gcc -o decaf src\*.c lex.yy.c decaf.tab.c  test.c
decaf.exe<b.c