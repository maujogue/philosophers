/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:47:32 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/08 14:46:50 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <time.h>

int	is_philo_dead(t_all *all, int i)
{
	int time_since_last_meal;

	time_since_last_meal =
		calculate_time(all->time) - all->philo[i]->last_meal ;
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

void	philo_eats(t_all *all, int i)
{
	pthread_mutex_lock(all->philo[i]->l_fork);
	pthread_mutex_lock(&(all->philo[i]->r_fork));
	if (is_philo_dead(all, i) == 0)
	{
		pthread_mutex_unlock(all->philo[i]->l_fork);
		pthread_mutex_unlock(&(all->philo[i]->r_fork));
		return ;
	}
	print_message(all, FORK, i);
	print_message(all, FORK, i);
	print_message(all, EAT, i);
	all->philo[i]->last_meal = calculate_time(all->time);
	ft_usleep(all, all->tt_eat, i);
	// usleep(all->tt_eat * 1000);
	pthread_mutex_unlock(all->philo[i]->l_fork);
	pthread_mutex_unlock(&(all->philo[i]->r_fork));
}

void	philo_sleeps(t_all *all, int i)
{
	print_message(all, SLEEP, i);
	ft_usleep(all, all->tt_sleep, i);
	// usleep(all->tt_sleep * 1000);
}

void	philo_thinks(t_all *all, int i)
{
	print_message(all, THINK, i);	
}

void    *routine(void *all_i)
{
	t_all *all = (t_all *)all_i;
	int	i;

    i = all->i++;
	if (all->nb == 1 && i == 0)
	{
		philo_sleeps(all, i);
		philo_thinks(all, i);
		ft_usleep(all, all->tt_die, i);
		return (NULL);
	}
	while (1)
	{
		if (is_philo_dead(all, i) == 0)
			break ;
		philo_eats(all, i);
		philo_sleeps(all, i);
		philo_thinks(all, i);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_all		all;

	if (argc != 5)
		return (0);
	init_all(&all, argv);
	philo(&all);
	return (0);
}
