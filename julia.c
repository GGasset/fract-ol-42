/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:57:08 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/10 13:12:45 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	construct(t_julia *this)
{
	int		r_provided;
	double	i;

	if (!this->cx)
		this->cx = -.835;
	if (!this->cy)
		this->cy = .2321;
	if (!this->n)
		this->n = 2;
	r_provided = this->r != 0;
	if (!r_provided)
		this->r = sqrt(this->cx * this->cx + this->cy * this->cy);
	i = 0;
	while (i * i - i < this->r && !r_provided)
		i++;
	if (!r_provided)
		this->r = i;
}

static int	get_color(size_t i, t_args args, t_julia vs)
{
	int		r;
	int		g;
	int		b;
	float	percent;

	if (i == args.max_i)
		return (0xFFFFFFFF);
	i = i + 1;
	i -= log(log(vs.zx * vs.zx + vs.zy * vs.zy)) / log(vs.n);
	percent = i / (float)args.max_i;
	b = (int)(percent * 200) + 55;
	g = (int)(percent * 200) + 42;
	r = (int)(percent * 170) + 36;
	return ((255 << 24) + (r << 16) + (g << 8) + b);
}

int	get_julia(int x, int y, t_render_data *data, t_julia vs)
{
	size_t	i;

	vs.zx = (x / (double)data->img.res.x) * data->args.zoom * 2 * vs.r - vs.r;
	vs.zx += data->args.movement_x;
	vs.zy = (y / (double)data->img.res.y) * data->args.zoom * 2 * vs.r - vs.r;
	vs.zy += data->args.movement_y;
	i = 0;
	while (vs.zx * vs.zx + vs.zy * vs.zy < vs.r * vs.r && i < data->args.max_i)
	{
		vs.x_tmp = vs.zx * vs.zx - vs.zy * vs.zy;
		vs.zy = 2 * vs.zx * vs.zy + vs.cy;
		vs.zx = vs.x_tmp + vs.cx;
		i++;
	}
	return (get_color(i, data->args, vs));
}
