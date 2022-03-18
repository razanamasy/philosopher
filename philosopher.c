/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:24:04 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/30 16:24:48 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	join_the_threads(t_ressource *ressource)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < ressource->nb_philo)
	{
		ret = pthread_join(ressource->philo[i].philo_thread, NULL);
		if (ret != 0)
			return (0);
		i++;
	}
	return (1);
}

int	create_multithreads(t_ressource *ressource)
{
	int			i;
	int			ret;
	t_philo		*philo;

	i = 0;
	ret = 0;
	philo = ressource->philo;
	ressource->time_start = get_actual_time();
	while (i < ressource->nb_philo)
	{
		philo[i].last_time_meal = ressource->time_start;
		ret = pthread_create(&(philo[i].philo_thread),
				NULL, (void *)philo_state, (void *)&philo[i]);
		if (ret != 0)
			return (0);
		i++;
	}
	stop_conditions_monitor(ressource, ressource->philo);
	if (!join_the_threads(ressource))
		return (0);
	return (1);
}

int	destroy_all_mutex(t_ressource *ressource)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(ressource->m_eat)) != 0)
		return (0);
	if (pthread_mutex_destroy(&(ressource->m_print)) != 0)
		return (0);
	if (pthread_mutex_destroy(&(ressource->m_death)) != 0)
		return (0);
	if (pthread_mutex_destroy(&(ressource->set_death)) != 0)
		return (0);
	while (i < ressource->nb_philo)
	{
		if (pthread_mutex_destroy(&(ressource->philo[i].meal_set)) != 0)
			return (0);
		if (pthread_mutex_destroy(&(ressource->philo[i].nb_meal_set)) != 0)
			return (0);
		if (pthread_mutex_destroy(&(ressource->spoon[i])) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_ressource		ressource;

	if (!check_error(argc, argv))
		return (1);
	if (!init_ressource(&ressource, argc, argv))
	{
		return (1);
	}
	if (!create_multithreads(&ressource))
	{
		free_tabs(&ressource);
		return (1);
	}
	if (!destroy_all_mutex(&ressource))
	{
		free_tabs(&ressource);
		return (1);
	}
	free_tabs(&ressource);
}
