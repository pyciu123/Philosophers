#include "../include/philo.h"

static int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static void	destroy_mutex(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	while (i < program->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

static int	check_meals_count(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_limit_reached == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_if_dead(philo) && check_meals_count(philo) == 0)
	{
		think(philo);
		eat(philo);
		f_sleep(philo);
	}
	return (NULL);
}

void	init_threads(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philo[i].thread, NULL, &routine,
				&program->philo[i]) != 0)
		{
			destroy_mutex(program, forks);
			return ;
		}
		i++;
	}
	if (pthread_create(&program->monitor_thread, NULL, &monitor, program) != 0)
	{
		destroy_mutex(program, forks);
		return ;
	}
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_join(program->philo[i].thread, NULL);
		i++;
	}
	pthread_join(program->monitor_thread, NULL);
}
