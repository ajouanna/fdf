/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:22 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/12 17:19:26 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** transforme la carte chargee en image a plat
*/

void	flat_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 30, c->map_color,
	"Desole, la transformation plate n'est pas encore implementee...");
}

/*
** transforme la carte chargee en image parallele
*/

void	parallel_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 30, c->map_color,
	"Desole, la transformation parallele n'est pas encore implementee...");
}

/*
** transforme la carte chargee en image isometrique
** theorie : pour transformer une referentieli 3D (x,y,z) en referentiel
** 2D (x',y'), on applique ces formules :
** x' = rac(2)/2(x -y) = 0,707 (x-y)
** y' = rac(2/3) z - 1/rac(6) (x + y) = 0,816 z -0,408 (x+y)
*/

void	isometric_transform(t_context *context)
{
	int y;
	int x;
	int z;
	double xx;
	double yy;

	mlx_string_put(context->mlx, context->win, 10, 30, context->map_color,
	"Transformation isometrique");
	y = -1;
	while (context->map[++y])
	{
		x = 0;
		while (context->map[y][x] >= 0)
		{
			z = context->map[y][x];
			xx = 10 + 0.707 *(x - y);
			yy = 10 + 0.816 * z -0.408 * (x + y);
			img_pixel_put(context, xx, yy, context->map_color);
			x++;
		}
	}
}

/*
** transforme la carte chargee en image conique
*/

void	conical_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 30, c->map_color,
	"Desole, la transformation conique n'est pas encore implementee...");
}
