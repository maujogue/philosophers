/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:47:32 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/06 15:10:32 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <time.h>

pthread_mutex_t mutex;

void    *routine(void *nb)
{
	pthread_mutex_lock(&mutex);
	// printf("philosophers %d created\n", *(int*)i);
	pthread_mutex_unlock(&mutex);
	free(nb);
	return (nb);
}

int	philo(t_table *table)
{
	int	i;
	int	*a;
	int	*res;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < table->nb_ph)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&(table->th[i]), NULL, &routine, a) != 0)
			return (perror(""), 1);
		i++;
	}
	i = 0;
	while (i < table->nb_ph)
	{
		if (pthread_join(table->th[i], (void **)&res) != 0)
			return (perror(""), 1);
		printf("philosophers %d created\n", *(int *)res);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	free(res);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc != 2)
		return (0);
	init_philo(&table, argv);
	philo(&table);
	return (0);
}