// HEADER

NAME = ft_display_file
FLAGS = -Wall -Wextra -Werror
SRCS = ft_display_file.c tools.c

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
