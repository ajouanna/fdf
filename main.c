/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajouanna <ajouanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:08:49 by ajouanna          #+#    #+#             */
/*   Updated: 2016/12/12 17:20:19 by ajouanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** affiche le contenu d'un  tableau d'int a 2 dimensions
*/

void	print_map(int **map)
{
	int i;
	int j;

	ft_putstr("print_map\n");
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] >= 0)
		{
			ft_putnbr(map[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

/*
** enchainement des traitements
** DEBUG : penser a supprimer print_map
*/

int		main(int argc, char **argv)
{
	t_context	context;

	if (argc != 2)
	{
		ft_putstr("Usage: fdf map_file\n");
		return (0);
	}
	if ((context.map = malloc(sizeof(int *))) == NULL)
	{
		ft_putstr("malloc error\n");
		return (0);
	}
	context.map[0] = 0;
	if (read_file(argv[1], &context))
	{
		print_map(context.map);
		if (setup_mlx(&context) == 0)
			return (0);
	}
	return (0);
}
