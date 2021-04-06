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
            if(node->symbol != NULL) {
                if(node->symbol->type != SYMBOL_IDENTIFIER) {
                    fprintf(stderr, "Semantic ERROR: identifier %s already declared.\n", node->symbol->text);
                    ++SemanticErrors;
                }

                node->symbol->type = SYMBOL_VECTOR;
                setDataType(node);
            }
            break;
        case AST_VARIAVEL:
            if(node->symbol != NULL) {
                if(node->symbol->type != SYMBOL_IDENTIFIER) {
                    fprintf(stderr, "Semantic ERROR: identifier %s already declared.\n", node->symbol->text);
                    ++SemanticErrors;
                }
                node->symbol->type = SYMBOL_VARIABLE;
                setDataType(node);
            }
            break;
        case AST_FUNCAO_CABECALHO:
            if(node->symbol != NULL) {
                if(node->symbol->type != SYMBOL_IDENTIFIER) {
                    fprintf(stderr, "Semantic ERROR: redeclaration of identifier %s\n", node->symbol->text);
                    ++SemanticErrors;
                }
                node->symbol->type = SYMBOL_FUNCTION;
                setDataType(node);
            }
            break;

        default: 
            break;
    }

    for(i=0; i<MAX_SONS; i++)
        checkAndSetDeclarations(node->nodes[i]);
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
                fprintf(stderr, "Semantic ERROR: invalid left operand for ADD\n");
                ++SemanticErrors;
            }
            if(isIntegerOperand(node->nodes[1]) == 0) {
                fprintf(stderr, "Semantic ERROR: invalid right operand for ADD\n");
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
    int type = node->type;
    if(node == NULL)
        return ret;
    if(
        type == AST_OP_ADD || 
        type == AST_OP_MINUS ||
        type == AST_OP_MULT ||
        type == AST_OP_DIV ||
        (type == AST_SYMBOL && node->symbol->type == SYMBOL_LIT_INT) ||
        (type == AST_FUNCAO_CHAMADA && node->symbol->dataType == DATATYPE_INT) ||
        (type == AST_VETOR && node->symbol->dataType == DATATYPE_INT) ||
        (type == AST_SYMBOL && node->symbol->dataType == DATATYPE_INT)
        )
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