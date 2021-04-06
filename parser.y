%{ 
    /*  
     *  Autor: Gustavo Oliva Barnasque
     *  Matricula: 00263056
     */ 

     AstNode* astFinal;
%}

%union 
{
    HashNode* symbol;
    AstNode* ast;
}

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
%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEGER  
%token<symbol> LIT_TRUE
%token<symbol> LIT_FALSE
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING
%token<symbol> ';'

%token TOKEN_ERROR

%type<ast> programa
%type<ast> tipo
%type<ast> literal
%type<ast> literal_rec
%type<ast> variavel
%type<ast> variaveis
%type<ast> vetor
%type<ast> l_declaracao
%type<ast> declaracao
%type<ast> funcao
%type<ast> cabecalho_funcao
%type<ast> l_parametros_declaracao
%type<ast> lc_parametros_declaracao
%type<ast> funcao_chamada
%type<ast> l_parametros_chamada
%type<ast> lc_parametros_chamada
%type<ast> corpo_funcao
%type<ast> bloco_comandos
%type<ast> l_comando
%type<ast> lc_comando
%type<ast> comando
%type<ast> l_expressao_string
%type<ast> fluxo
%type<ast> expressao


%left '+' '-'
%left '*' '/'
%left '|' '&'
%left '<' '>' OPERATOR_GE OPERATOR_LE OPERATOR_EQ OPERATOR_DIF
%left '~' '$' '#'

%nonassoc KW_THEN
%nonassoc KW_ELSE

%{
    // C Code before the rules
    int yyerror(); // yyerror declaration
%}

%%

// regras
programa: l_declaracao { 
                        $$ = $1; 
                        astFinal = $$; 
                        astPrint(astFinal, 0); 
                        checkAndSetDeclarations(astFinal); 
                        checkUndeclared();
                        checkOperands(astFinal);
                        }
    ;

tipo: KW_BOOL       { $$ = astCreate(AST_T_BOOL, NULL, NULL, NULL, NULL, NULL); }
    | KW_CHAR       { $$ = astCreate(AST_T_CHAR, NULL, NULL, NULL, NULL, NULL); }
    | KW_INT        { $$ = astCreate(AST_T_INT, NULL, NULL, NULL, NULL, NULL); }
    | KW_POINTER    { $$ = astCreate(AST_T_POINTER, NULL, NULL, NULL, NULL, NULL); }
    ;

literal: LIT_INTEGER { $$ = astCreate(AST_SYMBOL, $1, NULL, NULL, NULL, NULL); }
    | LIT_CHAR       { $$ = astCreate(AST_SYMBOL, $1, NULL, NULL, NULL, NULL); }
    | LIT_TRUE       { $$ = astCreate(AST_SYMBOL, $1, NULL, NULL, NULL, NULL); }
    | LIT_FALSE      { $$ = astCreate(AST_SYMBOL, $1, NULL, NULL, NULL, NULL); }
    ;

literal_rec: literal literal_rec    { $$ = astCreate(AST_LITERAIS, NULL, $1, $2, NULL, NULL); }
    |                               { $$ = NULL;}
    ;

variavel: tipo TK_IDENTIFIER        { $$ = astCreate(AST_VARIAVEL, $2, $1, NULL, NULL, NULL); }
    ;

variaveis: variavel ':' literal ';' { $$ = astCreate(AST_VARIAVEIS, NULL, $1, $3, NULL, NULL); }
    | vetor                         { $$ = $1; }
    ;

vetor: tipo '[' LIT_INTEGER ']' TK_IDENTIFIER ':' literal_rec ';'   { $$ = astCreate(AST_VETOR_DECLARACAO_INIT, $5, $1, astCreate(AST_VETOR_TAMANHO, $3, NULL, NULL, NULL, NULL), $7, NULL); }
    | tipo '[' LIT_INTEGER ']' TK_IDENTIFIER ';'                    { $$ = astCreate(AST_VETOR_DECLARACAO, $5, $1, astCreate(AST_VETOR_TAMANHO, $3, NULL, NULL, NULL, NULL), NULL, NULL); }
    ;

l_declaracao: declaracao l_declaracao   { $$ = astCreate(AST_LISTA_DECLARACAO, NULL, $1, $2, NULL, NULL); }
    |                                   { $$ = NULL; }
    ;

declaracao: variaveis   { $$ = $1; }
    | funcao            { $$ = $1; }
    ;


funcao: cabecalho_funcao corpo_funcao ';'                           { $$ = astCreate(AST_FUNCAO, NULL, $1, $2, NULL, NULL); }
    ;

cabecalho_funcao: tipo TK_IDENTIFIER '(' l_parametros_declaracao ')'          { $$ = astCreate(AST_FUNCAO_CABECALHO, $2, $1, $4, NULL, NULL); }
    ;
l_parametros_declaracao: tipo TK_IDENTIFIER lc_parametros_declaracao          { $$ = astCreate(AST_LISTA_PARAMETROS_DECLARACAO, $2, $1, $3, NULL, NULL); }
    |                                                                         { $$ = NULL; }
    ;
lc_parametros_declaracao: ',' tipo TK_IDENTIFIER lc_parametros_declaracao     { $$ = astCreate(AST_LISTA_PARAMETROS_DECLARACAO_C, $3, $2, $4, NULL, NULL); }
    |                                                                         { $$ = NULL; }
    ;

funcao_chamada: TK_IDENTIFIER '(' l_parametros_chamada')'   { $$ = astCreate(AST_FUNCAO_CHAMADA, $1, $3, NULL, NULL, NULL); }
    ;
l_parametros_chamada: expressao lc_parametros_chamada       { $$ = astCreate(AST_LISTA_PARAMETROS, NULL, $1, $2, NULL, NULL); }
    |                                                       { $$ = NULL; }
    ;
lc_parametros_chamada: ',' expressao lc_parametros_chamada  { $$ = astCreate(AST_LISTA_PARAMETROS_CHAMADA_C, NULL, $2, $3, NULL, NULL); }
    |                                                       { $$ = NULL; }
    ;

corpo_funcao: bloco_comandos        { $$ = $1; }
    ;

bloco_comandos: '{' l_comando '}'   { $$ = astCreate(AST_BLOCO_COMANDOS, NULL, $2, NULL, NULL, NULL); }
    ;

l_comando: comando lc_comando       { $$ = astCreate(AST_LISTA_COMANDOS, NULL, $1, $2, NULL, NULL); }
    |                               { $$ = NULL; }
    ;
lc_comando: ';' comando lc_comando  { $$ = astCreate(AST_LISTA_COMANDOS_C, NULL, $2, $3, NULL, NULL); }
    | ';'                           { $$ = astCreate(AST_PONTOVIRGULA, NULL, NULL, NULL, NULL, NULL);; }
    ;

comando: TK_IDENTIFIER LEFT_ASSIGN expressao                    { $$ = astCreate(AST_LEFT_ASSIGN, $1, $3, NULL, NULL, NULL); }
    | expressao RIGHT_ASSIGN TK_IDENTIFIER                      { $$ = astCreate(AST_RIGHT_ASSIGN, $3, $1, NULL, NULL, NULL); }
    | TK_IDENTIFIER '[' expressao ']' LEFT_ASSIGN expressao     { $$ = astCreate(AST_LEFT_ASSIGN_VECTOR, $1, $3, $6, NULL, NULL); }
    | expressao RIGHT_ASSIGN TK_IDENTIFIER '[' expressao ']'    { $$ = astCreate(AST_RIGHT_ASSIGN_VECTOR, $3, $1, $5, NULL, NULL); }
    | fluxo                                                     { $$ = $1; }
    | KW_READ TK_IDENTIFIER                                     { $$ = astCreate(AST_READ, $2, NULL, NULL, NULL, NULL); }
    | KW_PRINT l_expressao_string                               { $$ = astCreate(AST_PRINT, NULL, $2, NULL, NULL, NULL); }
    | KW_RETURN expressao                                       { $$ = astCreate(AST_RETURN, NULL, $2, NULL, NULL, NULL); }
    | bloco_comandos                                            { $$ = $1; }
    |                                                           { $$ = NULL; }
    ;

