/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:09:54 by bthomas           #+#    #+#             */
/*   Updated: 2025/12/05 09:50:33 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"
#include <unistd.h>

typedef struct s_thread_data
{
    t_mlx_data	*mlx;
    int			start_x;
    int			end_x; /* exclusive */
}	t_thread_data;

static void	*render_thread(void *arg)
{
    t_thread_data	*td;
    t_mlx_data		*mlx;
    int				x;
    int				y;
    t_complex		c;
    float			n;

    td = (t_thread_data *)arg;
    mlx = td->mlx;
    for (x = td->start_x; x < td->end_x; ++x)
    {
        for (y = 0; y < WINHEIGHT; ++y)
        {
            c.x = mlx->minx + (long double)x * mlx->scale_x;
            c.i = mlx->maxi - (long double)y * mlx->scale_y;
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
    return (NULL);
}

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
    int				nthreads;
    pthread_t		*threads;
    t_thread_data	*td;
    int				i;
    int				chunk;
    int				rem;
    int				start;

    nthreads = (int)sysconf(_SC_NPROCESSORS_ONLN);
    if (nthreads <= 0)
        nthreads = 1;
    if (nthreads > WINWIDTH)
        nthreads = WINWIDTH;

    threads = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    td = (t_thread_data *)malloc(sizeof(t_thread_data) * nthreads);
    if (!threads || !td)
    {
        if (threads)
            free(threads);
        if (td)
            free(td);
        render_thread(&(t_thread_data){ .mlx = mlx, .start_x = 0, .end_x = WINWIDTH });
        return ;
    }

    chunk = WINWIDTH / nthreads;
    rem = WINWIDTH % nthreads;
    start = 0;
    i = 0;
    while (i < nthreads)
    {
        td[i].mlx = mlx;
        td[i].start_x = start;
        td[i].end_x = start + chunk + (rem > 0 ? 1 : 0);
        if (td[i].end_x > WINWIDTH)
            td[i].end_x = WINWIDTH;
        start = td[i].end_x;
        if (rem > 0)
            --rem;
        pthread_create(&threads[i], NULL, render_thread, &td[i]);
        ++i;
    }
    while (--i >= 0)
        pthread_join(threads[i], NULL);

    free(threads);
    free(td);
}
