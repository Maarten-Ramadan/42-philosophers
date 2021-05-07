# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mramadan <mramadan@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/25 16:39:10 by mramadan      #+#    #+#                  #
#    Updated: 2021/02/22 10:16:00 by Marty         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

SRC_DIR = ./srcs

SRC = main.c parse.c utils.c activities.c

FILES = $(addprefix $(SRC_DIR)/, $(SRC))

FLAGS = -Wall -Werror -Wextra -O3

all: $(NAME)

$(NAME): $(FILES)
	@gcc $(FLAGS) -I ./includes/ $(FILES) -o $(NAME)
	@echo "[philo_two] Compiled successfuly! [OK]"

clean:

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
