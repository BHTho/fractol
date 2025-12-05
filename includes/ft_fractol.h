/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:36:17 by bthomas           #+#    #+#             */
/*   Updated: 2025/12/05 09:49:16 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <pthread.h>
# include "ft_printf.h"
# define MAX_ITER 30
# define WINWIDTH 1080
# define WINHEIGHT 720
# define BLACKHEX 0x00000000
# define KEY_ESC XK_ESCAPE
# define KEY_LEFT XK_LEFT
# define KEY_RIGHT XK_RIGHT
# define KEY_UP XK_UP
# define KEY_DOWN XK_DOWN
# define KEY_XBUTT 17
# define MOUSE_WHL_DWN 5
# define MOUSE_WHL_UP 4

typedef struct s_complex
{
	long double	x;
	long double	i;
}	t_complex;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
	long double	minx;
	long double	maxx;
	long double	mini;
	long double	maxi;
	long double	scale_x;
	long double	scale_y;
	int			r_fact;
	int			g_fact;
	int			b_fact;
	int			iters;
	char		set;
	t_complex	z;
}	t_mlx_data;

void	custom_pixel_put(t_mlx_data *mlx, int x, int y, int colour);
float	calc_set(t_complex c, t_mlx_data *mlx);
int		burning_ship(t_complex c, t_mlx_data *mlx);
int		mandelbrot_quick(t_complex c);
int		get_colour(float n, t_mlx_data *mlx);
void	fill_image(t_mlx_data *mlx);
int		buttonpress(int button, t_mlx_data *mlx);
int		clean_close(t_mlx_data *mlx);
int		mouse_scroll(int button, int x, int y, t_mlx_data *mlx);
void	update_scale(t_mlx_data *mlx, int button, int x, int y);
void	refresh_image(t_mlx_data *mlx);
void	shift_img(t_mlx_data *mlx, int button);
void	sharpen(t_mlx_data *mlx, int button);
void	attach_hooks(t_mlx_data *mlx);
int		exit_help(void);
float	smooth_n(int n, t_complex z, t_mlx_data *mlx);
void	init_colours(t_mlx_data *mlx);
int		colour_shift(int button, t_mlx_data *mlx);
float	ft_atof(char *s);
void	print_cowboy(void);

#endif
