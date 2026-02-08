# CS-4145 Section 71
# Assignment 5: Syntax Error enhancement
# File: makefile - Makefile for building the parser, scanner and analyzer
# Author: Jacob A. Geldbach
# Date: 09/01/2025
# Description: Makefile for building current c- compiler, will evolve as the c- compiler is built out

# Binary and source setup
BIN = c-
NAME = parser

# Compiler and flags
CC = g++
CFLAGS = -g       	# Debug symbols (-g) + compile warnings
LDFLAGS = -g                	# Debug symbols for linking
SRC_DIR = .
BIN_DIR = .
# Source, header, and object files
SRCS = $(addprefix $(SRC_DIR)/, $(NAME).y $(NAME).l util.c ourgetopt.cpp lex.yy.c $(NAME).tab.c symbolTable.cpp semantic.cpp yyerror.cpp) 
HDRS = $(addprefix $(SRC_DIR)/, scanType.h util.h globals.h ourgetopt.h $(NAME).tab.h symbolTable.h semantic.h yyerror.h)
OBJS = $(addprefix $(BIN_DIR)/, lex.yy.o $(NAME).tab.o util.o ourgetopt.o symbolTable.o semantic.o yyerror.o)

# Rule to build the final binary
$(BIN): $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)

# Rule to generate lex.yy.c using Flex
$(SRC_DIR)/lex.yy.c: $(SRC_DIR)/$(NAME).l $(SRC_DIR)/$(NAME).tab.h $(HDRS)
	flex -o $(SRC_DIR)/lex.yy.c $(SRC_DIR)/$(NAME).l 

# Rule to generate parser.tab.c and parser.tab.h using Bison
$(SRC_DIR)/$(NAME).tab.c $(SRC_DIR)/$(NAME).tab.h: $(SRC_DIR)/$(NAME).y
	bison -v -t -d -o $(SRC_DIR)/$(NAME).tab.c $(SRC_DIR)/$(NAME).y 

# Rule to generate all .o files from SRCS
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	@mkdir -p $(BIN_DIR)      # Ensure BIN_DIR exists
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS)
	@mkdir -p $(BIN_DIR)      # Ensure BIN_DIR exists
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the workspace
clean: 
	rm -f *~ $(OBJS) $(BIN) $(SRC_DIR)/lex.yy.c $(SRC_DIR)/$(NAME).tab.h $(SRC_DIR)/$(NAME).tab.c $(SRC_DIR)/$(NAME).output JG_Assignment*.tar

# Create a tarball for submission (headers, sources, and Makefile)
tar: $(HDRS) $(SRCS) makefile
	tar -cvf JG_Assignment5.tar $(HDRS) $(SRCS) makefile
