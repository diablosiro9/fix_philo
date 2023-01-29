/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:46:42 by dojannin          #+#    #+#             */
/*   Updated: 2023/01/28 18:50:19 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
// COMMENT FOR COMPIL : gcc -g -pthread main.c"

typedef struct s_philo
{
	pthread_mutex_t		is_dead;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*r_fork;
	long				last_meal;
	int					id;
	int					died;
	int					eating;
	int					nb_philo;
	useconds_t			last_time;
	struct s_all		*all;
	unsigned long long	time_for_dead;
	long				time_for_eat;
	long				time_for_sleep;
}t_philo;

typedef struct s_all
{
	t_philo				*philo;
	pthread_t			*tab_philo;
	int					num_philo;
	useconds_t			time_act;
	unsigned long long	time_start;
	struct timeval		timeval;
	int					eat_enough;
	int					number_eats;
	pthread_mutex_t		*forks;
	pthread_mutex_t		aff;
	int					died;
	pthread_mutex_t		die;
	pthread_t			*died_philo;
	unsigned long long	time_for_dead;
	long				time_for_eat;
	long				time_for_sleep;
}t_all;

int					ft_usleep(useconds_t usec);
int					ft_atoi(char *s);
int					ft_atol(char const *s);
int					do_atoi(char const *s, int i, int res, int new_res);
unsigned long long	philo_get_time(void);
pthread_t			*tab_thread(pthread_t *tab, int nombre);
pthread_mutex_t		*tab_mutex(pthread_mutex_t *tab, int nb);
void				*routine(void *all);
t_philo				*eat(t_philo *phil);
t_philo				*distrib_fork(t_philo *phil);
void				*still_alive(void *all);
int					parsing(int ac, char **av, t_all *all);
void				put_message(t_philo *phil, int i);
void				message_five(t_philo *phil, long long start);
t_philo				*check_death(t_philo *phil);

#endif