l_expressao_string: LIT_STRING              { $$ = astCreate(AST_SYMBOL, $1, NULL, NULL, NULL, NULL); }
    | expressao                             { $$ = $1; }
    | LIT_STRING ',' l_expressao_string     { $$ = astCreate(AST_PRINT_ARG1, NULL, astCreate(AST_SYMBOL, $1, NULL, NULL, NULL, NULL), $3, NULL, NULL);}
    | expressao ',' l_expressao_string      { $$ = astCreate(AST_PRINT_ARG2, NULL, $1, $3, NULL, NULL); }
    ;

fluxo: KW_IF '(' expressao ')' KW_THEN comando                  { $$ = astCreate(AST_IF, NULL, $3, $6, NULL, NULL); }
    | KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando   { $$ = astCreate(AST_IF_ELSE, NULL, $3, $6, $8, NULL); }
    | KW_WHILE '(' expressao ')' comando                        { $$ = astCreate(AST_WHILE, NULL, $3, $5, NULL, NULL); }
    

expressao: literal                      { $$ = $1; }
    | TK_IDENTIFIER                     { $$ = astCreate(AST_SYMBOL, $1, NULL, NULL, NULL, NULL); }
    | TK_IDENTIFIER '[' expressao ']'   { $$ = astCreate(AST_VETOR, $1, $3, NULL, NULL, NULL); }
    | '(' expressao ')'                 { $$ = astCreate(AST_PARENTESES, NULL, $2, NULL, NULL, NULL); }
    | expressao '+' expressao           { $$ = astCreate(AST_OP_ADD, NULL, $1, $3, NULL, NULL); }
    | expressao '-' expressao           { $$ = astCreate(AST_OP_MINUS, NULL, $1, $3, NULL, NULL); /*fprintf(stderr, "%d - %d = %d\n", $1, $3, $1 - $3);*/ }
    | expressao '*' expressao           { $$ = astCreate(AST_OP_MULT, NULL, $1, $3, NULL, NULL); }
    | expressao '/' expressao           { $$ = astCreate(AST_OP_DIV, NULL, $1, $3, NULL, NULL); /*fprintf(stderr, "%d / %d = %d\n", $1, $3, $1 / $3);*/ }
    | expressao '<' expressao           { $$ = astCreate(AST_OP_LO, NULL, $1, $3, NULL, NULL); }
    | expressao '>' expressao           { $$ = astCreate(AST_OP_GR, NULL, $1, $3, NULL, NULL); }
    | expressao '|' expressao           { $$ = astCreate(AST_OP_PIPE, NULL, $1, $3, NULL, NULL); }
    | expressao '&' expressao           { $$ = astCreate(AST_OP_AND, NULL, $1, $3, NULL, NULL); }
    | '~' expressao                     { $$ = astCreate(AST_OP_TIL, NULL, $2, NULL, NULL, NULL); }
    | '$' expressao                     { $$ = astCreate(AST_OP_DOLAR, NULL, $2, NULL, NULL, NULL); }
    | '#' expressao                     { $$ = astCreate(AST_OP_HASHTAG, NULL, $2, NULL, NULL, NULL); }
    | expressao OPERATOR_LE expressao   { $$ = astCreate(AST_OP_LE, NULL, $1, $3, NULL, NULL); }
    | expressao OPERATOR_GE expressao   { $$ = astCreate(AST_OP_GE, NULL, $1, $3, NULL, NULL); }
    | expressao OPERATOR_EQ expressao   { $$ = astCreate(AST_OP_EQ, NULL, $1, $3, NULL, NULL); }
    | expressao OPERATOR_DIF expressao  { $$ = astCreate(AST_OP_DIF, NULL, $1, $3, NULL, NULL); }
    | funcao_chamada                    { $$ = $1; }
    ;

%%

// Anything in C

int yyerror() {
    fprintf(stderr, "Syntax Error at Line: %d near \"%s\"\n", getLineNumber(), yytext);
    
    //printHashTable(); // For Debug Purposes
    
    exit(3);
}
