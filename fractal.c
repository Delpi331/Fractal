/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-pin <ddel-pin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:08:06 by ddel-pin          #+#    #+#             */
/*   Updated: 2025/05/05 15:02:02 by ddel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	render_mandelbrot(t_fractal *fractal)
{
	int		x;
	int		y;
	double	re;
	double	im;

	y = -1;
	while (++y < fractal->height)
	{
		x = -1;
		while (++x < fractal->width)
		{
			re = fractal->min_re + (double)x / fractal->width * (fractal->max_re
					- fractal->min_re);
			im = fractal->min_im + (double)y / fractal->height
				* (fractal->max_im - fractal->min_im);
			my_mlx_pixel_put(fractal, x, y, get_color(mandelbrot(re, im),
					fractal->max_iter));
		}
	}
}

void	render_julia(t_fractal *fractal)
{
	int		x;
	int		y;
	double	re;
	double	im;

	y = -1;
	while (++y < fractal->height)
	{
		x = -1;
		while (++x < fractal->width)
		{
			re = fractal->min_re + (double)x / fractal->width * (fractal->max_re
					- fractal->min_re);
			im = fractal->min_im + (double)y / fractal->height
				* (fractal->max_im - fractal->min_im);
			my_mlx_pixel_put(fractal, x, y, get_color(julia(re, im, fractal),
					fractal->max_iter));
		}
	}
}

void	render_fractal(t_fractal *fractal, t_fractal_type type)
{
	if (type == MANDELBROT)
		render_mandelbrot(fractal);
	else
		render_julia(fractal);
}

void	my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
	char	*dst;

	dst = fractal->addr + (y * fractal->line_length + x * (fractal->bpp / 8));
	*(unsigned int *)dst = color;
}
