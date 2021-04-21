/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

#include "semantic.h"
#include "ast.h"

int SemanticErrors = 0;

void semanticVerification(AstNode* node) {
    fprintf(stderr, "---------------------\n");
    fprintf(stderr, "Start Semantic Verification\n");
    //printf("Start SetDeclarations\n");
    checkAndSetDeclarations(node); 
    //printf("End SetDeclarations\n");

    //printf("Start setBaseDataTypes\n");
    setBaseDataTypes(node);
    //printf("End setBaseDataTypes\n");

    //printf("Start checkUndeclared\n");
    checkUndeclared();
    //printf("End checkUndeclared\n");

    //printf("Start checkOperands\n");
    checkOperands(node);
    //printf("End checkOperands\n");

    //printf("Start checkFuncReturn\n");
    checkFuncReturn(node);
    //printf("End checkFuncReturn\n");

    /*printf("Start checkFuncCallParams\n");
    preCheckFuncCallParams(node);
    checkFuncCallParams(node);
    printf("End checkFuncCallParams\n");
*/
    fprintf(stderr, "End Semantic Verification\n");
    fprintf(stderr, "---------------------\n");
}

void setBaseDataTypes(AstNode* node) {
    int i;
    if(node == NULL)
        return;
    
    for(i=0; i<MAX_SONS; i++)
        setBaseDataTypes(node->nodes[i]);

    if(node->type == AST_SYMBOL) {
        switch(node->symbol->type) {
            case SYMBOL_LIT_CHAR:
                node->dataType = AST_DATATYPE_CHAR;
                break;
            case SYMBOL_LIT_INT:
                node->dataType = AST_DATATYPE_INT;
                break;
            case SYMBOL_LIT_TRUE:
            case SYMBOL_LIT_FALSE:
                node->dataType = AST_DATATYPE_BOOL;
                break;
            case SYMBOL_LIT_STRING:
                node->dataType = AST_DATATYPE_STRING;
                break;
            default:
                setDataTypeBasedOnSymbolDataType(node);
                break;
        }
    }
    if(node->type == AST_FUNCAO_CHAMADA)
        setDataTypeBasedOnSymbolDataType(node);
    if(node->type == AST_VETOR)
        setDataTypeBasedOnSymbolDataType(node);
}
void setDataTypeBasedOnSymbolDataType(AstNode* node) {
    if(node->symbol == NULL) {
        node->dataType = AST_DATATYPE_ERROR;
    }
    switch (node->symbol->dataType) {
        case DATATYPE_CHAR:
            node->dataType = AST_DATATYPE_CHAR;
            break;
        case DATATYPE_INT:
            node->dataType = AST_DATATYPE_INT;
            break;
        case DATATYPE_BOOL:
            node->dataType = AST_DATATYPE_BOOL;
            break;
        case DATATYPE_POINTER:
            node->dataType = AST_DATATYPE_POINTER;
        default:
            break;
    }
}


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
            node->symbol->numParameters = countParametersFunction(node->nodes[1]);
            //printf("%s, coutn params: %d\n", node->symbol->text, node->symbol->numParameters );
            break;
        default: 
            break;
    }

    for(i=0; i<MAX_SONS; i++)
        checkAndSetDeclarations(node->nodes[i]);
}

int countParametersFunction(AstNode* node) {
    if(node == NULL )
        return 0;

    return 1 + countParametersFunction(node->nodes[1]);
}
int countParametersCallFunction(AstNode* node) {
    if(node == NULL)
        return 0;
    
    return 1 + countParametersCallFunction(node->nodes[1]);
}

int* getDataTypesFuncParameters(AstNode* node) {
    int* aux;

    if(node->symbol->numParameters == 0)
        return NULL;

    //printf("params: %d %d\n", node->symbol->numParameters, node->nodes[1]->symbol->type);
    aux = (int*) malloc(sizeof(int)*(node->symbol->numParameters));

    fillDataTypeFuncParameters(node->nodes[1], aux, 0);

    printf("fillDataTypeFuncParameters");
    for(int i=0; i<node->symbol->numParameters; i++) {
        printf("%d, ", aux[i]);
    }
    printf("\n");
    return aux;
}

