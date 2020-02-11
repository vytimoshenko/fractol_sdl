/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:55:53 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/12 01:28:35 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	sdl_events(t_global *global)
{
	SDL_Event		event;
	int				quit;

	quit = 0;
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
		}
	}
}

void	draw(t_global *global)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	run_open_cl(global->status, global->open_cl, global->sdl->data);
	if (!(global->status->hide_info))
		draw_text(global);
	draw_image(global->sdl);
	gettimeofday(&end, NULL);
	count_frames(global->sdl, start, end);
	printf("frame#%d - ", global->sdl->frames);
	printf("%dfps\n", global->sdl->fps);
}

void	draw_image(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->main_surface);
	sdl->main_surface = NULL;
	sdl->main_surface = SDL_CreateRGBSurfaceFrom(sdl->data, IMG_SIZE_W,
	IMG_SIZE_H, 32, sizeof(int) * IMG_SIZE_W, 0, 0, 0, 0);
	SDL_BlitSurface(sdl->text_surface, NULL, sdl->main_surface, NULL);
	SDL_BlitSurface(sdl->main_surface, NULL, sdl->win_surface, NULL);
	SDL_UpdateWindowSurface(sdl->win);
	SDL_FreeSurface(sdl->text_surface);
	sdl->text_surface = NULL;
}

void	draw_text(t_global *global)
{
	t_sdl	*sdl;

	sdl = global->sdl;
	// SDL_Rect text_rect;
	// text_rect.x = text_rect.y = 0;
	// text_rect.w = IMG_SIZE_W;
	// text_rect.h = IMG_SIZE_H;
	// SDL_Rect dst_rect = {0, 0, text_rect.w, text_rect.h};
	sdl->text_surface = TTF_RenderText_Blended(sdl->text_font,
	"Funny Fractol project", sdl->text_color);
}

void	count_frames(t_sdl *sdl, struct timeval start, struct timeval end)
{
	++sdl->frames;
	sdl->frame_time = (double)(end.tv_usec - start.tv_usec) / 1000 +
	(double)(end.tv_sec - start.tv_sec) * 1000;
	sdl->fps = 1000 / sdl->frame_time;
}
