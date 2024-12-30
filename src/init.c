#include "../include/philo.h"

void	init_forks(t_program *program, int num_of_forks)
{
	int	i;

	i = 0;
	program->forks = malloc(sizeof(t_fork) * num_of_forks);
	if (!program->forks)
		return ;
	while (i < num_of_forks)
	{
		program->forks[i].id = i + 1;
		pthread_mutex_init(&program->forks[i].mutex, NULL);
		i++;
	}
}

static int	get_left_id(int philo_id, int num_of_philos)
{
	if (philo_id == 1)
		return (num_of_philos);
	else
		return (philo_id - 1);
}

static int	get_right_id(int philo_id, int num_of_philos)
{
	if (philo_id == num_of_philos)
		return (1);
	else
		return (philo_id + 1);
}

void	init_philo(t_program *program, int num_of_philos)
{
	int	i;
	int	l_fork_id;
	int	r_fork_id;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * num_of_philos);
	if (!program->philos)
		return ;
	while (i < num_of_philos)
	{
		l_fork_id = get_left_id(i + 1, num_of_philos) - 1;
		r_fork_id = get_right_id(i + 1, num_of_philos) - 1;
		program->philos[i].id = i + 1;
		program->philos[i].l_fork = &program->forks[l_fork_id];
		program->philos[i].r_fork = &program->forks[r_fork_id];
		program->philos[i].last_meal_time = get_current_time();
		program->philos[i].program = program;
		program->philos[i].is_eating = 0;
		i++;
	}
}

void	init_program(t_program *program)
{
	program->num_philo = 0;
	program->forks = NULL;
	program->philos = NULL;
	program->time_to_die = 0;
	program->time_to_eat = 0;
	program->time_to_sleep = 0;
	program->all_alive = 1;
	pthread_mutex_init(&program->print_locks, NULL);
	pthread_mutex_init(&program->state_lock, NULL);
}