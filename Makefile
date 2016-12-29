NAME = fdf
SRC = .
INC = .
OBJ = .
LIST_SRC = $(SRC)/main.c $(SRC)/file.c $(SRC)/draw.c $(SRC)/init.c \
		$(SRC)/process.c $(SRC)/transform.c $(SRC)/check.c $(SRC)/color.c \
		$(SRC)/keys.c $(SRC)/display.c $(SRC)/point.c

LIST_OBJ = $(LIST_SRC:$(SRC)/%.c=$(OBJ)/%.o)
	#CFLAG = -Wall -Wextra -Werror
CFLAG = -Wall -Wextra -Werror -g 
LIBFT = libft.a
LIBFTPATH = ./libft/
INC_LIBFTPATH  = $(LIBFTPATH)includes
OS:=$(shell uname)
ifeq ($(OS),Linux)
	LIBSMLX = -lmlx -lXext -lX11 -lm
	LIBMLXPATH = ../minilibx
	INCMINI = ../minilibx
else
	LIBSMLX = -lmlx -lm -framework OpenGL -framework AppKit
	LIBMLXPATH = .
	INCMINI = .
endif
all : $(NAME)

$(NAME) : $(LIST_SRC)
	make -C $(LIBFTPATH)
	gcc $(CFLAG) $(LIST_SRC) -I $(INC) -I $(INCMINI) -I $(INC_LIBFTPATH) -L$(LIBFTPATH)\
		-L$(LIBMLXPATH) -lft $(LIBSMLX) -o $(NAME)

clean :
	make clean -C $(LIBFTPATH)
	/bin/rm -f  $(LIST_OBJ)

fclean : clean
	make fclean -C $(LIBFTPATH)
	/bin/rm -f $(NAME)

re : fclean all
