NAME = philo

SRCS :=	main.c validation.c parsing.c run_philo.c utiles1.c utiles2.c

GCC = gcc -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)

%.o:        %.c
		$(GCC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		$(GCC) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

PHONY: all clean fclean re