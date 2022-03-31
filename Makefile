NAME		= fdf

FLAGS		= -Wall -Wextra -Werror -Ofast
INCL		= -I. -I./mlx -I./libft
LIB			= -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit

SRCS		= $(addprefix srcs/,	\
			  main.c				\
			  render.c				\
			  utils.c				\
			  bresenham.c			\
			  bresenham2.c			\
			  draw.c				\
			  image.c				\
			  keyboard.c			\
			  mouse.c				\
			  view_matrix.c			\
			  color.c				\
			  rotation.c			\
			  exit.c				\
			  parsing.c)


all :		$(NAME)

$(NAME) :	libft.a libmlx.a
	gcc $(FLAGS) $(INCL) $(LIB) $(SRCS) -o $(NAME)

libft.a :
	make -C ./libft

libmlx.a :
	make -C ./mlx

clean :
	make fclean -C ./libft
	make clean -C ./mlx
	rm $(NAME)

fclean :	clean

re :		fclean all

.PHONY :	re all clean fclean
