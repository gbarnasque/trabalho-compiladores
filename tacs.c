/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */
#include "tacs.h"

TacNode* tacCreate(int type, HashNode* res, HashNode* op1, HashNode* op2) {
    TacNode* ret;
    ret = (TacNode*) malloc(sizeof(TacNode));
    ret->type = type;
    ret->res = res;
    ret->op1 = op1;
    ret->op2 = op2;
    ret->prev = NULL;
    ret->next = NULL;

    return ret;
}

void tacPrint(TacNode* node) {
    if(node == NULL)
        return;
    fprintf(stderr, "TAC(");
    switch (node->type)
    {
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
        case TAC_MULT: fprintf(stderr, "TAC_MULT"); break;
        case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
    
        default: fprintf(stderr, "TAC UNKNOWN"); break;
    }

    fprintf(stderr, ", %s", (node->res != NULL) ? node->res->text : "");
    fprintf(stderr, ", %s", (node->op1 != NULL) ? node->op1->text : "");
    fprintf(stderr, ", %s", (node->op2 != NULL) ? node->op2->text : "");
    fprintf(stderr, ");\n");
    
}

void tacPrintBackwards(TacNode* node) {
    if(node == NULL)
        return;

    tacPrintBackwards(node->prev);
    tacPrint(node);
}

//Code Generation

TacNode* generateCode(AstNode* node) {
    int i;
    TacNode* result = NULL;
    TacNode* code[MAX_SONS];

    if(node == NULL)
        return NULL;

    // Process Children
    for(i=0; i<MAX_SONS; i++){
        code[i] = generateCode(node->nodes[i]);
    }
    
    // Process Current Node (AST)
    switch (node->type)
    {
        case AST_SYMBOL:
            result = tacCreate(TAC_SYMBOL, node->symbol, NULL, NULL);
            break;
        
        default: // return union of code for all children(subtrees)
            
            break;
    }

    return result;
}
