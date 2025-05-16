CC = cc
RM = rm -f
# FLAGS = -Wall -Wextra -Werror -fsanitize=address
# FLAGS = -Wall -Wextra -Werror
READLINE = $(shell brew --prefix readline)
CFLAGS = -Wall -Wextra -Werror -I$(READLINE)/include  -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror  -fsanitize=address
LDFLAGS =   $(CFLAGS) -L$(READLINE)/lib -lreadline

SRC = parsing/main.c parsing/tokenization.c parsing/tokenization_helper.c parsing/grabage.c parsing/error.c\
	parsing/error_helper.c parsing/expand.c parsing/expand_helper1.c parsing/expand_helper2.c\
	parsing/ft_rename.c parsing/ft_herdoc.c parsing/ft_herdoc_expand.c parsing/ft_herdoc_expand_helper.c\
	parsing/parsing.c parsing/parsing_helper.c\
	libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_cmp.c libft/ft_strjoin.c\
	libft/linked_list.c libft/ft_substr.c libft/ft_strdup.c libft/ft_isprint.c\
	libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_strncmp.c\
	libft/ft_strndup.c libft/ft_allocate.c libft/ft_strcat.c libft/ft_strncpy.c\
	libft/ft_memset.c libft/ft_strcmp.c libft/ft_split.c\
	peltend/env.c libft/ft_lstadd_back_bonus.c libft/ft_lstdelone_bonus.c libft/ft_lstnew_bonus.c\
	libft/ft_lstsize_bonus.c peltend/ft_tchc_data.c peltend/pwd.c peltend/echo.c\
	peltend/unset.c peltend/exit.c peltend/cd.c peltend/export.c peltend/tchcke_pluss.c\
	peltend/ft_thchk_cotchen.c libft/ft_strchr.c peltend/are_env.c libft/ft_strlcpy.c\
	peltend/excoshen.c peltend/excoshen_n_test.c libft/ft_strcpy.c libft/ft_lstclear_bonus.c \
	peltend/export_one.c peltend/export_tow.c peltend/expoert_three.c  

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME) 

# parsing/%.o: parsing/%.c include/minishell.h
# 	$(CC) $(CFLAGS) -c $< -o $@

# peltend/%.o: peltend/%.c include/minishell.hz
# 	$(CC) $(CFLAGS) -c $< -o $@

# libft/%.o: libft/%.c  include/minishell.h
# 	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.c include/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
