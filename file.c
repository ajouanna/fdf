/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:06:48 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/09 17:08:42 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


/*
** agrandit un tableau d'int termine par un -1 et ajoute la
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
** transforme un char ** en int * dont la derniere valeur est -1
*/

int	*convert_to_tabint( char **tab)
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
	res[i] = -1;
	return (res);	
}

/*
** remplissage de la carte ligne par ligne
*/

int	insert_line(t_context *context, char *line)
{
	char	**tab;
	int	*tab_int;
	int	res;

	if ((tab = ft_strsplit(line, ' ')) == NULL)
		return (0);
	if ((tab_int = convert_to_tabint(tab)) == NULL)
		return (0);
	res = realloc_tab(context, tab_int); 
	free(tab);
	return (res);
}

/*
** lecture du fichier contenant la carte
*/

int	read_file(char *filename, t_context *context)
{
	int fd;
	char *line;

	line = NULL;
	errno = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr(strerror(errno));
		ft_putchar('\n');
		return (0);
	}
	while (get_next_line(fd,&line) == 1) 
	{
		if (insert_line(context, line) == 0)
		{
			break;
		}
	}
	close(fd);
	return (1);
}
