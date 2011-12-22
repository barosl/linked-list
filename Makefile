NAME = linked-list
OBJS = main.o linked.o

STRIP = strip

CFLAGS = -Wall -Wextra -Werror -Wc++-compat

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $+
	$(STRIP) $(NAME)

clean:
	rm -f $(NAME) $(OBJS)
