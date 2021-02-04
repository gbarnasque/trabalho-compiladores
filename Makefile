# Makefile para trabalho 1 de compiladores

etapa1: lex.yy.c
	gcc lex.yy.c -o etapa1

all: compile

compile: gcc -o

clean: 
	rm -rf *.o *.out *.exe lex.yy.c