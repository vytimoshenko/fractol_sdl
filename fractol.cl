#define MANDELBROT		1
#define JULIA			2
#define BURNING_SHIP	3
#define SPIDER			4
#define SIN				5

#define NEW				0
#define OLD				1


typedef struct			s_kernel_arg
{
	int					img_size_x;

	int					fractal_type;
	
	int					color_theme;
	int					iter;
	int					pause;
	double				zoom;

	double				x_center;
	double				y_center;
	double				x_shift;
	double				y_shift;
	
	double				x_julia;
	double				y_julia;
}						t_kernel_arg;

int 	get_color(int i, int max, int color_theme);
int		set_colors(unsigned char o, unsigned char r, unsigned char g, unsigned char b);

int		set_colors(unsigned char o, unsigned char r, unsigned char g, unsigned char b)
{
	return ((int)o << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

int 		get_color(int i, int max, int color_theme)
{
	int			red;
	int			blue;
	int			green;
	double		n;

	n = (double)i / (double)max;
	red = (int)(9 * (1 - n) * pow(n, 3) * 255);
	green = (int)(15 * pow((1 - n), 2) * pow(n, 2) * 255);
	blue = (int)(8.5 * pow((1 - n), 3) * n * 255);
	if (color_theme == 0)
		return (set_colors(0, red, blue, green));
	else if (color_theme == 1)
		return (set_colors(0, blue, green, red));
	else if (color_theme == 2)
		return (set_colors(0, blue, red, green));
	else if (color_theme == 3)
		return (set_colors(0, red, green, blue));
	return (0);
}

__kernel void fractol(__global int *data, t_kernel_arg kernel_arg)
{
    	double	re[2];
    	double	im[2];
    	double	c_re;
    	double	c_im;
    	int     i;
        size_t  id;
        int     x;
        int     y;

        id = get_global_id(0);
    	i = 0;
    	x = id % kernel_arg.img_size_x;
    	y = id / kernel_arg.img_size_x;
    	c_re = (x - kernel_arg.x_center) / kernel_arg.zoom + kernel_arg.x_shift;
        c_im = (y - kernel_arg.y_center) / kernel_arg.zoom + kernel_arg.y_shift;
        re[NEW] = c_re;
        im[NEW] = c_im;
        if (kernel_arg.fractal_type == MANDELBROT)
        {
    		while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < kernel_arg.iter)
   	 		{
    			re[OLD] = re[NEW];
        		im[OLD] = im[NEW];
        		im[NEW] = 2 * im[OLD] * re[OLD] + c_im;
        	    re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + c_re;
    		}
    	}
    	else if (kernel_arg.fractal_type == JULIA)
    	{
    		while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < kernel_arg.iter)
   	 		{
    			re[OLD] = re[NEW];
        		im[OLD] = im[NEW];
        		im[NEW] = 2 * im[OLD] * re[OLD] + kernel_arg.y_julia;
        	    re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + kernel_arg.x_julia;
    		}
    	}
		else if (kernel_arg.fractal_type == BURNING_SHIP)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < kernel_arg.iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				im[NEW] = 2.0 * fabs(re[OLD] * im[OLD]) + c_im;
				re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + c_re;
			}
		}
		else if (kernel_arg.fractal_type == SPIDER)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] < 4 && ++i < kernel_arg.iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				re[NEW] = re[OLD] * re[OLD] - im[OLD] * im[OLD] + c_re;
				im[NEW] = 2 * re[OLD] * im[OLD] + c_im;
				c_im = c_im / 2 + im[NEW];
				c_re = c_re / 2 + re[NEW];
			}
		}
		else if (kernel_arg.fractal_type == SIN)
		{
			while (re[NEW] * re[NEW] + im[NEW] * im[NEW] > 1 && ++i < kernel_arg.iter)
			{
				re[OLD] = re[NEW];
				im[OLD] = im[NEW];
				re[NEW] = cos(re[OLD]) * cosh(im[OLD]);
				im[NEW] = sin(re[OLD]) * sinh(im[OLD]);
				re[OLD] = (c_re * re[NEW] + c_im * im[NEW]) / (re[NEW] * re[NEW] + im[NEW] * im[NEW]);
				im[OLD] = (c_re * im[NEW] - c_im * re[NEW]) / (re[NEW] * re[NEW] + im[NEW] * im[NEW]);
			}
		}
    	if (i < kernel_arg.iter)
    	    ((__global int *)data)[id] = get_color(i, kernel_arg.iter, kernel_arg.color_theme);
    	else
            ((__global int *)data)[id] = 0;
}
