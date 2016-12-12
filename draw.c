/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:22 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/12 17:19:26 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** dessine un carre a la position fournie
*/

void	draw_square(t_context *c, int x, int y)
{
	int xx;
	int yy;
	int size;

	size = 50;
	yy = y;
	while (yy < y + size)
	{
		xx = x;
		while (xx < x + size)
		{
			mlx_pixel_put(c->mlx, c->win, xx, yy, c->map_color);
			xx++;
		}
		yy++;
	}
}

/*
** affiche les commandes dans la fenetre
*/

void	display_commands(t_context *context)
{
	mlx_string_put(context->mlx, context->win, 10, 10, context->map_color,
			"Pour quitter, tapez ESC");
	mlx_string_put(context->mlx, context->win, 10, 20, context->map_color,
			"Cliquez n importe ou !");
}
