/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:30:44 by dojannin          #+#    #+#             */
/*   Updated: 2023/01/29 16:17:37 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message_five(t_philo *phil, long long start)
{
	(void)start;
	printf("%llu %d is died \n", \
		philo_get_time() - phil->all->time_start, phil->id);
	usleep(2000);
	pthread_mutex_unlock(&phil->all->die);
	pthread_mutex_lock(&phil->all->aff);
	return ;
}

void	message_six(t_philo *phil)
{
	printf("%llu Each philosophers ate %d times. \n", \
		philo_get_time() - phil->all->time_start, phil->all->number_eats);
	usleep(2000);
	pthread_mutex_unlock(&phil->all->die);
	pthread_mutex_lock(&phil->all->aff);
	return ;
}

void	first_messages(t_philo *phil, int i)
{
	if (i == 1)
		printf("%llu %d has taken a fork\n", \
			philo_get_time() - phil->all->time_start, phil->id);
	else if (i == 2)
		printf("%llu %d is eating \n", \
			philo_get_time() - phil->all->time_start, phil->id);
	else if (i == 3)
		printf("%llu %d is sleeping \n", \
			philo_get_time() - phil->all->time_start, phil->id);
	else if (i == 4)
		printf("%llu %d is thinking \n", \
			philo_get_time() - phil->all->time_start, phil->id);
}

void	put_message(t_philo *phil, int i)
{
	static int	flop = 0;

	if (flop == 1)
		return ;
	if (i == 5)
	{
		flop = 1;
		return (message_five(phil, phil->all->time_start));
	}
	else if (i == 6)
		return (message_six(phil));
	pthread_mutex_lock(&phil->all->aff);
	if (i == 1 || i == 2 || i == 3 || i == 4)
		first_messages(phil, i);
	if (i != 5 && i != 6)
		pthread_mutex_unlock(&phil->all->aff);
}
