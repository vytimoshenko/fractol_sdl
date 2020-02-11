/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_open_cl_run.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:12:19 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/11 05:15:12 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	run_open_cl(t_status *status, t_open_cl *open_cl, int *res)
{
	cl_event event;

	event = NULL;
	set_arg_open_cl_kernel(status, open_cl);
	if (clEnqueueNDRangeKernel(open_cl->command_queue, open_cl->kernel, 1, NULL,
	&(open_cl->global_work_size), &(open_cl->local_work_size), 0, NULL, &event))
		put_open_cl_error(open_cl, "clEnqueueNDRangeKernel");
	if (clWaitForEvents(1, &event))
		put_open_cl_error(open_cl, "clWaitForEvents");
	if (clFlush(open_cl->command_queue))
		put_open_cl_error(open_cl, "clFlush");
	get_execution_time(open_cl, event);
	clReleaseEvent(event);
	if (clEnqueueReadBuffer(open_cl->command_queue, open_cl->buf, CL_TRUE, 0,
	open_cl->global_work_size * sizeof(int), res, 0, NULL, NULL))
		put_open_cl_error(open_cl, "clEnqueueReadBuffer");
}

void	set_arg_open_cl_kernel(t_status *status, t_open_cl *open_cl)
{
	t_kernel_arg	kernel_arg;

	if (!(open_cl->buf))
	{
		if (!(open_cl->buf = clCreateBuffer(open_cl->context, CL_MEM_WRITE_ONLY,
		open_cl->global_work_size * sizeof(int), NULL, NULL)))
			put_open_cl_error(open_cl, "clCreateBuffer");
	}
	if (clSetKernelArg(open_cl->kernel, 0, sizeof(cl_mem), &(open_cl->buf)))
		put_open_cl_error(open_cl, "clSetKernelArg");
	pack_arg_to_struct(status, &kernel_arg);
	if (clSetKernelArg(open_cl->kernel, 1, sizeof(kernel_arg), &kernel_arg))
		put_open_cl_error(open_cl, "clSetKernelArg");
}

void	pack_arg_to_struct(t_status *status, t_kernel_arg *kernel_arg)
{
	kernel_arg->img_size_x = IMG_SIZE_W;
	kernel_arg->fractal_type = status->fractal_type;
	kernel_arg->color_theme = status->color_theme;
	kernel_arg->iter = status->iter;
	kernel_arg->pause = status->pause;
	kernel_arg->zoom = status->zoom;
	kernel_arg->x_center = status->x_center;
	kernel_arg->y_center = status->y_center;
	kernel_arg->x_shift = status->x_shift;
	kernel_arg->y_shift = status->y_shift;
	kernel_arg->x_julia = status->x_julia;
	kernel_arg->y_julia = status->y_julia;
}

void	get_execution_time(t_open_cl *open_cl, cl_event event)
{
	cl_ulong start;
	cl_ulong end;

	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(start),
	&start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(end), &end,
	NULL);
	open_cl->execution_time = (int)((end - start) / 1000000);
}
