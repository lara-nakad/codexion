# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/01 14:24:10 by lnakad            #+#    #+#              #
#    Updated: 2026/04/01 22:15:11 by lnakad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
RM = rm -f
SOURCES = behavior.c checking_values.c clean_up.c general.c init.c \
main.c monitor.c operations.c schedular.c simulation.c synchronization.c \
utils.c write.c

OBJS = ${SOURCES:.c=.o}
all: ${NAME}
$(NAME): $(OBJS)
		 $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@
	
clean:
	${RM} ${OBJS}
fclean: clean
	${RM} ${NAME}
re: fclean all
.PHONY: all clean fclean