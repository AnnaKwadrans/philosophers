/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 19:27:06 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid_arguments(int argc, char **argv)
{
	if (!valid_number_of_args(argc) || !are_args_digits(argv)
		|| !are_args_positive(argv))
		return (0);
	return (1);
}

bool	valid_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("usage:\n./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	return (1);
}

bool	are_args_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		//printf("%s\n", argv[i]);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("arguments must contain digits only\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

bool	are_args_positive(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("arguments must be positive numbers\n");
			return (0);
		}
		i++;
	}
	return (1);
}
