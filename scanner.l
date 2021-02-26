%{
  /*
   *  Autor: Gustavo Oliva Barnasque
   *  Matricula: 00263056
   */

  #include <stdlib.h>
  #include <stdio.h>
  #include "y.tab.h"
  #include "hash.h"

  #define SYMBOL_LIT_INT    1
  #define SYMBOL_LIT_CHAR   2
  #define SYMBOL_LIT_STRING 3
  #define SYMBOL_LIT_TRUE   4
  #define SYMBOL_LIT_FALSE  5
  #define SYMBOL_IDENTIFIER 6


  int running = 1;
  int lineNumber = 1;

  int isRunning(void) {
    return running;
  }

  int getLineNumber(void) {
    return lineNumber;
  }
  
  void initMe(void) {
    hashInit();
  }
%}

%x COMMENT

%%

"char"        {return KW_CHAR;}
"int"         {return KW_INT;}
"bool"        {return KW_BOOL;}
"pointer"     {return KW_POINTER;}
"if"          {return KW_IF;}
"then"        {return KW_THEN;}
"else"        {return KW_ELSE;}
"while"       {return KW_WHILE;}
"read"        {return KW_READ;}
"print"       {return KW_PRINT;}
"return"      {return KW_RETURN;}

"<="          {return OPERATOR_LE;}
">="          {return OPERATOR_GE;}
"=="          {return OPERATOR_EQ;}
"!="          {return OPERATOR_DIF;}
"<-"          {return LEFT_ASSIGN;}
"->"          {return RIGHT_ASSIGN;}

"true"        {return LIT_TRUE;}
"false"       {return LIT_FALSE;}
[0-9]+        {hashInsert(SYMBOL_LIT_INT, yytext); return LIT_INTEGER;}
'[^']*'       {hashInsert(SYMBOL_LIT_CHAR, yytext); return LIT_CHAR;}
\"((\\\")*[^\"]*)*\"        {hashInsert(SYMBOL_LIT_STRING, yytext); return LIT_STRING;}


[-,;:()\[\]{}+*/<>\|\&\~$#] {return yytext[0];}
[_a-zA-z][_0-9a-zA-Z]*      {hashInsert(SYMBOL_IDENTIFIER, yytext); return TK_IDENTIFIER;}

"\n"          { ++lineNumber;}
[ \t] 
"//".*  
"/*"          {BEGIN(COMMENT);}
.             {return TOKEN_ERROR;}


<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>"\n" {++lineNumber;}
<COMMENT>. 

%%

#include "y.tab.c"
#include "hash.c"
#include "main.c"

int yywrap() {
  running = 0;
  return 1;
}