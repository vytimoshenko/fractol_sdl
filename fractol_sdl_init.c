/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/14 23:28:59 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_sdl	*init_sdl(t_status *status)
{
	t_sdl	*sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_put_errno(PROGRAM_NAME);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		put_sdl_error(sdl, "SDL_Init");
	get_display_mode(sdl);
	if (!(sdl->win = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, sdl->win_size_w, sdl->win_size_h,
	SDL_WINDOW_RESIZABLE)))
		put_sdl_error(sdl, "SDL_CreateWindow");
	SDL_GetWindowSize(sdl->win, &sdl->win_size_w, &sdl->win_size_h);
	status->img_size_w = sdl->win_size_w;
	status->img_size_h = sdl->win_size_h;
	status->x_center = (double)status->img_size_w / 2;
	status->y_center = (double)status->img_size_h / 2;
	if (!(sdl->win_surface = SDL_GetWindowSurface(sdl->win)))
		put_sdl_error(sdl, "SDL_GetWindowSurface");
	if (!(sdl->data = (int *)ft_memalloc(sizeof(int) * sdl->win_size_w *
	sdl->win_size_h)))
		ft_put_errno(PROGRAM_NAME);
	init_ttf(sdl);
	return (sdl);
}

void	get_display_mode(t_sdl *sdl)
{
	SDL_DisplayMode current;

	SDL_GetCurrentDisplayMode(0, &current);
	sdl->display_w = current.w;
	sdl->display_h = current.h;
	sdl->dispaly_refresh_rate = current.refresh_rate;
	sdl->win_size_w = sdl->display_w * 4 / 5;
	sdl->win_size_h = sdl->display_h * 4 / 5;
}

void	change_screen_mode(t_status *status, t_sdl *sdl)
{
	ft_memdel((void **)&sdl->data);
	SDL_GetWindowSize(sdl->win, &sdl->win_size_w, &sdl->win_size_h);
	if (sdl->win_size_w < WIN_SIZE_MIN_W)
		SDL_SetWindowSize(sdl->win, WIN_SIZE_MIN_W, sdl->win_size_h);
	if (sdl->win_size_h < WIN_SIZE_MIN_H)
		SDL_SetWindowSize(sdl->win, sdl->win_size_w, WIN_SIZE_MIN_H);
	SDL_GetWindowSize(sdl->win, &sdl->win_size_w, &sdl->win_size_h);
	status->img_size_w = sdl->win_size_w;
	status->img_size_h = sdl->win_size_h;
	status->x_center = (double)status->img_size_w / 2;
	status->y_center = (double)status->img_size_h / 2;
	if (!(sdl->data = (int *)ft_memalloc(sizeof(int) * sdl->win_size_w *
	sdl->win_size_h)))
		ft_put_errno(PROGRAM_NAME);
}

void	clean_sdl(t_sdl *sdl)
{
	if (sdl)
	{
		if ((sdl->main_surface))
			SDL_FreeSurface(sdl->main_surface);
		if ((sdl->text_surface))
			SDL_FreeSurface(sdl->text_surface);
		if ((sdl->win_surface))
			SDL_FreeSurface(sdl->win_surface);
		if (sdl->win)
			SDL_DestroyWindow(sdl->win);
		ft_memdel((void **)&sdl->data);
		TTF_CloseFont(sdl->text_font_welcome);
		TTF_CloseFont(sdl->text_font_main);
		ft_memdel((void **)&sdl);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
}

void	put_sdl_error(t_sdl *sdl, char *str)
{
	ft_putstr(PROGRAM_NAME);
	ft_putstr(": error occured in SDL function ");
	ft_putendl(str);
	ft_putendl(SDL_GetError());
	clean_sdl(sdl);
	exit(1);
}
