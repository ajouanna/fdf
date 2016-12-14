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
** affiche ma photo...
*/

void	dummy_transform(t_context *c)
{
	int width;
	int heigth;

	mlx_string_put(c->mlx, c->win, 10, 40, c->map_color,
	"Tu veux ma photo ?");
	c->img = mlx_xpm_file_to_image(c->mlx, MA_PHOTO, &width, &heigth);
	if (c->img == NULL)
		mlx_string_put(c->mlx, c->win, 10, 40, c->map_color,
			"OOPS : ! Fichier manquant ?");
}

/*
** transforme la carte chargee en image parallele
*/

void	parallel_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 40, c->map_color,
	"Desole, la transformation parallele n'est pas encore implementee...");
}

/*
** theorie : pour transformer une referentieli 3D (x,y,z) en referentiel
** 2D (x',y'), on applique ces formules :
** x' = rac(2)/2(x -y) = 0,707 (x-y)
** y' = rac(2/3) z - 1/rac(6) (x + y) = 0,816 z -0,408 (x+y)
** FIX THIS : mettre une couleur qui a du sens...
*/

void	iso_point(t_context *context, int x, int y, int z, t_point *point)
{
	x *= context->ratio;
	y *= context->ratio;
	point->x = 10 + 0.707 *(x - y);
	point->y = 10 + 0.816 * z -0.408 * (x + y);
	point->color = z;
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

	mlx_string_put(context->mlx, context->win, 10, 40, context->map_color,
	"Transformation isometrique");
	y = -1;
	while (context->map[++y])
	{
		x = 0;
		while (context->map[y][x] >= 0)
		{
			if (context->map[y][x+1] >= 0)
			{
				iso_point(context, x, y, context->map[y][x], &p1);
				iso_point(context, x + 1, y, context->map[y][x + 1], &p2);
				img_draw_line(context, p1.x, p1.y,
							p2.x, p2.y,
							context->map_color);
			}
			x++;
		}
	}
}

/*
** transforme la carte chargee en image conique
*/

void	conical_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 40, c->map_color,
	"Desole, la transformation conique n'est pas encore implementee...");
}
