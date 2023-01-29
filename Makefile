# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 14:59:45 by dojannin          #+#    #+#              #
#    Updated: 2023/01/28 18:11:51 by dojannin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ = $(SRCS:.c=.o)

CFLAGS += -Wall -Wextra -Werror -pthread 

SRCS = 	main.c \
		utils.c \
		utils2.c \
		parse.c \
		routines.c \
		message.c \
		death.c \
				
%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@
	
$(NAME):		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

bonus:		$(OBJBONUS)
	$(CC) $(CFLAGS) $(OBJBONUS) -o $(NAME) 

all:			$(NAME)

clean:			
				rm -f $(OBJ)

fclean:			clean
					rm -f $(NAME)

norme:
					norminette -R CheckForbiddenSourceHeader $(SRCS) 

re:				fclean all

.PHONY :		all clean fclean re
