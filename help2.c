/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 19:32:10 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/13 15:58:19 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

int		check_st_ed(t_ways *ways, int end)
{
	while (ways != NULL)
	{
		if (ways->way[ways->len - 1] == end)
			return (1);
		ways = ways->next;
	}
	return (0);
}

int		find_del(int *way, int len, int del)
{
	int		i;

	i = 1;
	while (i < len - 1)
		if (way[i++] == del)
			return (1);
	return (0);
}

void	out_connections(t_map map)
{
	int		i;
	int		j;

	i = 0;
	ft_printf("  ");
	while (i < map.num - 1)
		ft_printf("{bold}[%d]{eoc}", i++);
	ft_printf("{bold}[%d]{eoc}\n", i);
	i = 0;
	while (i < map.num)
	{
		j = 0;
		ft_printf("{bold}%d{eoc}:", i);
		while (j < map.num - 1)
			ft_printf(" %d ", map.rooms[i].to[j++]);
		ft_printf(" %d", map.rooms[i].to[j]);
		i++;
		ft_printf("\n");
	}
}
