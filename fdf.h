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

typedef		enum
{
	PARALLEL,
	ISOMETRIC,
	CONICAL,
	FLAT
}		e_projection_type;

/*
** cette structure stocke l'environnement complet necessaire aux
** traitements
*/

typedef struct	s_context
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int		img_bpp;
	int		img_size_line;
	int		img_endian;
	int			**map;
	int		map_color;
	e_projection_type	proj_type;
	int		width;
	int		height;
}				t_context;

int				setup_mlx(t_context *context);
int				read_file(char *filename, t_context *context);
void			draw_square(t_context *c, int x, int y);
void			display_commands(t_context *context);
void			process_image(t_context *context);
void			reprocess_image(t_context *context);
void			img_pixel_put(t_context *context, int x, int y, int color);
void			flat_transform(t_context *c);
void			parallel_transform(t_context *c);
void			isometric_transform(t_context *c);
void			conical_transform(t_context *c);
#endif
