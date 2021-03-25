NAME=webserv
SRC=main.cpp
#HPP= ""  # FIXME
CC= clang++
OBJ=$(SRC:.cpp=.o)
FLAGS= -g -Wall -Wextra # -Werror FIXME

all: $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) # $(HPP)  # FIXME
	$(CC) $(FLAGS) -o $(NAME) $(OBJ);

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME);

re: fclean all
