/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:46:54 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/06 15:10:06 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_table
{
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			nb_ph;
	pthread_t	*th;
}	t_table;

typedef struct s_philo
{

}	t_ph;

void	init_philo(t_table *table, char **argv);