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
        case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
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
        case TAC_WHILE: fprintf(stderr, "TAC_WHILE"); break;
        case TAC_RETURN: fprintf(stderr, "TAC_RETURN"); break;
        case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
        case TAC_READ: fprintf(stderr, "TAC_READ"); break;
        case TAC_PRINT_ARG: fprintf(stderr, "TAC_PRINT_ARG"); break;
        case TAC_FUNCAO_CHAMADA: fprintf(stderr, "TAC_FUNCAO_CHAMADA"); break;
        case TAC_FUNCAO_CABECALHO: fprintf(stderr, "TAC_FUNCAO_CABECALHO"); break; 
        case TAC_LISTA_PARAMETROS_DECLARACAO: fprintf(stderr, "TAC_LISTA_PARAMETROS_DECLARACAO"); break;
        case TAC_VETOR_DECLARACAO: fprintf(stderr, "TAC_VETOR_DECLARACAO"); break;
        case TAC_VETOR_TAMANHO: fprintf(stderr, "TAC_VETOR_TAMANHO"); break;
        case TAC_CONTINUE_VEC_DECL: fprintf(stderr, "TAC_CONTINUE_VEC_DECL"); break;
        case TAC_VARIAVEL: fprintf(stderr, "TAC_VARIAVEL"); break;
        case TAC_VARIAVEL_START: fprintf(stderr, "TAC_VARIAVEL_START"); break;

        case TAC_T_BOOL: fprintf(stderr, "TAC_T_BOOL"); break;
        case TAC_T_CHAR: fprintf(stderr, "TAC_T_CHAR"); break;
        case TAC_T_INT: fprintf(stderr, "TAC_T_INT"); break;
        case TAC_T_POINTER: fprintf(stderr, "TAC_T_POINTER"); break;

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

TacNode* makeUnaryOperationWithSymbol(int TacType, HashNode* symbol, TacNode* code0) {
    return tacJoin(code0, tacCreate(TacType, symbol, getRes(code0), NULL));
}

TacNode* makeUnaryOperation(int TacType, TacNode* code0) {
    return tacJoin(code0, tacCreate(TacType, makeTemp(), getRes(code0), NULL));
}

TacNode* makeBinaryOperationwithSymbol(int TacType, HashNode* symbol, TacNode* code0, TacNode* code1) {
    return tripleTacJoinLast(code0, code1, tacCreate(TacType, symbol, getRes(code0), getRes(code1)));
}

