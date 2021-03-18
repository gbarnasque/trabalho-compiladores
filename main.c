/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */



void descompiladorAST(AstNode*, FILE*);

int main(int argc, char** argv) {
  
  FILE* out_arq;

  if(argc < 3) {
    fprintf(stderr, "Call: ./etapa3 file_in_name file_out_name\n");
    exit(1);
  }  

  yyin = fopen(argv[1], "r");
  
  if(yyin == 0){
    fprintf(stderr, "Unable to open file: %s\n", argv[1]);
    exit(2);
  }

  initMe();

  yyparse();

  out_arq = fopen(argv[2], "w+");
  if(out_arq == 0){
    fprintf(stderr, "Unable to open file: %s\n", argv[2]);
    exit(2);
  }

  descompiladorAST(astFinal, out_arq);
  descompiladorAST(NULL, out_arq);

  printf("File has %d lines\n", getLineNumber());
  //printHashTable();
  printf("Compilation successful!\n");

  /*while(isRunning()) {
    token = yylex();

    if(running == 0)
      break;

    switch(token) {
      case KW_CHAR: 
        printf("Linha %d: Encontrei KW_CHAR\n", getLineNumber());
        break;
      case KW_INT:
        printf("Linha %d: Encontrei KW_INT\n", getLineNumber());
        break;
      case KW_BOOL: 
        printf("Linha %d: Encontrei KW_BOOL\n", getLineNumber());
        break;
      case KW_POINTER: 
        printf("Linha %d: Encontrei KW_POINTER\n", getLineNumber());
        break;
      case KW_IF: 
        printf("Linha %d: Encontrei KW_IF\n", getLineNumber());
        break;
      case KW_THEN: 
        printf("Linha %d: Encontrei KW_THEN\n", getLineNumber());
        break;
      case KW_ELSE: 
        printf("Linha %d: Encontrei KW_ELSE\n", getLineNumber());
        break;
      case KW_WHILE: 
        printf("Linha %d: Encontrei KW_WHILE\n", getLineNumber());
        break;
      case KW_READ: 
        printf("Linha %d: Encontrei KW_READ\n", getLineNumber());
        break;
      case KW_PRINT: 
        printf("Linha %d: Encontrei KW_PRINT\n", getLineNumber());
        break;
      case KW_RETURN: 
        printf("Linha %d: Encontrei KW_RETURN\n", getLineNumber());
        break;
      case OPERATOR_LE: 
        printf("Linha %d: Encontrei OPERATOR_LE\n", getLineNumber());
        break;
      case OPERATOR_GE: 
        printf("Linha %d: Encontrei OPERATOR_GE\n", getLineNumber());
        break;
      case OPERATOR_EQ: 
        printf("Linha %d: Encontrei OPERATOR_EQ\n", getLineNumber());
        break;
      case OPERATOR_DIF: 
        printf("Linha %d: Encontrei OPERATOR_DIF\n", getLineNumber());
        break;
      case LEFT_ASSIGN: 
        printf("Linha %d: Encontrei LEFT_ASSIGN\n", getLineNumber());
        break;
      case RIGHT_ASSIGN: 
        printf("Linha %d: Encontrei RIGHT_ASSIGN\n", getLineNumber());
        break;
      case TK_IDENTIFIER:
        printf("Linha %d: Encontrei TK_IDENTIFIER: %s\n", getLineNumber(), yytext);
        break;
      case LIT_INTEGER:
        printf("Linha %d: Encontrei LIT_INTEGER: %s\n", getLineNumber(), yytext);
        break;
      case LIT_TRUE:
        printf("Linha %d: Encontrei LIT_TRUE\n", getLineNumber());
        break;
      case LIT_FALSE:
        printf("Linha %d: Encontrei LIT_FALSE\n", getLineNumber());
        break;
      case LIT_CHAR:
        printf("Linha %d: Encontrei LIT_CHAR: %s\n", getLineNumber(), yytext);
        break;
      case LIT_STRING:
        printf("Linha %d: Encontrei LIT_STRING: %s\n", getLineNumber(), yytext);
        break;
      case TOKEN_ERROR:
        printf("Linha %d: Unexpected token: %d\n", getLineNumber(), token);
        break;
      default:
        printf("Linha %d: Encontrei %c\n", getLineNumber(), yytext[0]);
        break;
    }
  }*/

  exit(0);
}

