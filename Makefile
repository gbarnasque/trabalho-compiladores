# Autor: Gustavo Oliva Barnasque
# Matricula: 00263056
#
# Makefile para etapa 4 de compiladores 

ETAPA=etapa4

${ETAPA}: y.tab.c lex.yy.c
	gcc lex.yy.c -o ${ETAPA}

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean: 
	rm ${ETAPA} lex.yy.c y.tab.* y.output