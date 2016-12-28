/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 16:00:02 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/28 17:32:47 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** calcule la couleur selon les parametres suivants :
** z = valeur de la hauteur
*/

int	color(t_context *c, int z)
{
	double ratio;

	if (c->is_monochrome)
		return (c->map_color);
	else
	{
		ratio = (double)(z - c->z_min) / (double)(c->z_max - c->z_min);
		if (ratio <= 0.25)
			return (0x00000FF0);
		if (ratio > 0.25 && ratio <= 0.50)
			return (0x0000FF00);
		if (ratio > 0.50 && ratio <= 0.75)
			return (0x00555550);
		if (ratio > 0.75)
			return (0x00FFFFFF);
		return (c->map_color);
	}
}
