#______________________________________//_______________________________________
SRC_DIR		=	./source \
				./test
SRC			=	Externo.cpp \
				Acao.cpp \
				Carteira.cpp \
				Menu.cpp
SRC_MAIN	=	main.cpp
SRC_TESTE	=	teste_main.cpp

OBJ_DIR		=	./build
OBJ			=	$(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJ_MAIN	=	$(SRC_MAIN:%.cpp=$(OBJ_DIR)/%.o)
OBJ_TESTE	=	$(SRC_TESTE:%.cpp=$(OBJ_DIR)/%.o)

PY_VERSION	=	$(shell python3 --version | cut -d " " -f2 | cut -d "." -f1,2)

INCD_DIR	=	-I ./include \
				-I /usr/include/python${PY_VERSION}
INCD		=	Externo.h \
				Acao.h \
				Carteira.h \
				Menu.h
#______________________________________//_______________________________________
vpath %.cpp $(SRC_DIR)
vpath %.h $(INCD_DIR)
#______________________________________//_______________________________________
TARGET		=	main

TESTE		=	teste

CFLAGS		=	-Wall -Wextra -Werror -std=c++11 #-fsanitize=address

PY_LIB_PATH	=	/usr/lib/python${PY_VERSION}/config-${PY_VERSION}-x86_64-linux-gnu/

PY_FLAGS	=	-L $(PY_LIB_PATH) -lpython$(PY_VERSION)

PY_CACHE	=	./py_source/__pycache__

CC			=	g++

RM			=	rm -rf
#______________________________________//_______________________________________
all:			$(TARGET)

$(TARGET):	$(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_MAIN) $(PY_FLAGS) -o $(TARGET)
	@echo "\033[1;32m"
	@echo "/ ************************************ \\"
	@echo "|          Executavel Criado           |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

$(TESTE):	$(OBJ) $(OBJ_TESTE)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_TESTE) $(PY_FLAGS) -o $(TESTE)
	@echo "\033[1;32m"
	@echo "/ ************************************ \\"
	@echo "|          Executavel Criado           |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

$(OBJ_DIR)/%.o:	%.cpp $(INCD)
	mkdir -p $(OBJ_DIR)
	$(CC) $(INCD_DIR) $(CFLAGS) $< -c $(PY_FLAGS) -o $@
#______________________________________//_______________________________________
clean:
	$(RM) $(OBJ_DIR)
	@echo "\033[1;31m"
	@echo "/ ************************************ \\"
	@echo "|        Arquivos .o Deletados         |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"

fclean:		clean
	$(RM) $(TARGET) $(TESTE) $(PY_CACHE)
	@echo "\033[1;31m"
	@echo "/ ************************************ \\"
	@echo "|         Executavel Deletado          |"
	@echo "\\ ************************************ /"
	@echo "\033[0m"
#______________________________________//_______________________________________
re:			fclean all

ret:		fclean $(TESTE)
#______________________________________//_______________________________________
git:
	git add .
	git status
	git commit -m "$m"

.PHONY:		all clean fclean re ret git
