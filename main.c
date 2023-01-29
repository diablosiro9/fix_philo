/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:23 by dojannin          #+#    #+#             */
/*   Updated: 2023/01/29 17:28:04 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help_laucher(t_all *all, int i)
{
	pthread_create(&all->tab_philo[i], NULL, \
		&routine, &(all->philo[i]));
	usleep(100);
	pthread_create(&all->died_philo[i], NULL, \
		&still_alive, &(all->philo[i]));
	pthread_detach(all->tab_philo[i]);
	pthread_detach(all->died_philo[i]);
}

void	laucher(t_all *all, int i)
{
	int	j;

	j = all->num_philo;
	all->time_start = philo_get_time();
	while (i < j)
	{
		all->philo[i].all = all;
		all->philo[i].all->time_start = all->time_start;
		if (i % 2 == 0)
			help_laucher(all, i);
		i++;
	}
	i = 0;
	usleep(100);
	while (i < j)
	{
		all->philo[i].all = all;
		all->philo[i].all->time_start = all->time_start;
		if (i % 2 != 0)
			help_laucher(all, i);
		i++;
	}
}

void	free_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->all->num_philo)
	{
		free(philo);
	}
}

t_all	*doing_all(t_all *all)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&all->die);
	laucher(all, i);
	pthread_mutex_lock(&all->die);
	pthread_mutex_destroy(&all->die);
	pthread_mutex_destroy(&all->aff);
	return (all);
}

int	main(int ac, char **av)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all) * 1);
	all->num_philo = 0;
	if (!all)
		return (0);
	if (ac != 5 && ac != 6 && ac != 2)
		return (printf("Error: Number's parameters\n"));
	if (parsing(ac, av, all) == 0)
		return (0);
	all = doing_all(all);
	free(all->died_philo);
	free(all->tab_philo);
	free(all);
	return (0);
}
