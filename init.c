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
*/
void		more_keys(int keycode, t_context *context)
{
	if ((keycode == 65451) || (keycode == 65451))
	{
		context->ratio_xy += 1;
	}
	if ((keycode == 65453) || (keycode == 65453))
	{
		context->ratio_xy -= 1;
		if (context->ratio_xy <= 0)
			context->ratio_xy -= 1;
	}
	if ((keycode == 65361) || (keycode == 65361))
	{
		context->img_x -=10;
		if (context->img_x <= 0)
			context->img_x = 0;
	}
	if ((keycode == 65362) || (keycode == 65362))
	{
		context->img_y -=10;
		if (context->img_y <= 0)
			context->img_y = 0;
	}
	if ((keycode == 65363) || (keycode == 65363))
	{
		context->img_x +=10;
		if (context->img_x >= context->width)
			context->img_x = context->width;
	}
	if ((keycode == 65364) || (keycode == 65364))
	{
		context->img_y +=10;
		if (context->img_y >= context->height)
			context->img_y = context->height;
	}
	if ((keycode == 113) || (keycode == 113)) // Q pour agrandir la hauteur
	{
		context->ratio_z++;
	}
	if ((keycode == 119) || (keycode == 119)) // W pour diminuer la hauteur
	{
		context->ratio_z--;
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
	if ((keycode == 53) || (keycode == 65307))
		exit(0);
	if ((keycode == 38) || (keycode == 38))
	{
		context->proj_type = PARALLEL;
	}
	if ((keycode == 233) || (keycode == 233))
	{
		context->proj_type = ISOMETRIC;
	}
	if ((keycode == 34) || (keycode == 34))
	{
		context->proj_type = CONICAL;
	}
	if ((keycode == 44) || (keycode == 44))
	{
		context->proj_type = DUMMY;
	}
	more_keys(keycode, context);
	reprocess_image(context);
	return (1);
}

/*
** traitement des evenements souris
*/

int		handle_mouse(int button, int x, int y, void *param)
{
	ft_putstr("mouse button clicked : ");
	ft_putnbr(button);
	ft_putstr(" x = ");
	ft_putnbr(x);
	ft_putstr(" y = ");
	ft_putnbr(y);
	ft_putchar('\n');
	draw_square(param, x, y);
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
	context->ratio_xy = DEFAULT_RATIO;
	context->ratio_z = 1;
	context->img_x = IMG_X;
	context->img_y = IMG_Y;
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
