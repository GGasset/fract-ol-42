/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_router.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:18:24 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/10 12:52:20 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int	draw_julia(t_render_data *args)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	while (x < args->img.res.x)
	{
		y = 0;
		while (y < args->img.res.y)
		{
			i = y * args->img.res.x + x;
			((int *)args->img.addr)[i] = get_julia(x, y, args, args->julia);
			y++;
		}
		x++;
	}
	return (0);
}

static int	draw_mandelbrot(t_render_data *args)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	while (x < args->img.res.x)
	{
		y = 0;
		while (y < args->img.res.y)
		{
			i = y * args->img.res.x + x;
			((int *)args->img.addr)[i] = get_mandelbrot(x, y,
					args->img.res, args->args);
			y++;
		}
		x++;
	}
	return (0);
}

static int	route_drawing(t_render_data *args)
{
	if (!ft_strncmp(args->argv[1], "mandelbrot", 40))
		return (draw_mandelbrot(args));
	if (!ft_strncmp(args->argv[1], "julia", 40))
		return (draw_julia(args));
	return (1);
}

int	draw(t_render_data *args)
{
	if (route_drawing(args))
	{
		mlx_loop_end(args->mlx);
		return (1);
	}
	return (0);
}
