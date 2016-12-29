/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:55:33 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/29 15:39:49 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** cette fonction met a jour les 4 points extremes de l'image 2d
** dans un but de debugging
** Elle retourne toujours 1
*/

int	check_corner_point(t_context *context, t_point *point)
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
	return (1);
}
