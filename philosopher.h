/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazanam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:07:09 by hrazanam          #+#    #+#             */
/*   Updated: 2021/11/30 14:43:14 by hrazanam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_ressource	t_ressource;

typedef struct s_philo
{
	pthread_t				philo_thread;
	pthread_mutex_t			meal_set;
	pthread_mutex_t			nb_meal_set;
	struct s_ressource		*ressource;
	int						id;
	int						left_spoon;
	int						right_spoon;
	long long				last_time_meal;
	int						nb_meal;
	int						only_one;

}	t_philo;

typedef struct s_ressource
{
	struct s_philo		*philo;
	pthread_mutex_t		*spoon;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		m_print;
	pthread_mutex_t		m_death;
	pthread_mutex_t		set_death;
	int					nb_philo;
	int					is_dead;
	int					nb_meal_max;
	int					all_eat;
	long long			time_start;
	struct timeval		tv;
	useconds_t			time_to_eat;
	useconds_t			time_to_sleep;
	useconds_t			time_to_die;
}	t_ressource;

int			ft_atoi(const char *nptr);
int			init_ressource(t_ressource *ressource, int argc, char *argv[]);
void		*philo_state(void *philo_n);
void		stop_conditions_monitor(t_ressource *ressource, t_philo *philo);
long long	get_actual_time(void);
void		timer_print(t_philo *philo, char *message);
void		timer_print_dead(t_philo *philo, char *message);
void		smart_sleep(long long time, t_ressource *ressource);

void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);

int			one(t_philo *philo);
int			take_fork(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);

void		free_tabs(t_ressource *ressource);
int			check_error(int argc, char *argv[]);
void		free_tabs(t_ressource *ressource);

#endif
