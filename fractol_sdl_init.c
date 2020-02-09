/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/10 02:08:03 by mperseus         ###   ########.fr       */
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
	SDL_WINDOWPOS_UNDEFINED, WIN_SIZE_X, WIN_SIZE_Y, 0);
	// SDL_SetWindowFullscreen(sdl->win, 0);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, 0);
	sdl->fractal_texture = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, IMG_SIZE_X, IMG_SIZE_Y);
	sdl->data = (int *)malloc(sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);
	ft_memset(sdl->data, 128, sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);

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

	SDL_UpdateTexture(sdl->fractal_texture, NULL, sdl->data, sizeof(int) * IMG_SIZE_X);
	SDL_QueryTexture(sdl->fractal_texture, NULL, NULL, NULL, NULL);
	// SDL_BlitSurface(sdl->surface, &source_rect, temp_surface, NULL);
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->fractal_texture, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
	SDL_Delay(20);

	SDL_Rect text_rect;
		text_rect.x = text_rect.y = 0;
		text_rect.w = text_rect.h = 500;
		SDL_Rect dst_rect = {0, 0, text_rect.w, text_rect.h};
	sdl->text_surface = TTF_RenderText_Solid(sdl->text_font, str = ft_itoa(global->status->fractal_type), sdl->text_color);
	sdl->text_texture = SDL_CreateTextureFromSurface(sdl->ren, sdl->text_surface);

	// SDL_SetTextureBlendMode(sdl->fractal_texture, SDL_BLENDMODE_BLEND);
	// SDL_SetRenderTarget(sdl->ren, sdl->fractal_texture);

	SDL_FreeSurface(sdl->text_surface);
	SDL_QueryTexture(sdl->text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->text_texture, NULL,  &dst_rect);
	SDL_DestroyTexture(sdl->text_texture);
	SDL_RenderPresent(sdl->ren);
	sdl->text_surface = NULL;
	sdl->text_texture = NULL;
	free(str);
	SDL_Delay(10);
}

void	draw_fractal(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->fractal_texture, NULL, sdl->data, sizeof(int) * IMG_SIZE_X);
	SDL_QueryTexture(sdl->fractal_texture, NULL, NULL, NULL, NULL);
	// SDL_BlitSurface(sdl->surface, &source_rect, temp_surface, NULL);
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->fractal_texture, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
	SDL_Delay(20);
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
		// if (!(global->status->hide_info))
		run_open_cl(global->status, global->open_cl, global->sdl->data);
			draw_text(global);	
		// draw_fractal(global->sdl);
	}
}
