NAME=webserv

#SRC_FILES=main.cpp Server.cpp Request.cpp
#HPP= Request.hpp Server.hpp  # FIXME

SRC_FILES=$(shell ls -1 | grep \.cpp )
HPP= $(shell ls -1 | grep \.hpp ) $(addprefix interfaces/, $(shell ls -1 interfaces | grep \.hpp ))

CC= clang++
OBJ_DIR=obj/
SRC_DIR=./

SRC=$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ=$(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

FLAGS= -g -Wall -Wextra -I interfaces -I . # -Werror FIXME

all: $(NAME)

deb:
	@echo "SOURCES " $(SRC_FILES)
	@echo "HEADERS " $(HPP)
	@echo $(SRC)
	@echo $(OBJ)

$(OBJ_DIR) : 
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp 
	@echo $@
	@echo $<
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)  $(HPP)  # FIXME
	$(CC) $(FLAGS) -o $(NAME) $(OBJ);

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME);

re: fclean all
