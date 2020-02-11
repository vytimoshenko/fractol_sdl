/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_open_cl_clean.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 00:43:04 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/11 03:37:49 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_open_cl_1(t_open_cl *open_cl)
{
	if (open_cl->command_queue)
	{
		if (clFlush(open_cl->command_queue))
			put_open_cl_error(open_cl, "clFlush");
		if (clFinish(open_cl->command_queue))
			put_open_cl_error(open_cl, "clFinish");
		if (clReleaseCommandQueue(open_cl->command_queue))
			put_open_cl_error(open_cl, "clReleaseCommandQueue");
	}
	if (open_cl->context)
	{
		if (clReleaseContext(open_cl->context))
			put_open_cl_error(open_cl, "clReleaseContext");
	}
	if (open_cl->kernel)
	{
		if (clReleaseKernel(open_cl->kernel))
			put_open_cl_error(open_cl, "clReleaseKernel");
	}
}

void	clean_open_cl_2(t_open_cl *open_cl)
{
	if (open_cl->program)
	{
		if (clReleaseProgram(open_cl->program))
			put_open_cl_error(open_cl, "clReleaseProgram");
	}
	if (open_cl->buf)
	{
		if (clReleaseMemObject(open_cl->buf))
			put_open_cl_error(open_cl, "clReleaseMemObject");
	}
}

void	clean_open_cl_info(t_open_cl *open_cl)
{
	if (open_cl->platform_name)
		ft_memdel((void **)&(open_cl->platform_name));
	if (open_cl->device_name)
		ft_memdel((void **)&(open_cl->device_name));
	if (open_cl->driver_ver)
		ft_memdel((void **)&(open_cl->driver_ver));
	if (open_cl->source_str)
		ft_memdel((void **)&(open_cl->source_str));
	if (open_cl->program_build_log)
		ft_memdel((void **)&(open_cl->program_build_log));
}

void	clean_open_cl(t_open_cl *open_cl)
{
	if (open_cl)
	{
		clean_open_cl_1(open_cl);
		clean_open_cl_2(open_cl);
		clean_open_cl_info(open_cl);
		ft_memdel((void **)&open_cl);
	}
}
