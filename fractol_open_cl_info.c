/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_open_cl_info.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:08:54 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/09 03:52:21 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	get_open_cl_info(t_open_cl *open_cl)
{
	get_device_info(open_cl);
	get_platform_info(open_cl);
}

void	get_platform_info(t_open_cl *open_cl)
{
	size_t	info_size;

	if (clGetPlatformInfo(open_cl->platform_id, CL_PLATFORM_NAME, 0, NULL,
	&info_size))
		put_open_cl_error(open_cl, "clGetPlatformInfo");
	if (!(open_cl->platform_name = (char *)ft_memalloc(info_size)))
		ft_put_errno(PROGRAM_NAME);
	if (clGetPlatformInfo(open_cl->platform_id, CL_PLATFORM_NAME, info_size,
	open_cl->platform_name, NULL))
		put_open_cl_error(open_cl, "clGetPlatformInfo");
}

void	get_device_info(t_open_cl *open_cl)
{
	size_t	info_size;

	if (clGetDeviceInfo(open_cl->device_id, CL_DEVICE_NAME, 0, NULL,
	&info_size))
		put_open_cl_error(open_cl, "clGetDeviceInfo");
	if (!(open_cl->device_name = (char *)ft_memalloc(info_size)))
		ft_put_errno(PROGRAM_NAME);
	if ((clGetDeviceInfo(open_cl->device_id, CL_DEVICE_NAME, info_size,
	open_cl->device_name, NULL)))
		put_open_cl_error(open_cl, "clGetDeviceInfo");
	if ((clGetDeviceInfo(open_cl->device_id, CL_DRIVER_VERSION, 0, NULL,
	&info_size)))
		put_open_cl_error(open_cl, "clGetDeviceInfo");
	if (!(open_cl->driver_ver = (char *)ft_memalloc(info_size)))
		ft_put_errno(PROGRAM_NAME);
	if ((clGetDeviceInfo(open_cl->device_id, CL_DRIVER_VERSION, info_size,
	open_cl->driver_ver, NULL)))
		put_open_cl_error(open_cl, "clGetDeviceInfo");
	if ((clGetDeviceInfo(open_cl->device_id, CL_DEVICE_MAX_COMPUTE_UNITS,
	sizeof(open_cl->device_comp_units), &(open_cl->device_comp_units), NULL)))
		put_open_cl_error(open_cl, "clGetDeviceInfo");
	if (clGetDeviceInfo(open_cl->device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY,
	sizeof(open_cl->device_frequency), &(open_cl->device_frequency), NULL))
		put_open_cl_error(open_cl, "clGetDeviceInfo");
}
