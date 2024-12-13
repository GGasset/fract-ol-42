/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:51:23 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/10 13:21:37 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int	max_iter_color(size_t time)
{
	int		r;
	int		g;
	int		b;
	double	percentage;

	return (0xFFDFFFDF);
	time *= 1;
	time += 50;
	percentage = time / 50.0;
	r = 255 / 2.1 - 1;
	g = 0;
	b = 200;
	r *= sin(percentage * 5) + 1.1;
	g += (sin(percentage / 3) / 2 + .5) * (200);
	b -= (sin(percentage * 7) / 2 + .5) * 150;
	return ((255 << 24) + (r << 16) + (g << 8) + b);
}

static int	get_color(size_t iter_n, size_t time, t_args args)
{
	int		a;
	int		r;
	int		g;
	int		b;
	double	percent;

	if (iter_n == args.max_i - 1)
		return (max_iter_color(time));
	if (iter_n + 1 < args.min_i && args.min_i < args.max_i)
		return (0x010301);
	time += 200;
	time /= 2;
	time = 110;
	percent = iter_n / (double)args.max_i;
	r = (int)(time * 13 * percent) % 255;
	g = (time * 2) % (int)(percent * 126 + 1);
	g *= 2;
	g += time % 2;
	b = (time * 7) % 63 * 4 + (int)percent * 8 % 4;
	a = 255;
	return (b + (g << 8) + (r << 16) + (a << 24));
}

int	get_mandelbrot(int x, int y, t_res res, t_args args)
{
	size_t			i;
	t_mandelbrot	vars;

	ft_bzero(&vars, sizeof(t_mandelbrot));
	vars.x0 = (x / (double)res.x) * args.zoom * 2.47 - 2 + args.movement_x;
	vars.y0 = (y / (double)res.y) * args.zoom * 2.30 - 1.15 + args.movement_y;
	i = 0;
	while (vars.x2 + vars.y2 <= 4 && i < args.max_i)
	{
		vars.y = 2 * vars.x * vars.y + vars.y0;
		vars.x = vars.x2 - vars.y2 + vars.x0;
		vars.x2 = vars.x * vars.x;
		vars.y2 = vars.y * vars.y;
		i++;
	}
	return (get_color(i - 1, args.time, args));
}
