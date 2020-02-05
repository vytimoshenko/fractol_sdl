/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mlx_put_info_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 18:27:57 by mperseus          #+#    #+#             */
/*   Updated: 2020/01/31 23:13:11 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_info_to_window(t_global *global)
{
	put_control_keys_1(global->status, global->mlx);
	put_control_keys_2(global->mlx);
	put_open_cl_info(global->open_cl, global->mlx);
	put_status_1(global->mlx);
	put_status_2(global->status, global->mlx);
	put_status_3(global->status, global->mlx);
	put_status_4(global->status, global->mlx);
	put_status_5(global->status, global->mlx);
}

void	put_control_keys_1(t_status *status, t_mlx *mlx)
{
	int pos_x;
	int pos_y;

	pos_x = WIN_SIZE_X - 440;
	pos_y = 600;
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 130, pos_y, TEXT_COLOR,
	"CONTROL");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 30, TEXT_COLOR,
	"Type:             return");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 60, TEXT_COLOR,
	"Move:             arrows");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 80, TEXT_COLOR,
	"                  middle mouse button");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 110, TEXT_COLOR,
	"Zoom:             +/-");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 130, TEXT_COLOR,
	"                  mouse wheel scroll");
	if (status->fractal_type == JULIA)
		mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 160, TEXT_COLOR,
		"Constant:         space");
	else
		mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 160, TEXT_COLOR,
		"Constant:         not available");
}

void	put_control_keys_2(t_mlx *mlx)
{
	int pos_x;
	int pos_y;

	pos_x = WIN_SIZE_X - 440;
	pos_y = 600;
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 190, TEXT_COLOR,
	"Iterations:       </>");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 220, TEXT_COLOR,
	"Color:            C");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 250, TEXT_COLOR,
	"Hide info:        H");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 280, TEXT_COLOR,
	"Device:           D");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 310, TEXT_COLOR,
	"Reset:            R");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 340, TEXT_COLOR,
	"Exit:             ESC");
}

void	put_open_cl_info(t_open_cl *open_cl, t_mlx *mlx)
{
	int		pos_x;
	int		pos_y;
	char	*str;

	pos_x = WIN_SIZE_X - 440;
	pos_y = 400;
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 130, pos_y, TEXT_COLOR,
	"DEVICE");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 30, TEXT_COLOR,
	open_cl->device_name);
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 50, TEXT_COLOR,
	"   cores x     MHz");
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 50, TEXT_COLOR,
	str = ft_itoa((int)(open_cl->device_comp_units)));
	free(str);
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 110, pos_y + 50, TEXT_COLOR,
	str = ft_itoa((int)(open_cl->device_frequency)));
	free(str);
	mlx_string_put(mlx->mlx, mlx->win, pos_x, pos_y + 80, TEXT_COLOR,
	"OpenCL ver.:");
	mlx_string_put(mlx->mlx, mlx->win, pos_x + 130, pos_y + 80, TEXT_COLOR,
	open_cl->driver_ver);
}
