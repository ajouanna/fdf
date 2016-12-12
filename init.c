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
	mlx_put_image_to_window(context->mlx,context->win, context->image, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	display_commands(context);
	return (1);
}

/*
** traitement des evenements clavier
*/

int		handle_key(int keycode, void *param)
{
	ft_putstr("key pressed : ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	(void)param;
	if (keycode == 53)
		exit(0);
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
*/

int		setup_mlx(t_context *context)
{
	if ((context->mlx = mlx_init()) == NULL)
	{
		ft_putstr("mlx_init error\n");
		return (0);
	}
	context->proj_type = PARALLEL;
	context->win = mlx_new_window(context->mlx, DEFAULT_WIDTH, DEFAULT_HEIGHT,
			"Antoine");
	context->image = mlx_new_image(context->mlx, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	process_image(context);
	mlx_put_image_to_window(context->mlx,context->win, context->image, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	mlx_key_hook(context->win, handle_key, context);
	mlx_mouse_hook(context->win, handle_mouse, context);
	mlx_expose_hook(context->win, expose_hook, context);
	display_commands(context);
	mlx_loop(context->mlx);
	return (1);
}
