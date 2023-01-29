/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:11:37 by dojannin          #+#    #+#             */
/*   Updated: 2023/01/22 18:34:02 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

pthread_t	*tab_thread(pthread_t *tab, int nombre)
{
	tab = (pthread_t *)malloc(sizeof(pthread_t) * nombre);
	return (tab);
}

pthread_mutex_t	*tab_mutex(pthread_mutex_t *tab, int nb)
{
	int	i;

	i = 0;
	tab = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (!tab)
		return (NULL);
	while (i < nb)
	{
		pthread_mutex_init(&tab[i], NULL);
		i++;
	}
	return (tab);
}
