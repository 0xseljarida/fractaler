SRC = fractol_render.c cal_utils.c fractol_events.c fractol.c fractol_utils.c ft_putstr_fd.c extra_utils.c

NAME = fractol
HEADER = fractol.h
OBJ = ${SRC:.c=.o}

CC = cc

CFLAGS = -Wall -Wall -Werror

MLX = -Lmlx_linux -lmlx -lXext -lX11

RM = rm -f

all: ${NAME} ${HEADER}

bonus: all

${NAME}: ${OBJ} 
	${CC} ${OBJ} ${MLX} -o ${NAME}

clean:
	${RM} ${OBJ}
fclean:
	${RM} ${NAME} ${OBJ}
re: fclean all
