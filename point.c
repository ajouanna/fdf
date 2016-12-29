/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:22 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/29 15:47:25 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** theorie : pour transformer une referentieli 3D (x,y,z) en referentiel
** 2D (x',y'), on applique les formules decrites ici :
** https://fr.wikipedia.org/wiki/Perspective_axonom%C3%A9trique
*/

void		iso_point(t_context *context, t_3d_point *p_3d, t_point *point)
{
	int x;
	int y;
	int z;

	x = p_3d->x;
	y = p_3d->y;
	z = p_3d->z;
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
** utilitaire pour remplir un t_3d_point
*/

t_3d_point	*set_3d(t_3d_point *point, int x, int y, int z)
{
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}
