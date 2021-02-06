%{
  #include "tokens.h"
  #include "hash.h"
  #include "functions.h"
  int running = 1;
  int lineNumber = 1;
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

[0-9]+        {insert(LIT_INTEGER, yytext);return LIT_INTEGER;}
\'.\'         {insert(LIT_CHAR, yytext);return LIT_CHAR;}
\".+\"        {insert(LIT_STRING, yytext);return LIT_STRING;}
"true"        {insert(LIT_TRUE, yytext);return LIT_TRUE;}
"false"       {insert(LIT_FALSE, yytext);return LIT_FALSE;}

[-,;:()\[\]{}+*/<>\|\&\~$#] {return yytext[0];}
[_a-zA-z][_0-9a-zA-Z]*      {insert(TK_IDENTIFIER, yytext);return TK_IDENTIFIER;}

"\n"          { ++lineNumber;}
[ \t] 
"//".*  
"/*"          {BEGIN(COMMENT);}
.             {return TOKEN_ERROR;}


<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>"\n" {++lineNumber;}
<COMMENT>. 

%%

#include "hash.c"
#include "functions.c"
#include "main.c"

int yywrap() {
  running = 0;
  return 1;
}