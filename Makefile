SRCF = fractol_render.c cal_utils.c fractol_events.c fractol.c fractol_utils.c

NAME = fractol

OBJF = ${SRCF:.c=.o}

CC = cc

FLAGS = -Wall -Wall -Werror

MLX = -Lmlx_linux -lmlx -lXext -lX11

RM = rm -f

all: ${NAME}

${NAME}: ${OBJF}
	${CC} ${OBJF} ${MLX} -o ${NAME}

clean:
	${RM} ${OBJF}
fclean:
	${RM} ${NAME} ${OBJF}
re: fclean all
