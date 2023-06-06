/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:47:32 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/06 13:37:39 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <time.h>

int ok = 0;

pthread_mutex_t mutex;

void    *routine()
{
	int i;

	i = 0;
	while (i++ < 100000)
	{
		pthread_mutex_lock(&mutex);
		ok++;
		pthread_mutex_unlock(&mutex);
	}
	// printf("Test from threads\n");
	// sleep(2);
	// printf("Ending\n");
	return NULL;
}

void	*roll_dice()
{
	int value = rand() % 6 + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	return ((void*)result);
}

int main(int argc, char **argv)
{
	(void)argc;
	srand(time(NULL));
	int			*res;
	int         i;
	int			nb = atoi(argv[1]);
	pthread_t	th[nb];

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < nb)
	{
		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
			return (perror(""), 1);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (pthread_join(th[i], (void**) &res) != 0)
			return (perror(""), 1);
		printf("%d\n", *res);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	// printf("%d", ok);
	
	free(res);
	return (0);
}