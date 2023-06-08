/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:41:37 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/08 14:23:51 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_philo(t_all *all, int i)
{
    all->philo[i] = malloc(sizeof(t_philo));
    all->philo[i]->th = malloc (sizeof(pthread_t));
    all->philo[i]->nb = i + 1;
    all->philo[i]->last_meal = 0;
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

void	philo(t_all *all)
{
	int i = 0;
	while (all->philo[i])
	{
        // printf("created %d\n", i);
		if (pthread_create(all->philo[i]->th, NULL, &routine, (void *)all) != 0)
			return (perror(""));
		i++;
	}
    i = 0;
	while (all->philo[i])
	{
        // printf("joined %d\n", i);
		if (pthread_join(*(all->philo[i]->th), NULL) != 0)
			return (perror("ERROR"));
        pthread_detach(*(all->philo[i]->th));
		// printf("philosophers %d created\n", ((t_all *)res)->philo[i]->nb);
        i++;
	}
}

void	init_all(t_all *all, char **argv)
{
    int i;

    i = 0;
    all->nb = atoi(argv[1]);
    all->tt_die = atoi(argv[2]);
    all->tt_eat = atoi(argv[3]);
    all->tt_sleep = atoi(argv[4]);
    gettimeofday(&(all->time), NULL);
    all->philo = malloc (sizeof(pthread_t) * (all->nb + 1));
    all->i = 0;
    all->stop = 0;
    pthread_mutex_init(&(all->w_mutex), NULL);
    pthread_mutex_init(&(all->stop_mutex), NULL);
    while (i < all->nb)
    {
        // printf("-->%d\n", i);
	    init_philo(all, i);
        i++;
    }
    all->philo[i] = NULL;
}