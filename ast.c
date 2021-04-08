/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */
#include "ast.h"

AstNode* astCreate(int type, HashNode* symbol, AstNode* s0, AstNode* s1, AstNode* s2, AstNode* s3) {
    AstNode* ret;
    ret = (AstNode*) malloc(sizeof(AstNode));
    ret->type = type;
    ret->dataType = 0;
    ret->symbol = symbol;
    ret->nodes[0] = s0;
    ret->nodes[1] = s1;
    ret->nodes[2] = s2;
    ret->nodes[3] = s3;
    ret->lineNumber = getLineNumber();
    return ret;
}

void astPrint(AstNode* node, int level) {
    int i;
    if(node == NULL)
        return;

    for(i=0; i<level; i++)
        fprintf(stderr, "  ");
    fprintf(stderr, "AST(");

    printNodeType(node->type);

    if(node->symbol != NULL)
        fprintf(stderr, ", %s", node->symbol->text);
    else 
        fprintf(stderr, ", ''");
    
    printNodeDataType(node->dataType);

    for(i=0; i<MAX_SONS; i++)
        astPrint(node->nodes[i], level+1);
    //fprintf(stderr, ")\n");
}

void printNodeType(int type) {
    switch (type)
    {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
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
        case AST_END_PROGRAM: fprintf(stderr, ")"); break;
        default:
            fprintf(stderr, "AST_UNKNOW");
            break;
    }
}

void printNodeDataType(int datatype) {
    switch (datatype)
    {
    case AST_DATATYPE_BOOL: fprintf(stderr, ", AST_DATATYPE_BOOL\n"); break;
    case AST_DATATYPE_INT: fprintf(stderr, ", AST_DATATYPE_INT\n"); break;
    case AST_DATATYPE_CHAR: fprintf(stderr, ", AST_DATATYPE_CHAR\n"); break;
    case AST_DATATYPE_POINTER: fprintf(stderr, ", AST_DATATYPE_POINTER\n"); break;
    case AST_DATATYPE_STRING: fprintf(stderr, ", AST_DATATYPE_STRING\n"); break;
    case AST_DATATYPE_UNKNOWN: fprintf(stderr, ", AST_DATATYPE_UNKNOWN\n"); break;
    default: fprintf(stderr, ", ''\n"); break;
    }
}