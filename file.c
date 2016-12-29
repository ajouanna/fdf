/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:06:48 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/29 16:53:04 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
** agrandit un tableau d'int termine par un END_LINE et ajoute la
** ligne int_tab
*/

static int	realloc_tab(t_context *context, int *int_tab)
{
	int	**nouveau_tab;
	int	i;

	i = 0;
	while (context->map[i])
		i++;
	if ((nouveau_tab = malloc(sizeof(int *) * (i + 1 + 1))) == NULL)
		return (0);
	i = 0;
	while (context->map[i])
	{
		nouveau_tab[i] = context->map[i];
		i++;
	}
	free(context->map);
	nouveau_tab[i] = int_tab;
	nouveau_tab[i + 1] = NULL;
	context->map = nouveau_tab;
	return (1);
}

/*
** transforme un char ** en int * dont la derniere valeur est END_LINE
** FIX THIS : si END_LINE est une valeur lue dans le fichier, ca fausse tout...
*/

static int	*convert_to_tabint(char **tab)
{
	int i;
	int *res;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	res = malloc(sizeof(int) * (i + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		res[i] = ft_atoi(tab[i]);
		i++;
	}
	res[i] = END_LINE;
	return (res);
}

/*
** remplissage de la carte ligne par ligne
*/

static int	insert_line(t_context *context, char *line)
{
	char	**tab;
	int		*tab_int;
	int		res;

	if ((tab = ft_strsplit(line, ' ')) == NULL)
		return (0);
	if ((tab_int = convert_to_tabint(tab)) == NULL)
		return (0);
	res = realloc_tab(context, tab_int);
	free(tab);
	return (res);
}

/*
** verifier que la map respecte les caracteristiques attendues :
** toutes les lignes ont la meme largeur
*/

int			check_map(t_context *c)
{
	int i;
	int j;
	int first_pass;

	c->z_max = 0;
	c->z_min = 0;
	first_pass = 1;
	i = -1;
	while (c->map[++i])
	{
		j = -1;
		while (c->map[i][++j] != END_LINE)
		{
			c->z_max = (c->map[i][j] > c->z_max) ? c->map[i][j] : c->z_max;
			c->z_min = (c->map[i][j] < c->z_min) ? c->map[i][j] : c->z_min;
		}
		if (first_pass)
		{
			first_pass = 0;
			c->data_width = j;
		}
		else if (c->data_width != j)
			return (0);
	}
	return (1);
}

/*
** lecture du fichier contenant la carte
*/

int			read_file(char *filename, t_context *context)
{
	int		fd;
	char	*line;

	line = NULL;
	errno = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr(strerror(errno));
		ft_putchar('\n');
		return (0);
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (insert_line(context, line) == 0)
		{
			break ;
		}
	}
	close(fd);
	if (check_map(context) == 0)
	{
		ft_putstr("File  error: all lines should have same # points\n");
		return (0);
	}
	return (1);
}
