/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:41:37 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/07 16:30:44 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_philo(t_all *all, int i)
{
    all->philo[i] = malloc(sizeof(t_philo));
    all->philo[i]->th = malloc (sizeof(pthread_t));
    if (i == all->nb - 1)
        all->philo[i]->r_fork = all->philo[0]->l_fork;
    else
        pthread_mutex_init(&(all->philo[i]->r_fork), NULL);
    if (i == 0)
        pthread_mutex_init(&all->philo[i]->l_fork, NULL);
    else
        all->philo[i]->l_fork = all->philo[i - 1]->r_fork;
    all->philo[i]->nb = i;
    all->philo[all->i]->last_meal = 0;
}

void	init_threads(t_all *all)
{
	int	*res;
    
	all->i = 0;
	while (all->philo[all->i])
	{
		if (pthread_create(all->philo[all->i]->th, NULL, &routine, (void *)all) != 0)
			return (perror(""));
		all->i++;
	}
	all->i = 0;
	while (all->philo[all->i])
	{
		if (pthread_join(*(all->philo[all->i]->th), (void **)&res) != 0)
			return (perror("ERROR"));
		// printf("philosophers %d created\n", ((t_all *)res)->philo[i]->nb);
		all->i++;
	}
	// pthread_mutex_destroy(&mutex);
	// free(res);
}

void	init_all(t_all *all, char **argv)
{
    int i;

    i = 0;
    all->nb = atoi(argv[1]);
    all->tt_die = atoi(argv[2]);
    all->tt_eat = atoi(argv[3]);
    all->tt_sleep = atoi(argv[4]);
    all->philo = malloc (sizeof(pthread_t) * (all->nb + 1));
    all->i = 0;
    all->stop = 0;
    pthread_mutex_init(&(all->w_mutex), NULL);
    while (i < all->nb)
    {
	    init_philo(all, i);
        i++;
    }
    all->philo[i] = NULL;
    init_threads(all);
}