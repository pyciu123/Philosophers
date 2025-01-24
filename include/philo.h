#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				*dead;
	int				*is_limit_reached;
	int				meal_ate;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			last_meal_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	int				num_of_philos;
	int				eat_limit;
	int				is_limit_reached;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philo;
	pthread_t		monitor_thread;
}	t_program;

int				ft_atoi(const char *str);

// init.c
void			init_program(t_program *program, t_philo *philos, char **argv);
void			init_forks(pthread_mutex_t *fork, int num_of_philos);
void			init_philos(t_program *program, t_philo *philo,
					pthread_mutex_t *forks, char **argv);
// monitor.c
long			get_current_time(void);
void			msg(char *str, t_philo *philo, int id, int mon_check);
void			ft_usleep(int time);
void			*monitor(void *arg);

// threads_create.c
void			init_threads(t_program *program, pthread_mutex_t *forks);

// routine.c
void			think(t_philo *philo);
void			f_sleep(t_philo *philo);
void			eat(t_philo *philo);

#endif