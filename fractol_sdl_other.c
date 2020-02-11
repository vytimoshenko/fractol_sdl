/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sdl_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperseus <mperseus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:59:54 by mperseus          #+#    #+#             */
/*   Updated: 2020/02/12 01:28:31 by mperseus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	IMG_SaveJPG(sdl->main_surface, file_name, 100);
	free(file_name);
	++sdl->screenshot_num;
}

void	close_window(t_global *global)
{
	clean_open_cl(global->open_cl);
	clean_sdl(global->sdl);
	exit(0);
}
