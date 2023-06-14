/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:47:32 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/14 11:27:13 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <time.h>

void	*routine(void *all_i)
{
	t_all	*all;
	int		i;

	all = (t_all *)all_i;
	i = all->i++;
	if (all->philo[i]->id % 2 == 1)
		usleep(all->tt_eat * 1000);
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
		if (all->nb % 2 == 1)
			usleep(all->tt_eat * 1000);
	}
	return (NULL);
}

void	philo(t_all *all)
{
	int	i;

	i = 0;
	while (all->philo[i])
	{
		if (pthread_create(all->philo[i]->th, NULL, &routine, (void *)all) != 0)
			return (perror("ERROR"));
		i++;
		usleep(100);
	}
	i = 0;
	check_end_of_loop(all);
	while (all->philo[i])
	{
		if (pthread_join(*(all->philo[i]->th), NULL) != 0)
			return (perror("ERROR"));
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_all		all;

	if ((argc == 5 || argc == 6) && init_all(&all, argv, argc) == 0)
	{
		philo(&all);
		free_exit(&all, 0);
	}
	else
		write(2, "Invalid parameters\n", 20);
	return (0);
}
