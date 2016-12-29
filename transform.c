/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:22 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/29 16:34:13 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

/*
** affiche ma photo...
** en cas d'absence du fichier, affiche la transformation isometrique
*/

void		dummy_transform(t_context *c)
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

void		parallel_transform(t_context *c)
{
	isometric_transform(c);
}

/*
** transforme la carte chargee en image isometrique
** NB : l appel a check_corner_point ne sert qu'a debugguer
*/

void		isometric_transform(t_context *c)
{
	int			y;
	int			x;
	t_point		p1;
	t_point		p2;
	t_3d_point	p_3d;

	y = -1;
	while (c->map[++y])
	{
		x = -1;
		while (c->map[y][++x] != END_LINE)
		{
			iso_point(c, set_3d(&p_3d, x, y, c->map[y][x]), &p1);
			if (check_corner_point(c, &p1) && (c->map[y][x + 1] != END_LINE))
			{
				iso_point(c, set_3d(&p_3d, x + 1, y, c->map[y][x + 1]), &p2);
				img_draw_line(c, &p1, &p2);
			}
			if (c->map[y + 1])
			{
				iso_point(c, set_3d(&p_3d, x, y + 1, c->map[y + 1][x]), &p2);
				img_draw_line(c, &p1, &p2);
			}
		}
	}
}

/*
** transforme la carte chargee en image conique
*/

void		conical_transform(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 110, c->map_color,
	"Desole, la transformation conique n'est pas encore implementee...");
}
