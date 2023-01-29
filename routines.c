/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:58:54 by dojannin          #+#    #+#             */
/*   Updated: 2023/01/29 16:20:06 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*distrib_fork(t_philo *phil)
{
	pthread_mutex_lock(phil->r_fork);
	put_message(phil, 1);
	if (phil->nb_philo == 1)
		return (phil);
	pthread_mutex_lock(phil->left_fork);
	put_message(phil, 1);
	return (phil);
}

t_philo	*eat(t_philo *phil)
{
	phil->eating = 1;
	if (check_death(phil) != NULL)
		return (NULL);
	put_message(phil, 2);
	ft_usleep(phil->all->time_for_eat);
	phil->eating = 0;
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(phil->left_fork);
	phil->last_meal = philo_get_time() - phil->all->time_start;
	return (phil);
}

void	sleep_and_think(t_philo *philo)
{
	if (check_death(philo) != NULL)
		return ;
	put_message(philo, 3);
	ft_usleep(philo->all->time_for_sleep);
	put_message(philo, 4);
}

t_philo	*help_routine(t_philo *philo)
{
	distrib_fork(philo);
	if (philo->nb_philo == 1)
		return (NULL);
	eat(philo);
	if (philo->nb_philo == 2 && philo->id == 0)
		usleep(5000);
	return (philo);
}

void	*routine(void *phil)
{
	t_philo				*philo;
	int					eat_enough;
	static long long	start = 0;

	philo = (t_philo *)phil;
	eat_enough = 0;
	if (start == 0)
		start = philo->all->time_start;
	philo->all->time_start = start;
	while (1)
	{
		help_routine(philo);
		if (eat_enough == philo->all->number_eats - 1
			&& philo->id == philo->nb_philo)
		{
			philo->died = 1;
			pthread_mutex_lock(&philo->all->die);
			pthread_mutex_lock(&philo->all->aff);
			break ;
		}
		sleep_and_think(philo);
		if (check_death(phil) != NULL)
			return (NULL);
		eat_enough++;
	}
	return ((void *)phil);
}
