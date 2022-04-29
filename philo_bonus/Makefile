NAME = philo_bonus
DIR_OBJ = obj
LIST_TMP = ft_atoilong_bonus.c ft_init_bonus.c ft_utils_bonus.c main_bonus.c ft_routine_bonus.c
OBJ = $(addprefix $(DIR_OBJ)/, $(LIST_TMP:.c=.o))

all : $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra -g -pthread $(OBJ) -o $(NAME)


$(DIR_OBJ)/%.o : ./%.c ./philo_bonus.h
	mkdir -p $(DIR_OBJ)
	gcc -Wall -Werror -Wextra -g -pthread -c $< -o $@

clean :
	rm -rf $(DIR_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
