/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:06:48 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/29 15:49:51 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <math.h>

# define DEFAULT_COLOR 0x00FFFFFF
# define DEFAULT_WIDTH  1600
# define DEFAULT_HEIGHT 700
# define DEFAULT_RATIO 5
# define MA_PHOTO "./tonio.xpm"
# define IMG_X 60
# define IMG_Y 70
# ifndef M_PI
#  define M_PI 3.14159
# endif
# define END_LINE -0xFFFF

/*
** definition des touches MACOS et LINUX
*/

# define MAC_LEFT_SHIFT 257
# define MAC_PLUS 69
# define LIN_PLUS 65451
# define MAC_RIGHT_SHIFT 258
# define MAC_MINUS 78
# define LIN_MINUS 65453
# define MAC_LEFT_ARROW 123
# define LIN_LEFT_ARROW 65361
# define MAC_UP_ARROW 126
# define LIN_UP_ARROW 65362
# define MAC_RIGHT_ARROW 124
# define LIN_RIGHT_ARROW 65363
# define MAC_DOWN_ARROW 125
# define LIN_DOWN_ARROW 65364
# define MAC_Q 12
# define LIN_Q 113
# define MAC_W 13
# define LIN_W 119
# define MAC_C 8
# define LIN_C 99
# define MAC_8_NUMPAD 91
# define LIN_8_NUMPAD 65431
# define MAC_2_NUMPAD 84
# define LIN_2_NUMPAD 65433
# define MAC_4_NUMPAD 86
# define LIN_4_NUMPAD 65430
# define MAC_6_NUMPAD 88
# define LIN_6_NUMPAD 65432
# define MAC_ESC 53
# define LIN_ESC 65307
# define MAC_1 18
# define LIN_1 38
# define MAC_2 19
# define LIN_2 233
# define MAC_QUESTION 46
# define LIN_QUESTION 44

typedef	enum	e_projection_type
{
	PARALLEL,
	ISOMETRIC,
	CONICAL,
	DUMMY
}				t_projection_type;

/*
** cette structure stocke un point en 2D et sa couleur
*/

typedef	struct	s_point
{
	double	x;
	double	y;
	int		color;
}				t_point;

/*
** cette structure stocke un point en 3D
*/

typedef	struct	s_3d_point
{
	int	x;
	int	y;
	int	z;
}				t_3d_point;

/*
** cette structure stocke l'environnement complet necessaire aux
** traitements
*/

typedef struct	s_context
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*img_data;
	int					img_bpp;
	int					img_size_line;
	int					img_endian;
	int					**map;
	int					img_x;
	int					img_y;
	int					map_color;
	t_projection_type	proj_type;
	int					width;
	int					height;
	double				ratio_xy;
	double				ratio_z;
	int					is_monochrome;
	t_point				img_upper;
	t_point				img_lower;
	t_point				img_leftest;
	t_point				img_rightest;
	double				alpha;
	double				omega;
	int					data_width;
	int					z_max;
	int					z_min;
}				t_context;

int				setup_mlx(t_context *context);
int				read_file(char *filename, t_context *context);
void			draw_square(t_context *c, int x, int y);
void			display_commands(t_context *context);
void			process_image(t_context *context);
void			reprocess_image(t_context *context);
void			img_pixel_put(t_context *context, int x, int y, int color);
void			img_draw_line(t_context *context, int x1, int y1, int x2,
					int y2, int color);
void			clear_image(t_context *context);
void			dummy_transform(t_context *c);
void			parallel_transform(t_context *c);
void			isometric_transform(t_context *c);
void			conical_transform(t_context *c);
int				check_corner_point(t_context *context, t_point *point);
int				color(t_context *context, int z);
int				handle_key(int keycode, void *param);
void			iso_point(t_context *context, t_3d_point *p_3d, t_point *point);
t_3d_point		*set_3d(t_3d_point *point, int x, int y, int z);
#endif
