/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:17:42 by hrazanam          #+#    #+#             */
/*   Updated: 2021/12/01 10:13:39 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	timer_print(t_philo *philo, char *message)
{
	long long	current_time;
	long long	timestamp;

	pthread_mutex_lock(&(philo->ressource->set_death));
	pthread_mutex_lock(&(philo->ressource->m_print));
	if (philo->ressource->is_dead == 0)
	{
		current_time = get_actual_time();
		timestamp = current_time - philo->ressource->time_start;
		ft_putnbr_fd((int)timestamp, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(philo->id + 1, 1);
		ft_putchar_fd(' ', 1);
		write(1, message, ft_strlen(message));
	}
	pthread_mutex_unlock(&(philo->ressource->m_print));
	pthread_mutex_unlock(&(philo->ressource->set_death));
}

void	timer_print_dead(t_philo *philo, char *message)
{
	long long	current_time;
	long long	timestamp;

	current_time = get_actual_time();
	timestamp = current_time - philo->ressource->time_start;
	ft_putnbr_fd((int)timestamp, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id + 1, 1);
	ft_putchar_fd(' ', 1);
	write(1, message, ft_strlen(message));
}

long long	get_actual_time(void)
{
	struct timeval	tv_2;

	gettimeofday(&tv_2, NULL);
	return ((tv_2.tv_sec * 1000) + (tv_2.tv_usec / 1000));
}

void	smart_sleep(long long time, t_ressource *ressource)
{
	long long	i;

	i = get_actual_time();
	while (1)
	{
		pthread_mutex_lock(&(ressource->set_death));
		if (ressource->is_dead)
		{
			pthread_mutex_unlock(&(ressource->set_death));
			break ;
		}
		pthread_mutex_unlock(&(ressource->set_death));
		if (get_actual_time() - i >= time)
			break ;
		usleep(50);
	}
}
