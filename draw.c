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
** dessine un carre a la position fournie dans la fenetre
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
** affiche les parametres
*/

void	display_params(t_context *context)
{
	char *str;

	str = ft_itoa(context->ratio_xy);
	mlx_string_put(context->mlx, context->win, 10, context->height - 20, context->map_color,
			"Ratio plan : ");
	mlx_string_put(context->mlx, context->win, 150, context->height - 20, context->map_color,
			str);
	free(str);
	str = ft_itoa(context->ratio_z);
	mlx_string_put(context->mlx, context->win, 10, context->height - 10, context->map_color,
			"Ratio vertical : ");
	mlx_string_put(context->mlx, context->win, 150, context->height - 10, context->map_color,
			str);
	free(str);
}

/*
** affiche les commandes dans la fenetre
*/

void	display_commands(t_context *context)
{
	mlx_string_put(context->mlx, context->win, 10, 10, context->map_color,
			"Pour quitter, tapez ESC; Pour zoomer, tapez + ou - ; Monochrome, tapez m ; Couleur, tapez c ; deplacer l'image dans la fenetre, tapez les fleches");
	mlx_string_put(context->mlx, context->win, 10, 20, context->map_color,
			"1 a 3  : transformations parallele, iso, conique ; 2, 4, 6 et 8 du pave num : changer les angles de vue ; clic : repositionner l image a sa position initiale");
	mlx_string_put(context->mlx, context->win, 10, 30, context->map_color,
			"? : A propos");
	display_params(context);
}

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
** trace une droite verticale
*/
void	draw_vertical(t_context *context, int x, int y1, int y2, int color)
{
	int i;

	if (y1 > y2)
	{
		i = y1;
		y1 = y2;
		y2 = i;
	}
	i = y1;
	while (i <= y2)
	{
		img_pixel_put(context, x, i, color);
		i++;
	}
}

/*
** trace une droite d'un point a un autre
** y = a*x + b
*/

void	img_draw_line(t_context *context, int x1, int y1, int x2, int y2, int color)
{
	double a;
	double b;
	int i;

	if (x1 == x2)
	{
		draw_vertical(context, x1, y1, y2, color);
		return ;
	}
	if (x1 > x2)
	{
		i = x1;
		x1 = x2;
		x2 = i;
		i = y1;
		y1 = y2;
		y2 = i;
	}
	a = (double)(y2 - y1)/(double)(x2 - x1);
	b = y2 - a * x2;

	i = x1;
	while (i <= x2)
	{
		img_pixel_put(context, i, (a * i + b), color);
		i++;
	}
}
