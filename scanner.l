%{
  #include "tokens.h"
  //#include "hash.h"
  int running = 1;
  int lineNumber = 1;
%}

%x COMMENT

%%

int           {return KW_INT;}
[0-9]+        {return LIT_INTEGER;}
[-;{}+*:\[\]] {return 3;}
"\n"          { ++lineNumber;}
[ \t] 
"//".*  
"/*"          {BEGIN(COMMENT);}
.             {return TOKEN_ERROR;}


<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>"\n" {++lineNumber;}
<COMMENT>. 

%%

//#include "hash.c"
#include "main.c"

int yywrap() {
  running = 0;
  return 1;
}