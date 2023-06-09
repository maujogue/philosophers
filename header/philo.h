/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:46:54 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/09 13:05:02 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK 0
# define EAT 1
# define DEAD 2
# define SLEEP 3
# define THINK 4

typedef struct philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	pthread_t		*th;
	int				id;
	int				last_meal;
	int				nb_meal;
}	t_philo;

typedef struct all
{
	pthread_mutex_t	w_mutex;
	pthread_mutex_t	stop_mutex;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nb;
	int				nb_meal;
	int				i;
	t_philo			**philo;
	int				stop;
	struct timeval	time;
}	t_all;

void	init_all(t_all *all, char **argv, int argc);
void	init_philo(t_all *all, int i);
void	philo(t_all *all);
int		calculate_time(struct timeval start_time);
void	*routine(void *all_i);
void	print_message(t_all *all, int status, int i);
int		is_philo_dead(t_all *all, int i);
void	ft_usleep(t_all *all, int time_to, int i);

#endif
