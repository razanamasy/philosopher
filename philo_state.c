/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:18:28 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/30 14:43:39 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death_and_meal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->ressource->m_eat));
	pthread_mutex_lock(&(philo->ressource->set_death));
	if (philo->ressource->is_dead || philo->ressource->all_eat == 1)
	{
		pthread_mutex_unlock(&(philo->ressource->m_eat));
		pthread_mutex_unlock(&(philo->ressource->set_death));
		return (0);
	}
	pthread_mutex_unlock(&(philo->ressource->m_eat));
	pthread_mutex_unlock(&(philo->ressource->set_death));
	return (1);
}

void	*philo_state(void *philo_n)
{
	t_philo	*philo;

	philo = (t_philo *)philo_n;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!check_death_and_meal(philo))
			break ;
		if (!take_fork(philo))
			break ;
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
