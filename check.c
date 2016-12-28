/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:55:33 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/28 17:30:45 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
