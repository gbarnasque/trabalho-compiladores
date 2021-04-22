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
        case TAC_LO: fprintf(stderr, "TAC_LO"); break;
        case TAC_GR: fprintf(stderr, "TAC_GR"); break;
        case TAC_PIPE: fprintf(stderr, "TAC_PIPE"); break;
        case TAC_AND: fprintf(stderr, "TAC_AND"); break;
        case TAC_LE: fprintf(stderr, "TAC_LE"); break;
        case TAC_GE: fprintf(stderr, "TAC_GE"); break;
        case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
        case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
        case TAC_TIL: fprintf(stderr, "TAC_TIL"); break;
        case TAC_DOLAR: fprintf(stderr, "TAC_DOLAR"); break;
        case TAC_HASHTAG: fprintf(stderr, "TAC_HASHTAG"); break;
    
        default: fprintf(stderr, "TAC_UNKNOWN"); break;
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

TacNode* makeUnaryOperation(int TacType, TacNode* code0) {
    return tacJoin(code0, tacCreate(TacType, makeTemp(), getRes(code0), NULL));
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
        case AST_OP_MINUS:
            result = makeBinaryOperation(TAC_SUB, code[0], code[1]);
            break;
        case AST_OP_MULT:
            result = makeBinaryOperation(TAC_MULT, code[0], code[1]);
            break;
        case AST_OP_DIV:
            result = makeBinaryOperation(TAC_DIV, code[0], code[1]);
            break;
        case AST_OP_LO:
            result = makeBinaryOperation(TAC_LO, code[0], code[1]);
            break;
        case AST_OP_GR:
            result = makeBinaryOperation(TAC_GR, code[0], code[1]);
            break;
        case AST_OP_PIPE:
            result = makeBinaryOperation(TAC_PIPE, code[0], code[1]);
            break;
        case AST_OP_AND:
            result = makeBinaryOperation(TAC_AND, code[0], code[1]);
            break;
        case AST_OP_LE:
            result = makeBinaryOperation(TAC_LE, code[0], code[1]);
            break;
        case AST_OP_GE:
            result = makeBinaryOperation(TAC_GE, code[0], code[1]);
            break;
        case AST_OP_EQ:
            result = makeBinaryOperation(TAC_EQ, code[0], code[1]);
            break;
        case AST_OP_DIF:
            result = makeBinaryOperation(TAC_DIF, code[0], code[1]);
            break;
        case AST_OP_TIL:
            result = makeUnaryOperation(TAC_TIL, code[0]);
            break;
        case AST_OP_DOLAR:
            result = makeUnaryOperation(TAC_DOLAR, code[0]);
            break;
        case AST_OP_HASHTAG:
            result = makeUnaryOperation(TAC_HASHTAG, code[0]);
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
