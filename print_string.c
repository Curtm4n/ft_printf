/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:28:40 by cdapurif          #+#    #+#             */
/*   Updated: 2019/12/03 20:41:38 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_null(t_struct *data, int pre)
{
	pre = (pre >= 0 && pre < 7) ? pre : 6;
	if (data->width > pre && !(data->flag & MINUS))
		place_sep(data, data->width - pre);
	write(1, "(null)", pre);
	if (data->width > pre && data->flag & MINUS)
		place_sep(data, data->width - pre);
	data->nb_char += (data->width > pre) ? data->width : pre;
}

void	ft_print_s(t_struct *data, va_list args)
{
	int		pre;
	int		len_final;
	int		len_str;
	char	*str;

	str = va_arg(args, char *);
	pre = data->precision;
	if (str == NULL)
	{
		ft_handle_null(data, pre);
		return ;
	}
	if (pre >= 0 && pre < ft_strlen(str))
		len_str = pre;
	else
		len_str = ft_strlen(str);
	len_final = (data->width > len_str) ? data->width : len_str;
	if (!(data->flag & MINUS))
		place_sep(data, len_final - len_str);
	write(1, str, len_str);
	if (data->flag & MINUS)
		place_sep(data, len_final - len_str);
	data->nb_char += len_final;
}
