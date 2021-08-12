/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 20:18:52 by cdapurif          #+#    #+#             */
/*   Updated: 2019/11/27 20:07:49 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			place_precision(long long len)
{
	int		i;
	char	tab[(len > 0) ? len : 1];

	i = -1;
	if (len <= 0)
		return ;
	while (++i < len)
		tab[i] = '0';
	write(1, tab, len);
}

long long		ft_nblen(long long nbr)
{
	int i;

	i = 1;
	if (nbr < 0)
		nbr *= -1;
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void			place_sep(t_struct *data, long long len)
{
	int		i;
	char	sep;
	char	tab[(len > 0) ? len : 1];

	i = -1;
	if (len <= 0)
		return ;
	sep = (data->flag & 1) ? '0' : ' ';
	while (++i < len)
		tab[i] = sep;
	write(1, tab, len);
}

long long		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned int	ft_atoi(const char *str)
{
	unsigned int i;
	unsigned int nb;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb);
}
