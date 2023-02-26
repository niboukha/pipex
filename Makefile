# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niboukha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 17:33:08 by niboukha          #+#    #+#              #
#    Updated: 2023/02/24 17:33:10 by niboukha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = pipex.c  pipex_utils.c ft_calloc.c ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c ft_strchr.c

BONUS = pipex_bonus.c pipex_bonus_utils.c ft_calloc.c ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c ft_strchr.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all :$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

clean :
	rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: all re clean fclean
