# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 12:49:28 by ggasset-          #+#    #+#              #
#    Updated: 2024/12/11 18:28:24 by ggasset-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

libft_NAME=./libft/libft.a
minilibx_NAME=./minilibx-linux/libmlx_Linux.a
ARCHIVES= ${libft_NAME} ${minilibx_NAME}

C_FILES= main.c dealloc.c draw_router.c mandelbrot.c hooking.c julia.c argv.c
O_FILES= main.o dealloc.o draw_router.o	mandelbrot.o hooking.o julia.o argv.o

minilibx_COMPILATION_FLAGS= -I/usr/include -I./minilibx-linux/ -I./libft/ 
minilibx_LINKING_FLAGS=-L/usr/lib -lXext -lX11 -lm -lz 
CC_SECURITY_FLAGS= -Wall -Wextra -Werror
DEBUG_FLAGS= #-g #-fanalyzer

LOGO=\n ▗▄▄▄▄▖    ▗▄▄▄▄▖\n▐▌        ▐▌ \n▐▌ ▝▝▜▌   ▐▌ ▝▝▜▌\n▝▚▄▄▄▞▘   ▝▚▄▄▄▞▘     \n

all: libs-all ${NAME} logo

${NAME}: ${O_FILES} ${ARCHIVES}
	cc ${minilibx_LINKING_FLAGS} -o ${NAME} ${O_FILES} ${ARCHIVES}

%.o: %.c
	cc ${DEBUG_FLAGS} ${CC_SECURITY_FLAGS} ${minilibx_COMPILATION_FLAGS} -c $?

re: fclean all

fclean: clean
	rm -f ${NAME}

clean: libs-fclean
	rm -f ${O_FILES}

re-fractol:
	rm ${O_FILES}
	make all

# LIBRARIES

libs-all: libft minilib-all

libs-re: libs-fclean libs-all

libs-fclean: libft-fclean minilib-clean

libs-clean: libft-clean minilib-clean

# LIBFT

libft:
	make --directory=./libft/ all

libft-re: libft-fclean libft

libft-clean:
	make --directory=./libft/ clean

libft-fclean:
	make --directory=./libft/ fclean

# MINILIB

minilib-all:
	make --directory=./minilibx-linux/ all

minilib-clean:
	make --directory=./minilibx-linux/ clean

logo:
	@echo "${LOGO}"
	@sleep .25

.PHONY: all re fclean clean libs-all libs-re libs-fclean libs-clean libft libft-re libft-clean libft-fclean minilib-all minilib-clean logo