/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:17:00 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/10 14:53:02 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int	key_hook(int keycode, t_render_data *render_d)
{
	double	zoom;

	zoom = render_d->args.zoom;
	if (keycode == 65362)
		render_d->args.movement_y -= .1 * zoom;
	if (keycode == 65361)
		render_d->args.movement_x -= .1 * zoom;
	if (keycode == 65364)
		render_d->args.movement_y += .1 * zoom;
	if (keycode == 65363)
		render_d->args.movement_x += .1 * zoom;
	if (keycode == 65307)
		mlx_loop_end(render_d->mlx);
	return (0);
}

/*ft_putstr_fd("KeyPressed: ", 1);
ft_putnbr_fd(action, 1);
ft_putendl_fd("", 1);*/
static int	mouse_hook(int button, int x, int y, t_render_data *render_d)
{
	double	zoom;
	double	zoom2;

	zoom = render_d->args.zoom + 0 * x + 0 * y;
	if (button == 4)
		render_d->args.zoom -= .05 * zoom;
	else if (button == 5)
		render_d->args.zoom += .05 * zoom;
	else
		zoom = 0;
	zoom2 = render_d->args.zoom;
	zoom = zoom * (1 - (2 * (button == 5)));
	render_d->args.movement_y += render_d->args.zoom_mov_x * zoom;
	render_d->args.movement_x += render_d->args.zoom_mov_x * zoom;
	return (0);
}

static int	close_hook(t_render_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

void	create_hooks(t_render_data *r_d)
{
	mlx_key_hook(r_d->win, key_hook, r_d);
	mlx_mouse_hook(r_d->win, mouse_hook, r_d);
	mlx_hook(r_d->win, 17, (1L << 17), close_hook, r_d);
}
