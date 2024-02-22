
#TODO   fix relink, if I change header it doesnt recompile

NAME 	=	mini
CC	=	gcc
CFLAGS	=	-Wall -Werror -Wextra
OBJ_DIR = obj
OBJ	=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
NAMELIB	=	mini.a

LINK 	=	-lmlx  -framework OpenGL -framework AppKit -L ./mlx -lm
SRC		=	main.c
COMP	=	$(CC) $(CFLAGS) $(LINK)
RM		=	rm -f
all: $(NAME)

$(NAME): $(OBJ)
	$(COMP) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean