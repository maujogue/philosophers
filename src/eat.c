/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:54:48 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/14 10:33:34 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	lock_forks(t_all *all, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&(all->philo[i]->r_fork));
		pthread_mutex_lock(all->philo[i]->l_fork);
	}
	else
	{
		pthread_mutex_lock(all->philo[i]->l_fork);
		pthread_mutex_lock(&(all->philo[i]->r_fork));
	}
}

void	unlock_forks(t_all *all, int i)
{
	if (i == 0)
	{
		pthread_mutex_unlock(&(all->philo[i]->r_fork));
		pthread_mutex_unlock(all->philo[i]->l_fork);
	}
	else
	{
		pthread_mutex_unlock(all->philo[i]->l_fork);
		pthread_mutex_unlock(&(all->philo[i]->r_fork));
	}
}

int	philo_eats(t_all *all, int i)
{
	lock_forks(all, i);
	print_message(all, FORK, i);
	print_message(all, FORK, i);
	all->philo[i]->last_meal = calculate_time(all->time);
	print_message(all, EAT, i);
	all->philo[i]->nb_meal--;
	usleep(all->tt_eat * 1000);
	unlock_forks(all, i);
	pthread_mutex_lock(&(all->philo[i]->nb_meal_mutex));
	if (all->nb_meal != -1 && all->philo[i]->nb_meal == 0)
		return (pthread_mutex_unlock(&(all->philo[i]->nb_meal_mutex)), 1);
	pthread_mutex_unlock(&(all->philo[i]->nb_meal_mutex));
	return (0);
}
