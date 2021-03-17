/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */
#include "ast.h"

AstNode* astCreate(int type, HashNode* symbol, AstNode* s0, AstNode* s1, AstNode* s2, AstNode* s3) {
    AstNode* ret;
    ret = (AstNode*) malloc(sizeof(AstNode));
    ret->type = type;
    ret->symbol = symbol;
    ret->nodes[0] = s0;
    ret->nodes[1] = s1;
    ret->nodes[2] = s2;
    ret->nodes[3] = s3;

    return ret;
}

void astPrint(AstNode* node, int level) {
    int i;
    if(node == NULL)
        return;

    for(i=0; i<level; i++)
        fprintf(stderr, "  ");
    fprintf(stderr, "AST(");
    switch (node->type)
    {
    case AST_SYMBOL: 
            fprintf(stderr, "AST_SYMBOL");
            break;
    case AST_ADD:
            fprintf(stderr, "AST_ADD");
            break;
    case AST_MULT:
            fprintf(stderr, "AST_MULT");
            break;
    default:
            fprintf(stderr, "AST_UNKNOW");
            break;
    }

    if(node->symbol != 0)
        fprintf(stderr, ",%s\n", node->symbol->text);
    else 
        fprintf(stderr, ",0\n");
    
    for(i=0; i<MAX_SONS; i++)
        astPrint(node->nodes[i], level+1);
    //fprintf(stderr, ")\n");
}