/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mlx_control_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 18:34:41 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/05 16:46:17 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	control_type(t_status *status)
{
	if (status->fractal_type != 5)
		status->fractal_type++;
	else
		status->fractal_type = 1;
	reset_status(status);
}

void	control_iteration(t_status *status, int key)
{
	if (key == CHEVRON_RIGHT && status->iter)
		status->iter += 10;
	else if (key == CHEVRON_LEFT && status->iter > 10)
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
	global->open_cl = init_open_cl(global->status->device);
}

void	set_julia(t_status *status, int x, int y)
{
	status->x_julia = ((double)x - (double)IMG_SIZE_X / 2) * 0.002;
	status->y_julia = ((double)y - (double)IMG_SIZE_Y / 2) * 0.002;
}
