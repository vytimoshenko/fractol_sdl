# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 19:45:56 by hlorrine          #+#    #+#              #
#    Updated: 2020/02/13 01:09:59 by mperseus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	fractol

HDR		= 	fractol.h

SRC		= 	fractol_main.c					\
			fractol_status_init.c			\
			fractol_sdl_init.c				\
			fractol_sdl_run.c				\
			fractol_sdl_events.c			\
			fractol_sdl_control_1.c			\
			fractol_sdl_control_2.c			\
			fractol_sdl_draw_info.c			\
			fractol_sdl_other.c				\
			fractol_open_cl_init.c			\
			fractol_open_cl_info.c			\
			fractol_open_cl_run.c			\
			fractol_open_cl_clean.c			\
			fractol_open_cl_err.c
		
OBJ		= 	$(SRC:.c=.o)

MK_FT	=	make -C libft
CL_FT	=	make clean -C libft
FCL_FT	=	make fclean -C libft

MK_DIR	=	@/bin/mkdir screenshots

ADD_ERR =	-Wall -Wextra -Werror

ADD_OPT =	-Ofast

ADD_LIB =	-L ./libft				-l ft\
			-L ./SDL2/SDL2 			-l SDL2\
			-L ./SDL2/SDL2_ttf 		-l SDL2_ttf\
			-L ./SDL2/SDL2_image	-l SDL2_image
			
ADD_FMW =	-framework OpenCL 

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MK_FT)
			gcc -o $(NAME) $(OBJ) $(ADD_ERR) $(ADD_OPT) $(ADD_LIB) $(ADD_FMW)
			$(MK_DIR)

%.o:		%.c
			gcc -I $(HDR) $< -c -o $@ $(ADD_ERR) $(ADD_OPT)

clean:		
			@/bin/rm -f $(OBJ)
			$(CL_FT)
			@/bin/rm -rf screenshots

fclean: 	clean
			@/bin/rm -f $(NAME)
			$(FCL_FT)

re: 		fclean all

.PHONY: 	all clean fclean re