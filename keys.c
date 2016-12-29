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
	if ((keycode == 257) || (keycode == 69) || (keycode == 65451)) // shft gauche ou + du pave numerique
	{
		context->ratio_xy += 0.5;
	}
	if ((keycode == 258) || (keycode == 78) || (keycode == 65453)) // shft droite ou - du pave numerique
	{
		context->ratio_xy -= 0.5;
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
}

/*
** traitement de plus de touches
** je teste les touches macos et linux
*/

void		still_more_keys(int keycode, t_context *context)
{
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
	if ((keycode == 12) || (keycode == 113)) // Q pour agrandir la hauteur
		context->ratio_z += 0.5;
	if ((keycode == 13) || (keycode == 119)) // W pour diminuer la hauteur
	{
		context->ratio_z -= 0.5;
		if (context->ratio_z <= 0)
			context->ratio_z = 1;
	}
	if ((keycode == 8) || (keycode == 99)) // C pour couleur
		context->is_monochrome = (context->is_monochrome == 0) ? 1 : 0;
}

/*
** traitement de plus de touches
** je teste les touches macos et linux
*/

void		yet_more_keys(int keycode, t_context *context)
{
	if ((keycode == 91) || (keycode == 65431)) // 8 du pave pour augm omega
	{
		context->omega += M_PI/12;
	}
	if ((keycode == 84) || (keycode == 65433)) // 2 du pave pour dim ommega
	{
		context->omega -= M_PI/12;
	}
	if ((keycode == 86) || (keycode == 65430)) // 4 du pave pour augm alpha
	{
		context->alpha += M_PI/12;
		if (context->alpha > M_PI/2)
			context->alpha = M_PI/2;
	}
	if ((keycode == 88) || (keycode == 65432)) // 6 du pave pour dim alpha
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
	if ((keycode == 53) || (keycode == 65307)) // ESC
		exit(0);
	if ((keycode == 18) || (keycode == 38)) // touche 1
	{
		context->proj_type = PARALLEL;
		context->omega = M_PI / 4;
	}
	if ((keycode == 19) || (keycode == 233)) // touche 2
	{
		context->proj_type = ISOMETRIC;
		context->omega = M_PI / 6;
	}
	if ((keycode == 46) || (keycode == 44)) // touche ?
	{
		context->proj_type = DUMMY;
	}
	more_keys(keycode, context);
	still_more_keys(keycode, context);
	yet_more_keys(keycode, context);
	reprocess_image(context);
	return (1);
}
