/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buyilmaz <buyilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:53:05 by buyilmaz          #+#    #+#             */
/*   Updated: 2023/07/17 15:53:30 by buyilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char a)
{
	return (write(1, &a, 1));
}

int	checkid(va_list *args, char c)
{
	int	len;

	len = 0;
	if (c == 'u')
		len += (ft_unsigned(va_arg((*args), unsigned int)));
	else if (c == 'c')
		len += (ft_putchar(va_arg((*args), int)));
	else if (c == 'i' || c == 'd')
		len += (ft_int(va_arg((*args), int)));
	else if (c == 'x' || c == 'X')
		len += (ft_hex(va_arg((*args), unsigned int), c));
	else if (c == 'p')
		len += (ft_point(va_arg((*args), unsigned long), 1));
	else if (c == 's')
		len += (ft_string(va_arg((*args), char *)));
	else if (c == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		len;

	va_start(arg, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += checkid(&arg, str[i + 1]);
			i++;
		}
		else if (str[i] == '\0')
			return (0);
		else
			len += ft_putchar(str[i]);
		if (str[i] != '\0')
			i++;
	}
	va_end(arg);
	return (len);
}
