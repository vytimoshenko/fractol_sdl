/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_draw_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 01:03:59 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/14 22:03:03 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_ttf(t_sdl *sdl)
{
	if (TTF_Init())
		put_sdl_error(sdl, "TTF_Init");
	if (!(sdl->text_font_main = TTF_OpenFont(TEXT_FONT, TEXT_SIZE_MAIN)))
		put_sdl_error(sdl, "TTF_OpenFont");
	if (!(sdl->text_font_welcome = TTF_OpenFont(TEXT_FONT, TEXT_SIZE_WELCOME)))
		put_sdl_error(sdl, "TTF_OpenFont");
	sdl->text_color.r = TEXT_COLOR_R;
	sdl->text_color.g = TEXT_COLOR_G;
	sdl->text_color.b = TEXT_COLOR_B;
	sdl->text_color.a = TEXT_COLOR_A;
}

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
	SDL_FreeSurface(tmp_text_surface);
	tmp_text_surface = NULL;
	if (SDL_BlitSurface(sdl->main_surface, NULL, sdl->win_surface, NULL))
		put_sdl_error(sdl, "SDL_BlitSurface");
	SDL_FreeSurface(sdl->main_surface);
	sdl->main_surface = NULL;
	if (SDL_UpdateWindowSurface(sdl->win))
		put_sdl_error(sdl, "SDL_UpdateWindowSurface");
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
	"      FPS", sdl->text_color)))
		put_sdl_error(sdl, "STTF_RenderText_Blended");
	if (SDL_BlitSurface(tmp_text_surface1, NULL, tmp_text_surface2, NULL))
		put_sdl_error(sdl, "SDL_BlitSurface");
	SDL_FreeSurface(tmp_text_surface1);
	tmp_text_surface1 = NULL;
	if (status->device == 0)
	{
		if (!(sdl->text_surface = TTF_RenderText_Blended(sdl->text_font_main,
		"              CPU", sdl->text_color)))
			put_sdl_error(sdl, "STTF_RenderText_Blended");
	}
	else
	{
		if (!(sdl->text_surface = TTF_RenderText_Blended(sdl->text_font_main,
		"              GPU", sdl->text_color)))
			put_sdl_error(sdl, "STTF_RenderText_Blended");
	}
	if (SDL_BlitSurface(tmp_text_surface2, NULL, sdl->text_surface, NULL))
		put_sdl_error(sdl, "SDL_BlitSurface");
	SDL_FreeSurface(tmp_text_surface2);
	tmp_text_surface2 = NULL;
}

void	save_screenshot(t_sdl *sdl)
{
	char	*file_name;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(sdl->screenshot_num);
	tmp2 = ft_strjoin("_", tmp1);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, ".jpg");
	free(tmp2);
	tmp2 = ft_strjoin(PROGRAM_NAME, tmp1);
	free(tmp1);
	file_name = ft_strjoin(SCREENSHOT_PATH, tmp2);
	free(tmp2);
	if (IMG_SaveJPG(sdl->main_surface, file_name, 100))
		put_sdl_error(sdl, "IMG_SaveJPG");
	free(file_name);
	++sdl->screenshot_num;
}
