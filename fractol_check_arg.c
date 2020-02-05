/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_check_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 01:34:38 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/05 18:57:16 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_status(t_status *status)
{
	status->color_theme = 0;
	status->iter = 100;
	status->zoom = 300;
	status->x_shift = 0;
	status->y_shift = 0;
	status->x_julia = -0.7018;
	status->y_julia = -0.3842;
	status->x_center = (double)IMG_SIZE_X / 2;
	status->y_center = (double)IMG_SIZE_Y / 2;
	status->pause = 1;
}

void	check_argument(t_status *status, char *argv)
{
	if (ft_atoi(argv) == MANDELBROT)
		status->fractal_type = 1;
	else if (ft_atoi(argv) == JULIA)
		status->fractal_type = 2;
	else if (ft_atoi(argv) == BURNING_SHIP)
		status->fractal_type = 3;
	else if (ft_atoi(argv) == SPIDER)
		status->fractal_type = 4;
	else if (ft_atoi(argv) == SIN)
		status->fractal_type = 5;
	else
		error_wrong_argument();
}

void	error_wrong_argument(void)
{
	ft_putendl("usage:");
	ft_putendl("\tmandelbrot\t1");
	ft_putendl("\tjulia\t\t2");
	ft_putendl("\tburning ship\t3");
	ft_putendl("\tspider\t\t4");
	ft_putendl("\tsin\t\t5");
	exit(1);
}
