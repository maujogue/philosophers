/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:00:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/07 15:59:56 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int calculate_time(struct timeval start_time)
{
    struct timeval end_time;
    int time_passed;
    
    gettimeofday(&end_time, NULL);  
    time_passed = (end_time.tv_sec - start_time.tv_sec) * 1000.0 + (end_time.tv_usec - start_time.tv_usec) / 1000.0;
    return (time_passed);
}

void    print_message(t_all *all, struct timeval time, int status, int i)
{
    pthread_mutex_lock(&(all->w_mutex));
    if (status == FORK)
        printf("%d %d has taken a fork\n", calculate_time(time), all->philo[i]->nb);
    else if (status == EAT)
	    printf("%d %d is eating\n", calculate_time(time), all->philo[i]->nb);
    else if (status == SLEEP)
        printf("%d %d is sleeping\n", calculate_time(time), all->philo[i]->nb);
    else if (status == THINK)
        printf("%d %d is thinking\n", calculate_time(time), all->philo[i]->nb);
    else if (status == DEAD)
        printf("%d %d died\n", calculate_time(time), all->philo[i]->nb);
	pthread_mutex_unlock(&(all->w_mutex));
}