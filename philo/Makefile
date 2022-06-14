SRCS		=	philosophers.c				\
				srcs/utils.c				\
				srcs/initialization.c		\
				srcs/parsing.c				\
				srcs/action.c				\
				srcs/fork.c					\

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

RM			=	rm -f

CFLAGS		= 	-Wall -Wextra -Werror -g3 #-fsanitize=thread

CPPFLAGS	=	-I./includes

TH_FLAGS	=	-lpthread

NAME		= 	philo

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) $(TH_FLAGS)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re
