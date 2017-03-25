/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:19:32 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/13 10:11:13 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

char	*ft_strsub_e(char *s, unsigned int start, unsigned int end)
{
	size_t	i;
	char	*cr;

	i = 0;
	cr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!cr || !s)
		return (NULL);
	while (i < end - start)
	{
		cr[i] = s[start + i];
		i++;
	}
	cr[i] = '\0';
	return (cr);
}

void	pr_sp(int len, int sp)
{
	while (len++ < sp)
		ft_putchar(' ');
}

int		check_arr_1(int *arr, int end, int len)
{
	int		i;

	i = 0;
	while (i < len)
		if (arr[i++] != end)
			return (0);
	return (1);
}

int		check_arr_2(int *arr, int end, int len, int m)
{
	int		i;

	i = 0;
	while (i < len)
		if (arr[i++] == end && end != m)
			return (0);
	return (1);
}

void	delone(t_ways **ways)
{
	free((*ways)->way);
	free(*ways);
}
