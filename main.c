/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */


FILE* out_arq;
void descompiladorAST(AstNode*);

int main(int argc, char** argv) {
  
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
  descompiladorAST(NULL);

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

void descompiladorAST(AstNode* node) {
  if(out_arq == 0)
    return;
  if(node == NULL)
    return;

  switch (node->type)
  {
    case AST_SYMBOL: 
      fprintf(out_arq, "%s", node->symbol->text); 
      break;
    case AST_T_BOOL: 
      fprintf(out_arq, "bool"); 
      break;
    case AST_T_CHAR: 
      fprintf(out_arq, "char"); 
      break;
    case AST_T_INT: 
      fprintf(out_arq, "int"); 
      break;
    case AST_T_POINTER: 
      fprintf(out_arq, "pointer"); 
      break;
    case AST_LITERAIS: 
      descompiladorAST(node->nodes[0]); 
      fprintf(out_arq, " "); 
      descompiladorAST(node->nodes[1]); 
      break;
    case AST_VARIAVEL: 
      descompiladorAST(node->nodes[0]); 
      fprintf(out_arq, " %s", node->symbol->text); 
      break;
    case AST_VARIAVEIS: 
      descompiladorAST(node->nodes[0]); 
      fprintf(out_arq, " : "); 
      descompiladorAST(node->nodes[1]); 
      fprintf(out_arq, ";\n"); 
      break;
    case AST_VETOR_DECLARACAO_INIT: 
      descompiladorAST(node->nodes[0]); 
      fprintf(out_arq, "["); 
      descompiladorAST(node->nodes[1]); 
      fprintf(out_arq, "] %s : ", node->symbol->text); 
      descompiladorAST(node->nodes[2]); 
      fprintf(out_arq, ";\n"); 
      break;
    case AST_VETOR_DECLARACAO: 
      descompiladorAST(node->nodes[0]); 
      fprintf(out_arq, "["); 
      descompiladorAST(node->nodes[1]); 
      fprintf(out_arq, "] %s ;\n", node->symbol->text); 
      break;
    case AST_LISTA_DECLARACAO: 
      descompiladorAST(node->nodes[0]); 
      descompiladorAST(node->nodes[1]); 
      break;
    case AST_FUNCAO: 
      descompiladorAST(node->nodes[0]); 
      descompiladorAST(node->nodes[1]); 
      fprintf(out_arq, ";\n"); 
      break;
    case AST_FUNCAO_CABECALHO: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " %s (", node->symbol->text);
      descompiladorAST(node->nodes[1]);
      fprintf(out_arq, ") ");
      break;
    case AST_LISTA_PARAMETROS_DECLARACAO: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " %s", node->symbol->text);
      descompiladorAST(node->nodes[1]);
      break;
    case AST_LISTA_PARAMETROS_DECLARACAO_C: 
      fprintf(out_arq, ", ");
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " %s", node->symbol->text);
      descompiladorAST(node->nodes[1]);
      break;
    case AST_FUNCAO_CHAMADA: 
      fprintf(out_arq, "%s(", node->symbol->text);
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, ")");
      break;
    case AST_LISTA_PARAMETROS: 
      descompiladorAST(node->nodes[0]);
      descompiladorAST(node->nodes[1]);
      break;
    case AST_LISTA_PARAMETROS_CHAMADA_C:
      fprintf(out_arq, ", ");
      descompiladorAST(node->nodes[0]);
      descompiladorAST(node->nodes[1]);
      break;
    case AST_BLOCO_COMANDOS:
      fprintf(out_arq, "{\n");
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, "\n}");
    break;
    case AST_LISTA_COMANDOS: 
      fprintf(out_arq, "  ");
      descompiladorAST(node->nodes[0]);
      descompiladorAST(node->nodes[1]);
      break;                
    case AST_LISTA_COMANDOS_C: 
      fprintf(out_arq, ";\n  ");
      descompiladorAST(node->nodes[0]);
      descompiladorAST(node->nodes[1]);
      break;
    case AST_PONTOVIRGULA: 
      fprintf(out_arq, ";");
      break;
    case AST_LEFT_ASSIGN: 
      fprintf(out_arq, "%s <- ", node->symbol->text);
      descompiladorAST(node->nodes[0]);
      break;
    case AST_RIGHT_ASSIGN:
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " -> %s", node->symbol->text);
      break;
    case AST_LEFT_ASSIGN_VECTOR: 
      fprintf(out_arq, "%s[", node->symbol->text);
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, "] <- ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_RIGHT_ASSIGN_VECTOR: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " -> %s[", node->symbol->text);
      descompiladorAST(node->nodes[1]);
      fprintf(out_arq, "]");
      break;
    case AST_READ: 
      fprintf(out_arq, "read %s", node->symbol->text); 
      break;
    case AST_PRINT: 
      fprintf(out_arq, "print ");
      descompiladorAST(node->nodes[0]);
      break;
    case AST_RETURN: 
      fprintf(out_arq, "return ");
      descompiladorAST(node->nodes[0]); 
      break;
    case AST_PRINT_ARG1: 
    case AST_PRINT_ARG2:
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, ", ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_IF: 
      fprintf(out_arq, "if (");
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, ") then ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_IF_ELSE: 
      fprintf(out_arq, "if (");
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, ") then ");
      descompiladorAST(node->nodes[1]);
      fprintf(out_arq, " else ");
      descompiladorAST(node->nodes[2]);
      break;
    case AST_WHILE: 
      fprintf(out_arq, "while (");
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, ") ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_VETOR: 
      fprintf(out_arq, "%s [", node->symbol->text);
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, "]");
      break;
    case AST_PARENTESES: 
      fprintf(out_arq, "(");
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, ")");
      break;
    case AST_OP_ADD: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " + ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_MINUS: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " - ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_MULT: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " * ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_DIV: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " / ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_LO: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " < ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_GR: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " > ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_PIPE: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " | ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_AND: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " & ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_TIL:
      fprintf(out_arq, " ~");
      descompiladorAST(node->nodes[0]);
      break;
    case AST_OP_DOLAR: 
      fprintf(out_arq, " $");
      descompiladorAST(node->nodes[0]);
      break;
    case AST_OP_HASHTAG: 
      fprintf(out_arq, " #");
      descompiladorAST(node->nodes[0]);
      break;
    case AST_OP_LE: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " <= ");
      descompiladorAST(node->nodes[1]); 
      break;
    case AST_OP_GE: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " >= ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_EQ:
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " == ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_OP_DIF: 
      descompiladorAST(node->nodes[0]);
      fprintf(out_arq, " != ");
      descompiladorAST(node->nodes[1]);
      break;
    case AST_VETOR_TAMANHO: fprintf(out_arq, "%s", node->symbol->text); break;

    default: break;
  }
}