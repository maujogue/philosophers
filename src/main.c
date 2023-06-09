/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:47:32 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/09 17:31:57 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <time.h>

int	philo_eats(t_all *all, int i)
{
	// if ((all->tt_die < all->tt_eat + all->tt_sleep)
	// 	|| (all->nb % 2 == 1 && all->tt_die < all->tt_eat * 3)
	//  || (all->nb % 2 == 0 && all->tt_die < all->tt_eat * 2))
	pthread_mutex_lock(all->philo[i]->l_fork);
	pthread_mutex_lock(&(all->philo[i]->r_fork));
	print_message(all, FORK, i);
	print_message(all, FORK, i);
	all->philo[i]->last_meal = calculate_time(all->time);
	print_message(all, EAT, i);
	all->philo[i]->nb_meal--;
	usleep(all->tt_eat * 1000);
	pthread_mutex_unlock(all->philo[i]->l_fork);
	pthread_mutex_unlock(&(all->philo[i]->r_fork));
	if (all->nb_meal != -1 && all->philo[i]->nb_meal == 0)
		return (1);
	return (0);
}

void	*routine(void *all_i)
{
	t_all	*all;
	int		i;

	all = (t_all *)all_i;
	i = all->i++;
	if (all->nb == 1 && i == 0)
	{
		print_message(all, FORK, i);
		usleep(all->tt_die * 1000);
		return (NULL);
	}
	while (all->stop == 0)
	{
		if (philo_eats(all, i) == 1)
			break ;
		print_message(all, SLEEP, i);
		usleep(all->tt_sleep * 1000);
		print_message(all, THINK, i);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_all		all;

	if ((argc == 5 || argc == 6) && init_all(&all, argv, argc) == 0)
	{
		philo(&all);
		// free_exit(&all);
	}
	else
		write(2, "Invalid parameters\n", 20);
	return (0);
}
