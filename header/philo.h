/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:46:54 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/07 15:58:45 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define FORK 0
#define EAT 1
#define DEAD 2
#define SLEEP 3
#define THINK 4


typedef struct s_philo
{
	
	pthread_mutex_t l_fork;
	pthread_mutex_t r_fork;
	pthread_t	*th;
	int			nb;
	int			last_meal;
	
}	t_philo;

typedef struct s_all
{
	pthread_mutex_t w_mutex;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			nb;
	int			i;
	t_philo		**philo;
	int			stop;
}	t_all;

void	init_all(t_all *all, char **argv);
void	init_philo(t_all *all, int i);
void	init_threads(t_all *all);
int		calculate_time(struct timeval start_time);
void    *routine(void *all_i);
void    print_message(t_all *all, struct timeval start_time, int status, int i);