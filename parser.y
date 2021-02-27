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

%{
    // C Code before the rules
    int yyerror(); // yyerror declaration
%}

%%

// regras
programa: programa variaveis 
    |
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

variaveis: tipo TK_IDENTIFIER ':' literal ';'
    | vetor
    ;

vetor: tipo '[' LIT_INTEGER ']' TK_IDENTIFIER ':' literal_rec ';'
    | tipo '[' LIT_INTEGER ']' TK_IDENTIFIER ';'
    ;

terminador_ponto_virgula: ';'
    ;
/*
funcao: cabecalho_funcao corpo_funcao
    ;

cabecalho_funcao:
    ;

corpo_funcao: comando
    ;

comando:
    ;

bloco:
    ;






decl: dec resto
    |
    ;

resto: ',' dec resto 
    |
    ;

dec:  KW_INT TK_IDENTIFIER
    | KW_INT TK_IDENTIFIER '(' ')' body
    ;

body: '{' lcmd '}'
    ;

lcmd: cmd lcmd
    |
    ;

cmd: TK_IDENTIFIER LEFT_ASSIGN expr
    | expr RIGHT_ASSIGN TK_IDENTIFIER
    ;

expr: LIT_INTEGER
    | LIT_TRUE
    | LIT_FALSE
    | LIT_CHAR
    | LIT_STRING
    | TK_IDENTIFIER
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr '|' expr
    | expr '&' expr
    | expr '~' expr
    | expr '$' expr
    | expr '#' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | '(' expr ')'
    | '~' expr
    | '$' expr
    | '#' expr
    ;
    */
%%

// Anything in C

int yyerror() {
    fprintf(stderr, "Syntar Error at Line: %d near \"%s\"\n", getLineNumber(), yytext);
    printHashTable();
    exit(3);
}
