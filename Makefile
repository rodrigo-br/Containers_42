SRCS	=	$(shell ls ./ | grep .cpp$)

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	containers

CC 		=	c++
CFLAGS	=	-g3 -Wall -Wextra -Werror -Wshadow -std=c++98

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -rf $(OBJS)
			rm -rf leaks.txt

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

test:	re
		valgrind --leak-check=full --show-leak-kinds=all --log-file="leaks.txt" ./$(NAME)