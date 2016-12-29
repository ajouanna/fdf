/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 17:03:47 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/28 17:26:47 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** traitement de plus de touches
** je teste les touches macos et linux
** FIX THIS : lister les codes touches dans ce commentaire plutot que dans le code
*/

void		more_keys(int keycode, t_context *context)
{
	if ((keycode == MAC_LEFT_SHIFT) || (keycode == MAC_PLUS) || (keycode == LIN_PLUS))
	{
		context->ratio_xy += 0.5;
	}
	if ((keycode == MAC_RIGHT_SHIFT) || (keycode == MAC_MINUS) || (keycode == LIN_MINUS))
	{
		context->ratio_xy -= 0.5;
		if (context->ratio_xy <= 0)
			context->ratio_xy = 1;
	}
	if ((keycode == MAC_LEFT_ARROW) || (keycode == LIN_LEFT_ARROW))
	{
		context->img_x -=10;
		if (context->img_x <= 0)
			context->img_x = 0;
	}
	if ((keycode == MAC_UP_ARROW) || (keycode == LIN_UP_ARROW))
	{
		context->img_y -=10;
		if (context->img_y <= 0)
			context->img_y = 0;
	}
}

/*
** traitement de plus de touches
** je teste les touches macos et linux
*/

void		still_more_keys(int keycode, t_context *context)
{
	if ((keycode == MAC_RIGHT_ARROW) || (keycode == LIN_RIGHT_ARROW))
	{
		context->img_x +=10;
		if (context->img_x >= context->width)
			context->img_x = context->width;
	}
	if ((keycode == MAC_DOWN_ARROW) || (keycode == LIN_DOWN_ARROW))
	{
		context->img_y +=10;
		if (context->img_y >= context->height)
			context->img_y = context->height;
	}
	if ((keycode == MAC_Q) || (keycode == LIN_Q))
		context->ratio_z += 0.5;
	if ((keycode == MAC_W) || (keycode == LIN_W))
	{
		context->ratio_z -= 0.5;
		if (context->ratio_z <= 0)
			context->ratio_z = 1;
	}
	if ((keycode == MAC_C) || (keycode == LIN_C))
		context->is_monochrome = (context->is_monochrome == 0) ? 1 : 0;
}

/*
** traitement de plus de touches
** je teste les touches macos et linux
*/

void		yet_more_keys(int keycode, t_context *context)
{
	if ((keycode == MAC_8_NUMPAD) || (keycode == LIN_8_NUMPAD))
	{
		context->omega += M_PI/12;
	}
	if ((keycode == MAC_2_NUMPAD) || (keycode == LIN_2_NUMPAD))
	{
		context->omega -= M_PI/12;
	}
	if ((keycode == MAC_4_NUMPAD) || (keycode == LIN_4_NUMPAD))
	{
		context->alpha += M_PI/12;
		if (context->alpha > M_PI/2)
			context->alpha = M_PI/2;
	}
	if ((keycode == MAC_6_NUMPAD) || (keycode == LIN_6_NUMPAD))
	{
		context->alpha -= M_PI/12;
		if (context->alpha <= 0)
			context->alpha = 0;
	}
}

/*
** traitement des evenements clavier
** NB : je n'appelle pas la transfo conique car pas implementee
*/

int		handle_key(int keycode, void *param)
{
	t_context *context = param;
	ft_putstr("key pressed : ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if ((keycode == MAC_ESC) || (keycode == LIN_ESC))
		exit(0);
	if ((keycode == MAC_1) || (keycode == LIN_1))
	{
		context->proj_type = PARALLEL;
		context->omega = M_PI / 4;
	}
	if ((keycode == MAC_2) || (keycode == LIN_2))
	{
		context->proj_type = ISOMETRIC;
		context->omega = M_PI / 6;
	}
	if ((keycode == MAC_QUESTION) || (keycode == LIN_QUESTION))
	{
		context->proj_type = DUMMY;
	}
	more_keys(keycode, context);
	still_more_keys(keycode, context);
	yet_more_keys(keycode, context);
	reprocess_image(context);
	return (1);
}
