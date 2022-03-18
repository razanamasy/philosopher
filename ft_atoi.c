/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:47:47 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/30 20:33:00 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_space(char c)
{
	if (c == '\f' || c == '\t' || c == '\v' || c == '\n'
		|| c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static int	ft_isnum(char c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

static int	ft_issign(char c)
{
	if ((c == '-' || c == '+'))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (is_space(nptr[i]))
		i++;
	if (!(ft_issign(nptr[i]) || ft_isnum(nptr[i])))
		return (0);
	if (ft_issign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	if (!(ft_isnum(nptr[i])))
		return (0);
	while (ft_isnum(nptr[i]))
		nb = 10 * nb + (int)nptr[i++] - '0';
	if (nptr[i] != '\0')
		return (0);
	return (sign * nb);
}
