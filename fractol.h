/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:05:42 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/08 03:40:04 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include "./libft/libft.h"
# include "./SDL2/SDL.h"
# include "mlx.h"
# include <OpenCL/opencl.h>

# define PROGRAM_NAME			"fractol"

# define WIN_SIZE_X 			2560
# define WIN_SIZE_Y				1400
# define IMG_SIZE_X				2560
# define IMG_SIZE_Y				1400

# define TEXT_COLOR  			0xFFFFFF
# define BACK_COLOR  			0x555555

# define CPU					0
# define GPU					1

# define SOURCE_NAME			"fractol.cl"
# define KERNEL_NAME			"fractol"
# define MAX_SOURCE_SIZE		8192
# define LOCAL_WORK_SIZE		64

# define MANDELBROT				1
# define JULIA					2
# define BURNING_SHIP			3
# define SPIDER					4
# define SIN					5

typedef struct			s_sdl
{
    SDL_Window     		*win;
    SDL_Renderer   		*ren;
    SDL_Texture    		*tex;
    int             	*data;
}						t_sdl;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	int					*data;

	int					bits_per_pixel;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct			s_open_cl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;

	char				*platform_name;
	char				*device_name;
	char				*driver_ver;
	cl_uint				device_comp_units;
	cl_uint				device_frequency;

	size_t				source_size;
	char				*source_str;
	char				*program_build_log;

	size_t				global_work_size;
	size_t				local_work_size;

	cl_mem				buf;
}						t_open_cl;

typedef struct			s_status
{
	int					device;
	int					fractal_type;

	int					hide_info;
	int					color_theme;
	int					iter;
	int					pause;
	double				zoom;

	double				x_center;
	double				y_center;
	double				x_shift;
	double				y_shift;

	int					x_mouse_position;
	int					y_mouse_position;

	int					middle_mouse_button;
	double				x_move;
	double				y_move;

	double				x_julia;
	double				y_julia;
}						t_status;

typedef struct			s_global
{
	t_status			*status;
	t_sdl				*sdl;
	t_mlx				*mlx;
	t_open_cl			*open_cl;
}						t_global;

typedef struct			s_kernel_arg
{
	int					img_size_x;

	int					fractal_type;

	int					color_theme;
	int					iter;
	int					pause;
	double				zoom;

	double				x_center;
	double				y_center;
	double				x_shift;
	double				y_shift;

	double				x_julia;
	double				y_julia;
}						t_kernel_arg;

int						main(int argc, char **argv);
t_status				*init_status(int argc, char **argv);
t_mlx					*init_mlx(void);
t_sdl					*init_sdl(void);
void					draw(t_global *global);
void					mlx_hooks(t_global *global);

void					reset_status(t_status *status);
void					check_argument(t_status *status, char *arg);
void					error_wrong_argument(void);

void					mouse_move(int x, int y, t_global *global);
void						mouse_key_press(int key, int x, int y,
						t_global *global);
void					mouse_scroll(int wheel, t_global *global);
int						mouse_key_release(int key, int x, int y,
						t_global *global);
void						keyboard_key_press(int key, t_global *global);
void					close_window(t_global *global);

void					get_mouse_position(t_status *status, int x, int y);
void					control_zoom(t_status *status, int key);
void					control_mouse_zoom(t_status *status, int wheel);
void					control_shift(t_status *status, int key);
void					control_mouse_shift(t_status *status, int x, int y);

void					control_type(t_status *status);
void					control_iteration(t_status *status, int key);
void					control_colors(t_status *status);
void					control_device(t_global *global);
void					set_julia(t_status *status, int x, int y);

void					put_info_to_window(t_global *global);
void					put_control_keys_1(t_status *status, t_mlx *mlx);
void					put_control_keys_2(t_mlx *mlx);
void					put_open_cl_info(t_open_cl *open_cl, t_mlx *mlx);

void					put_status_1(t_mlx *mlx);
void					put_status_2(t_status *status, t_mlx *mlx);
void					put_status_3(t_status *status, t_mlx *mlx);
void					put_status_4(t_status *status, t_mlx *mlx);
void					put_status_5(t_status *status, t_mlx *mlx);

t_open_cl				*init_open_cl(int device);
void					get_device(t_open_cl *open_cl, int device);
void					read_open_cl_kernel(t_open_cl *open_cl);
void					load_open_cl_kernel(t_open_cl *open_cl);

void					get_open_cl_info(t_open_cl *open_cl);
void					get_device_info_1(t_open_cl *open_cl);
void					get_device_info_2(t_open_cl *open_cl);
void					get_platform_info(t_open_cl *open_cl);
void					get_program_build_log(t_open_cl *open_cl);

void					run_open_cl(t_global *global);
void					set_arg_open_cl_kernel(t_status *status,
						t_open_cl *open_cl);
void					pack_arg_to_struct(t_status *status,
						t_kernel_arg *kernel_arg);
void					execute_open_cl_kernel(t_open_cl *open_cl);
void					get_open_cl_result(t_open_cl *open_cl, t_sdl *sdl);

void					clean_open_cl(t_open_cl *open_cl);
void					clean_open_cl_1(t_open_cl *open_cl);
void					clean_open_cl_2(t_open_cl *open_cl);

void					put_error_pn(char *str);
void					put_open_cl_error(t_open_cl *open_cl, char *str,
						cl_int err_code);
char					*open_cl_error_interpret(cl_int err_code);
char					*open_cl_error_1(cl_int err_code);

char					*open_cl_error_2(cl_int err_code);
char					*open_cl_error_3(cl_int err_code);
char					*open_cl_error_4(cl_int err_code);
char					*open_cl_error_5(cl_int err_code);
char					*open_cl_error_6(cl_int err_code);


void	clean_sdl(t_sdl *sdl);

#endif
