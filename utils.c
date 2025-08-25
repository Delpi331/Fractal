/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-pin <ddel-pin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:08:48 by ddel-pin          #+#    #+#             */
/*   Updated: 2025/05/05 15:10:26 by ddel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	julia(double zr, double zi, t_fractal *fractal)
{
	double	zr2;
	double	zi2;
	int		iterations;

	zr2 = zr * zr;
	zi2 = zi * zi;
	iterations = 0;
	while (zr2 + zi2 < 4.0 && iterations < fractal->max_iter)
	{
		zi = 2.0 * zr * zi + fractal->ci;
		zr = zr2 - zi2 + fractal->cr;
		zr2 = zr * zr;
		zi2 = zi * zi;
		iterations++;
	}
	return (iterations);
}

int	mandelbrot(double cr, double ci)
{
	double	zr;
	double	zi;
	double	zr2;
	double	zi2;
	int		iterations;

	zr = 0.0;
	zi = 0.0;
	zr2 = 0.0;
	zi2 = 0.0;
	iterations = 0;
	while (zr2 + zi2 < 4.0 && iterations < 100)
	{
		zi = 2.0 * zr * zi + ci;
		zr = zr2 - zi2 + cr;
		zr2 = zr * zr;
		zi2 = zi * zi;
		iterations++;
	}
	return (iterations);
}

int	zoom(int button, int x, int y, t_fractal *fractal)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	mouse_re = fractal->min_re + (double)x / fractal->width * (fractal->max_re
			- fractal->min_re);
	mouse_im = fractal->min_im + (double)y / fractal->height * (fractal->max_im
			- fractal->min_im);
	if (button == 4)
		zoom_factor = 1.0 / 1.1;
	else
		zoom_factor = 1.1;
	fractal->min_re = mouse_re + (fractal->min_re - mouse_re) * zoom_factor;
	fractal->max_re = mouse_re + (fractal->max_re - mouse_re) * zoom_factor;
	fractal->min_im = mouse_im + (fractal->min_im - mouse_im) * zoom_factor;
	fractal->max_im = mouse_im + (fractal->max_im - mouse_im) * zoom_factor;
	fractal->zoom *= zoom_factor;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractal *fractal)
{
	if (button == 4 || button == 5)
	{
		zoom(button, x, y, fractal);
		render_fractal(fractal, fractal->type);
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	return (0);
}

int	get_color(int iterations, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)iterations / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (r << 16 | g << 8 | b);
}
