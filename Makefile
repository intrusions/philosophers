SRCS		=	philosophers.c utils.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

RM			=	rm -f

CFLAGS		= 	-Wall -Wextra -Werror -g3 

CPPFLAGS	=	-I./includes

NAME		= 	philo

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) -lpthread 

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re