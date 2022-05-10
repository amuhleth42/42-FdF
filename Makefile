NAME		= fdf

FLAGS		= -Wall -Wextra -Werror -Ofast
INCL		= -I. -I./mlx -I./libft
LIB			= -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit

SRCS_DIR	= srcs
OBJS_DIR	= $(shell mkdir -p objs && printf "objs")

SRCS		=	main.c				\
				render.c			\
			  	bresenham.c			\
				bresenham2.c		\
				draw.c				\
				keyboard.c			\
				mouse.c				\
				view_matrix.c		\
				color.c				\
				rotation.c			\
				exit.c				\
				parsing.c

OBJS	= $(SRCS:%.c=$(OBJS_DIR)/%.o)

all :		$(NAME)

$(OBJS_DIR)/%.o :	$(SRCS_DIR)/%.c
	gcc $(FLAGS) $(INCL) -c $< -o $@

$(NAME) :	libft.a libmlx.a $(OBJS)
	gcc $(FLAGS) $(INCL) $(LIB) $(OBJS) -o $(NAME)

libft.a :
	make -C ./libft

libmlx.a :
	make -C ./mlx

clean :
	make fclean -C ./libft
	make clean -C ./mlx
	rm -rf $(OBJS_DIR)
	rm $(NAME)

fclean :	clean

re :		fclean all

.PHONY :	re all clean fclean
