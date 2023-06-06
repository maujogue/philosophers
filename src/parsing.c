/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:41:37 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/06 15:09:52 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_philo(t_table *table, char **argv)
{
    table->nb_ph = atoi(argv[1]);
    // ph->tt_die = atoi(argv[2]);
    // ph->tt_eat = atoi(argv[3]);
    // ph->tt_sleep = atoi(argv[4]);
	table->th = malloc (sizeof(pthread_t) * table->nb_ph);
}