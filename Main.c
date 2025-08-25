/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-pin <ddel-pin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:02:54 by ddel-pin          #+#    #+#             */
/*   Updated: 2025/05/05 15:21:00 by ddel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	parse_arguments(int argc, char **argv, t_fractal *fractal)
{
	if (argc < 2)
		return (0);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		fractal->type = MANDELBROT;
		return (1);
	}
	else if (ft_strcmp(argv[1], "julia") == 0 && argc == 4)
	{
		fractal->type = JULIA;
		fractal->cr = atof(argv[2]);
		fractal->ci = atof(argv[3]);
		return (1);
	}
	return (0);
}

void	init_fractal(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, 800, 600, "Fractol");
	fractal->width = 800;
	fractal->height = 600;
	fractal->img = mlx_new_image(fractal->mlx, fractal->width, fractal->height);
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->line_length, &fractal->endian);
	fractal->min_re = -2.0;
	fractal->max_re = 2.0;
	fractal->min_im = -1.5;
	fractal->max_im = 1.5;
	fractal->zoom = 1.0;
	fractal->x_offset = -2.0;
	fractal->y_offset = -1.5;
	fractal->max_iter = 100;
}

void	setup_hooks(t_fractal *fractal)
{
	mlx_hook(fractal->win, 17, 0, close_window, fractal);
	mlx_hook(fractal->win, 2, 1, key_hook, fractal);
	mlx_mouse_hook(fractal->win, mouse_hook, fractal);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (!parse_arguments(argc, argv, &fractal))
		return (0);
	init_fractal(&fractal);
	render_fractal(&fractal, fractal.type);
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	setup_hooks(&fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
