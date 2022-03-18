# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 10:06:45 by hrazanam          #+#    #+#              #
#    Updated: 2021/11/30 20:11:11 by hrazanam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC_DIR		= .

SRCS		= $(SRC_DIR)/philosopher.c \
                        $(SRC_DIR)/ft_atoi.c \
                        $(SRC_DIR)/init.c \
                        $(SRC_DIR)/philo_state.c \
                        $(SRC_DIR)/stop_condition.c \
                        $(SRC_DIR)/time.c \
                        $(SRC_DIR)/actions.c \
                        $(SRC_DIR)/utils.c \
                        $(SRC_DIR)/exit.c \

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=thread


OBJS		= $(SRCS:.c=.o)

RM			= rm -f

.c.o:
			$(CC) $(CFLAGS) -I includes -c $(SRCS)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
