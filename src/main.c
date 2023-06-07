/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:47:32 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/07 16:31:07 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <time.h>

void	philo_dies(t_all *all, struct timeval time, int i)
{
	print_message(all, time, DEAD, i);
	pthread_mutex_lock(&(all->w_mutex));
	all->stop = 1;
	pthread_mutex_unlock(&(all->w_mutex));
}

void	philo_eats(t_all *all, struct timeval time, int i)
{
	if (calculate_time(time) - all->philo[i]->last_meal > all->tt_die)
		return (philo_dies(all, time, i));
	pthread_mutex_lock(&(all->philo[i]->l_fork));
	print_message(all, time, FORK, i);
	pthread_mutex_lock(&(all->philo[i]->r_fork));
	print_message(all, time, FORK, i);
	print_message(all, time, EAT, i);
	all->philo[i]->last_meal = calculate_time(time);
	usleep(all->tt_eat * 1000);
	pthread_mutex_unlock(&(all->philo[i]->l_fork));
	pthread_mutex_unlock(&(all->philo[i]->r_fork));
}

void	philo_sleeps(t_all *all, struct timeval time, int i)
{
	if (calculate_time(time) - all->philo[i]->last_meal > all->tt_die)
		return (philo_dies(all, time, i));
	print_message(all, time, SLEEP, i);
	usleep(all->tt_sleep * 1000);
}

void	philo_thinks(t_all *all, struct timeval time, int i)
{
	if (calculate_time(time) - all->philo[i]->last_meal > all->tt_die)
		return (philo_dies(all, time, i));
	print_message(all, time, THINK, i);	
}



void    *routine(void *all_i)
{
	t_all *all = (t_all *)all_i;
	struct	timeval time;
	int	i;

	if (all->i == all->nb)
		all->i = 0;
    i = all->i++;
	gettimeofday(&time, NULL);
	while (all->stop == 0)
	{
		printf("-->%d\n", all->stop);
		philo_eats(all, time, i);
		philo_sleeps(all, time, i);
		philo_thinks(all, time, i);
	}
	return (all_i);
}

int	main(int argc, char **argv)
{
	t_all		all;

	if (argc != 5)
		return (0);
	init_all(&all, argv);
	// philo(&all);
	return (0);
}
