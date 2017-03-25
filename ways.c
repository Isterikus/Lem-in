/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:19:15 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/11 20:02:42 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

void	fill_new_way(t_ways *ways, int room)
{
	int		i;

	while (ways->next != NULL)
		ways = ways->next;
	i = 0;
	while (i < ways->len && ways->way[i] != room)
		i++;
	i++;
	ways->next = (t_ways *)malloc(sizeof(t_ways));
	if (ways->next == NULL)
		error(9);
	ways->next->way = (int *)malloc(sizeof(int) * (i + 1));
	if (ways->next->way == NULL)
		error(9);
	i = 0;
	while (i < ways->len && ways->way[i] != room)
	{
		ways->next->way[i] = ways->way[i];
		i++;
	}
	ways->next->way[i] = ways->way[i];
	ways->next->next = NULL;
	ways->next->len = i + 2;
}

void	expand(int **d, int len)
{
	int		i;
	int		*temp;

	i = 0;
	temp = (int *)malloc(sizeof(int) * (len + 1));
	if (temp == NULL)
		error(9);
	while (i < len)
	{
		temp[i] = (*d)[i];
		i++;
	}
	free(*d);
	(*d) = (int *)malloc(sizeof(int) * (len + 1));
	if (*d == NULL)
		error(9);
	i = 0;
	while (i < len)
	{
		(*d)[i] = temp[i];
		i++;
	}
	free(temp);
}

int		new_way(t_ways *ways, int room, int i, t_map map)
{
	t_ways	*temp;

	temp = ways;
	fill_new_way(ways, room);
	while (temp->next != NULL)
		temp = temp->next;
	temp->way[temp->len - 1] = i;
	if (i == map.end)
		return (0);
	go_to(map, ways, i);
	return (1);
}

void	go_to(t_map map, t_ways *ways, int room)
{
	int		i;
	int		new;
	t_ways	*temp;

	new = 0;
	temp = ways;
	while (temp->next != NULL)
		temp = temp->next;
	i = -1;
	while (++i < map.num)
		if (map.rooms[room].to[i] == 1 && check_prev(temp, i, room))
		{
			if (new == 0)
			{
				expand(&(temp->way), temp->len);
				temp->way[temp->len] = i;
				temp->len += 1;
				if (i == map.end)
					return ;
				go_to(map, ways, i);
				new = 1;
			}
			else if (!new_way(ways, room, i, map))
				return ;
		}
}

void	remove_e(int end, t_ways **aa)
{
	t_ways	*temp;
	t_ways	*ways;

	ways = *aa;
	(!check_st_ed(*aa, end)) ? error(5) : 0;
	while (ways->way[ways->len - 1] != end)
	{
		temp = ways;
		ways = ways->next;
		delone(&temp);
		*aa = ways;
	}
	while (ways->next != NULL)
	{
		if (ways->next->way[ways->next->len - 1] != end)
		{
			temp = ways->next->next;
			delone(&(ways->next));
			ways->next = temp;
		}
		else
			ways = ways->next;
	}
	if (ways->way[ways->len - 1] != end)
		delone(&ways);
}
