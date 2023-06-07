PROJECT_NAME = 3_01_Lab

SRC_DIR = source
INC_DIR = include
OBJ_DIR = object
BIN_DIR = bin

INC = $(wildcard $(INC_DIR)/*)
SRC = $(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
EXE = $(BIN_DIR)/$(PROJECT_NAME)

OBJ_FOLDER = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(wildcard $(SRC_DIR)/*))

CC			=	gcc
RM			=	rm -r
# Flag for C compiler
CFLAGS		=	-Wall
# Flag to preprocessor
# "-I" + "[directory]"	=> Find header file in [directory]
#	Ex: -Iinclude		=> Find header file in folder name "include"
# CPPFLAGS	=	-Iinclude
CPPFLAGS	=	$(patsubst $(INC_DIR)/%, -I$(INC_DIR)/%, $(INC))
# Flag for linker
# "-L" + "directory"	=> Finc libraries in [directory]
#	Ex: -Llib			=> Find libraries in folder name "lib"
#LDFLAGS		:=	-Llib
#LDLIBS		:=	-lm

run: build
	@./$(EXE)

build: $(EXE)	

$(EXE): $(OBJ)
	@mkdir -p $(BIN_DIR)
	@gcc $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_FOLDER)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@$(RM) $(BIN_DIR)/* $(OBJ_DIR)/*

test:
	@echo $(INC)
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(CPPFLAGS)
