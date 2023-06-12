/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/12 12:58:53 by maujogue         ###   ########.fr       */
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
