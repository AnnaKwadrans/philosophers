/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 21:10:38 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid_arguments(int argc, char **argv)
{
	if (!valid_number_of_args(argc) || !are_args_valid_numbers(argv))
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

bool	are_args_valid_numbers(char **argv)
{
	long	num;
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		printf("%s\n", argv[i]);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("arguments must be digits\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
