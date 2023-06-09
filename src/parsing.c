/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:41:37 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/14 11:03:29 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_philo_mutex(t_all *all, int i)
{
	pthread_mutex_init(&(all->philo[i]->last_meal_mutex), NULL);
	pthread_mutex_init(&(all->philo[i]->nb_meal_mutex), NULL);
	if (i == 0)
		pthread_mutex_init(&(all->philo[i]->r_fork), NULL);
	else
	{
		pthread_mutex_init(&(all->philo[i]->r_fork), NULL);
		all->philo[i]->l_fork = &(all->philo[i - 1]->r_fork);
	}
	if (i == all->nb - 1)
		all->philo[0]->l_fork = &(all->philo[i]->r_fork);
}

void	init_philo(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nb)
	{
		all->philo[i] = NULL;
		all->philo[i] = malloc(sizeof(t_philo));
		if (!all->philo[i])
			free_exit(all, 1);
		all->philo[i]->th = NULL;
		all->philo[i]->th = malloc(sizeof(pthread_t));
		if (!all->philo[i]->th)
			free_exit(all, 1);
		all->philo[i]->id = i + 1;
		all->philo[i]->last_meal = 0;
		all->philo[i]->nb_meal = all->nb_meal;
		init_philo_mutex(all, i);
		i++;
	}
	all->philo[i] = NULL;
}

int	init_all(t_all *all, char **argv, int argc)
{
	all->nb = atoi(argv[1]);
	all->tt_die = atoi(argv[2]);
	all->tt_eat = atoi(argv[3]);
	all->tt_sleep = atoi(argv[4]);
	if (argc == 6)
		all->nb_meal = atoi(argv[5]);
	if (all->nb <= 0 || all->tt_die <= 0 || all->tt_eat <= 0
		|| all->tt_sleep <= 0 || (argc == 6 && all->nb_meal <= 0))
		return (1);
	all->nb_meal = -1;
	if (argc == 6)
		all->nb_meal = atoi(argv[5]);
	gettimeofday(&(all->time), NULL);
	all->philo = NULL;
	all->philo = malloc (sizeof(pthread_t) * (all->nb + 1));
	if (!all->philo)
		free_exit(all, 1);
	all->i = 0;
	all->stop = 0;
	pthread_mutex_init(&(all->w_mutex), NULL);
	pthread_mutex_init(&(all->stop_mutex), NULL);
	init_philo(all);
	return (0);
}