void fillDataTypeFuncParameters(AstNode* currentNode, int* dataTypeParameters, int curr) {
    int i;
    if(currentNode == NULL)
        return;

    dataTypeParameters[curr] = getSymbolDataTypeAsASTDataType(currentNode->symbol);

    fillDataTypeFuncParameters(currentNode->nodes[1], dataTypeParameters, curr+1);
}

void preCheckFuncCallParams(AstNode* node) {
    int i;
    if(node == NULL)
        return;

    for(i=0; i<MAX_SONS; i++)
        preCheckFuncCallParams(node->nodes[i]);

    if(node->type == AST_FUNCAO_CABECALHO){
    printf("ORIGINAL:\n");
        node->symbol->dataTypesParameters = getDataTypesFuncParameters(node);
    }

    
}

int* getDataTypesFuncParametersCall(AstNode* node) {
    int* aux;
    int* current;
    if(node->symbol->numParameters == 0)
        return NULL;

    aux = (int*) malloc(sizeof(int)*(node->symbol->numParameters));
    current = (int*) malloc(sizeof(int));
    fillDataTypeFuncParametersCall(node->nodes[0], aux, current);

    return aux;
}

void fillDataTypeFuncParametersCall(AstNode* currentNode, int* dataTypeParameters, int* current) {
    int i;
    if(currentNode == NULL)
        return;

    if(currentNode->dataType != AST_DATATYPE_ERROR && currentNode->dataType != AST_DATATYPE_ERROR ){
        dataTypeParameters[*current] = currentNode->dataType;//getSymbolDataTypeAsASTDataType(currentNode->symbol);
        *current++;
    }

    for(int i=0; i<MAX_SONS; i++)
        fillDataTypeFuncParametersCall(currentNode->nodes[i], dataTypeParameters, current);
    
}

void checkFuncCallParams(AstNode* node) {
    int i;
    int* aux;
    size_t sizeAux, sizeReal;
    if(node == NULL)
        return;
    
    for(i=0; i<MAX_SONS; i++)
        checkFuncCallParams(node->nodes[i]);
    //printf("%d\n", node->type);
    

    if(node->type == AST_FUNCAO_CHAMADA) {
        printf("func call\n");
        if(node->symbol != NULL){
            //aux = (int*) malloc(sizeof(int)*node->symbol->numParameters);
            printf("CHAMADA:\n");
            aux = getDataTypesFuncParametersCall(node);
            //sizeReal = sizeof(node->symbol->dataTypesParameters) / sizeof(int);
            //printf("%d\n", node->symbol->numParameters);
            //printf("%d %d\n", sizeAux, sizeReal);
            for(int i=0; i<node->symbol->numParameters; i++) {
                printf("%d %d\n", aux[i], node->symbol->dataTypesParameters[i]);
                if(aux[i] != node->symbol->dataTypesParameters[i]) {
                    fprintf(stderr, "[S21] Semantic ERRORS: incompatible types for func call in Line %d\n",  node->lineNumber);
                    ++SemanticErrors;
                }
            }
            // if(checkDataTypeParameters(node->nodes[1], node->symbol->dataTypesParameters, 0, node->symbol->numParameters) == 1) {
            //     fprintf(stderr, "[S21] Semantic ERRORS: incompatible types for func call in Line %d\n",  node->lineNumber);
            //     ++SemanticErrors;
            // }
        }
    }

}

// If return == 1, a mismatch occured
int checkDataTypeParameters(AstNode* currentNode, int* dataTypeParameters, int current, int capacity) {
    int i;
    if(currentNode == NULL)
        return 0;

    if(current > capacity-1)
        return 1;

    if(checkDataTypeCompatibility(dataTypeParameters[current], getSymbolDataTypeAsASTDataType(currentNode->symbol)) == 0)
        return 1;
    
    return checkDataTypeParameters(currentNode->nodes[1], dataTypeParameters, current+1, capacity);
}


void checkAndSetIdentifier(AstNode* node, int type) {
    if(node->symbol != NULL) {
        if(node->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "[S01] Semantic ERROR: identifier %s already declared\n", node->symbol->text);
            ++SemanticErrors;
        }
        node->symbol->type = type;
        setDataTypes(node);
    }
}

