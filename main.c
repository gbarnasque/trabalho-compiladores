/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

FILE* out_arq;

void descompiladorAST(AstNode* arvore) {
  astPrint(arvore, 0);
}

int main(int argc, char** argv) {
  //int token;
  
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
  descompiladorAST(astFinal);

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