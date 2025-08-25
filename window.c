/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-pin <ddel-pin@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:11:00 by ddel-pin          #+#    #+#             */
/*   Updated: 2025/05/05 15:11:38 by ddel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	clean_exit(t_fractal *fractal)
{
	if (fractal->img)
		mlx_destroy_image(fractal->mlx, fractal->img);
	if (fractal->win)
		mlx_destroy_window(fractal->mlx, fractal->win);
	if (fractal->mlx)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
	}
	exit(0);
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == 65307)
		clean_exit(fractal);
	return (0);
}

int	close_window(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	clean_exit(fractal);
	return (0);
}
