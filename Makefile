NAME = fdf
SRC = .
INC = .
OBJ = .
LIST_SRC = $(SRC)/main.c $(SRC)/file.c $(SRC)/draw.c $(SRC)/init.c \
		$(SRC)/process.c $(SRC)/transform.c

LIST_OBJ = $(LIST_SRC:$(SRC)/%.c=$(OBJ)/%.o)
	#CFLAG = -Wall -Wextra -Werror
CFLAG = -Wall -Wextra -Werror -g 
LIBSMLX = -lmlx -lframework OpenGL -lframework AppKit
LIBFT = libft.a
LIBFTPATH = ./libft/
INC_LIBFTPATH  = $(LIBFTPATH)includes
LIBMLXPATH = ../minilibx
INCMINI = ../minilibx
OS:=$(shell uname)
ifeq ($(OS),Linux)
	LIBSMLX = -lmlx -lXext -lX11
else
	LIBSMLX = -lmlx -framework OpenGL -framework AppKit
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
