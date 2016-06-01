
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MYBOOL = 258,
     MYBREAK = 259,
     MYCLASS = 260,
     MYELSE = 261,
     MYEXTENDS = 262,
     MYFOR = 263,
     MYIF = 264,
     MYINT = 265,
     MYNEW = 266,
     MYNULL = 267,
     MYRETURN = 268,
     MYSTRING = 269,
     MYTHIS = 270,
     MYVOID = 271,
     MYWHILE = 272,
     MYSTATIC = 273,
     MYPRINT = 274,
     MYREADINTEGER = 275,
     MYREADLINE = 276,
     MYINSTANCEOF = 277,
     MYFALSE = 278,
     MYTRUE = 279,
     MYSTRING2 = 280,
     MYIDENTIFIER = 281,
     MYSPACE = 282,
     MYINTEGER = 283,
     MYDEX = 284,
     MYHET = 285,
     MYLET = 286,
     MYEQU = 287,
     MYUEQU = 288,
     MYAND = 289,
     MYOR = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 13 "decaf.y"

int intValue;
char *stringValue;
struct Node *node;



/* Line 1676 of yacc.c  */
#line 95 "decaf.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


