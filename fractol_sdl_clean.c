/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:59:54 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/10 01:20:51 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_sdl(t_sdl *sdl)
{
	(void)sdl;
	if (sdl->fractal_texture)
		SDL_DestroyTexture(sdl->fractal_texture);
	if ((sdl->text_texture))
		SDL_DestroyTexture(sdl->text_texture);
	if ((sdl->text_surface))
		SDL_FreeSurface(sdl->text_surface);
	if (sdl->ren)
		SDL_DestroyRenderer(sdl->ren);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	TTF_CloseFont(sdl->text_font);
	TTF_Quit();
	SDL_Quit();
}

void	close_window(t_global *global)
{
	clean_open_cl(global->open_cl);
	clean_sdl(global->sdl);
    exit(0);
}