TacNode* makeBinaryOperation(int TacType, TacNode* code0, TacNode* code1) {
    return tripleTacJoinLast(code0, code1, tacCreate(TacType, makeTemp(), getRes(code0), getRes(code1)));
}
TacNode* makeTernaryOperationWithSymbol(int TacType, HashNode* symbol, TacNode* code0, TacNode* code1, TacNode* code2) {
    return quadTacJoinLast(code0, code1, tacCreate(TacType, symbol, getRes(code0), getRes(code1)), code2);
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
TacNode* makeIfThenElse(TacNode* code0, TacNode* code1, TacNode* code2) {
    TacNode* jumpFalse = NULL;
    TacNode* jumpInconditional = NULL;
    TacNode* label1 = NULL;
    TacNode* label2 = NULL;
    HashNode* newLabel1 = NULL;
    HashNode* newLabel2 = NULL;

    newLabel1 = makeLabel();
    newLabel2 = makeLabel();
    
    jumpFalse = tacCreate(TAC_JFALSE, newLabel1, getRes(code0), NULL );
    jumpFalse->prev = code0;

    jumpInconditional = tacCreate(TAC_JUMP, newLabel2, NULL, NULL);
    jumpInconditional->prev = code1;

    label1 = tacCreate(TAC_LABEL, newLabel1, NULL, NULL);
    label1->prev = jumpInconditional;

    label2 = tacCreate(TAC_LABEL, newLabel2, NULL, NULL);
    label2->prev = code2;
    
    
    return tripleTacJoinFirst(jumpFalse, label1, label2);
}
TacNode* makeWhile(TacNode* code0, TacNode* code1) { 
    TacNode* jumpFalse = NULL;
    TacNode* jumpInconditional = NULL;
    TacNode* label1 = NULL;
    TacNode* label2 = NULL;
    HashNode* newLabel1 = NULL;
    HashNode* newLabel2 = NULL;

    newLabel1 = makeLabel();
    newLabel2 = makeLabel();

    label2 = tacCreate(TAC_LABEL, newLabel2, NULL, NULL);
    label2->prev = code0;

    jumpFalse = tacCreate(TAC_WHILE, newLabel1, getRes(code0), NULL);
    jumpFalse->prev = label2;

    jumpInconditional = tacCreate(TAC_JUMP, newLabel2, NULL, NULL);
    jumpInconditional->prev = code1;

    label1 = tacCreate(TAC_LABEL, newLabel1, NULL, NULL);
    label1->prev = jumpInconditional;

    return tacJoin(jumpFalse, label1);
}
TacNode* makeVectorDecl(HashNode* symbol, TacNode* code0, TacNode* code1) {
    TacNode* vector = NULL;

    vector = tacCreate(TAC_VETOR_DECLARACAO, symbol, getRes(code0), getRes(code1));
    vector->prev = code1;
    
    return tacJoin(code0, vector);
}
TacNode* makeVectorDeclInit(HashNode* symbol, TacNode* code0, TacNode* code1, TacNode* code2) {
    return makeTernaryOperationWithSymbol(TAC_VETOR_DECLARACAO, symbol, code0, code1, code2);
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
        
        case AST_LEFT_ASSIGN_VECTOR:
        case AST_RIGHT_ASSIGN_VECTOR:
            result = tripleTacJoinFirst(code[0], code[1], tacCreate(TAC_COPY, node->symbol, getRes(code[0]), getRes(code[1])));
            break;

        case AST_IF: 
            result = makeIfThen(code[0], code[1]);
            break;
        case AST_IF_ELSE:
            result = makeIfThenElse(code[0], code[1], code[2]);
            break;
        case AST_WHILE:
            result = makeWhile(code[0], code[1]);
            break;

        case AST_RETURN:
            result = tacCreate(TAC_RETURN, NULL, getRes(code[0]), NULL);
            break;
        case AST_PRINT:
            result = tacJoin(code[0], tacCreate(TAC_PRINT, NULL, getRes(code[0]), NULL));
            break;
        case AST_READ:
            result = tacCreate(TAC_READ, node->symbol, NULL, NULL);
            break;

        case AST_PRINT_ARG1:
        case AST_PRINT_ARG2:
            result = makeBinaryOperation(TAC_PRINT_ARG, code[0], code[1]);
            break;

        case AST_FUNCAO_CHAMADA:
            //result = tacJoin(code[0], tacCreate(TAC_FUNCAO_CHAMADA, node->symbol, getRes(code[0]), NULL));
            result = makeUnaryOperationWithSymbol(TAC_FUNCAO_CHAMADA, node->symbol, code[0]);
            break;

        case AST_FUNCAO_CABECALHO:
            result = makeBinaryOperationwithSymbol(TAC_FUNCAO_CABECALHO, node->symbol, code[0], code[1]);
            break;
        case AST_LISTA_PARAMETROS_DECLARACAO:
        case AST_LISTA_PARAMETROS_DECLARACAO_C:
            result = makeBinaryOperationwithSymbol(TAC_LISTA_PARAMETROS_DECLARACAO, node->symbol, code[0], code[1]);
            break;

        case AST_VETOR_DECLARACAO:
            result = makeVectorDecl(node->symbol, code[0], code[1]);
            break;
        case AST_VETOR_DECLARACAO_INIT:
            result = makeVectorDeclInit(node->symbol, code[0], code[1], code[2]);
            break;
        case AST_LITERAIS:
            //result = tacJoin(code[0], tacCreate(TAC_CONTINUE_VEC_DECL, makeTemp(), code[1], NULL);
            result = makeBinaryOperation(TAC_CONTINUE_VEC_DECL, code[0], code[1]);
            break;
        case AST_VETOR_TAMANHO:
            result = tacCreate(TAC_VETOR_TAMANHO, node->symbol, NULL, NULL);
            break;

        case AST_VARIAVEL:
            result = makeUnaryOperationWithSymbol(TAC_VARIAVEL, node->symbol, code[0]);
            break;

        case AST_VARIAVEIS:
            result = makeBinaryOperation(TAC_VARIAVEL_START, code[0], code[1]);
            break;

        case AST_T_BOOL:
            result = tacCreate(TAC_T_BOOL, makeTemp(), NULL, NULL);
            break;
        case AST_T_CHAR:
            result = tacCreate(TAC_T_CHAR, makeTemp(), NULL, NULL);
            break;
        case AST_T_INT:
            result = tacCreate(TAC_T_INT, makeTemp(), NULL, NULL);
            break;
        case AST_T_POINTER:
            result = tacCreate(TAC_T_POINTER, makeTemp(), NULL, NULL);
            break;
            

        default: // return union of code for all children(subtrees)
            //result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
            result = quadTacJoinFirst(code[0], code[1], code[2], code[3]);
            break;
    }

    return result;
}
