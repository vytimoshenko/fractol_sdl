/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:59:54 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/10 19:36:17 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_sdl(t_sdl *sdl)
{
	(void)sdl;
	if ((sdl->main_surface))
		SDL_FreeSurface(sdl->main_surface);
	if ((sdl->text_surface))
		SDL_FreeSurface(sdl->text_surface);
	if (sdl->main_texture)
		SDL_DestroyTexture(sdl->main_texture);
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
