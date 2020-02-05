/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:37:34 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/06 01:50:24 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/SDL.h"
#include "fractol.h"

int main(int argc, char **argv)
{
    SDL_Window      *win;
    SDL_Renderer    *ren;
    SDL_Texture     *tex;
    SDL_Event       event;
    int             *data;
    
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, IMG_SIZE_X, IMG_SIZE_Y, 0);
    ren = SDL_CreateRenderer(win, -1, 0);
    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, IMG_SIZE_X, IMG_SIZE_Y);

    data = (int *)malloc(sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);
    memset(data, 128, sizeof(int) * IMG_SIZE_X * IMG_SIZE_Y);

    int quit = 0;
    while (!quit)
    {
        SDL_UpdateTexture(tex, NULL, data, sizeof(int) * IMG_SIZE_X);
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    exit(0);
}