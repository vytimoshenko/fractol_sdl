/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_draw_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 01:03:59 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/13 19:42:23 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_welcome(t_sdl *sdl)
{
	SDL_Surface *tmp_text_surface;
	SDL_Event	event;
	SDL_Rect 	text_rect;

	text_rect.w = 1800;
	text_rect.h = TEXT_SIZE_WELCOME;
	text_rect.x = sdl->win_size_w / 2 - text_rect.w / 2;
	text_rect.y = sdl->win_size_h / 2 - text_rect.h / 2 - 100;
	if (!(sdl->main_surface = SDL_CreateRGBSurfaceFrom(sdl->data,
	sdl->win_size_w, sdl->win_size_h, 32, sizeof(int) * sdl->win_size_w,
	0, 0, 0, 0)))
		put_sdl_error(sdl, "SDL_CreateRGBSurfaceFrom");
	if (!(tmp_text_surface = TTF_RenderText_Blended(sdl->text_font_welcome,
	PROGRAM_NAME, sdl->text_color)))
		put_sdl_error(sdl, "STTF_RenderText_Blended");
	if (SDL_BlitSurface(tmp_text_surface, NULL, sdl->main_surface, &text_rect))
		put_sdl_error(sdl, "SDL_BlitSurface");
	if (SDL_BlitSurface(sdl->main_surface, NULL, sdl->win_surface, NULL))
		put_sdl_error(sdl, "SDL_BlitSurface");
	if (SDL_UpdateWindowSurface(sdl->win))
		put_sdl_error(sdl, "SDL_UpdateWindowSurface");
	SDL_FreeSurface(tmp_text_surface);
	while (event.type != SDL_KEYDOWN && event.type != SDL_MOUSEBUTTONDOWN)
		SDL_WaitEvent(&event);
}

void	draw_info(t_sdl *sdl, t_status *status)
{
	char		*str;
	SDL_Surface *tmp_text_surface1;
	SDL_Surface *tmp_text_surface2;

	if (!(tmp_text_surface1 = TTF_RenderText_Blended(sdl->text_font_main,
	str = ft_itoa(sdl->fps), sdl->text_color)))
		put_sdl_error(sdl, "STTF_RenderText_Blended");
	free(str);
	if (!(tmp_text_surface2 = TTF_RenderText_Blended(sdl->text_font_main,
	"     FPS", sdl->text_color)))
		put_sdl_error(sdl, "STTF_RenderText_Blended");
	if (SDL_BlitSurface(tmp_text_surface1, NULL, tmp_text_surface2, NULL))
		put_sdl_error(sdl, "SDL_BlitSurface");
	SDL_FreeSurface(tmp_text_surface1);
	tmp_text_surface1 = NULL;
	if (status->device == 0)
	{
		if (!(sdl->text_surface = TTF_RenderText_Blended(sdl->text_font_main,
		"            CPU", sdl->text_color)))
			put_sdl_error(sdl, "STTF_RenderText_Blended");
	}
	else
	{
		if (!(sdl->text_surface = TTF_RenderText_Blended(sdl->text_font_main,
		"            GPU", sdl->text_color)))
			put_sdl_error(sdl, "STTF_RenderText_Blended");
	}
	if (SDL_BlitSurface(tmp_text_surface2, NULL, sdl->text_surface, NULL))
		put_sdl_error(sdl, "SDL_BlitSurface");
	SDL_FreeSurface(tmp_text_surface2);
	tmp_text_surface2 = NULL;
}
