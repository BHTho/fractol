/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:20:54 by bthomas           #+#    #+#             */
/*   Updated: 2024/05/22 10:21:22 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

float	ft_atof(char *s)
{
	int		i;
	int		j;
	int		sign;
	double	ret;

	ret = 0.0;
	i = -1;
	sign = 1;
	while (s[++i] && !ft_isdigit(s[i]))
		if (s[i] == '-')
			sign *= -1;
	while (ft_isdigit(s[i]))
	{
		ret *= 10;
		ret += s[i] - '0';
		i++;
	}
	if (s[i] != '.')
		return (ret * sign);
	j = i;
	while (s[++j] && ft_isdigit(s[j]))
		ret += ((double)s[j] - '0') / pow(10, (j - i));
	return (ret * sign);
}
