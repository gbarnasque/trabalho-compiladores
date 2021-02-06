int main(int argc, char** argv) {
  int token;
  
  if(argc < 2) {
    fprintf(stderr, "Call: ./a.out file_name\n");
    exit(1);
  }

  yyin = fopen(argv[1], "r");



  while(running) {
    token = yylex();

    if(running == 0)
      break;

    switch(token) {
      case KW_CHAR: 
        printf("Encontrei KW_CHAR\n");
        break;
      case KW_INT:
        printf("Encontrei KW_INT\n");
        break;
      case KW_BOOL: 
        printf("Encontrei KW_BOOL\n");
        break;
      case KW_POINTER: 
        printf("Encontrei KW_POINTER\n");
        break;
      case KW_IF: 
        printf("Encontrei KW_IF\n");
        break;
      case KW_THEN: 
        printf("Encontrei KW_THEN\n");
        break;
      case KW_ELSE: 
        printf("Encontrei KW_ELSE\n");
        break;
      case KW_WHILE: 
        printf("Encontrei KW_WHILE\n");
        break;
      case KW_READ: 
        printf("Encontrei KW_READ\n");
        break;
      case KW_PRINT: 
        printf("Encontrei KW_PRINT\n");
        break;
      case KW_RETURN: 
        printf("Encontrei KW_RETURN\n");
        break;
      case OPERATOR_LE: 
        printf("Encontrei OPERATOR_LE\n");
        break;
      case OPERATOR_GE: 
        printf("Encontrei OPERATOR_GE\n");
        break;
      case OPERATOR_EQ: 
        printf("Encontrei OPERATOR_EQ\n");
        break;
      case OPERATOR_DIF: 
        printf("Encontrei OPERATOR_DIF\n");
        break;
      case LEFT_ASSIGN: 
        printf("Encontrei LEFT_ASSIGN\n");
        break;
      case RIGHT_ASSIGN: 
        printf("Encontrei RIGHT_ASSIGN\n");
        break;
      case TK_IDENTIFIER:
        printf("Encontrei TK_IDENTIFIER: %s\n", yytext);
        break;
      case LIT_INTEGER:
        printf("Encontrei LIT_INTEGER: %s\n", yytext);
        break;
      case LIT_TRUE:
        printf("Encontrei LIT_TRUE\n");
        break;
      case LIT_FALSE:
        printf("Encontrei LIT_FALSE\n");
        break;
      case LIT_CHAR:
        printf("Encontrei LIT_CHAR: %s\n", yytext);
        break;
      case LIT_STRING:
        printf("Encontrei LIT_STRING: %s\n", yytext);
        break;
      case TOKEN_ERROR:
        printf("Unexpected token: %d\n", token);
        break;
      default:
        printf("Encontrei %c\n", yytext[0]);
        break;
    }
  }
  //printf("File has %d lines\n", lineNumber);
  printf("File has %d lines\n", getLineNumber());

  printHashTable();
  printf("Main done!\n");

  exit(0);
}