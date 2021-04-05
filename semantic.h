/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

extern int SemanticErrors;

void checkAndSetDeclarations(AstNode*);
void checkUndeclared();
int getSemanticErrors();
void setDataType(AstNode*);

#endif