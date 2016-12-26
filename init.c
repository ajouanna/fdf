/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:14:45 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/12 17:21:04 by ajouanna         ###   ########.fr       */
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
** traitement de plus de touches
** je teste les touches macos et linux
** FIX THIS : lister les codes touches dans ce commentaire plutot que dans le code
*/
void		more_keys(int keycode, t_context *context)
{
	if ((keycode == 257) || (keycode == 65451)) // shft gauche ou + du pave numerique
	{
		context->ratio_xy *= 2;
	}
	if ((keycode == 258) || (keycode == 65453)) // shft droite ou - du pave numerique
	{
		context->ratio_xy /= 2;
		if (context->ratio_xy <= 0)
			context->ratio_xy = 1;
	}
	if ((keycode == 123) || (keycode == 65361)) // fleche gauche
	{
		context->img_x -=10;
		if (context->img_x <= 0)
			context->img_x = 0;
	}
	if ((keycode == 126) || (keycode == 65362)) // fleche haute
	{
		context->img_y -=10;
		if (context->img_y <= 0)
			context->img_y = 0;
	}
	if ((keycode == 124) || (keycode == 65363)) //fleche droite
	{
		context->img_x +=10;
		if (context->img_x >= context->width)
			context->img_x = context->width;
	}
	if ((keycode == 125) || (keycode == 65364)) //fleche basse
	{
		context->img_y +=10;
		if (context->img_y >= context->height)
			context->img_y = context->height;
	}
	if ((keycode == 0) || (keycode == 113)) // Q pour agrandir la hauteur
	{
		context->ratio_z *= 2;
	}
	if ((keycode == 6) || (keycode == 119)) // W pour diminuer la hauteur
	{
		context->ratio_z /= 2;
		if (context->ratio_z <= 0)
			context->ratio_z = 1;
	}
	if ((keycode == 41) || (keycode == 109)) // M pour monochrome
	{
		context->is_monochrome = 1;
	}
	if ((keycode == 8) || (keycode == 99)) // C pour couleur
	{
		context->is_monochrome = 0;
	}
	if ((keycode == 12) || (keycode == 65430)) // 4 du pave pour augm alpha FIX THIS mettre la bonne valeurpour mac
	{
		context->alpha += M_PI/12;
		if (context->alpha > M_PI/2)
			context->alpha = M_PI/2;
	}
	if ((keycode == 14) || (keycode == 65432)) // 6 du pave pour dim alpha FIX THIS mettre la bonne valeurpour mac
	{
		context->alpha -= M_PI/12;
		if (context->alpha <= 0)
			context->alpha = 0;
	}
	if ((keycode == 13) || (keycode == 65431)) // 8 du pave pour augm omega FIX THIS mettre la bonne valeurpour mac
	{
		context->omega += M_PI/12;
		if (context->omega > M_PI/2)
			context->omega = M_PI/2;
	}
	if ((keycode == 1) || (keycode == 65433)) // 2 du pave pour dim ommega FIX THIS mettre la bonne valeurpour mac
	{
		context->omega -= M_PI/12;
		if (context->omega <= 0)
			context->omega = 0;
	}
}

/*
** traitement des evenements clavier
** FIX THIS : mettre les codes de touche mac
*/

int		handle_key(int keycode, void *param)
{
	t_context *context = param;
	ft_putstr("key pressed : ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if ((keycode == 53) || (keycode == 65307)) // ESC
		exit(0);
	if ((keycode == 18) || (keycode == 38)) // touche 1
	{
		context->proj_type = PARALLEL;
	}
	if ((keycode == 19) || (keycode == 233)) // touche 2
	{
		context->proj_type = ISOMETRIC;
	}
	if ((keycode == 20) || (keycode == 34)) // touche 3
	{
		context->proj_type = CONICAL;
	}
	if ((keycode == 46) || (keycode == 44)) // touche ?
	{
		context->proj_type = DUMMY;
	}
	more_keys(keycode, context);
	reprocess_image(context);
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
	context->alpha = M_PI / 5;
	context->omega = M_PI / 4;
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
