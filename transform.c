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
#include <unistd.h>

/*
** affiche ma photo...
** en cas d'absence du fichier, affiche la transformation isometrique
*/

void	dummy_transform(t_context *c)
{
	int width;
	int heigth;

	mlx_string_put(c->mlx, c->win, 10, 50, c->map_color,
	"Tu veux ma photo ?");
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
** calcule la couleur selon les parametres suivants :
** z = valeur de la hauteur
*/

int	color(t_context *context, int z)
{
	double ratio;

	if (context->is_monochrome)
		return (context->map_color);
	else
	{
		ratio = (double)(z - context->z_min)/(double)(context->z_max - context->z_min);
		if (ratio <= 0.25)
			return (0x00000FF0);
		if (ratio > 0.25 && ratio <= 0.50)
			return (0x0000FF00);
		if (ratio > 0.50 && ratio <= 0.75)
			return (0x00555550);
		if (ratio > 0.75)
			return (0x00FFFFFF);
		return (context->map_color); 
	}
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
	point->x = context->width /2 + point->x;
	point->y = - point->y;
	point->color = color(context, z);
}

/*
** détermine les points extremes de l'image
*/

void	check_corner_point(t_context *context, t_point *point)
{
	if (point->x < context->img_leftest.x)
	{
		context->img_leftest.x = point->x;
		context->img_leftest.y = point->y;
	}
	if (point->y < context->img_upper.y)
	{
		context->img_upper.x = point->x;
		context->img_upper.y = point->y;
	}
	if (point->x > context->img_rightest.x)
	{
		context->img_rightest.x = point->x;
		context->img_rightest.y = point->y;
	}
	if (point->y > context->img_lower.y)
	{
		context->img_lower.x = point->x;
		context->img_lower.y = point->y;
	}
}

/*
** transforme la carte chargee en image isometrique
*/

void	isometric_transform(t_context *context)
{
	int y;
	int x;
	t_point p1;
	t_point p2;

	y = -1;
	while (context->map[++y])
	{
		x = 0;
		while (context->map[y][x] != END_LINE)
		{
			iso_point(context, x, y, context->map[y][x], &p1);
			if (context->map[y][x+1] >= 0)
			{
				iso_point(context, x + 1, y, context->map[y][x + 1], &p2);
				img_draw_line(context, p1.x, p1.y,
							p2.x, p2.y, p1.color);
			}
			if (context->map[y+1])
			{
				iso_point(context, x, y + 1, context->map[y + 1][x], &p2);
				img_draw_line(context, p1.x, p1.y,
							p2.x, p2.y, p1.color);
					
			}
			check_corner_point(context, &p1);
			x++;
		}
	}
}

/*
** transforme la carte chargee en image conique
*/

void	conical_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 50, c->map_color,
	"Desole, la transformation conique n'est pas encore implementee...");
}
