/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:08:25 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/29 11:22:10 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	one(t_philo *philo)
{
	if (philo->only_one)
	{
		while (1)
		{
			pthread_mutex_lock(&(philo->ressource->set_death));
			if (philo->ressource->is_dead)
			{
				pthread_mutex_unlock(&(philo->ressource->set_death));
				return (0);
			}
			pthread_mutex_unlock(&(philo->ressource->set_death));
			usleep(100);
		}
		return (0);
	}
	return (1);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->ressource->spoon[philo->right_spoon]));
	timer_print(philo, "has taken a fork\n");
	if (!one(philo))
		return (0);
	pthread_mutex_lock(&(philo->ressource->spoon[philo->left_spoon]));
	timer_print(philo, "has taken a fork\n");
	return (1);
}

void	eat(t_philo *philo)
{
	timer_print(philo, "is eating\n");
	pthread_mutex_lock(&(philo->meal_set));
	philo->last_time_meal = get_actual_time();
	pthread_mutex_unlock(&(philo->meal_set));
	smart_sleep(philo->ressource->time_to_eat, philo->ressource);
	pthread_mutex_lock(&(philo->nb_meal_set));
	philo->nb_meal++;
	pthread_mutex_unlock(&(philo->nb_meal_set));
	pthread_mutex_unlock(&(philo->ressource->spoon[philo->right_spoon]));
	pthread_mutex_unlock(&(philo->ressource->spoon[philo->left_spoon]));
}

void	sleep_and_think(t_philo *philo)
{
	timer_print(philo, "is sleeping\n");
	smart_sleep(philo->ressource->time_to_sleep, philo->ressource);
	timer_print(philo, "is thinking\n");
}
