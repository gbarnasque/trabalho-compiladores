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
      case KW_INT:
        printf("Encontrei KW_INT\n");
        break;
      case LIT_INTEGER:
        printf("Encontrei LIT_INT\n");
        break;
      case TOKEN_ERROR:
        printf("Unexpected token: %d\n", token);
        break;
      default:
        printf("Encontrei %c\n", yytext[0]);
        break;
    }
  }
  printf("File has %d lines\n", lineNumber);
  printf("Main done!\n");

  exit(0);
}