/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:14:18 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/13 17:38:14 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

void	error(int num)
{
	if (num == 1)
		ft_printf("{red}Error{eoc}\n{underlined}Bad number of ants!{eoc}");
	else if (num == 2)
		ft_printf("{red}Error{eoc}\n{underlined}No tubes!{eoc}");
	else if (num == 3)
		ft_printf("{red}Error{eoc}\n{underlined}No start or end!{eoc}");
	else if (num == 4)
		ft_printf("{red}Error{eoc}\n{underlined}Invalid tube! \
No such room!{eoc}");
	else if (num == 5)
		ft_printf("{red}Error{eoc}\n{underlined}No way between \
start and end!{eoc}");
	else if (num == 6)
		ft_printf("{red}Error{eoc}\n{underlined}Bad format!{eoc}");
	else if (num == 7)
		ft_printf("{red}Error{eoc}\n{underlined}Double start/end!{eoc}");
	else if (num == 8)
		ft_printf("{red}Error{eoc}\n{underlined}Start/End \
are after rooms!{eoc}");
	else if (num == 9)
		ft_printf("{red}Error{eoc}\n{underlined}Malloc error!{eoc}");
	else if (num == 10)
		ft_printf("{red}Error{eoc}\n{underlined}No rooms!{eoc}");
	exit(0);
}

void	rd_in(char **str)
{
	int		i;
	int		rd;
	char	buf[BUFF + 1];
	char	*temp;

	i = 0;
	*str = (char *)malloc(sizeof(char) * (BUFF + 1));
	if (*str == NULL)
		error(9);
	while ((rd = read(0, buf, BUFF)) > 0)
	{
		buf[rd] = '\0';
		temp = ft_strdup(*str);
		free(*str);
		*str = ft_strjoin(temp, buf);
		free(temp);
	}
	if (!(*str[0]))
		error(10);
}

void	output(t_map map)
{
	int		i;

	ft_printf("Number of ants: {bold}%d{eoc}\n", map.ants);
	ft_printf("Rooms: {bold}%d{eoc}\n", map.num);
	ft_printf("{yellow}Name{eoc}      {green}X{eoc}     {red}Y{eoc}\n");
	i = 0;
	while (i < map.num)
	{
		if (map.rooms[i].comment != NULL)
			ft_printf("%s", map.rooms[i].comment);
		if (i == map.start)
			ft_printf("{underlined}##start{eoc}\n");
		else if (i == map.end)
			ft_printf("{underlined}##end{eoc}\n");
		ft_printf("{yellow}%s{eoc}", map.rooms[i].name);
		pr_sp(ft_strlen(map.rooms[i].name), 10);
		ft_printf("{green}%d{eoc}", map.rooms[i].x);
		pr_sp(ft_intlen(map.rooms[i].x, 1), 6);
		ft_printf("{red}%d{eoc}\n", map.rooms[i].y);
		i++;
	}
}

void	out(t_ways *ways, char *str, t_map map)
{
	int		i;

	i = 0;
	while (str[i] != '-')
		i++;
	while (str[i] != '\n')
		i--;
	i++;
	ft_printf("%s\n", str + i);
	out_connections(map);
	while (ways != NULL)
	{
		i = 0;
		ft_printf("{magenta}%d{eoc}:\t", ways->len - 1);
		while (i < ways->len - 1)
			ft_printf("[%d]\t", ways->way[i++]);
		ft_printf("[%d]\n", ways->way[i]);
		ways = ways->next;
	}
	ft_printf("\n");
}

int		main(void)
{
	char	*str;
	t_map	map;
	t_ways	*ways;

	rd_in(&str);
	fill_struct(str, &map, 0, 0);
	ways = (t_ways *)malloc(sizeof(t_ways));
	if (ways == NULL)
		error(9);
	ways->way = (int *)malloc(sizeof(int));
	if (ways->way == NULL)
		error(9);
	ways->way[0] = map.start;
	ways->len = 1;
	ways->next = NULL;
	go_to(map, ways, map.start);
	remove_e(map.end, &ways);
	output(map);
	out(ways, str, map);
	solve(&ways);
	ants(ways, map);
	free(str);
	return (0);
}
