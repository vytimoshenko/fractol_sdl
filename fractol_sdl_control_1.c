/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_control_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 18:34:41 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/14 21:56:16 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	get_mouse_position(t_status *status, int x, int y)
{
	status->x_mouse_position = x;
	status->y_mouse_position = y;
	if (x < 0 || y < 0 || x > status->img_size_w || y > status->img_size_h)
	{
		status->x_mouse_position = 0;
		status->y_mouse_position = 0;
	}
}

void	control_zoom(t_status *status, int key)
{
	if (key == SDL_SCANCODE_EQUALS)
		status->zoom *= 1.1;
	else if (key == SDL_SCANCODE_MINUS)
		status->zoom /= 1.1;
}

void	control_mouse_zoom(t_status *status, int wheel)
{
	int		x;
	int		y;
	double	tmp;

	x = status->x_mouse_position;
	y = status->y_mouse_position;
	tmp = status->zoom;
	if (wheel > 0)
		status->zoom *= 1.1;
	if (wheel < 0)
		status->zoom /= 1.1;
	if (tmp < status->zoom)
	{
		status->x_shift -= (status->x_center - x) * 1.1 / status->zoom;
		status->y_shift -= (status->y_center - y) * 1.1 / status->zoom;
	}
	else
	{
		status->x_shift -= (status->x_center - x) / 1.1 / status->zoom;
		status->y_shift -= (status->y_center - y) / 1.1 / status->zoom;
	}
	status->x_center = x;
	status->y_center = y;
}

void	control_shift(t_status *status, int key)
{
	if (key == SDL_SCANCODE_DOWN)
		status->y_shift -= 10 / status->zoom;
	else if (key == SDL_SCANCODE_UP)
		status->y_shift += 10 / status->zoom;
	else if (key == SDL_SCANCODE_RIGHT)
		status->x_shift -= 10 / status->zoom;
	else if (key == SDL_SCANCODE_LEFT)
		status->x_shift += 10 / status->zoom;
}

void	control_mouse_shift(t_status *status, int x, int y)
{
	if (status->middle_mouse_button == 1)
	{
		status->x_move = x;
		status->y_move = y;
		status->middle_mouse_button = 2;
	}
	if (status->middle_mouse_button == 2)
	{
		status->x_shift -= (x - status->x_move) / status->zoom;
		status->y_shift += (status->y_move - y) / status->zoom;
		status->x_move = x;
		status->y_move = y;
	}
}

void	set_julia(t_status *status, int x, int y)
{
	status->x_julia = ((double)x - (double)status->img_size_w / 2) * 0.002;
	status->y_julia = ((double)y - (double)status->img_size_h / 2) * 0.002;
}
