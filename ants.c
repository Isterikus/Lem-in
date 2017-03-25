/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 18:15:24 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/13 09:55:16 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

t_ways	*find_min_way(t_ways *ways)
{
	t_ways	*min;
	int		i;

	min = ways;
	i = 0;
	while (ways != NULL)
	{
		if (min->len > ways->len)
			min = ways;
		ways = ways->next;
	}
	return (min);
}

int		find_next(t_ways *ways, int elem, int end)
{
	int		i;

	i = 0;
	if (elem == end)
	{
		return (-1);
	}
	while (ways != NULL)
	{
		i = 0;
		while (1)
		{
			if (ways->way[i] == elem)
				return (ways->way[i + 1]);
			if (ways->way[i++] == end)
				break ;
		}
		ways = ways->next;
	}
	return (-1);
}

void	fill_arr(int **arr, t_map map, t_ways **ways)
{
	int		i;
	t_ways	*temp;
	t_ways	*new;

	i = 0;
	(*arr) = (int *)malloc(sizeof(int) * map.ants);
	if (*arr == NULL)
		error(9);
	while (i < map.ants)
		(*arr)[i++] = -1;
	i = 0;
	temp = find_min_way(*ways);
	while (i < map.ants)
	{
		(*arr)[i++] = temp->way[1];
		temp->len++;
		new = find_min_way(*ways);
		if (temp->len > new->len)
			temp = new;
	}
}

void	ants_walking(t_map map, int *send)
{
	int		i;
	int		j;

	i = 0;
	while (i < map.ants)
	{
		if (send[i] != -1)
		{
			printf("L%d-%s", i + 1, map.rooms[send[i]].name);
			j = i + 1;
			while (j < map.ants)
				if (send[j++] != -1)
				{
					printf(" ");
					break ;
				}
		}
		i++;
	}
	printf("\n");
}

void	ants(t_ways *ways, t_map map)
{
	int		i;
	int		*arr;
	int		*send;

	i = 0;
	fill_arr(&arr, map, &ways);
	((send = (int *)malloc(sizeof(int) * map.ants)) == NULL) ? error(9) : 0;
	while (i < map.ants)
		send[i++] = -1;
	while (!check_arr_1(arr, -1, map.ants))
	{
		i = 0;
		while (i < map.ants)
		{
			if (check_arr_2(send, arr[i], map.ants, map.end) || arr[i] == -1)
			{
				send[i] = arr[i];
				arr[i] = find_next(ways, arr[i], map.end);
			}
			i++;
		}
		ants_walking(map, send);
	}
	free(arr);
	free(send);
}
