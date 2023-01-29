/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:11:29 by dojannin          #+#    #+#             */
/*   Updated: 2023/01/29 18:25:11 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*check_death(t_philo *phil)
{
	if (philo_get_time() - (phil->last_meal) - phil->all->time_start \
				>= phil->all->time_for_dead - 1)
	{
		put_message(phil, 5);
		return (phil);
	}
	else
		return (NULL);
}

void	*help_alive(t_philo *philo)
{
	put_message(philo, 6);
	return (NULL);
}

void	*still_alive(void *phil)
{
	t_philo		*philo;
	static int	flop;

	philo = (t_philo *)phil;
	flop = 0;
	while (1)
	{
		if (flop == 1)
			return (NULL);
		if (philo->eating == 0 && ((philo_get_time() - \
			(philo->last_meal) - philo->all->time_start \
				> philo->all->time_for_dead - 1) || philo->died == 1))
		{
			pthread_mutex_lock(&philo->all->aff);
			flop = 1;
			if (philo->died == 1)
				return (help_alive(philo));
			put_message(phil, 5);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
