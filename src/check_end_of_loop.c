/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_of_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:59:19 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/12 13:46:02 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	is_philo_dead(t_all *all, int i)
{
	int	time_since_last_meal;

	pthread_mutex_lock(&(all->philo[i]->last_meal_mutex));
	time_since_last_meal
		= calculate_time(all->time) - all->philo[i]->last_meal;
	pthread_mutex_unlock(&(all->philo[i]->last_meal_mutex));
	if (time_since_last_meal > all->tt_die && all->philo[i]->nb_meal != 0)
	{
		print_message(all, DEAD, i);
		pthread_mutex_lock(&(all->stop_mutex));
		all->stop = 1;
		pthread_mutex_unlock(&(all->stop_mutex));
		return (0);
	}
	return (1);
}

int	has_philo_finished_eating(t_all *all)
{
	int	i;

	i = 0;
	while (all->philo[i])
	{
		pthread_mutex_lock(&(all->philo[i]->nb_meal_mutex));
		if (all->philo[i]->nb_meal != 0)
		{
			pthread_mutex_unlock(&(all->philo[i]->nb_meal_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(all->philo[i]->nb_meal_mutex));
		i++;
	}
	return (0);
}

void	check_end_of_loop(t_all *all)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_philo_dead(all, i) == 0 || has_philo_finished_eating(all) == 0)
			break ;
		i += 1;
		if (i == all->nb)
			i = 0;
	}
}
