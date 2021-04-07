/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

#include "semantic.h"
#include "ast.h"

int SemanticErrors = 0;

void checkAndSetDeclarations(AstNode* node) {
    int i;
    if(node == NULL)
        return;


    switch(node->type) {
        case AST_VETOR_DECLARACAO_INIT:
        case AST_VETOR_DECLARACAO:
            checkAndSetIdentifier(node, SYMBOL_VECTOR);
            break;
        case AST_VARIAVEL:
        case AST_LISTA_PARAMETROS_DECLARACAO:
        case AST_LISTA_PARAMETROS_DECLARACAO_C:
            checkAndSetIdentifier(node, SYMBOL_VARIABLE);
            break;
        case AST_FUNCAO_CABECALHO:
            checkAndSetIdentifier(node, SYMBOL_FUNCTION);
            break;

        default: 
            break;
    }

    for(i=0; i<MAX_SONS; i++)
        checkAndSetDeclarations(node->nodes[i]);
}

void checkAndSetIdentifier(AstNode* node, int type) {
    if(node->symbol != NULL) {
        if(node->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "[S01] Semantic ERROR: identifier %s already declared\n", node->symbol->text);
            ++SemanticErrors;
        }
        node->symbol->type = type;
        setDataType(node);
    }
}

void checkOperands(AstNode* node) {
    int i;
    if(node == NULL)
        return;

    switch(node->type) {
        case AST_OP_ADD:
        case AST_OP_MINUS:
        case AST_OP_MULT:
        case AST_OP_DIV:
            if(isIntegerOperand(node->nodes[0]) == 0)  {
                fprintf(stderr, "[S03] Semantic ERRORS: invalid left operand: %s\n", node->nodes[0]->symbol->text);
                ++SemanticErrors;
            }
            if(isIntegerOperand(node->nodes[1]) == 0) {
                fprintf(stderr, "[S04] Semantic ERROR: invalid right operand: %s\n", node->nodes[1]->symbol->text);
                ++SemanticErrors;
            }
            break;

        default:
            break;
    }

    for(i=0; i<MAX_SONS; i++)
        checkOperands(node->nodes[i]);
}

int isIntegerOperand(AstNode* node) {
    int ret = 0;
    int type;
    if(node == NULL)
        return ret;

    type = node->type;
    if( type == AST_OP_ADD || 
        type == AST_OP_MINUS ||
        type == AST_OP_MULT ||
        type == AST_OP_DIV
        )
        ret = 1;

    if(node->symbol != NULL && (
        (type == AST_SYMBOL && node->symbol->type == SYMBOL_LIT_INT) ||
        (type == AST_FUNCAO_CHAMADA && node->symbol->dataType == DATATYPE_INT) ||
        (type == AST_VETOR && node->symbol->dataType == DATATYPE_INT) ||
        (type == AST_SYMBOL && node->symbol->dataType == DATATYPE_INT)
        ))
        ret = 1;
        

    return ret;
}

int isCharOperand(AstNode* node) {
    int ret = 0;
    int type = node->type;


    return ret;
}

int isBoolOperand(AstNode* node) {
    int ret = 0;

    return ret;
}
int isPointerOperand(AstNode* node) {
    int ret = 0;

    return ret;
}

void checkUndeclared() {
    SemanticErrors += hashCheckUndeclared();
}

int getSemanticErrors() {
    return SemanticErrors;
}
void setDataType(AstNode* node) {
    if(node->nodes[0] != NULL) {
        switch (node->nodes[0]->type)
        {
            case AST_T_BOOL:
                node->symbol->dataType = DATATYPE_BOOL;
                break;
            case AST_T_CHAR:
                node->symbol->dataType = DATATYPE_CHAR;
                break;
            case AST_T_INT:
                node->symbol->dataType = DATATYPE_INT;
                break;
            case AST_T_POINTER:
                node->symbol->dataType = DATATYPE_POINTER;
                break;
            default:
                break;
        }
    }
}