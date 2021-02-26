# Autor: Gustavo Oliva Barnasque
# Matricula: 00263056
#
# Makefile para etapa 2 de compiladores 

ETAPA=etapa2

${ETAPA}: y.tab.c lex.yy.c
	gcc lex.yy.c -o ${ETAPA} -Wall

y.tab.c: 
	yacc parser.y -d

lex.yy.c: scanner.l
	lex scanner.l

clean: 
	rm ${ETAPA} lex.yy.c y.tab.*