/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_open_cl_clean.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 00:43:04 by mperseus          #+#    #+#             */
/*   Updated: 2020/01/28 00:44:08 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_open_cl_1(t_open_cl *open_cl)
{
	cl_int	err_code;

	if (open_cl->command_queue)
	{
		if ((err_code = clFlush(open_cl->command_queue)))
			put_open_cl_error(open_cl, "clFlush error", err_code);
		if ((err_code = clFinish(open_cl->command_queue)))
			put_open_cl_error(open_cl, "clFinish error", err_code);
		if ((err_code = clReleaseCommandQueue(open_cl->command_queue)))
			put_open_cl_error(open_cl, "clReleaseCommandQueue error", err_code);
	}
	if (open_cl->context)
	{
		if ((err_code = clReleaseContext(open_cl->context)))
			put_open_cl_error(open_cl, "clReleaseContext error", err_code);
	}
	if (open_cl->kernel)
	{
		if ((err_code = clReleaseKernel(open_cl->kernel)))
			put_open_cl_error(open_cl, "clReleaseKernel error", err_code);
	}
}

void	clean_open_cl_2(t_open_cl *open_cl)
{
	cl_int	err_code;

	if (open_cl->program)
	{
		if ((err_code = clReleaseProgram(open_cl->program)))
			put_open_cl_error(open_cl, "clReleaseProgram error", err_code);
	}
	if (open_cl->buf)
	{
		if ((err_code = clReleaseMemObject(open_cl->buf)))
			put_open_cl_error(open_cl, "clReleaseMemObject error", err_code);
	}
}

void	clean_open_cl(t_open_cl *open_cl)
{
	clean_open_cl_1(open_cl);
	clean_open_cl_2(open_cl);
}
