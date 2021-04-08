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
void fillDataTypes(AstNode*);

void checkAndSetDeclarations(AstNode*);
void checkUndeclared();
void checkOperands(AstNode*);
int getSemanticErrors();

void checkFuncReturn(AstNode*);

int countParametersFunction(AstNode*);
int isIntegerOperand(AstNode*);
int isCharOperand(AstNode*);
int isBoolOperand(AstNode*);
int isPointerOperand(AstNode*);
int hasSymbolIdentifier(AstNode*);
void setDataTypes(AstNode*);
int getSymbolDataTypeAsASTDataType(HashNode*);

void checkAndSetIdentifier(AstNode*, int);

#endif