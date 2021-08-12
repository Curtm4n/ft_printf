/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:36:49 by cdapurif          #+#    #+#             */
/*   Updated: 2019/12/03 19:30:00 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*ft_size(const char *format, t_struct *data)
{
	while (*format == 'h' || *format == 'l' || *format == 'L')
	{
		if (*format == 'h')
		{
			data->size |= H;
			format++;
			if (*format == 'h')
			{
				data->size |= HH;
				format++;
			}
		}
		if (*format == 'l' || *format == 'L')
		{
			data->size |= L;
			format++;
			if (*format == 'l')
			{
				data->size |= LL;
				format++;
			}
		}
	}
	return (format);
}
