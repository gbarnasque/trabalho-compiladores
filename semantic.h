/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

extern int SemanticErrors;

void semanticVerification(AstNode*);

void setBaseDataTypes(AstNode*);
void setDataTypeBasedOnSymbolDataType(AstNode*);

void checkAndSetDeclarations(AstNode*);
void checkUndeclared();
void checkOperands(AstNode*);
int getSemanticErrors();

void checkFuncReturn(AstNode*);
void preCheckFuncCallParams(AstNode*);
void checkFuncCallParams(AstNode*);
int getReturnDataTypeFunc(AstNode*);

int countParametersFunction(AstNode*);
int countParametersCallFunction(AstNode*);
int* getDataTypesFuncParameters(AstNode*);
int* getDataTypesFuncParametersCall(AstNode*);
void fillDataTypeFuncParameters(AstNode*, int*, int);
void fillDataTypeFuncParametersCall(AstNode*, int*, int*);
int checkDataTypeParameters(AstNode*, int*, int, int);

int isIntegerOperand(AstNode*);
int isCharOperand(AstNode*);
int isBoolOperand(AstNode*);
int isPointerOperand(AstNode*);
int hasSymbolIdentifier(AstNode*);
void setDataTypes(AstNode*);
int getSymbolDataTypeAsASTDataType(HashNode*);


void checkAndSetIdentifier(AstNode*, int);
int checkDataTypeCompatibility(int, int);

#endif