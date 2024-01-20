/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element_value4_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:14:29 by hyungdki          #+#    #+#             */
/*   Updated: 2024/01/20 22:34:04 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	type_split2(char ***split, int suf_into, t_suf_type *suf);
static int	set_suf_data(char *info, int suf_into, t_suf_type *suf);
extern void	remove_newline(char	*str);

int	type_split(char *buffer, char ***split, int type, t_suf_type *suf)
{
	int	suf_into;

	*split = ft_split(buffer, ' ');
	if (*split == T_NULL)
		return (1);
	suf_into = 0;
	if (type == TYPE_SP)
		suf_into = 5;
	else if (type == TYPE_PL)
		suf_into = 6;
	else if (type == TYPE_CY || type == TYPE_CN)
		suf_into = 7;
	return (type_split2(split, suf_into, suf));
}

inline static int	type_split2(char ***split, int suf_into, t_suf_type *suf)
{
	int	cnt;
	int	idx;

	idx = -1;
	while ((*split)[++idx] != T_NULL)
		;
	cnt = set_suf_data((*split)[suf_into], suf_into, suf);
	if (cnt == 0)
	{
		free_2d_array2((void ***)split);
		return (2);
	}
	if (!(idx == cnt || (idx == (cnt + 1)
				&& (*split)[cnt][0] == '\n')))
	{
		free_2d_array2((void ***)split);
		return (2);
	}
	remove_newline((*split)[cnt - 1]);
	return (0);
}

inline static int	set_suf_data(char *info, int suf_into, t_suf_type *suf)
{
	int	cnt;

	cnt = 0;
	if (ft_strcmp(info, "rgb") == 0)
	{
		cnt = suf_into + 2;
		(*suf) = RGB;
	}
	else if (ft_strcmp(info, "im") == 0)
	{
		cnt = suf_into + 2;
		(*suf) = IM;
	}
	else if (ft_strcmp(info, "bmt") == 0)
	{
		cnt = suf_into + 3;
		(*suf) = BMT;
	}
	else if (ft_strcmp(info, "chk") == 0)
	{
		cnt = suf_into + 5;
		(*suf) = CHK;
	}
	return (cnt);
}
