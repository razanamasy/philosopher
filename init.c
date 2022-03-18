/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:24:10 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/30 16:09:14 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	mutex_philo(int i, t_ressource *ressource)
{	
	if (pthread_mutex_init(&(ressource->philo[i].meal_set), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(ressource->philo[i].nb_meal_set), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(ressource->spoon[i]), NULL) != 0)
		return (0);
	return (1);
}

int	init_philo(t_ressource *ressource)
{
	int	i;

	i = 0;
	while (i < ressource->nb_philo)
	{
		ressource->philo[i].ressource = ressource;
		ressource->philo[i].id = i;
		if (ressource->nb_philo == 1)
			ressource->philo[i].only_one = ressource->nb_philo;
		else
			ressource->philo[i].only_one = 0;
		ressource->philo[i].nb_meal = 0;
		ressource->philo[i].left_spoon = i;
		if (!mutex_philo(i, ressource))
			return (0);
		if (i == ressource->nb_philo - 1)
			ressource->philo[i].right_spoon = 0;
		else
			ressource->philo[i].right_spoon = i + 1;
		i++;
	}
	return (1);
}

int	mutex_ressource(t_ressource *ressource)
{
	if (pthread_mutex_init(&(ressource->m_eat), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(ressource->m_print), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(ressource->m_death), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(ressource->set_death), NULL) != 0)
		return (0);
	return (1);
}

int	malloc_philo_spoon(t_ressource *ressource)
{
	ressource->philo = malloc(ressource->nb_philo * sizeof(t_philo));
	if (ressource->philo == NULL)
		return (0);
	ressource->spoon = malloc(ressource->nb_philo * sizeof(pthread_mutex_t));
	if (ressource->philo == NULL)
	{
		free_tabs(ressource);
		return (0);
	}
	return (1);
}

int	init_ressource(t_ressource *ressource, int argc, char *argv[])
{
	ressource->is_dead = 0;
	ressource->all_eat = 0;
	if (argc == 6)
		ressource->nb_meal_max = ft_atoi(argv[5]);
	else
		ressource->nb_meal_max = -1;
	ressource->time_to_eat = (useconds_t)ft_atoi(argv[3]);
	ressource->time_to_sleep = (useconds_t)ft_atoi(argv[4]);
	ressource->time_to_die = (useconds_t)ft_atoi(argv[2]);
	ressource->nb_philo = ft_atoi(argv[1]);
	if (!mutex_ressource(ressource))
		return (0);
	if (!malloc_philo_spoon(ressource))
		return (0);
	if (!init_philo(ressource))
	{
		free_tabs(ressource);
		return (0);
	}
	ressource->time_start = get_actual_time();
	return (1);
}
