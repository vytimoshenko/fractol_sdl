/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:55:53 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/14 22:15:43 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	loop(t_global *global)
{
	SDL_Event	event;
	int			quit;

	quit = 0;
	draw_welcome(global->sdl);
	draw(global);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				close_window(global);
			else if (event.type == SDL_MOUSEMOTION)
				mouse_move(event.motion.x, event.motion.y, global);
			else if (event.type == SDL_MOUSEBUTTONDOWN)
				mouse_key_press(event.button.button, global);
			else if (event.type == SDL_MOUSEBUTTONUP)
				mouse_key_release(event.button.button, global);
			else if (event.type == SDL_MOUSEWHEEL)
				mouse_scroll(event.wheel.y, global);
			else if (event.type == SDL_KEYDOWN)
				keyboard_key_press(event.button.button, global);
			else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
			event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
			event.window.event ==  SDL_WINDOWEVENT_RESTORED)
				resize_window(global);
		}
	}
}

void	draw(t_global *global)
{
	Uint64	start;
	Uint64	end;

	start = SDL_GetPerformanceCounter();
	run_open_cl(global->status, global->open_cl, global->sdl->data);
	if (!(global->status->hide_info))
		draw_info(global->sdl, global->status);
	draw_image(global->sdl, global->status->hide_info);
	end = SDL_GetPerformanceCounter();
	count_frames(global->sdl, start, end);
}

void	draw_image(t_sdl *sdl, int hide_info)
{
	SDL_FreeSurface(sdl->main_surface);
	sdl->main_surface = NULL;
	if (sdl->win_surface)
		SDL_FreeSurface(sdl->win_surface);
	sdl->win_surface = NULL;
	if (!(sdl->win_surface = SDL_GetWindowSurface(sdl->win)))
		put_sdl_error(sdl, "SDL_GetWindowSurface");
	if (!(sdl->main_surface = SDL_CreateRGBSurfaceFrom(sdl->data,
	sdl->win_size_w, sdl->win_size_h, 32, sizeof(int) * sdl->win_size_w,
	0, 0, 0, 0)))
		put_sdl_error(sdl, "SDL_CreateRGBSurfaceFrom");
	if (!(hide_info))
	{
		if (SDL_BlitSurface(sdl->text_surface, NULL, sdl->main_surface, NULL))
			put_sdl_error(sdl, "SDL_BlitSurface");
		SDL_FreeSurface(sdl->text_surface);
		sdl->text_surface = NULL;
	}
	if (SDL_BlitSurface(sdl->main_surface, NULL, sdl->win_surface, NULL))
		put_sdl_error(sdl, "SDL_BlitSurface");
	if (SDL_UpdateWindowSurface(sdl->win))
		put_sdl_error(sdl, "SDL_UpdateWindowSurface");
}

void	count_frames(t_sdl *sdl, Uint64 start, Uint64 end)
{
	++sdl->frames;
	sdl->frame_time = (end - start) / (float)SDL_GetPerformanceFrequency();
	sdl->fps = 1.0f / sdl->frame_time;
}
