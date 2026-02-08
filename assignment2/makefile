# CS-4145 Section 71
# Assignment 2: Flex Scanner + Bison Parser
# File: makefile - Makefile for building the parser and scanner
# Author: Jacob A. Geldbach
# Date: 09/01/2025
# Description: Makefile for building the parser and scanner, will evolve as the c- compiler is built out

# Binary and source setup
BIN = c-
NAME = parser

# Compiler and flags
CC = g++
CFLAGS = -g       		  # Debug symbols (-g) + compile warnings
LDFLAGS = -g                  # Debug symbols for linking

# Source, header, and object files
SRCS = $(NAME).y $(NAME).l util.c ourgetopt.cpp
HDRS = scanType.h util.h globals.h ourgetopt.h
OBJS = lex.yy.o $(NAME).tab.o util.o ourgetopt.o

# Rule to build the final binary
$(BIN): $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)

# Rule to generate lex.yy.c using Flex
lex.yy.c: $(NAME).l $(NAME).tab.h $(HDRS)
	flex $(NAME).l

# Rule to generate parser.tab.c and parser.tab.h using Bison
$(NAME).tab.c $(NAME).tab.h: $(NAME).y
	bison -v -t -d $(NAME).y 

# Rule to compile C or C++ files into .o object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the workspace
clean: 
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(NAME).tab.h $(NAME).tab.c $(NAME).output JG_Assignment2.tar

# Create a tarball for submission (headers, sources, and Makefile)
tar: $(HDRS) $(SRCS) makefile
	tar -cvf JG_Assignment2.tar $(HDRS) $(SRCS) makefile
