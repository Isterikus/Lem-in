/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:18:11 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/13 17:27:17 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

void	comment(char *str, int *i, t_map *map, int j)
{
	char	*temp;

	temp = ft_strsub_e(str, *i, pass(str, i, '\n'));
	if (j == (*map).num && (!ft_strcmp(temp, "##start\n") ||
		!ft_strcmp(temp, "##end\n")))
		error(8);
	if (ft_strcmp(temp, "##start\n") == 0)
	{
		if ((*map).start != -1)
			error(7);
		(*map).start = j;
	}
	else if (ft_strcmp(temp, "##end\n") == 0)
	{
		if ((*map).end != -1)
			error(7);
		(*map).end = j;
	}
	else if (j < (*map).num)
		(*map).rooms[j].comment = ft_strjoin2((*map).rooms[j].comment, temp);
	free(temp);
}

void	fill_tubes(char *str, int i, t_map *map)
{
	char	*name1;
	char	*name2;
	int		n1;
	int		n2;

	((*map).start == -1 || (*map).end == -1) ? error(3) : 0;
	while (str[i - 1] && str[i])
	{
		while (str[i] == '#')
			pass(str, &i, '\n');
		if (!str[i - 1])
			break ;
		if (str[i] == '\n')
			error(6);
		name1 = ft_strsub_e(str, i, pass(str, &i, '-') - 1);
		name2 = ft_strsub_e(str, i, pass(str, &i, '\n') - 1);
		n1 = find_name(*map, name1);
		n2 = find_name(*map, name2);
		if (n1 == -1 || n2 == -1)
			error(4);
		(*map).rooms[n1].to[n2] = 1;
		(*map).rooms[n2].to[n1] = 1;
		free(name1);
		free(name2);
	}
}

void	zero(t_map *map, int j)
{
	int		i;

	i = 0;
	(*map).rooms[j].to = (int *)malloc(sizeof(int) * (*map).num);
	if ((*map).rooms[j].to == NULL)
		error(9);
	while (i < (*map).num)
	{
		(*map).rooms[j].to[i] = 0;
		i++;
	}
}

void	check_right(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	pass(str, &j, '-');
	if (!str[j - 1])
		error(2);
	while (str[j] != '\n')
		j--;
	while (i <= j)
	{
		while (str[i] == '#')
			pass(str, &i, '\n');
		if (i > j)
			break ;
		(str[i] == ' ') ? error(6) : 0;
		while (str[i] != ' ' && str[i] != '\n')
			i++;
		(str[i++] == '\n' || !ft_isdigit(str[i])) ? error(6) : 0;
		while (str[i] != ' ' && str[i] != '\n')
			i++;
		(str[i++] == '\n' || !ft_isdigit(str[i])) ? error(6) : 0;
		pass(str, &i, '\n');
	}
}

void	fill_struct(char *str, t_map *map, int i, int j)
{
	(((*map).ants = ft_atoi(str)) <= 0) ? error(1) : 0;
	pass(str, &i, '\n');
	check_right(str + i);
	(((*map).num = count_rooms(str, i)) < 2) ? error(10) : 0;
	(*map).start = -1;
	(*map).end = -1;
	(((*map).rooms = (t_rooms *)malloc(sizeof(t_rooms) *\
		(*map).num)) == NULL) ? error(9) : 0;
	while (j < (*map).num)
	{
		(*map).rooms[j].comment = NULL;
		while (str[i] == '#')
			comment(str, &i, map, j);
		(*map).rooms[j].name = ft_strsub_e(str, i, pass(str, &i, ' ') - 1);
		(*map).rooms[j].x = ft_atoi(str + i);
		pass(str, &i, ' ');
		(*map).rooms[j].y = ft_atoi(str + i);
		pass(str, &i, '\n');
		zero(map, j++);
	}
	while (str[i] == '#')
		comment(str, &i, map, j);
	fill_tubes(str, i, map);
}