void checkOperands(AstNode* node) {
    int i;
    //printf("aqui null\n");

    if(node == NULL)
        return;
    
    for(i=0; i<MAX_SONS; i++)
        checkOperands(node->nodes[i]);

    switch(node->type) {
        // Integer or Chars
        case AST_OP_ADD:
        case AST_OP_MINUS:
            if( ((node->nodes[0]->symbol != NULL) && ((isPointerOperand(node->nodes[1]) == 1) && (node->nodes[0]->symbol->type == SYMBOL_LIT_INT || node->nodes[0]->symbol->type == SYMBOL_LIT_CHAR))) || 
                ((node->nodes[1]->symbol != NULL) && ((isPointerOperand(node->nodes[0]) == 1) && (node->nodes[1]->symbol->type == SYMBOL_LIT_INT || node->nodes[1]->symbol->type == SYMBOL_LIT_CHAR)))) {
                node->dataType = AST_DATATYPE_POINTER;
                return;
                }
        case AST_OP_MULT:
        case AST_OP_DIV:
            //printf("\n%d %d %d %d\n", isIntegerOperand(node->nodes[0]), isCharOperand(node->nodes[0]), isIntegerOperand(node->nodes[1]), isCharOperand(node->nodes[1]));
            if(isIntegerOperand(node->nodes[0]) == 0 && isCharOperand(node->nodes[0]) == 0)  {
                fprintf(stderr, "[S03] Semantic ERRORS: invalid Left operand at Line %d\n", node->lineNumber);
                ++SemanticErrors;
            }
            if(isIntegerOperand(node->nodes[1]) == 0 && isCharOperand(node->nodes[1]) == 0) {
                fprintf(stderr, "[S04] Semantic ERROR: invalid Right operand at Line %d\n", node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_INT;
            break;
        
        case AST_OP_EQ:
        case AST_OP_GE:
        case AST_OP_LE:
        case AST_OP_GR:
        case AST_OP_LO:
        case AST_OP_DIF:
            if(isIntegerOperand(node->nodes[0]) == 0 && isCharOperand(node->nodes[0]) == 0)  {
                fprintf(stderr, "[S12] Semantic ERRORS: invalid Left operand at Line %d\n", node->lineNumber);
                ++SemanticErrors;
            }
            if(isIntegerOperand(node->nodes[1]) == 0 && isCharOperand(node->nodes[1]) == 0) {
                fprintf(stderr, "[S13] Semantic ERROR: invalid Right operand at Line %d\n", node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_BOOL;
            break;

        // Booleans
        case AST_OP_AND:
        case AST_OP_PIPE:
        
            if(isBoolOperand(node->nodes[0]) == 0)  {
                fprintf(stderr, "[S05] Semantic ERRORS: invalid Left operand at Line %d\n", node->lineNumber);
                ++SemanticErrors;
            }
            if(isBoolOperand(node->nodes[1]) == 0) {
                fprintf(stderr, "[S06] Semantic ERROR: invalid Right operand at Line %d\n", node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_BOOL;
            break;

        case AST_OP_TIL:
            if(isBoolOperand(node->nodes[0]) == 0)  {
                fprintf(stderr, "[S07] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_BOOL;
            break;

        case AST_IF:
        case AST_IF_ELSE:
        case AST_WHILE:
            if(isBoolOperand(node->nodes[0]) == 0) {
                fprintf(stderr, "[S08] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_UNKNOWN;
            break;

        // Pointers
        case AST_OP_DOLAR:
            if(hasSymbolIdentifier(node->nodes[0]) == 0) {
                fprintf(stderr, "[S09] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_POINTER;
            break;
        case AST_OP_HASHTAG:
            if(isPointerOperand(node->nodes[0]) == 0) {
                fprintf(stderr, "[S10] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_INT;
            break;

        // Demais
        case AST_PARENTESES:
            node->dataType = node->nodes[0]->dataType;
            break;

        case AST_VETOR:
            if(isIntegerOperand(node->nodes[0]) == 0 && isCharOperand(node->nodes[0]) == 0){
                fprintf(stderr, "[S11] Semantic ERRORS: invalid index of vector at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            setDataTypeBasedOnSymbolDataType(node);
            break;
    

        case AST_RETURN:
            node->dataType = node->nodes[0]->dataType;
            break;
        
        case AST_PRINT_ARG1:
        case AST_PRINT_ARG2:
            node->dataType = AST_DATATYPE_STRING;
            break;

        case AST_PRINT:
            if((node->symbol != NULL && node->symbol->dataType != SYMBOL_LIT_STRING) || (node->nodes[0] != NULL && node->nodes[0]->dataType != AST_DATATYPE_STRING)) {
                fprintf(stderr, "[S14] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_UNKNOWN;
            break;
        
        case AST_READ:
            if(hasSymbolIdentifier(node) == 0) {
                fprintf(stderr, "[S15] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_UNKNOWN;
            break;

        // Assigns
        case AST_RIGHT_ASSIGN_VECTOR: 
            if( ((isIntegerOperand(node->nodes[1]) == 0) && (isCharOperand(node->nodes[1]) == 0)) ||
                (getSymbolDataTypeAsASTDataType(node->symbol) != node->nodes[0]->dataType)
            ) {
                fprintf(stderr, "[S16] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            } 
            node->dataType = AST_DATATYPE_UNKNOWN;
            break;

        case AST_LEFT_ASSIGN_VECTOR:
            if( ((isIntegerOperand(node->nodes[0]) == 0) && (isCharOperand(node->nodes[0]) == 0)) ||
                (getSymbolDataTypeAsASTDataType(node->symbol) != node->nodes[1]->dataType)
            ) {
                fprintf(stderr, "[S17] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            } 
            node->dataType = AST_DATATYPE_UNKNOWN;
            break;

        case AST_RIGHT_ASSIGN:
        case AST_LEFT_ASSIGN:
            if(getSymbolDataTypeAsASTDataType(node->symbol) != node->nodes[0]->dataType) {
                fprintf(stderr, "[S18] Semantic ERRORS: invalid operand at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = AST_DATATYPE_UNKNOWN;
            break;

        case AST_FUNCAO_CHAMADA:
            if(countParametersCallFunction(node->nodes[0]) != node->symbol->numParameters) {
                fprintf(stderr, "[S19] Semantic ERRORS: number of variables does not match at Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
            node->dataType = getSymbolDataTypeAsASTDataType(node->symbol);
            break;
        default:
            break;
    }
    //astPrint(astFinal, 0);
}

int getSymbolDataTypeAsASTDataType(HashNode* node) {
    if(node == NULL)
        return 0;
    switch (node->dataType)
    {
    case DATATYPE_BOOL:
        return AST_DATATYPE_BOOL;
        break;
    case DATATYPE_INT:
        return AST_DATATYPE_INT;
        break;
    case DATATYPE_POINTER:
        return AST_DATATYPE_POINTER;
        break;
    case DATATYPE_CHAR:
        return AST_DATATYPE_CHAR;
        break;
    default:
        return AST_DATATYPE_ERROR;
        break;
    }
}

void checkFuncReturn(AstNode* node) {
    int i;
    if(node == NULL)
        return;    
    
    if(node->type == AST_FUNCAO) {
        if(node->nodes[0] != NULL){
            if(checkDataTypeCompatibility(node->nodes[0]->dataType, getReturnDataTypeFunc(node->nodes[1])) == 0) {
                fprintf(stderr, "[S20] Semantic ERRORS: invalid return at func in Line %d\n",  node->lineNumber);
                ++SemanticErrors;
            }
        }
    }

    for(i=0; i<MAX_SONS; i++)
        checkFuncReturn(node->nodes[i]);
}

int getReturnDataTypeFunc(AstNode* node) {
    int ret = 0;
    int i;
    if(node == NULL)
        return ret;


    if(node->type == AST_RETURN){
        return node->dataType;
    }
    

    for(i=0; i<MAX_SONS; i++){
        ret = getReturnDataTypeFunc(node->nodes[i]);
        if(ret != 0)
            return ret;
    }
    return ret;
}

int checkDataTypeCompatibility(int datatype1, int datatype2) {
    if(datatype1 == 0 || datatype2 == 0){
        return 0;
    }
    else if(datatype1 == datatype2) {
        return 1;
    }
    else if(datatype1 == AST_DATATYPE_INT && datatype2 == AST_DATATYPE_CHAR) {
        return 1;
    }
    else if(datatype2 == AST_DATATYPE_INT && datatype1 == AST_DATATYPE_CHAR) {
        return 1;
    }
    return 0;
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

    if(node->symbol != NULL) {
        if( (type == AST_SYMBOL && node->symbol->type == SYMBOL_LIT_INT) ||
            (type == AST_FUNCAO_CHAMADA && node->symbol->dataType == DATATYPE_INT) ||
            (type == AST_VETOR && node->symbol->dataType == DATATYPE_INT) ||
            (type == AST_SYMBOL && node->symbol->dataType == DATATYPE_INT)
        )
            ret = 1;
    }
        
    if(node->dataType == AST_DATATYPE_INT)
        ret = 1;

    return ret;
}

int isCharOperand(AstNode* node) {
    int ret = 0;
    int type;
    if(node == NULL)
        return ret;

    type = node->type;
    if(node->symbol != NULL) {
        if( (type == AST_SYMBOL && node->symbol->type == SYMBOL_LIT_CHAR) ||
            (type == AST_FUNCAO_CHAMADA && node->symbol->dataType == DATATYPE_CHAR) ||
            (type == AST_VETOR && node->symbol->dataType == DATATYPE_CHAR) ||
            (type == AST_SYMBOL && node->symbol->dataType == DATATYPE_CHAR)
            )   
            ret = 1;
    }

    if(node->dataType == AST_DATATYPE_CHAR)
        ret = 1;
    
    return ret;
}

int isBoolOperand(AstNode* node) {
    int ret = 0;
    int type;

    if(node == NULL)
        return ret;

    type = node->type;
    if(node->symbol != NULL) {
        if( (type == AST_SYMBOL && (node->symbol->type == SYMBOL_LIT_FALSE || node->symbol->type == SYMBOL_LIT_TRUE)) ||
            (type == AST_FUNCAO_CHAMADA && node->symbol->dataType == DATATYPE_BOOL) ||
            (type == AST_VETOR && node->symbol->dataType == DATATYPE_BOOL) ||
            (type == AST_SYMBOL && node->symbol->dataType == DATATYPE_BOOL)
            ) 
            ret = 1;
    }

    if(node->dataType == AST_DATATYPE_BOOL)
        ret = 1;

    return ret;
}
int isPointerOperand(AstNode* node) {
    int ret = 0;
    int type;

    if(node == NULL)
        return ret;

    type = node->type;
    if(node->symbol != NULL) {
        if( (type == AST_FUNCAO_CHAMADA && node->symbol->dataType == DATATYPE_POINTER) ||
            (type == AST_VETOR && node->symbol->dataType == DATATYPE_POINTER) ||
            (type == AST_SYMBOL && node->symbol->dataType == DATATYPE_POINTER)
            )
            ret = 1;
    }

    if(node->dataType == AST_DATATYPE_POINTER)
        ret = 1;

    return ret;
}

int hasSymbolIdentifier(AstNode* node) {
    int ret = 0;
    int type;

    if(node == NULL)
        return ret;
    
    if(node->symbol != NULL) {
        type = node->symbol->type;
        if( (type == SYMBOL_FUNCTION) ||
            (type == SYMBOL_VARIABLE) ||
            (type == SYMBOL_VECTOR)
            )
            ret = 1;
    }
    return ret;
}
/*
int isIdentifier(AstNode* node) {
    int ret = 0;
    int type;

    if(node == NULL)
        return ret;
    
    if(node->symbol != NULL) {
        type = node->symbol->type;
        if( (type == SYMBOL_FUNCTION) ||
            (type == SYMBOL_VARIABLE) ||
            (type == SYMBOL_VECTOR)
            )
            ret = 1;
    }
    return ret;
}
*/

void checkUndeclared() {
    SemanticErrors += hashCheckUndeclared();
}

int getSemanticErrors() {
    return SemanticErrors;
}
void setDataTypes(AstNode* node) {
    if(node->nodes[0] != NULL) {
        switch (node->nodes[0]->type)
        {
            case AST_T_BOOL:
                node->dataType = AST_DATATYPE_BOOL;
                node->symbol->dataType = DATATYPE_BOOL;
                break;
            case AST_T_CHAR:
                node->dataType = AST_DATATYPE_CHAR;
                node->symbol->dataType = DATATYPE_CHAR;
                break;
            case AST_T_INT:
                node->dataType = AST_DATATYPE_INT;
                node->symbol->dataType = DATATYPE_INT;
                break;
            case AST_T_POINTER:
                node->dataType = AST_DATATYPE_POINTER;
                node->symbol->dataType = DATATYPE_POINTER;
                break;
            default:
                break;
        }
    }
}