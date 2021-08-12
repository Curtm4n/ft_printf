/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:38:37 by cdapurif          #+#    #+#             */
/*   Updated: 2021/08/12 18:56:45 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_init(void (*func_type[13])(t_struct *, va_list))
{
	func_type[0] = &ft_print_c;
	func_type[1] = &ft_print_s;
	func_type[2] = &ft_print_addr;
	func_type[3] = &ft_print_int;
	func_type[4] = &ft_print_int;
	func_type[5] = &ft_print_uint;
	func_type[6] = &ft_print_lowhex;
	func_type[7] = &ft_print_uphex;
	func_type[8] = &ft_print_octal;
	func_type[9] = &ft_store_nb_char;
	func_type[10] = &ft_print_float;
	func_type[11] = &ft_print_g;
	func_type[12] = &ft_print_e;
}

const char	*ft_flag(const char *format, t_struct *data)
{
	while (*format == '-' || *format == '0' || *format == '+' ||
		*format == '#' || *format == ' ' || *format == '\'')
	{
		if (*format == '0')
			data->flag |= ZERO;
		if (*format == '-')
			data->flag |= MINUS;
		if (*format == '+')
			data->flag |= PLUS;
		if (*format == '#')
			data->flag |= HASH;
		if (*format == ' ')
			data->flag |= SPACE;
		if (*format == '\'')
			data->flag |= APOSTROPHE;
		format++;
	}
	if ((data->flag & ZERO) && (data->flag & MINUS))
		data->flag ^= ZERO;
	if ((data->flag & PLUS) && (data->flag & SPACE))
		data->flag ^= SPACE;
	return (format);
}

const char	*ft_width(const char *format, t_struct *data, va_list args)
{
	if (*format == '*')
	{
		data->width = va_arg(args, int);
		if (data->width < 0)
		{
			data->width *= -1;
			data->flag |= MINUS;
			if ((data->flag & 1) && (data->flag & 2))
				data->flag ^= 1;
		}
		format++;
	}
	if (*format >= '0' && *format <= '9')
		data->width = ft_atoi(format);
	while (*format >= '0' && *format <= '9')
		format++;
	return (format);
}

const char	*ft_precision(const char *format, t_struct *data, va_list args)
{
	if (*format == '.')
	{
		format++;
		if (*format == '*')
		{
			data->precision = va_arg(args, int);
			format++;
			return (format);
		}
		data->precision = ft_atoi(format);
		while (*format >= '0' && *format <= '9')
			format++;
	}
	return (format);
}

const char	*pars_specifier(const char *format, t_struct *data, va_list args)
{
	void	(*func_type[13])(t_struct *, va_list);
	int		index;
	char	*types;

	format++;
	if (*format == '\0')
		return (format);
	index = -1;
	types = "cspdiuxXonfge";
	reset_struct(data);
	format = ft_flag(format, data);
	format = ft_width(format, data, args);
	format = ft_precision(format, data, args);
	format = ft_size(format, data);
	if (*format == '%')
		return (ft_handle_percent(format, data));
	ft_init(&func_type[0]);
	while (++index < 13)
		if (*format == types[index])
		{
			(*func_type[index])(data, args);
			format++;
			break ;
		}
	return (format);
}
