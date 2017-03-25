/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:23:19 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/13 16:22:15 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_H
# define LEM_H

# define BUFF 100

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "./libft/printf_functions/includes/header.h"

typedef struct		s_rooms
{
	char			*name;
	char			*comment;
	int				y;
	int				x;
	int				*to;
}					t_rooms;

typedef struct		s_map
{
	int				ants;
	int				num;
	int				start;
	int				end;
	t_rooms			*rooms;
}					t_map;

typedef struct		s_ways
{
	int				len;
	int				*way;
	struct s_ways	*next;
}					t_ways;

void				error(int num);
char				*ft_strsub_e(char *s, unsigned int start, unsigned int end);
void				fill_struct(char *str, t_map *map, int i, int j);
void				output(t_map map);
void				go_to(t_map map, t_ways *ways, int room);
void				remove_e(int end, t_ways **ways);
void				solve(t_ways **ways);
void				ants(t_ways *ways, t_map map);
void				expand(int **d, int len);
void				delone(t_ways **ways);
void				pr_sp(int len, int sp);
int					pass(char *str, int *i, char c);
int					count_rooms(char *str, int i);
int					find_name(t_map map, char *name);
int					check_arr_1(int *arr, int end, int len);
int					check_arr_2(int *arr, int end, int len, int m);
int					check_prev(t_ways *way, int num, int room);
int					check_st_ed(t_ways *ways, int end);
int					find_del(int *way, int len, int del);
void				out_connections(t_map map);

#endif
