/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:00:46 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/30 20:21:26 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_tabs(t_ressource *ressource)
{
	if (ressource->philo != NULL)
	{
		free(ressource->philo);
		ressource->philo = NULL;
	}
	if (ressource->spoon != NULL)
	{
		free(ressource->spoon);
		ressource->spoon = NULL;
	}
}

int	check_error(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("Only 4 or 5 arguments\n");
		return (0);
	}
	if (!ft_atoi(argv[1]) || !ft_atoi(argv[2])
		|| !ft_atoi(argv[3]) || !ft_atoi(argv[4]))
	{
		printf("Bad format\n");
		return (0);
	}
	if (argc == 6 && !ft_atoi(argv[5]))
	{
		printf("Bad format\n");
		return (0);
	}
	return (1);
}
