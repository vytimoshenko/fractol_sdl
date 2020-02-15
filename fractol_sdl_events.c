/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:03:15 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/16 00:48:38 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_move(int x, int y, t_global *global)
{
	get_mouse_position(global->status, x, y);
	if (global->status->fractal_type == JULIA && !global->status->pause)
		set_julia(global->status, x, y);
	control_mouse_shift(global->status, x, y);
	if (global->status->middle_mouse_button)
		draw(global);
}

void	mouse_key_press(int key, t_global *global)
{
	if (key == SDL_BUTTON_MIDDLE)
	{
		global->status->middle_mouse_button = 1;
		draw(global);
	}
}

void	mouse_key_release(int key, t_global *global)
{
	if (key == SDL_BUTTON_MIDDLE)
		global->status->middle_mouse_button = 0;
}

void	mouse_scroll(int wheel, t_global *global)
{
	control_mouse_zoom(global->status, wheel);
	draw(global);
}

int		keyboard_key_press(int key, t_global *global)
{
	if (key == SDL_SCANCODE_ESCAPE)
		close_window(global);
	else if (key == SDL_SCANCODE_SPACE)
		global->status->pause = global->status->pause ? 0 : 1;
	else if (key == SDL_SCANCODE_RETURN)
		control_type(global->status, global->sdl);
	else if (key == SDL_SCANCODE_C)
		control_colors(global->status);
	else if (key == SDL_SCANCODE_H)
		global->status->hide_info = global->status->hide_info ? 0 : 1;
	else if (key == SDL_SCANCODE_R)
	{
		reset_status(global->status);
		reset_render_status(global->sdl);
	}
	else if (key == SDL_SCANCODE_D)
		control_device(global);
	else if (key == SDL_SCANCODE_S)
		save_screenshot(global->sdl, global->status);
	else if (key == SDL_SCANCODE_COMMA || key == SDL_SCANCODE_PERIOD)
		control_iteration(global->status, key);
	else if (key == SDL_SCANCODE_MINUS || key == SDL_SCANCODE_EQUALS)
		control_zoom(global->status, key);
	else if (key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT ||
	key == SDL_SCANCODE_DOWN || key == SDL_SCANCODE_UP)
		control_shift(global->status, key);
	else
		return (0);
	draw(global);
	return (0);
}

void	resize_window(t_global *global)
{
	change_screen_mode(global->status, global->sdl);
	reset_render_status(global->sdl);
	clean_open_cl(global->open_cl);
	global->open_cl = init_open_cl(global->status);
	draw(global);
}

void	close_window(t_global *global)
{
	clean_open_cl(global->open_cl);
	clean_sdl(global->sdl);
	exit(0);
}
