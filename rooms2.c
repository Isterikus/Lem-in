/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 19:26:27 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/11 19:30:11 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

int		pass(char *str, int *i, char c)
{
	while (str[(*i)] && str[(*i)] != c)
		(*i)++;
	(*i)++;
	return (*i);
}

int		count_rooms(char *str, int i)
{
	int		j;

	j = 0;
	while (str[i] != '-')
	{
		i++;
		while (str[i] == '#')
			pass(str, &i, '\n');
		(str[i] == '\n' && str[i + 1] == '\n') ? error(5) : 0;
		if (str[i] == '\n')
			j++;
		if (!str[i])
			error(2);
	}
	return (j);
}

int		find_name(t_map map, char *name)
{
	int		i;

	i = 0;
	while (i < map.num)
	{
		if (!ft_strcmp(map.rooms[i].name, name))
			return (i);
		i++;
	}
	return (-1);
}

int		check_prev(t_ways *way, int num, int room)
{
	int		i;

	i = 0;
	while (i < way->len && way->way[i] != room)
		if (way->way[i++] == num)
			return (0);
	return (1);
}
