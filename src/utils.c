/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/12 11:13:01 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	calculate_time(struct timeval start_time)
{
	struct timeval	end_time;
	int				time_passed;

	gettimeofday(&end_time, NULL);
	time_passed = (end_time.tv_sec - start_time.tv_sec) * 1000.0
		+ (end_time.tv_usec - start_time.tv_usec) / 1000.0;
	return (time_passed);
}

void	print_message(t_all *all, int status, int i)
{
	int	timestamp;

	timestamp = calculate_time(all->time);
	pthread_mutex_lock(&(all->w_mutex));
	if (status == FORK && all->stop == 0)
		printf("%d %d has taken a fork\n", timestamp, all->philo[i]->id);
	else if (status == EAT && all->stop == 0)
		printf("%d %d is eating\n", timestamp, all->philo[i]->id);
	else if (status == SLEEP && all->stop == 0)
		printf("%d %d is sleeping\n", timestamp, all->philo[i]->id);
	else if (status == THINK && all->stop == 0)
		printf("%d %d is thinking\n", timestamp, all->philo[i]->id);
	else if (status == DEAD && all->stop == 0)
	{
		printf("%d %d died\n", timestamp, all->philo[i]->id);
	}
	pthread_mutex_unlock(&(all->w_mutex));
}

void	free_exit(t_all *all, int exit_code)
{
	int	i;

	i = 0;
	while (all->philo && all->philo[i])
	{
		free(all->philo[i]->th);
		free(all->philo[i]);
		i++;
	}
	free(all->philo);
	if (exit_code == 1)
		write(2, "Malloc Error\n", 13);
	exit(exit_code);
}

int	is_philo_dead(t_all *all, int i)
{
	int	time_since_last_meal;

	pthread_mutex_lock(&(all->philo[i]->last_meal_mutex));
	time_since_last_meal
		= calculate_time(all->time) - all->philo[i]->last_meal;
	pthread_mutex_unlock(&(all->philo[i]->last_meal_mutex));
	if (time_since_last_meal > all->tt_die)
	{
		print_message(all, DEAD, i);
		pthread_mutex_lock(&(all->stop_mutex));
		all->stop = 1;
		pthread_mutex_unlock(&(all->stop_mutex));
		return (0);
	}
	return (1);
}

void	check_philo(t_all *all)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_philo_dead(all, i) == 0)
			break ;
		i += 1;
		if (i == all->nb)
			i = 0;
	}
}
