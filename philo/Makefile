NAME = philo
DIR_OBJ = obj
LIST_TMP = ft_atoilong.c ft_init.c ft_monitor.c ft_utils.c ft_routine.c ft_start_threads.c main.c
OBJ = $(addprefix $(DIR_OBJ)/, $(LIST_TMP:.c=.o))

all : $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra -g -pthread $(OBJ) -o $(NAME)

$(DIR_OBJ)/%.o : ./%.c ./philo.h
	mkdir -p $(DIR_OBJ)
	gcc -Wall -Werror -Wextra -g -pthread -c $< -o $@

clean :
	rm -rf $(DIR_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
