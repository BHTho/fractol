/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:33:10 by bthomas           #+#    #+#             */
/*   Updated: 2024/05/22 09:29:05 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	attach_hooks(t_mlx_data *mlx)
{
	mlx_hook(mlx->win, 2, (1L << 0), buttonpress, mlx);
	mlx_hook(mlx->win, KEY_XBUTT, 0, clean_close, mlx);
	mlx_mouse_hook(mlx->win, mouse_scroll, mlx);
}

int	buttonpress(int button, t_mlx_data *mlx)
{
	if (button == XK_Escape)
		clean_close(mlx);
	else if (button >= 65361 && button <= 65364)
		shift_img(mlx, button);
	else if (button == 45 || button == 61)
		sharpen(mlx, button);
	return (colour_shift(button, mlx));
}

int	mouse_scroll(int button, int x, int y, t_mlx_data *mlx)
{
	if (button == MOUSE_WHL_DWN || button == MOUSE_WHL_UP)
	{
		mlx_mouse_get_pos(mlx->mlx, mlx->win, &x, &y);
		update_scale(mlx, button, x, y);
		refresh_image(mlx);
	}
	return (0);
}
