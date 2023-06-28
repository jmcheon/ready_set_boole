NAME = rsb

INCLUDES = ./

SRCS_DIR = src/
SRCS = main.cpp \
		exercise.cpp \
		Tokenizer.cpp \
		RPNtree.cpp \
		ReadySetBoole.cpp
		

OBJS_DIR = obj/

OBJS = $(SRCS:.cpp=.o)
OBJS := $(addprefix $(OBJS_DIR), $(OBJS))

MKDIR = /bin/mkdir -p
MKDIR_OBJS = $(MKDIR) $(OBJS_DIR)

CC = c++
CFLAGS = -Wall -Werror -Wextra
RM = /bin/rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I $(INCLUDES)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@$(MKDIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	$(RM) $(OBJS) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean
