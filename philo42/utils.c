/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:04:41 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 16:55:45 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		if (sign == 1 && (num > (INT_MAX - (*nptr - '0')) / 10))
			return (INT_MAX);
		if (sign == -1 && (num > (-(INT_MIN + (*nptr - '0')) / 10)))
			return (INT_MIN);
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * sign);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	atoi_limit_checker(const char *nptr)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		if (sign == 1 && (num > (INT_MAX - (*nptr - '0')) / 10))
			return (1);
		if (sign == -1 && (num > (-(INT_MIN + (*nptr - '0')) / 10)))
			return (1);
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (0);
}
