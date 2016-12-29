/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:22 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/29 16:33:38 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** efface le contenu de l'image
*/

void	clear_image(t_context *context)
{
	mlx_destroy_image(context->mlx, context->img);
	context->img = mlx_new_image(context->mlx, context->width, context->height);
	context->img_data = mlx_get_data_addr(context->img, &(context->img_bpp),
		&(context->img_size_line), &(context->img_endian));
}

/*
** positionne un pixel dans l'image a la position x,y si cette position
** est dans l'image
** FIX THIS : je devrais tenir compte de context->endian pour afficher la
** couleur
*/

void	img_pixel_put(t_context *context, int x, int y, int color)
{
	int		pos;

	if (x >= 0 && x < context->width && y >= 0 && y < context->height)
	{
		pos = (x * context->img_bpp / 8) + (y * context->img_size_line);
		context->img_data[pos] = color % 256;
		context->img_data[pos + 1] = (color >> 8) % 256;
		context->img_data[pos + 2] = (color >> 16) % 256;
	}
}

/*
** echqnge les contenus de 2 t_point
*/

void	swap(t_point *p1, t_point *p2)
{
	double	swap;
	int		i;

	swap = p1->x;
	p1->x = p2->x;
	p2->x = swap;
	swap = p1->y;
	p1->y = p2->y;
	p2->y = swap;
	i = p1->color;
	p1->color = p2->color;
	p2->color = i;
}

/*
** trace une droite verticale
*/

void	draw_vertical(t_context *context, t_point *p1, t_point *p2)
{
	int i;
	int color;

	color = p1->color;
	if (p1->y > p2->y)
	{
		swap(p1, p2);
	}
	i = p1->y;
	while (i <= p2->y)
	{
		img_pixel_put(context, p1->x, i, color);
		i++;
	}
}

/*
** trace une droite d'un point a un autre
** y = a*x + b
*/

void	img_draw_line(t_context *c, t_point *p1, t_point *p2)
{
	double	a;
	double	b;
	int		i;
	int		color;

	if (p1->x == p2->x)
	{
		draw_vertical(c, p1, p2);
		return ;
	}
	color = p1->color;
	if (p1->x > p2->x)
	{
		swap(p1, p2);
	}
	a = (p2->y - p1->y) / (p2->x - p1->x);
	b = p2->y - a * p2->x;
	i = p1->x - 1;
	while (++i <= p2->x)
		img_pixel_put(c, i, (a * i + b), color);
}
