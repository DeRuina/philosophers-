/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:05:40 by druina            #+#    #+#             */
/*   Updated: 2023/08/13 23:02:07 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].time_to_die = program->time_to_die;
		philos[i].time_to_eat = program->time_to_eat;
		philos[i].time_to_sleep = program->time_to_sleep;
		philos[i].last_meal = get_current_time();
    philos[i].write = &program->write;
		philos[i].l_fork = &forks[i];
    philos[i].dead = &program->dead;
		if (i == 0)
			philos[i].r_fork = &forks[program->num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		pthread_mutex_init(&philos[i].lock, NULL);
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos, char **argv)
{
	program->start_time = get_current_time();
	program->num_of_philos = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		program->num_times_to_eat = ft_atoi(argv[5]);
	else
		program->num_times_to_eat = -1;
  program->finished_eating = 0;
  program->dead = 0;
  program->philos = philos;
	pthread_mutex_init(&program->lock, NULL);
	pthread_mutex_init(&program->write, NULL);
}
