/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:57:12 by dojannin          #+#    #+#             */
/*   Updated: 2023/01/28 13:47:36 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	attribute_forks(t_all *all)
{
	int	i;

	i = 0;
	pthread_mutex_init(&all->aff, NULL);
	pthread_mutex_init(&all->die, NULL);
	while (i < all->num_philo)
	{
		if (i == 0)
			all->philo[i].left_fork = &all->forks[all->num_philo - 1];
		else
			all->philo[i].left_fork = &all->forks[i - 1];
		all->philo[i].r_fork = &all->forks[i];
		all->philo[i].id = i + 1;
		all->philo[i].eating = 0;
		all->philo[i].time_for_eat = all->time_for_eat;
		all->philo[i].time_for_dead = all->time_for_dead;
		all->philo[i].time_for_sleep = all->time_for_sleep;
		all->philo[i].last_meal = 0;
		all->philo[i].died = 0;
		all->philo[i].nb_philo = all->num_philo;
		pthread_mutex_init(&all->philo[i].is_dead, NULL);
		i++;
	}
}

int	help_parsing(char **av, t_all *all, t_philo *philo)
{
	all->eat_enough = 0;
	all->died_philo = tab_thread(all->died_philo, all->num_philo);
	all->time_for_dead = ft_atol(av[2]);
	all->time_for_eat = ft_atol(av[3]);
	all->time_for_sleep = ft_atol(av[4]);
	if (all->time_for_dead < 60 || all->time_for_eat < 60
		|| all->time_for_sleep < 60)
	{
		printf("Error: Time_Values must be equal or greater than 60.\n");
		return (0);
	}
	all->time_start = 0;
	philo->time_for_dead = all->time_for_dead;
	philo->time_for_eat = all->time_for_eat;
	philo->time_for_sleep = all->time_for_sleep;
	philo->all = all;
	return (1);
}

int	return_parsing(char **av, t_all *all, t_philo *philo)
{
	if (help_parsing(av, all, philo) == 0)
		return (0);
	return (1);
}

int	parsing(int ac, char **av, t_all *all)
{
	t_philo	*philo;
	int		save;

	save = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (0);
	all->num_philo = ft_atoi(av[1]);
	save = all->num_philo;
	if (all->num_philo < 0)
	{
		printf("Error: Number's Philos is negative.\n");
		return (0);
	}
	if (ac == 6)
		all->number_eats = ft_atoi(av[5]);
	all->tab_philo = tab_thread(all->tab_philo, all->num_philo);
	if (all->tab_philo == NULL)
		return (0);
	all->forks = tab_mutex(all->forks, ft_atoi(av[1]));
	all->num_philo = save;
	all->philo = philo;
	attribute_forks(all);
	return (return_parsing(av, all, philo));
}
