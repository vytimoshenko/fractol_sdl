/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/12 01:29:13 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_sdl	*init_sdl(void)
{
	t_sdl	*sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_put_errno(PROGRAM_NAME);
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	sdl->win = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_SIZE_W, WIN_SIZE_H, 0);
	sdl->win_surface = SDL_GetWindowSurface(sdl->win);
	sdl->data = (int *)ft_memalloc(sizeof(int) * IMG_SIZE_W * IMG_SIZE_H);
	sdl->text_font = TTF_OpenFont(TEXT_FONT, 124);
	sdl->text_color.r = 255;
	sdl->text_color.g = 255;
	sdl->text_color.b = 255;
	sdl->text_color.a = 255;
	return (sdl);
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
