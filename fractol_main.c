/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:09:39 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/08 03:41:51 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_sdl		*init_sdl(void)
{
	t_sdl *sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_put_errno(PROGRAM_NAME);
	SDL_Init(SDL_INIT_VIDEO);
	sdl->win = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
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

int		sdl_events(t_global *global, SDL_Event event)
{
	if (event.type == SDL_QUIT)
	{
		close_window(global);
		return (1);
	}
	if (event.type == SDL_MOUSEMOTION)
		mouse_move(event.motion.x, event.motion.y, global);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		mouse_key_press(event.button.button, event.motion.x, event.motion.y, global);
	if (event.type == SDL_MOUSEBUTTONUP)
		mouse_key_release(event.button.button, event.motion.x, event.motion.y, global);
	if (event.type == SDL_MOUSEWHEEL)
		mouse_scroll(event.wheel.y, global);
	if (event.type == SDL_KEYDOWN)
		keyboard_key_press(event.button.button, global);
	return (0);
}

void		draw(t_global *global)
{
	SDL_Event	event;
	int			ret;

	ret = 0;
	while (!ret)
	{
		run_open_cl(global);
		SDL_UpdateTexture(global->sdl->tex, NULL, global->sdl->data,
		sizeof(int) * IMG_SIZE_X);
		// if (!(global->status->hide_info))
		// 	put_info_to_window(global);
		SDL_PollEvent(&event);
		if ((ret = sdl_events(global, event)))
			break ;
		SDL_RenderClear(global->sdl->ren);
		SDL_RenderCopy(global->sdl->ren, global->sdl->tex, NULL, NULL);
		SDL_RenderPresent(global->sdl->ren);
	}
}

int			main(int argc, char **argv)
{
	t_global	global;

	global.status = init_status(argc, argv);
	global.sdl = init_sdl();
	global.open_cl = init_open_cl(global.status->device);
	draw(&global);
	exit(0);
}
