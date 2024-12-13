/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:21:05 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/10 13:01:49 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
//		r=.5\n		n=.5\n
	/*usage_str[4] = "	Constrains:\n		r:\n";
	usage_str[5] = "			r > 0\n";
	usage_str[6] = "			r ** n >= sqrt(cx**2 + cy**2)\n";*/
int	notify_usage(void)
{
	const size_t	usage_str_n = 6;
	size_t			i;
	char			*usage_str[6];

	usage_str[0] = "Usage: ./fractol fractal_name [-option=value]\n";
	usage_str[1] = "fractal_names:\n	mandelbrot\n	julia\n";
	usage_str[2] = "options:\n  All fractals:\n";
	usage_str[3] = "	-res=[high,low]\n";
	usage_str[4] = "  Julia:\n";
	usage_str[5] = "	-cx=.5\n	-cy=.5\n";
	i = 0;
	while (i < usage_str_n)
	{
		ft_putstr_fd(usage_str[i], 1);
		i++;
	}
	return (0);
}

static int	render_image(t_render_data *render_d)
{
	render_d->img.img = mlx_new_image(render_d->mlx,
			render_d->img.res.x, render_d->img.res.y);
	if (!render_d->img.img)
		return (mlx_loop_end(render_d->mlx), 1);
	render_d->img.addr = mlx_get_data_addr(render_d->img.img,
			&render_d->img.bits_per_pixel, &render_d->img.line_length,
			&render_d->img.endian);
	if (!render_d->img.addr)
		return (free_img(render_d), mlx_loop_end(render_d->mlx), 1);
	if (draw(render_d))
		return (0);
	mlx_put_image_to_window(render_d->mlx, render_d->win, render_d->img.img,
		0, 0);
	render_d->args.time++;
	free_img(render_d);
	mlx_loop(render_d->mlx);
	return (0);
}

static void	render_loop(t_render_data *render_d)
{
	create_hooks(render_d);
	render_d->args.zoom = 1;
	mlx_loop_hook(render_d->mlx, render_image, render_d);
	mlx_loop(render_d->mlx);
}

int	main(int argc, char *argv[])
{
	t_render_data	render_d;

	ft_bzero(&render_d, sizeof(t_render_data));
	render_d.argc = argc;
	render_d.argv = argv;
	if (parse_args(&render_d))
		return (notify_usage());
	render_d.mlx = mlx_init();
	if (!render_d.mlx)
		return (1);
	render_d.img.res.x = 1080;
	render_d.img.res.y = 720;
	render_d.win = mlx_new_window(render_d.mlx, render_d.img.res.x,
			render_d.img.res.y, "fractol");
	if (!render_d.win)
		return (free_mlx(render_d.mlx));
	render_loop(&render_d);
	free_all(&render_d);
	return (0);
}
