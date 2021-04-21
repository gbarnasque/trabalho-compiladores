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

    if(node->type == TAC_SYMBOL)
        return;

    fprintf(stderr, "TAC(");
    switch (node->type)
    {
        case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
        case TAC_MULT: fprintf(stderr, "TAC_MULT"); break;
        case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
        case TAC_COPY: fprintf(stderr, "TAC_COPY"); break;
        case TAC_JFALSE: fprintf(stderr, "TAC_JFALSE"); break;
        case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
    
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

TacNode* tacJoin(TacNode* list1, TacNode* list2) {
    TacNode* point;
    if(list1 == NULL)
        return list2;
    if(list2 == NULL)
        return list1;
        
    for(point = list2; point->prev != NULL; point = point->prev){

    }
    point->prev = list1;
    return list2;
}

TacNode* tripleTacJoinLast(TacNode* l1, TacNode* l2, TacNode* l3) {
    return tacJoin(tacJoin(l1,l2), l3);
}
TacNode* quadTacJoinLast(TacNode* l1, TacNode* l2, TacNode* l3, TacNode* l4) {
    return tacJoin(tripleTacJoinLast(l1,l2,l3), l4);
}
TacNode* tripleTacJoinFirst(TacNode* l1, TacNode* l2, TacNode* l3) {
    return tacJoin(l1, tacJoin(l2,l3));
}
TacNode* quadTacJoinFirst(TacNode* l1, TacNode* l2, TacNode* l3, TacNode* l4) {
    return tacJoin(l1, tripleTacJoinFirst(l2,l3,l4));
}

HashNode* getRes(TacNode* node) {
    if(node == NULL)
        return NULL;
    return node->res;
}

TacNode* makeBinaryOperation(int TacType, TacNode* code0, TacNode* code1) {
    return tripleTacJoinLast(code0, code1, tacCreate(TacType, makeTemp(), getRes(code0), getRes(code1)));
}

TacNode* makeIfThen(TacNode* code0, TacNode* code1) {
    TacNode* jump = NULL;
    TacNode* label = NULL;
    HashNode* newLabel = NULL;

    newLabel = makeLabel();
    jump = tacCreate(TAC_JFALSE, newLabel, getRes(code0), NULL);
    jump->prev = code0;
    label = tacCreate(TAC_LABEL, newLabel, NULL, NULL);
    label->prev = code1;
    return tacJoin(jump, label);
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
        case AST_OP_ADD:
            //result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_ADD, NULL, (code[0] != NULL) ? code[0]->res : NULL, (code[1] != NULL) ? code[1]->res : NULL));
            //result = tripleTacJoinLast(code[0], code[1], tacCreate(TAC_ADD, makeTemp(), getRes(code[0]), getRes(code[1])));
            result = makeBinaryOperation(TAC_ADD, code[0], code[1]);
            break;
        case AST_LEFT_ASSIGN:
        case AST_RIGHT_ASSIGN:
            result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol, getRes(code[0]), NULL));
            break;
        

        case AST_IF: 
            result = makeIfThen(code[0], code[1]);
            break;

        default: // return union of code for all children(subtrees)
            //result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
            result = quadTacJoinFirst(code[0], code[1], code[2], code[3]);
            break;
    }

    return result;
}
