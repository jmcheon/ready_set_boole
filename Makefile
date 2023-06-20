NAME := rsb
SRCS := ReadySetBoole.cpp Tokenizer.cpp RPNtree.cpp main.cpp
OBJS := $(SRCS:.cpp=.o)

CC := c++
CFLAGS := -Wall -Werror -Wextra
RM = /bin/rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I ./

.cpp.o:
	@$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean
