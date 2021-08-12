/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_nb_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curtman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:53:16 by curtman           #+#    #+#             */
/*   Updated: 2019/12/01 17:54:58 by curtman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_store_nb_char(t_struct *data, va_list args)
{
	int *value;

	value = va_arg(args, int *);
	*value = data->nb_char;
}
