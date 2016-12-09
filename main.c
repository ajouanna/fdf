/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:08:49 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/09 17:41:00 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"

/*
** dessine un carre a la position fournie
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
			mlx_pixel_put(c->mlx, c->win, xx, yy, 0x00FF00FF);
			xx++;
		}
		yy++;
	}
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
** enchainement des traitements
*/

int		main()
{
	t_context context;

	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, 400, 400, "Antoine");
	mlx_key_hook(context.win, handle_key, &context);
	mlx_mouse_hook(context.win, handle_mouse, &context);
	mlx_loop(context.mlx);
}
