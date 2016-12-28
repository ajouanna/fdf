/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:22 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/28 16:35:07 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

/*
** affiche ma photo...
** en cas d'absence du fichier, affiche la transformation isometrique
*/

void	dummy_transform(t_context *c)
{
	int width;
	int heigth;

	c->img = mlx_xpm_file_to_image(c->mlx, MA_PHOTO, &width, &heigth);
	if (c->img == NULL)
	{
		mlx_string_put(c->mlx, c->win, 10, 50, c->map_color,
			"OOPS : ! Fichier manquant ?");
		sleep(1);
		isometric_transform(c);
	}
}

/*
** transforme la carte chargee en image parallele
*/

void	parallel_transform(t_context *c)
{
	isometric_transform(c);
}

/*
** theorie : pour transformer une referentieli 3D (x,y,z) en referentiel
** 2D (x',y'), on applique les formules decrites ici :
** https://fr.wikipedia.org/wiki/Perspective_axonom%C3%A9trique
*/

void	iso_point(t_context *context, int x, int y, int z, t_point *point)
{
	x *= context->ratio_xy;
	y *= context->ratio_xy;
	point->x = cos(context->omega) * x - sin(context->omega) * y;
	point->y = cos(context->alpha) * z * context->ratio_z -
	sin(context->alpha) * (sin(context->omega) * x + cos(context->omega) * y);
	point->x = context->width / 4 + point->x;
	point->y = -point->y;
	point->color = color(context, z);
}

/*
** transforme la carte chargee en image isometrique
*/

void	isometric_transform(t_context *context)
{
	int		y;
	int		x;
	t_point p1;
	t_point p2;

	y = -1;
	while (context->map[++y])
	{
		x = -1;
		while (context->map[y][++x] != END_LINE)
		{
			iso_point(context, x, y, context->map[y][x], &p1);
			if (context->map[y][x + 1] != END_LINE)
			{
				iso_point(context, x + 1, y, context->map[y][x + 1], &p2);
				img_draw_line(context, p1.x, p1.y, p2.x, p2.y, p1.color);
			}
			if (context->map[y + 1])
			{
				iso_point(context, x, y + 1, context->map[y + 1][x], &p2);
				img_draw_line(context, p1.x, p1.y, p2.x, p2.y, p1.color);
			}
			check_corner_point(context, &p1);
		}
	}
}

/*
** transforme la carte chargee en image conique
*/

void	conical_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 110, c->map_color,
	"Desole, la transformation conique n'est pas encore implementee...");
}
