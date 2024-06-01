#______________________________________//_______________________________________
SRC_DIR		=	./source \
				./test
SRC			=	Utils.cpp
SRC_MAIN	=	main.cpp
SRC_TESTE	=	teste_main.cpp

OBJ_DIR		=	./build
OBJ			=	$(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJ_MAIN	=	$(SRC_MAIN:%.cpp=$(OBJ_DIR)/%.o)
OBJ_TESTE	=	$(SRC_TESTE:%.cpp=$(OBJ_DIR)/%.o)

PY_VERSION	=	$(shell python3 --version | cut -d " " -f2 | cut -d "." -f1,2)

INCD_DIR	=	-I ./include \
				-I /usr/include/python${PY_VERSION}
INCD		=	Utils.h
#______________________________________//_______________________________________
vpath %.cpp $(SRC_DIR)
vpath %.h $(INCD_DIR)
#______________________________________//_______________________________________
TARGET		=	main

TESTE		=	teste

CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address

PY_LIB_PATH	=	/usr/lib/python${PY_VERSION}/config-${PY_VERSION}-x86_64-linux-gnu/

PY_FLAGS	=	-L $(PY_LIB_PATH) -lpython$(PY_VERSION)

CC			=	g++

RM			=	rm -rf
#______________________________________//_______________________________________
all:			$(TARGET)

$(TARGET):	$(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(PY_FLAGS) $(OBJ) $(OBJ_MAIN) -o $(TARGET)
	@echo "\033[1;32m"
	@echo "/ ************************************ \\"
	@echo "|          Executavel Criado           |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

$(TESTE):	$(OBJ) $(OBJ_TESTE)
	$(CC) $(CFLAGS) $(PY_FLAGS) $(OBJ) $(OBJ_TESTE) -o $(TESTE)
	@echo "\033[1;32m"
	@echo "/ ************************************ \\"
	@echo "|          Executavel Criado           |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

$(OBJ_DIR)/%.o:	%.cpp $(INCD)
	mkdir -p $(OBJ_DIR)
	$(CC) $(INCD_DIR) $(CFLAGS) $(PY_FLAGS) $< -c -o $@
#______________________________________//_______________________________________
clean:
	$(RM) $(OBJ_DIR)
	@echo "\033[1;31m"
	@echo "/ ************************************ \\"
	@echo "|        Arquivos .o Deletados         |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

fclean:		clean
	$(RM) $(TARGET) $(TESTE)
	@echo "\033[1;31m"
	@echo "/ ************************************ \\"
	@echo "|         Executavel Deletado          |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"
#______________________________________//_______________________________________
re:			fclean all

.PHONY:		all clean fclean re
