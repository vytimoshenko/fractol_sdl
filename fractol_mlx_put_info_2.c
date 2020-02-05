/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mlx_put_info_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 03:05:11 by mperseus          #+#    #+#             */
/*   Updated: 2020/01/31 23:15:24 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_status_1(t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;

	pos_x = WIN_SIZE_X - 440;
	pos_y = 70;
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 130, pos_y, TEXT_COLOR,
	"STATUS");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 30, TEXT_COLOR,
	"Type:");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 30, TEXT_COLOR,
	"Mandelbrot");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 50, TEXT_COLOR,
	"Julia");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 70, TEXT_COLOR,
	"Burning ship");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 90, TEXT_COLOR,
	"Spider");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 110, TEXT_COLOR,
	"Sin");
}

void	put_status_2(t_status *status, t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;

	pos_x = WIN_SIZE_X - 440;
	pos_y = 70;
	if (status->fractal_type == MANDELBROT)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 150, pos_y + 30, TEXT_COLOR,
		">");
	else if (status->fractal_type == JULIA)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 150, pos_y + 50, TEXT_COLOR,
		">");
	else if (status->fractal_type == BURNING_SHIP)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 150, pos_y + 70, TEXT_COLOR,
		">");
	else if (status->fractal_type == SPIDER)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 150, pos_y + 90, TEXT_COLOR,
		">");
	else if (status->fractal_type == SIN)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 150, pos_y + 110, TEXT_COLOR,
		">");
}

void	put_status_3(t_status *status, t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;
	char	*str;

	pos_x = WIN_SIZE_X - 440;
	pos_y = 70;
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 140, TEXT_COLOR,
	"Iterations:");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 140, TEXT_COLOR,
	str = ft_itoa(status->iter));
	free(str);
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 170, TEXT_COLOR,
	"Color:");
	if (status->color_theme == 0)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 170, TEXT_COLOR,
		"Theme #1");
	else if (status->color_theme == 1)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 170, TEXT_COLOR,
		"Theme #2");
	else if (status->color_theme == 2)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 170, TEXT_COLOR,
		"Theme #3");
	else if (status->color_theme == 3)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 170, TEXT_COLOR,
		"Theme #4");
}

void	put_status_4(t_status *status, t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;

	pos_x = WIN_SIZE_X - 440;
	pos_y = 70;
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 200, TEXT_COLOR,
	"Device:");
	if (status->device == 0)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 200, TEXT_COLOR,
		"CPU");
	if (status->device == 1)
		mlx_string_put(mlx->mlx, mlx->win, pos_x + 170, pos_y + 200, TEXT_COLOR,
		"GPU");
}

void	put_status_5(t_status *status, t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;
	char	*str;

	pos_x = 20;
	pos_y = WIN_SIZE_Y - 40;
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y, TEXT_COLOR, "X:");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 20, pos_y, TEXT_COLOR,
	str = ft_itoa(status->x_mouse_position));
	free(str);
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 80, pos_y, TEXT_COLOR, "Y:");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 100, pos_y, TEXT_COLOR,
	str = ft_itoa(status->y_mouse_position));
	free(str);
}
