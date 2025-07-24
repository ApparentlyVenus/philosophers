NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -f

SRCDIR = src
INCDIR = inc
OBJDIR = obj

SOURCES = main.c parse_init.c actions.c routine.c forks.c utils.c monitoring.c cleanup.c
SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
