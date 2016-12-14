/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:14:45 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/12 17:21:04 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** traitement de l'image
** Cette fonction doit etre appelee a chaque fois qu'on change qque chose
** a l'image.
** A CODER
*/

void		process_image(t_context *context)
{
	if (context->proj_type == DUMMY)
		dummy_transform(context);
	else if (context->proj_type == CONICAL)
		conical_transform(context);
	else if (context->proj_type == PARALLEL)
		parallel_transform(context);
	else if (context->proj_type == ISOMETRIC)
		isometric_transform(context);
}

/*
** efface l'image, relance le traitement et reaffiche les commandes
*/

void		reprocess_image(t_context *context)
{
	mlx_clear_window(context->mlx, context->win);
	clear_image(context);
	process_image(context);
	mlx_put_image_to_window(context->mlx,context->win, context->img,
	        context->img_x, context->img_y);
	display_commands(context);
}
