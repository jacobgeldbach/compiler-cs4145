# CS-4145 Section 71
# Assignment 1: Flex Scanner + Bison Parser
# File: makefile - Makefile for building the parser and scanner
# Author: Jacob A. Geldbach
# Date: 09/01/2025
# Description: Makefile for building the parser and scanner, will evolve as c- compiler is built out

BIN = c-
NAME = parser
CC = g++

SRCS = $(NAME).y  $(NAME).l
HDRS = scanType.h
OBJS = lex.yy.o $(NAME).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN)

lex.yy.c : $(NAME).l $(NAME).tab.h $(HDR)
	flex $(NAME).l

$(NAME).tab.h $(NAME).tab.c : $(NAME).y
	bison -v -t -d $(NAME).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(NAME).tab.h $(NAME).tab.c $(NAME).output JG_Assignment1.tar

tar : $(HDR) $(SRCS) makefile
	tar -cvf JG_Assignment1.tar $(HDRS) $(SRCS)  makefile
