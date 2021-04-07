/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

extern int SemanticErrors;

void checkAndSetDeclarations(AstNode*);
void checkUndeclared();
void checkOperands(AstNode*);
int getSemanticErrors();

int isIntegerOperand(AstNode*);
int isCharOperand(AstNode*);
int isBoolOperand(AstNode*);
int isPointerOperand(AstNode*);
void setDataType(AstNode*);

void checkAndSetIdentifier(AstNode*, int);

#endif