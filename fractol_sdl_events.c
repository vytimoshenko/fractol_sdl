/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:03:15 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/08 21:15:15 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_move(int x, int y, t_global *global)
{
	get_mouse_position(global->status, x, y);
	if (global->status->fractal_type == JULIA && !global->status->pause)
		set_julia(global->status, x, y);
	control_mouse_shift(global->status, x, y);
	draw(global);
}

void	mouse_key_press(int key, t_global *global)
{
	if (key == SDL_BUTTON_MIDDLE)
		global->status->middle_mouse_button = 1;
	draw(global);
}

void	mouse_key_release(int key, t_global *global)
{
	if (key == SDL_BUTTON_MIDDLE)
		global->status->middle_mouse_button = 0;
	draw(global);
}

void	mouse_scroll(int wheel, t_global *global)
{
	control_mouse_zoom(global->status, wheel);
	draw(global);
}

void	keyboard_key_press(int key, t_global *global)
{
	if (key == SDL_SCANCODE_ESCAPE)
		close_window(global);
	control_iteration(global->status, key);
	control_zoom(global->status, key);
	control_shift(global->status, key);
	if (key == SDL_SCANCODE_SPACE)
		global->status->pause = global->status->pause ? 0 : 1;
	if (key == SDL_SCANCODE_RETURN)
		control_type(global->status);
	if (key == SDL_SCANCODE_C)
		control_colors(global->status);
	if (key == SDL_SCANCODE_H)
		global->status->hide_info = global->status->hide_info ? 0 : 1;
	if (key == SDL_SCANCODE_R)
		reset_status(global->status);
	if (key == SDL_SCANCODE_D)
		control_device(global);
	draw(global);
}
