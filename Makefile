SRC = main.c fractol_parse.c fractol_render.c fractol_events.c fractol_init.c fractol_math.c string_utils.c

NAME = fractol

OBJ = ${SRC:.c=.o}

CC = cc

CFLAGS = -Wall -Wall -Werror

MLX = -Lmlx_linux -lmlx -lXext -lX11

RM = rm -f

all: ${NAME}

${OBJ}: fractol.h

${NAME}: ${OBJ}
	${CC} ${OBJ} ${MLX} -o ${NAME}

clean:
	${RM} ${OBJ}
fclean:
	${RM} ${NAME} ${OBJ}
re: fclean all
