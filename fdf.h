/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:06:48 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/09 17:08:42 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"

/*
** cette structure stocke l'environnement complet necessaire aux
** traitements
*/

typedef struct	s_context
{
	void	*mlx;
	void	*win;
	int	**map;
	int	map_color;
}				t_context;

int	read_file(char *filename, t_context *context);
#endif
