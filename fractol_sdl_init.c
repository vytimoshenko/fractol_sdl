/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/10 19:58:48 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_sdl	*init_sdl(void)
{
	t_sdl		*sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_put_errno(PROGRAM_NAME);
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	// IMG_Init();
	sdl->win = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_SIZE_W, WIN_SIZE_H, 0);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, 0);
	sdl->data = (int *)ft_memalloc(sizeof(int) * IMG_SIZE_W * IMG_SIZE_H);
	sdl->text_font = TTF_OpenFont(TEXT_FONT, 124);
	sdl->text_color.r = 255;
	sdl->text_color.g = 255;
	sdl->text_color.b = 255;
	sdl->text_color.a = 255;
	return (sdl);
}

void	sdl_events(t_global *global, SDL_Event event)
{
	if (event.type == SDL_QUIT)
		close_window(global);
	if (event.type == SDL_MOUSEMOTION)
		mouse_move(event.motion.x, event.motion.y, global);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		mouse_key_press(event.button.button, global);
	if (event.type == SDL_MOUSEBUTTONUP)
		mouse_key_release(event.button.button, global);
	if (event.type == SDL_MOUSEWHEEL)
		mouse_scroll(event.wheel.y, global);
	if (event.type == SDL_KEYDOWN)
		keyboard_key_press(event.button.button, global);
}

void	draw_text(t_global *global)
{
	t_sdl	*sdl;
	char	*str;
	
	sdl = global->sdl;
	SDL_Rect text_rect;
	text_rect.x = text_rect.y = 0;
	text_rect.w = IMG_SIZE_W;
	text_rect.h = IMG_SIZE_H;
	// SDL_Rect dst_rect = {0, 0, text_rect.w, text_rect.h};
	sdl->text_surface = TTF_RenderText_Solid(sdl->text_font, str = ft_itoa(global->status->fractal_type), sdl->text_color);
	free(str);
}

void	draw_fractal(t_sdl *sdl)
{
	sdl->main_surface = SDL_CreateRGBSurfaceFrom(sdl->data, IMG_SIZE_W, IMG_SIZE_H, 32, sizeof(int) * IMG_SIZE_W, 0, 0, 0, 0);
	SDL_BlitSurface(sdl->text_surface, NULL, sdl->main_surface, NULL);
	sdl->main_texture = SDL_CreateTextureFromSurface(sdl->ren, sdl->main_surface);
	SDL_QueryTexture(sdl->main_texture, NULL, NULL, NULL, NULL);
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->main_texture, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
	SDL_FreeSurface(sdl->main_surface);
	SDL_FreeSurface(sdl->text_surface);
	SDL_DestroyTexture(sdl->main_texture);
	sdl->main_surface = NULL;
	sdl->text_surface = NULL;
	sdl->main_texture = NULL;
}

void	draw(t_global *global)
{
	SDL_Event	event;
	int			ret;

	ret = 0;
	while (!ret)
	{
		SDL_PollEvent(&event);
		sdl_events(global, event);
		run_open_cl(global->status, global->open_cl, global->sdl->data);
		if (!(global->status->hide_info))
			draw_text(global);	
		draw_fractal(global->sdl);
	}
}
