/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:14:45 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/28 17:05:39 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** traitement de l'elevement expose
*/

int		expose_hook(void *param)
{
	t_context *context;

	context = (t_context *)param;
	mlx_clear_window(context->mlx, context->win);
	mlx_put_image_to_window(context->mlx,context->win,
		context->img, context->img_x, context->img_y);
	display_commands(context);
	return (1);
}

/*
** traitement des evenements souris : replacer l'image a la position
** initiale
*/

int		handle_mouse(int button, int x, int y, void *param)
{
	t_context *context = param;
	(void)button;
	(void)x;
	(void)y;
	context->img_x = IMG_X;
	context->img_y = IMG_Y;
	context->ratio_xy = (double)context->width/(double)context->data_width;
	context->ratio_xy /= 2;
	context->ratio_z = 1;
	reprocess_image(context);
	return (1);
}

/*
** initialise la librairie mlx et lance les traitements
** NB: par defaut, l'affichage est de type PARALLEL
** TBD : calculer la taille de la fenêtre en fonction du fichier de donnees
*/

int		setup_mlx(t_context *context)
{
	if ((context->mlx = mlx_init()) == NULL)
	{
		ft_putstr("mlx_init error\n");
		return (0);
	}
	context->proj_type = ISOMETRIC;
	context->width = DEFAULT_WIDTH;
	context->height = DEFAULT_HEIGHT;
	context->map_color = DEFAULT_COLOR;
	context->ratio_xy = (double)context->width/(double)context->data_width;
	context->ratio_xy /= 2;
	context->ratio_z = 1;
	context->img_x = IMG_X;
	context->img_y = IMG_Y;
	context->is_monochrome = 1;
	context->img_leftest.x = context->width / 4;
	context->img_leftest.y = 0;
	context->img_rightest.x = context->width / 2;
	context->img_rightest.y = 0;
	context->img_upper.x = 0;
	context->img_upper.y = context->height / 4;
	context->img_lower.x = 0;
	context->img_lower.y = context->height / 2;
	context->alpha = 2 * M_PI / 6;
	context->omega = M_PI / 6;
	context->win = mlx_new_window(context->mlx, context->width, context->height,
			"Antoine");
	context->img = mlx_new_image(context->mlx, context->width, context->height);
	context->img_data = mlx_get_data_addr(context->img, &(context->img_bpp),
		&(context->img_size_line), &(context->img_endian));
	process_image(context);
	mlx_put_image_to_window(context->mlx,context->win, context->img,
		context->img_x, context->img_y);
	mlx_key_hook(context->win, handle_key, context);
	mlx_mouse_hook(context->win, handle_mouse, context);
	mlx_expose_hook(context->win, expose_hook, context);
	display_commands(context);
	mlx_loop(context->mlx);
	return (1);
}
