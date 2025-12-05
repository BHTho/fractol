/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:09:54 by bthomas           #+#    #+#             */
/*   Updated: 2024/05/29 21:43:58 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	refresh_image(t_mlx_data *mlx)
{
	fill_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	shift_img(t_mlx_data *mlx, int button)
{
	long double	x_shift;
	long double	y_shift;

	x_shift = 0.0;
	y_shift = 0.0;
	if (button == XK_Left)
		x_shift = -25.0;
	if (button == XK_Right)
		x_shift = 25.0;
	if (button == XK_Up)
		y_shift = 25.0;
	if (button == XK_Down)
		y_shift = -25.0;
	mlx->minx += x_shift * mlx->scale_x;
	mlx->maxx += x_shift * mlx->scale_x;
	mlx->mini += y_shift * mlx->scale_y;
	mlx->maxi += y_shift * mlx->scale_y;
	mlx->scale_x = (mlx->maxx - mlx->minx) / (WINWIDTH - 1);
	mlx->scale_y = (mlx->maxi - mlx->mini) / (WINHEIGHT - 1);
	refresh_image(mlx);
}

void	sharpen(t_mlx_data *mlx, int button)
{
	if (button == 45 && mlx->iters > 10)
		mlx->iters -= 5;
	else if (button == 61)
		mlx->iters += 5;
	refresh_image(mlx);
}

void	update_scale(t_mlx_data *mlx, int button, int x, int y)
{
	long double	x_offset;
	long double	y_offset;
	long double	zoom_fact;

	if (button == MOUSE_WHL_DWN)
		zoom_fact = 0.80;
	else
		zoom_fact = 1.30;
	x_offset = mlx->minx + x * mlx->scale_x;
	y_offset = mlx->maxi - y * mlx->scale_y;
	mlx->minx = x_offset + (mlx->minx - x_offset) * zoom_fact;
	mlx->maxx = x_offset + (mlx->maxx - x_offset) * zoom_fact;
	mlx->mini = y_offset + (mlx->mini - y_offset) * zoom_fact;
	mlx->maxi = y_offset + (mlx->maxi - y_offset) * zoom_fact;
	mlx->scale_x = (mlx->maxx - mlx->minx) / (WINWIDTH - 1);
	mlx->scale_y = (mlx->maxi - mlx->mini) / (WINHEIGHT - 1);
}

void	fill_image(t_mlx_data *mlx)
{
	long double		x;
	long double		y;
	t_complex		c;
	float			n;

	x = -1;
	while (++x <= WINWIDTH)
	{
		y = -1;
		while (++y <= WINHEIGHT)
		{
			c.x = mlx->minx + x * mlx->scale_x;
			c.i = mlx->maxi - y * mlx->scale_y;
			if (mlx->set == 'm' && mandelbrot_quick(c))
				n = mlx->iters;
			else if (mlx->set != 'b')
				n = calc_set(c, mlx);
			else
				n = burning_ship(c, mlx);
			if (n < mlx->iters)
				custom_pixel_put(mlx, x, y, get_colour(n, mlx));
			else
				custom_pixel_put(mlx, x, y, BLACKHEX);
		}
	}
}
