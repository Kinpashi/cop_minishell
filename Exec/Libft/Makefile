CC = cc
CFLAGS = -Wall -Wextra -Werror 

RM = rm -rf
AR = ar rc

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
	   ft_split.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	   ft_strchr.c ft_strdup.c ft_striteri.c ft_itoa.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
	   ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\

B_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
		 ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJECTS = $(SRCS:.c=.o)
B_OBJECTS = $(B_SRCS:.c=.o)

RED='\033[0;31m'

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
	$(AR) $(NAME) $@

bonus: all $(B_OBJECTS)

clean:
	@echo $(RED) "REMOVING .o"
	@echo "######################### 100%"
	@$(RM) $(OBJECTS) $(B_OBJECTS)

fclean: clean
	@echo $(RED) "REMOVING BIN"
	@echo "######################### 100%"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
