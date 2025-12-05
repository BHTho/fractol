/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:03:21 by bthomas           #+#    #+#             */
/*   Updated: 2024/05/23 10:03:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	clean_close(t_mlx_data *mlx)
{
	print_cowboy();
	ft_printf("Closing down, goodbye...\n");
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_loop_end(mlx->mlx);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(1);
	return (0);
}

void	custom_pixel_put(t_mlx_data *mlx, int x, int y, int colour)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->linelen + x * (mlx->bpp / 8));
	*(unsigned int *)dst = colour;
}
