/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/09 04:17:59 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_sdl	*init_sdl(void)
{
	t_sdl *sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ft_put_errno(PROGRAM_NAME);
	SDL_Init(SDL_INIT_VIDEO);
	sdl->win = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_SIZE_X, WIN_SIZE_Y, 0);
	// SDL_SetWindowFullscreen(sdl->win, 0);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, 0);
	sdl->tex = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STATIC, IMG_SIZE_X, IMG_SIZE_Y);
	sdl->data = (int *)malloc(sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);
	ft_memset(sdl->data, 128, sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);
	return (sdl);
}

void	draw(t_global *global)
{
	SDL_Event	event;
	int			ret;

	ret = 0;
	while (!ret)
	{
		run_open_cl(global->status, global->open_cl, global->sdl->data);
		SDL_UpdateTexture(global->sdl->tex, NULL, global->sdl->data,
		sizeof(int) * IMG_SIZE_X);
		// if (!(global->status->hide_info))
		// 	put_info_to_window(global);
		SDL_PollEvent(&event);
		sdl_events(global, event);
		SDL_RenderClear(global->sdl->ren);
		SDL_RenderCopy(global->sdl->ren, global->sdl->tex, NULL, NULL);
		SDL_RenderPresent(global->sdl->ren);
	}
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

// TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

// SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

// SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

// SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

// SDL_Rect Message_rect; //create a rect
// Message_rect.x = 0;  //controls the rect's x coordinate 
// Message_rect.y = 0; // controls the rect's y coordinte
// Message_rect.w = 100; // controls the width of the rect
// Message_rect.h = 100; // controls the height of the rect

// //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

// //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

// SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

// //Don't forget too free your surface and texture


// std::string score_text = "score: " + std::to_string(score);        
// SDL_Color textColor = { 255, 255, 255, 0 };
// SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
// SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
// int text_width = textSurface->w;
// int text_height = textSurface->h;
// SDL_FreeSurface(textSurface);
// SDL_Rect renderQuad = { 20, win_height - 30, text_width, text_height };
// SDL_RenderCopy(renderer, text, NULL, &renderQuad);
// SDL_DestroyTexture(text);


// void	put_info_to_window(t_global *global)
// {
// 	TTF_Font *Sans = TTF_OpenFont("Sans.ttf", 24);
// 	SDL_Color White = {255, 255, 255};
// 	SDL_Surface *text = TTF_RenderText_Solid(Sans, "Hello World!", White);
// 	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
// 	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); 
// }