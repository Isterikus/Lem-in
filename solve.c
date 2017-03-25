/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:26:06 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/11 19:32:12 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

int		find_min(t_ways *ways, int pr)
{
	int		min;

	min = 100000;
	while (ways != NULL)
	{
		if (ways->len < min && ways->len != pr)
			min = ways->len;
		ways = ways->next;
	}
	if (min < pr)
		return (100000);
	return (min);
}

int		find_max(t_ways *ways)
{
	int		max;

	max = ways->len;
	while (ways != NULL)
	{
		if (ways->len > max)
			max = ways->len;
		ways = ways->next;
	}
	return (max);
}

int		compare(t_ways *way1, t_ways *way2)
{
	int		i;

	i = 0;
	while (i < way1->len && i < way2->len)
	{
		if (way1->way[i] != way2->way[i])
			return (1);
		i++;
	}
	if (i != way1->len || i != way2->len)
		return (1);
	return (0);
}

void	del_ways(t_ways **ways, int del, t_ways *tp)
{
	t_ways	*temp;
	t_ways	*move;

	while (find_del((*ways)->way, (*ways)->len, del) && compare(*ways, tp))
	{
		temp = *ways;
		(*ways) = (*ways)->next;
		delone(&temp);
	}
	move = (*ways);
	while (move->next != NULL)
		if (find_del(move->next->way, move->next->len, del)
			&& compare(move->next, tp))
		{
			temp = move->next->next;
			delone(&(move->next));
			move->next = temp;
		}
		else
			move = move->next;
	if (find_del(move->way, move->len, del) && compare(move, tp))
		delone(&move);
}

void	solve(t_ways **ways)
{
	int		min;
	t_ways	*temp;
	int		i;
	int		max;

	temp = *ways;
	i = 1;
	min = find_min(*ways, -1);
	while (temp->len != min)
		temp = temp->next;
	while (i < temp->len - 1)
		del_ways(ways, temp->way[i++], temp);
	temp = *ways;
	while (((min = find_min(*ways, min)) !=
		(max = find_max(*ways))) && min != 100000)
	{
		while (temp->len != min)
			temp = temp->next;
		i = 1;
		while (i < temp->len)
			del_ways(ways, temp->way[i++], temp);
	}
}
