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

    printNodeType(node->type);

    if(node->symbol != 0)
        fprintf(stderr, ",%s\n", node->symbol->text);
    else 
        fprintf(stderr, ",''\n");
    
    for(i=0; i<MAX_SONS; i++)
        astPrint(node->nodes[i], level+1);
    //fprintf(stderr, ")\n");
}

void printNodeType(int type) {
    switch (type)
    {
        
    
        default:
            fprintf(stderr, "AST_UNKNOW");
            break;
    }
}