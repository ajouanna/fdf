/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:22 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/29 17:07:54 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** affiche les parametres
** FIX THIS : ft_itoa convertit in entier en chaine. Si je lui passe un double,
** c est la partie entiere du double qui sera prise en compte, d ou un affichage
** tronque
*/

void	display_params(t_context *c)
{
	char *str;

	str = ft_itoa(c->ratio_xy);
	mlx_string_put(c->mlx, c->win, 10, c->height - 30, c->map_color,
			"Ratio plan : ");
	mlx_string_put(c->mlx, c->win, 150, c->height - 30, c->map_color, str);
	free(str);
	str = ft_itoa(c->ratio_z);
	mlx_string_put(c->mlx, c->win, 300, c->height - 30, c->map_color,
			"Ratio vertical : ");
	mlx_string_put(c->mlx, c->win, 450, c->height - 30, c->map_color, str);
	free(str);
	str = ft_itoa(c->alpha * 180 / M_PI);
	mlx_string_put(c->mlx, c->win, 10, c->height - 20, c->map_color,
			"Alpha (deg): ");
	mlx_string_put(c->mlx, c->win, 150, c->height - 20, c->map_color, str);
	free(str);
	str = ft_itoa(c->omega * 180 / M_PI);
	mlx_string_put(c->mlx, c->win, 300, c->height - 20, c->map_color,
			"Omega (deg): ");
	mlx_string_put(c->mlx, c->win, 450, c->height - 20, c->map_color, str);
	free(str);
}

/*
** affiche les commandes dans la fenetre
*/

void	display_commands(t_context *c)
{
	mlx_string_put(c->mlx, c->win, 10, 10, c->map_color,
		"Quitter, tapez ESC; Zoomer, tapez + ou - ; Couleur/Mono, tapez c");
	mlx_string_put(c->mlx, c->win, 10, 25, c->map_color,
		"Deplacer l'image dans la fenetre, tapez les fleches");
	mlx_string_put(c->mlx, c->win, 10, 40, c->map_color,
		"Augmenter/diminuer altitude , tapez Q/W");
	mlx_string_put(c->mlx, c->win, 10, 55, c->map_color,
		"1 : transformations parallele, 2: transformation isomorphique");
	mlx_string_put(c->mlx, c->win, 10, 70, c->map_color,
		"2, 4, 6 et 8 du pave num : changer les angles de vue");
	mlx_string_put(c->mlx, c->win, 10, 85, c->map_color,
		"Clic : repositionner l image a sa position initiale");
	mlx_string_put(c->mlx, c->win, 10, 100, c->map_color,
		"? : A propos");
	display_params(c);
}
