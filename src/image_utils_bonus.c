/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:56:57 by bthomas           #+#    #+#             */
/*   Updated: 2024/05/22 10:12:31 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	init_colours(t_mlx_data *mlx)
{
	mlx->r_fact = 9;
	mlx->g_fact = 15;
	mlx->b_fact = 1;
}

int	colour_shift(int button, t_mlx_data *mlx)
{
	if (button == XK_w && mlx->r_fact < 30)
		mlx->r_fact++;
	else if (button == XK_q && mlx->r_fact > 1)
		mlx->r_fact--;
	else if (button == XK_s)
		mlx->g_fact++;
	else if (button == XK_a && mlx->g_fact > 1)
		mlx->g_fact--;
	else if (button == XK_x)
		mlx->b_fact++;
	else if (button == XK_z && mlx->b_fact > 1)
		mlx->b_fact--;
	else
		return (0);
	ft_printf("r_fact: %d g_fact: %d b_fact: %d\n", mlx->r_fact, mlx->g_fact,
		mlx->b_fact);
	refresh_image(mlx);
	return (0);
}

int	burning_ship(t_complex c, t_mlx_data *mlx)
{
	int				n;
	long double		temp_x;
	t_complex		z;

	z.i = mlx->z.i;
	z.x = mlx->z.x;
	n = 0;
	while (n < mlx->iters)
	{
		temp_x = (z.x * z.x) - (z.i * z.i) + c.x;
		z.i = -2 * fabsl(z.x) * fabsl(z.i) + c.i;
		z.x = temp_x;
		if ((z.x * z.x + z.i * z.i) > 4)
			break ;
		n++;
	}
	return (smooth_n(n, z, mlx));
}
