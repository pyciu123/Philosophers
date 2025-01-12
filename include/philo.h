/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubapyciarz <kubapyciarz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:17:49 by kubapyciarz       #+#    #+#             */
/*   Updated: 2025/01/12 14:45:06 by kubapyciarz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_program t_program;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			is_eating;
	pthread_t	thread;
	t_fork		*l_fork;
	t_fork		*r_fork;
	long		last_meal_time;
	t_program	*program;
}	t_philo;

typedef struct s_program
{
	int				num_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				all_alive;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_locks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}	t_program;

// init.c
void	init_program(t_program *program);
void	init_philo(t_program *program, int num_of_philos);
void	init_forks(t_program *program, int num_of_forks);

// monitor.c
long	get_current_time(void);
void	*life_monitor(void *arg);
int		ft_usleep(size_t milliseconds);

// routine
void	*philo_routine(void *arg);

// threads
int		run_monitor(t_program *program, pthread_t *monitor);
int		run_philosophers(t_program *program);
void philo_thread_join(t_program *program);

#endif