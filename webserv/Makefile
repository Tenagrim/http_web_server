
CC= clang++
CFLAGS= -g -Wall -Wextra -Werror

NAME=webserv

SRC_DIR=./
UTILS_DIR=$(SRC_DIR)utils
OBJ_DIR=obj/
HPP_DIRS=./ ./interfaces/

SRC_FILES=$(shell ls -1 $(SRC_DIR) | grep \.cpp )
UTILS_FILES=$(shell ls -1 $(UTILS_DIR) | grep \.cpp)
HPP= $(shell ls -1 | grep \.hpp ) $(addprefix interfaces/, $(shell ls -1 interfaces | grep \.hpp ))

SRC=$(addprefix $(SRC_DIR), $(SRC_FILES))
UTILS= $(addprefix utils/, $(UTILS_FILES))
OBJ=$(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o)) $(addprefix $(OBJ_DIR), $(UTILS_FILES:.cpp=.o))
DEP=$(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.d)) $(addprefix $(OBJ_DIR), $(UTILS_FILES:.cpp=.d))

LINK=$(addprefix -I, $(HPP_DIRS))

all: $(NAME)

deb:
	@echo "SOURCES " $(SRC_FILES) "\n"
	@echo "UTILS " $(UTILS) "\n"
	@echo "HEADERS " $(HPP) "\n"
	@echo "SRC" $(SRC) "\n"
	@echo "OBJ" $(OBJ) "\n"
	@echo "DEP" $(DEP) "\n"

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)%.o: utils/%.cpp
	$(CC) $(CFLAGS) $(LINK) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) $(LINK) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(LINK) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -rf $(NAME);

re: fclean all