void descompiladorAST(AstNode* node, FILE* arq) {
  if(node == NULL)
    return;

  switch (node->type)
  {
    case AST_SYMBOL: fprintf(arq, "%s", node->symbol->text); break;
    case AST_T_BOOL: fprintf(stderr, "AST_T_BOOL"); break;
    case AST_T_CHAR: fprintf(stderr, "AST_T_CHAR"); break;
    case AST_T_INT: fprintf(stderr, "AST_T_INT"); break;
    case AST_T_POINTER: fprintf(stderr, "AST_T_POINTER"); break;
    case AST_LITERAIS: fprintf(stderr, "AST_LITERAIS"); break;
    case AST_VARIAVEL: fprintf(stderr, "AST_VARIAVEL"); break;
    case AST_VARIAVEIS: fprintf(stderr, "AST_VARIAVEIS"); break;
    case AST_VETOR_DECLARACAO_INIT: fprintf(stderr, "AST_VETOR_DECLARACAO_INIT"); break;
    case AST_VETOR_DECLARACAO: fprintf(stderr, "AST_VETOR_DECLARACAO"); break;
    case AST_LISTA_DECLARACAO: fprintf(stderr, "AST_LISTA_DECLARACAO"); break;
    case AST_FUNCAO: fprintf(stderr, "AST_FUNCAO"); break;
    case AST_FUNCAO_CABECALHO: fprintf(stderr, "AST_FUNCAO_CABECALHO"); break;
    case AST_LISTA_PARAMETROS_DECLARACAO: fprintf(stderr, "AST_LISTA_PARAMETROS_DECLARACAO"); break;
    case AST_LISTA_PARAMETROS_DECLARACAO_C: fprintf(stderr, "AST_LISTA_PARAMETROS_DECLARACAO_C"); break;
    case AST_FUNCAO_CHAMADA: fprintf(stderr, "AST_FUNCAO_CHAMADA"); break;
    case AST_LISTA_PARAMETROS: fprintf(stderr, "AST_LISTA_PARAMETROS"); break;
    case AST_LISTA_PARAMETROS_CHAMADA_C: fprintf(stderr, "AST_LISTA_PARAMETROS_CHAMADA_C"); break;
    case AST_BLOCO_COMANDOS: fprintf(stderr, "AST_BLOCO_COMANDOS"); break;
    case AST_LISTA_COMANDOS: fprintf(stderr, "AST_LISTA_COMANDOS"); break;                
    case AST_LISTA_COMANDOS_C: fprintf(stderr, "AST_LISTA_COMANDOS_C"); break;
    case AST_PONTOVIRGULA: fprintf(stderr, "AST_PONTOVIRGULA"); break;
    case AST_LEFT_ASSIGN: fprintf(stderr, "AST_LEFT_ASSIGN"); break;
    case AST_RIGHT_ASSIGN: fprintf(stderr, "AST_RIGHT_ASSIGN"); break;
    case AST_LEFT_ASSIGN_VECTOR: fprintf(stderr, "AST_LEFT_ASSIGN_VECTOR"); break;
    case AST_RIGHT_ASSIGN_VECTOR: fprintf(stderr, "AST_RIGHT_ASSIGN_VECTOR"); break;
    case AST_READ: fprintf(stderr, "AST_READ"); break;
    case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
    case AST_PRINT_ARG1: fprintf(stderr, "AST_PRINT_ARG1"); break;
    case AST_PRINT_ARG2: fprintf(stderr, "AST_PRINT_ARG2"); break;
    case AST_IF: fprintf(stderr, "AST_IF"); break;
    case AST_IF_ELSE: fprintf(stderr, "AST_IF_ELSE"); break;
    case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
    case AST_VETOR: fprintf(stderr, "AST_VETOR"); break;
    case AST_PARENTESES: fprintf(stderr, "AST_PARENTESES"); break;
    case AST_OP_ADD: fprintf(stderr, "AST_OP_ADD"); break;
    case AST_OP_MINUS: fprintf(stderr, "AST_OP_MINUS"); break;
    case AST_OP_MULT: fprintf(stderr, "AST_OP_MULT"); break;
    case AST_OP_DIV: fprintf(stderr, "AST_OP_DIV"); break;
    case AST_OP_GR: fprintf(stderr, "AST_OP_GR"); break;
    case AST_OP_LO: fprintf(stderr, "AST_OP_LO"); break;
    case AST_OP_PIPE: fprintf(stderr, "AST_OP_PIPE"); break;
    case AST_OP_AND: fprintf(stderr, "AST_OP_AND"); break;
    case AST_OP_TIL: fprintf(stderr, "AST_OP_TIL"); break;
    case AST_OP_DOLAR: fprintf(stderr, "AST_OP_DOLAR"); break;
    case AST_OP_HASHTAG: fprintf(stderr, "AST_OP_HASHTAG"); break;
    case AST_OP_LE: fprintf(stderr, "AST_OP_LE"); break;
    case AST_OP_GE: fprintf(stderr, "AST_OP_GE"); break;
    case AST_OP_EQ: fprintf(stderr, "AST_OP_EQ"); break;
    case AST_OP_DIF: fprintf(stderr, "AST_OP_DIF"); break;
    case AST_RETURN: fprintf(stderr, "AST_RETURN"); break;
    case AST_VETOR_TAMANHO: fprintf(stderr, "AST_VETOR_TAMANHO"); break;

    default: break;
  }
  
  fprintf(arq, "chegou aqui dsadasdsadase novo");
  //astPrint(node, 0);
}