/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/12 19:00:32 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_sdl	*init_sdl(void)
{
	t_sdl	*sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_put_errno(PROGRAM_NAME);
	if (SDL_Init(SDL_INIT_VIDEO))
		put_sdl_error(sdl, "SDL_Init");
	if (!(sdl->win = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_SIZE_W, WIN_SIZE_H, 0)))
		put_sdl_error(sdl, "SDL_CreateWindow");
	if (!(sdl->win_surface = SDL_GetWindowSurface(sdl->win)))
		put_sdl_error(sdl, "SDL_GetWindowSurface");
	if (!(sdl->data = (int *)ft_memalloc(sizeof(int) * IMG_SIZE_W *
	IMG_SIZE_H)))
		ft_put_errno(PROGRAM_NAME);
	init_ttf(sdl);
	return (sdl);
}

void	init_ttf(t_sdl *sdl)
{
	if (TTF_Init())
		put_sdl_error(sdl, "TTF_Init");
	if (!(sdl->text_font = TTF_OpenFont(TEXT_FONT, TEXT_SIZE)))
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
		if ((sdl->win_surface))
			SDL_FreeSurface(sdl->win_surface);
		if (sdl->win)
			SDL_DestroyWindow(sdl->win);
		TTF_CloseFont(sdl->text_font);
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
	clean_sdl(sdl);
	exit(1);
}
