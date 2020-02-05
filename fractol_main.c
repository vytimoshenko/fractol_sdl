/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:09:39 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/06 02:57:05 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_sdl		*init_sdl(void)
{
	t_sdl *sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_put_errno(PROGRAM_NAME);
	SDL_Init(SDL_INIT_VIDEO);
	sdl->win = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, IMG_SIZE_X, IMG_SIZE_Y, 0);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, 0);
	sdl->tex = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STATIC, IMG_SIZE_X, IMG_SIZE_Y);
	sdl->data = (int *)malloc(sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);
	ft_memset(sdl->data, 128, sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);
	return (sdl);
}

t_status	*init_status(int argc, char **argv)
{
	t_status		*status;

	if (argc != 2)
		error_wrong_argument();
	if (!(status = (t_status *)ft_memalloc(sizeof(t_status))))
		ft_put_errno(PROGRAM_NAME);
	check_argument(status, argv[1]);
	reset_status(status);
	return (status);
}

t_mlx		*init_mlx(void)
{
	t_mlx *mlx;

	if (!(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx))))
		ft_put_errno(PROGRAM_NAME);
	if (!(mlx->mlx = mlx_init()))
		put_error_pn("mlx_init error");
	if (!(mlx->win = (void *)mlx_new_window(mlx->mlx, WIN_SIZE_X, WIN_SIZE_Y,
	PROGRAM_NAME)))
		put_error_pn("mlx_new_window error");
	if (!(mlx->img = (void *)mlx_new_image(mlx->mlx, IMG_SIZE_X, IMG_SIZE_Y)))
		put_error_pn("mlx_new_image error");
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel),
	&(mlx->size_line), &(mlx->endian));
	return (mlx);
}

void		draw(t_global *global)
{
	mlx_clear_window(global->mlx->mlx, global->mlx->win);
	run_open_cl(global);
	mlx_put_image_to_window(global->mlx->mlx, global->mlx->win,
	global->mlx->img, 0, 0);
	if (!(global->status->hide_info))
		put_info_to_window(global);
}

void		mlx_hooks(t_global *global)
{
	mlx_hook(global->mlx->win, 2, 0, keyboard_key_press, global);
	mlx_hook(global->mlx->win, 4, 0, mouse_key_press, global);
	mlx_hook(global->mlx->win, 5, 0, mouse_key_release, global);
	mlx_hook(global->mlx->win, 6, 0, mouse_move, global);
	mlx_hook(global->mlx->win, 17, 0, close_window, global->open_cl);
	mlx_loop(global->mlx->mlx);
}

void		sdl_events(t_global *global)
{
	SDL_Event	event;
	int			quit;
	t_sdl		*sdl;

	sdl = global->sdl;
	quit = 0;
	while (!quit)
	{
		run_open_cl(global);
		SDL_UpdateTexture(sdl->tex, NULL, global->mlx->data,
		sizeof(int) * IMG_SIZE_X);
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
			quit = 1;
			break ;
			case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				global->status->zoom *= 1.1;
				draw(global);
			}
		}
		SDL_RenderClear(sdl->ren);
		SDL_RenderCopy(sdl->ren, sdl->tex, NULL, NULL);
		SDL_RenderPresent(sdl->ren);
	}
	SDL_DestroyTexture(sdl->tex);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

int			main(int argc, char **argv)
{
	t_global	global;

	global.status = init_status(argc, argv);
	global.mlx = init_mlx();
	global.open_cl = init_open_cl(global.status->device);
	global.sdl = init_sdl();
	// draw(&global);
	// mlx_hooks(&global);
	sdl_events(&global);
	exit(0);
}
