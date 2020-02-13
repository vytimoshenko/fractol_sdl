/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_control_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 18:34:41 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/13 22:33:07 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	control_type(t_status *status, t_sdl *sdl)
{
	if (status->fractal_type != 5)
		status->fractal_type++;
	else
		status->fractal_type = 1;
	reset_status(status);
	reset_render_status(sdl);
}

void	control_iteration(t_status *status, int key)
{
	if (key == SDL_SCANCODE_PERIOD && status->iter)
		status->iter += 10;
	else if (key == SDL_SCANCODE_COMMA && status->iter > 10)
		status->iter -= 10;
}

void	control_colors(t_status *status)
{
	if (status->color_theme != 3)
		status->color_theme++;
	else
		status->color_theme = 0;
}

void	control_device(t_global *global)
{
	if (global->status->device == 0)
		global->status->device++;
	else
		global->status->device = 0;
	clean_open_cl(global->open_cl);
	reset_render_status(global->sdl);
	global->open_cl = init_open_cl(global->status);
}

void	control_fullscreen(t_global *global)
{
	if (global->status->fullscreen == 0)
		global->status->fullscreen++;
	else
		global->status->fullscreen = 0;
	clean_sdl(global->sdl);
	global->sdl = init_sdl(global->status);
	reset_render_status(global->sdl);
	clean_open_cl(global->open_cl);
	global->open_cl = init_open_cl(global->status);
}

void	set_julia(t_status *status, int x, int y)
{
	status->x_julia = ((double)x - (double)status->img_size_w / 2) * 0.002;
	status->y_julia = ((double)y - (double)status->img_size_h / 2) * 0.002;
}
