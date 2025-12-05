/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:36:02 by bthomas           #+#    #+#             */
/*   Updated: 2024/05/29 10:47:22 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static int	init_mlxalloc(t_mlx_data *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WINWIDTH, WINHEIGHT, "Fractol");
	if (!mlx->win)
		return (1);
	mlx->img = mlx_new_image(mlx->mlx, WINWIDTH, WINHEIGHT);
	if (!mlx->img)
		return (1);
	return (0);
}

static int	initialise(t_mlx_data *mlx, char **av, int ac)
{
	ft_memset(mlx, 0, sizeof(mlx));
	if (init_mlxalloc(mlx))
		return (1);
	mlx->set = *av[1];
	mlx->z.x = 0;
	mlx->z.i = 0;
	if (mlx->set == 'j' && ac >= 4)
	{
		mlx->z.x = ft_atof(av[2]);
		mlx->z.i = ft_atof(av[3]);
	}
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->linelen,
			&mlx->endian);
	mlx->minx = -2.5;
	mlx->maxx = 1.5;
	mlx->mini = -1.5;
	mlx->maxi = 1.5;
	mlx->scale_x = (mlx->maxx - mlx->minx) / (WINWIDTH - 1);
	mlx->scale_y = (mlx->maxi - mlx->mini) / (WINHEIGHT - 1);
	mlx->iters = MAX_ITER;
	init_colours(mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx_data	mlx;

	if (ac < 2 || (*av[1] == 'j' && ac < 4))
		return (exit_help());
	if (*av[1] != 'm' && *av[1] != 'b' && *av[1] != 'j')
		return (exit_help());
	ft_printf("initialising...\n");
	if (initialise(&mlx, av, ac))
	{
		ft_putendl_fd("Error: failed mlx malloc.", 2);
		return (1);
	}
	ft_printf("filling image...\n");
	fill_image(&mlx);
	ft_printf("putting image to window...\n");
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	attach_hooks(&mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
