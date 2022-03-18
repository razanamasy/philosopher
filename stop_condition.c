/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 09:58:17 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/29 10:44:04 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	return_death(t_ressource *ressource, t_philo *philo)
{
	pthread_mutex_lock(&(philo->ressource->set_death));
	if (ressource->is_dead)
	{
		pthread_mutex_unlock(&(philo->ressource->set_death));
		return (0);
	}
	pthread_mutex_unlock(&(philo->ressource->set_death));
	return (1);
}

int	check_death(t_ressource *ressource, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < ressource->nb_philo && !(ressource->is_dead))
	{
		pthread_mutex_lock(&(philo[i].meal_set));
		if (get_actual_time() - philo[i].last_time_meal
			>= ressource->time_to_die)
		{
			pthread_mutex_lock(&(philo->ressource->set_death));
			pthread_mutex_lock(&(philo->ressource->m_print));
			if (ressource->is_dead == 0)
				timer_print_dead(&philo[i], "died\n");
			pthread_mutex_unlock(&(philo->ressource->m_print));
			ressource->is_dead = 1;
			pthread_mutex_unlock(&(philo->ressource->set_death));
		}
		pthread_mutex_unlock(&(philo[i].meal_set));
		usleep(100);
		i++;
	}
	if (!return_death(ressource, philo))
		return (0);
	return (1);
}

int	set_meal(int i, t_ressource *ressource, t_philo *philo)
{
	if (i == ressource->nb_philo)
	{
		pthread_mutex_lock(&(philo->ressource->m_eat));
		ressource->all_eat = 1;
		pthread_mutex_unlock(&(philo->ressource->m_eat));
		return (0);
	}
	return (1);
}

int	check_nb_meal(t_ressource *ressource, t_philo *philo)
{
	int	i;

	i = 0;
	if (ressource->nb_meal_max != -1)
	{
		while (i < ressource->nb_philo)
		{
			if (!check_death(ressource, philo))
				return (0);
			pthread_mutex_lock(&(philo[i].nb_meal_set));
			if (philo[i].nb_meal >= ressource->nb_meal_max)
			{
				pthread_mutex_unlock(&(philo[i].nb_meal_set));
				i++;
			}
			else
				pthread_mutex_unlock(&(philo[i].nb_meal_set));
			usleep(100);
		}
	}
	if (!(set_meal(i, ressource, philo)))
		return (0);
	return (1);
}

void	stop_conditions_monitor(t_ressource *ressource, t_philo *philo)
{
	while (1)
	{
		if (!check_death(ressource, philo))
			break ;
		if (!check_nb_meal(ressource, philo))
			break ;
	}
}
