/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:18 by bthomas           #+#    #+#             */
/*   Updated: 2024/05/22 10:19:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

float	smooth_n(int n, t_complex z, t_mlx_data *mlx)
{
	float	mod;

	if (n == mlx->iters)
		return ((float)n);
	mod = sqrt(z.x * z.x + z.i * z.i);
	return (n + 1 - log(log(mod)) / log(2));
}

/*
	* Mandelbrot Calculation:
	* f(z) = z^2 + c
	*
	*  f(z) = new position.
	*  z^2 = current postion.
	*  c = starting position.
	*
	*  both z & c are complex numbers with real and imaginary components;
	*  z^2 = (x + yi)(x + yi)
	*  z^2 = x^2 + xyi + xyi - y^2
	*  z^2 = x^2 - y^2 + 2xyi
	*/
float	calc_set(t_complex c, t_mlx_data *mlx)
{
	int				n;
	long double		temp_x;
	t_complex		z;

	z.i = mlx->z.i;
	z.x = mlx->z.x;
	if (mlx->set == 'j')
	{
		z.i = c.i;
		z.x = c.x;
		c.x = mlx->z.x;
		c.i = mlx->z.i;
	}
	n = 0;
	while (n < mlx->iters)
	{
		temp_x = (z.x * z.x) - (z.i * z.i) + c.x;
		z.i = 2 * z.x * z.i + c.i;
		z.x = temp_x;
		if ((z.x * z.x + z.i * z.i) > 4)
			break ;
		n++;
	}
	return (smooth_n(n, z, mlx));
}

/*
 *  The first step calculates the distance to (0.25, 0).
 *    This relates to the cardioid shape (the main large shape).
 *    The first if statement checks if it's within the main large shape
 *
 *  The second check calculates the distance from (-1,0) which is
 *  the small circle to the left of the main shape.
 *    the second if statement check if the point is within this circle.
 *
 *  mandelbrot_quick speeds up the calculations at the start but is
 *  useless after the two main shapes are not visible.
 */
int	mandelbrot_quick(t_complex c)
{
	long double	dist_0_25;
	long double	dist_sq_neg_1;

	dist_0_25 = sqrt((c.x - 0.25) * (c.x - 0.25) + c.i * c.i);
	if (c.x < dist_0_25 - 2 * dist_0_25 * dist_0_25 + 0.25)
		return (1);
	dist_sq_neg_1 = (c.x + 1) * (c.x + 1) + c.i * c.i;
	if (dist_sq_neg_1 <= 1.0 / 16.0)
		return (1);
	return (0);
}
/* You can play around with the functions to produce different 
colour schemes
	* The r value is the function:
	*   9 * (1 - t) * t^3
	*   r is a bell curve. Slowly coming to a peak at ~0.77 before
	*   plummeting to 0
	*
	* The g value is similar to r:
	*   15 * (1 - t)^2 * t^2
	*   g is also a bell curve but not skewed to the right like r.
	*
	* The b value is a concave curve.
	*   tapering off faster than r.
	*   1 - (1 - t)^2
	*/

int	get_colour(float n, t_mlx_data *mlx)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = n / mlx->iters;
	r = (int)(mlx->r_fact * (1 - t) * t * t * t * 255);
	g = (int)(mlx->g_fact * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(mlx->b_fact * (1 - (1 - t) * (1 - t)) * 255);
	return ((r << 16) | (g << 8) | b);
}
