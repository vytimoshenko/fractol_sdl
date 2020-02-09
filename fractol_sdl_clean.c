/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:59:54 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/09 03:52:41 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_sdl(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->tex);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

void	close_window(t_global *global)
{
	clean_open_cl(global->open_cl);
	clean_sdl(global->sdl);
    exit(0);
}
