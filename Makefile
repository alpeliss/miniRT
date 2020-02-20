NAME = miniRT

SRCDIR = ./srcs/

SRCNAMES =	main.c \
			utils.c

INC = ./includes/
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
OBJ = $(patsubst %.c,%.o, $(SRC))

LIB_MLX = minilibX/libmlx.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -framework OpenGL -framework Appkit
RM = rm -f

all: $(NAME)

.c.o:
		${CC} ${CFLAGS} -I ${INC} -c $<  -o ${<:.c=.o}

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(SANI) -o $(NAME) $(LIBFT) $(OBJ) $(MLXFLAGS)
		@echo "\033[0;32m[OK] \033[0m\033[0;33m Compiling file:\033[0m " $@

clean:
	@echo "\033[0;32m[OK] \033[0m\033[0;33m :\033[0m " $@
	@/bin/rm -f $(OBJ)

fclean: clean
		@echo "\033[0;32m[OK] \033[0m\033[0;33m :\033[0m " $@
		@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
