# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 15:21:52 by sbhatta           #+#    #+#              #
#    Updated: 2023/07/02 12:57:49 by sbhatta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Werror -Wall
LIBFT_PATH = ./lib/libft
LIBFT = $(LIBFT_PATH)/libft.a
NAME = pipex
BONUS = pipex_bonus

SRC = 	 ./src/free_and_exit.c ./src/handle_process.c ./src/parse_env.c ./src/execute.c ./src/awk_sed_check.c
OBJ = $(SRC:.c=.o)

BONUS_SRC = ./src/free_and_exit.c ./src/handle_process.c ./src/parse_env.c ./src/execute.c ./src/is_here_doc_bonus.c ./src/awk_sed_check.c
BONUS_OBJ = $(BONUS_SRC:.c=.o);

all:$(NAME)
bonus:$(BONUS)

$(NAME): $(OBJ) $(LIBFT)
		$(CC) ./src/main.c -o $@ $^

%.o:%.c
		$(CC) -c $(CFLAGS) -o $@ $<

$(BONUS): $(LIBFT) $(BONUS_OBJ) 
		$(CC) ./src/main_bonus.c ./src/free_and_exit.o ./src/handle_process.o ./src/parse_env.o ./src/execute.o ./src/is_here_doc_bonus.o ./src/awk_sed_check.o ./lib/libft/libft.a  -o $(BONUS)
		
$(LIBFT):
		@make all -C $(LIBFT_PATH)

clean:
		make -C $(LIBFT_PATH) clean
		rm -f $(OBJ)
		
fclean: clean
		make -C $(LIBFT_PATH) fclean
		rm -f $(NAME)
		
re:		fclean all

clean_bonus:
		make -C $(LIBFT_PATH) clean
		rm -f $(BONUS_OBJ)
		
fclean_bonus: clean_bonus
		make -C $(LIBFT_PATH) fclean
		rm -f $(BONUS)
		
re_bonus: fclean bonus

.PHONY: all clean fclean re fclean_bonus clean_bonus re_bonus bonus