/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/13 04:23:40 by mperseus         ###   ########.fr       */
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
	if (!(sdl->win = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_SIZE_W, WIN_SIZE_H, SDL_WINDOW_FULLSCREEN)))
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

void	init_ttf(t_sdl *sdl)
{
	if (TTF_Init())
		put_sdl_error(sdl, "TTF_Init");
	if (!(sdl->text_font_main = TTF_OpenFont(TEXT_FONT, TEXT_SIZE_MAIN)))
		put_sdl_error(sdl, "TTF_OpenFont");
	if (!(sdl->text_font_welcome = TTF_OpenFont(TEXT_FONT, TEXT_SIZE_WELCOME)))
		put_sdl_error(sdl, "TTF_OpenFont");
	sdl->text_color.r = TEXT_COLOR_R;
	sdl->text_color.g = TEXT_COLOR_G;
	sdl->text_color.b = TEXT_COLOR_B;
	sdl->text_color.a = TEXT_COLOR_A;
}

void	reset_render_status(t_sdl *sdl)
{
	sdl->frames = 0;
	sdl->fps = 0;
	sdl->frame_time = 0;
}

void	clean_sdl(t_sdl *sdl)
{
	if (sdl)
	{
		if ((sdl->main_surface))
			SDL_FreeSurface(sdl->main_surface);
		if ((sdl->text_surface))
			SDL_FreeSurface(sdl->text_surface);
		if (sdl->win)
			SDL_DestroyWindow(sdl->win);
		TTF_CloseFont(sdl->text_font_main);
		TTF_CloseFont(sdl->text_font_welcome);
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
