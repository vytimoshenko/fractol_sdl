# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 19:45:56 by hlorrine          #+#    #+#              #
#    Updated: 2020/02/09 03:52:08 by mperseus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	fractol

HDR		= 	fractol.h

SRC		= 	fractol_main.c					\
			fractol_status_init.c			\
			fractol_sdl_init.c				\
			fractol_sdl_events.c			\
			fractol_sdl_control_1.c			\
			fractol_sdl_control_2.c			\
			fractol_sdl_clean.c				\
			fractol_open_cl_init.c			\
			fractol_open_cl_info.c			\
			fractol_open_cl_run.c			\
			fractol_open_cl_clean.c			\
			fractol_open_cl_err.c
		
OBJ		= 	$(SRC:.c=.o)

LIB		=	make -C libft

ADD_ERR =	-Wall -Wextra -Werror

ADD_OPT =	-Ofast

ADD_LIB =	-L./libft -lft\
			-L/usr/local/lib/\
			-L SDL2/lib -l SDL2
			
ADD_FMW =	-lmlx -framework OpenGL -framework AppKit\
			-framework OpenCL 

all:		$(NAME)

$(NAME):	$(OBJ)
			$(LIB)
			gcc -o $(NAME) $(OBJ) $(ADD_ERR) $(ADD_OPT) $(ADD_LIB) $(ADD_FMW)

%.o: %.c
			gcc -I $(HDR) $< -c -o $@ $(ADD_ERR) $(ADD_OPT)

clean:
			@/bin/rm -f $(OBJ)

fclean: 	clean
			@/bin/rm -f $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re