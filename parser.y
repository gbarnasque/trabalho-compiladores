%{ 
    /*  
     *  Autor: Gustavo Oliva Barnasque
     *  Matricula: 00263056
     *
     *  Token region
     */ 
%}
%token KW_CHAR
%token KW_INT
%token KW_BOOL
%token KW_POINTER

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token TK_IDENTIFIER

%token LIT_INTEGER
%token LIT_TRUE
%token LIT_FALSE
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '+' '-'
%left '*' '/'
%left '|' '&'
%left '<' '>' OPERATOR_GE OPERATOR_LE OPERATOR_EQ OPERATOR_DIF
%left '~' '$' '#'


%{
    // C Code before the rules
    int yyerror(); // yyerror declaration
%}

%%

// regras
programa: l_declaracao 
    ;

tipo: KW_BOOL
    | KW_CHAR
    | KW_INT
    | KW_POINTER
    ;

literal: LIT_INTEGER
    | LIT_CHAR
    | LIT_TRUE
    | LIT_FALSE
    ;

literal_rec: literal literal_rec
    |
    ;

variavel: tipo TK_IDENTIFIER
    ;

variaveis: variavel ':' literal ';'
    | vetor
    ;

vetor: tipo '[' LIT_INTEGER ']' TK_IDENTIFIER ':' literal_rec ';'
    | tipo '[' LIT_INTEGER ']' TK_IDENTIFIER ';'
    ;

l_declaracao: declaracao l_declaracao
    | 
    ;

declaracao: variaveis
    | funcao
    ;


funcao: cabecalho_funcao corpo_funcao ';'
    ;

cabecalho_funcao: variavel '(' l_parametros_declaracao ')'
    ;
l_parametros_declaracao: variavel lc_parametros_declaracao
    |
    ;
lc_parametros_declaracao: ',' variavel lc_parametros_declaracao
    |
    ;

funcao_chamada: TK_IDENTIFIER '(' l_parametros_chamada')'
    ;
l_parametros_chamada: expressao lc_parametros_chamada
    |
    ;
lc_parametros_chamada: ',' expressao lc_parametros_chamada
    |
    ;

corpo_funcao: bloco_comandos
    ;

bloco_comandos: '{' l_comando '}'
    ;

l_comando: comando lc_comando
    |
    ;
lc_comando: ';' comando lc_comando
    | ';' 
    ;

comando: TK_IDENTIFIER LEFT_ASSIGN expressao
    | expressao RIGHT_ASSIGN TK_IDENTIFIER
    | TK_IDENTIFIER '[' expressao ']' LEFT_ASSIGN expressao
    | expressao RIGHT_ASSIGN TK_IDENTIFIER '[' expressao ']'
    | fluxo
    | KW_READ TK_IDENTIFIER
    | KW_PRINT l_expressao_string
    | KW_RETURN expressao 
    | bloco_comandos
    |
    ;

l_expressao_string: LIT_STRING
    | expressao
    | LIT_STRING ',' l_expressao_string
    | expressao ',' l_expressao_string
    ;

fluxo: KW_IF '(' expressao ')' KW_THEN comando
    | KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando
    | KW_WHILE '(' expressao ')' comando
    

expressao: literal
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expressao ']'
    | '(' expressao ')'
    | expressao '+' expressao
    | expressao '-' expressao
    | expressao '*' expressao
    | expressao '/' expressao
    | expressao '<' expressao
    | expressao '>' expressao 
    | expressao '|' expressao
    | expressao '&' expressao
    | '~' expressao
    | '$' expressao
    | '#' expressao
    | expressao OPERATOR_LE expressao
    | expressao OPERATOR_GE expressao
    | expressao OPERATOR_EQ expressao
    | expressao OPERATOR_DIF expressao
    | funcao_chamada
    ;

%%

// Anything in C

int yyerror() {
    fprintf(stderr, "Syntax Error at Line: %d near \"%s\"\n", getLineNumber(), yytext);
    
    //printHashTable(); // For Debug Purposes
    
    exit(3);
}
