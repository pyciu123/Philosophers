#include "../include/philo.h"

void	init_program(t_program *program, t_philo *philos, char **argv)
{
	program->dead_flag = 0;
	program->philo = philos;
	program->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		program->eat_limit = ft_atoi(argv[5]);
	else
		program->eat_limit = 0;
	program->is_limit_reached = 0;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philos(t_program *program, t_philo *philo,
pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].is_eating = 0;
		philo[i].dead = &program->dead_flag;
		philo[i].is_limit_reached = &program->is_limit_reached;
		philo[i].meal_ate = 0;
		philo[i].start_time = get_current_time();
		philo[i].last_meal_time = get_current_time();
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].write_lock = &program->write_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].l_fork = &forks[i];
		if (i == program->num_of_philos - 1)
			philo[i].r_fork = &forks[0];
		else
			philo[i].r_fork = &forks[i + 1];
		i++;
	}
}
