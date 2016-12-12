/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:06:48 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/12 17:17:55 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"

# define DEFAULT_COLOR 0x00FF00FF
# define DEFAULT_WIDTH  800
# define DEFAULT_HEIGHT 400

/*
** cette structure stocke l'environnement complet necessaire aux
** traitements
*/

typedef struct	s_context
{
	void	*mlx;
	void	*win;
	int		**map;
	int		map_color;
}				t_context;

int				setup_mlx(t_context *context);
int				read_file(char *filename, t_context *context);
void			draw_square(t_context *c, int x, int y);
void			display_commands(t_context *context);

#endif
