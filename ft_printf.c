/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:56:23 by cdapurif          #+#    #+#             */
/*   Updated: 2019/11/26 16:53:22 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_write_basics(const char *format, t_struct *data)
{
	int i;

	i = 0;
	while (format[i] != '\0' && format[i] != '%')
		i++;
	write(1, format, i);
	data->nb_char += i;
	return (i);
}

void		reset_struct(t_struct *data)
{
	data->flag = 0;
	data->width = 0;
	data->precision = -1;
	data->size = 0;
}

int			ft_printf(const char *format, ...)
{
	t_struct	data;
	char		current_char;
	va_list		args;

	data.nb_char = 0;
	va_start(args, format);
	while ((current_char = *format) != '\0')
	{
		if (current_char != '%')
			format += ft_write_basics(format, &data);
		if ((current_char = *format) == '%')
			format = pars_specifier(format, &data, args);
	}
	va_end(args);
	return (data.nb_char);
}
