#include "../include/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	check_if_philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (philo->is_eating == 1)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_for_death(t_program *program)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = program->philo;
	while (i < program->num_of_philos)
	{
		if (!check_if_philo_eating(&philo[i]))
		{
			if (get_current_time() - philo[i].last_meal_time
				>= philo[i].time_to_die)
			{
				pthread_mutex_lock(&program->dead_lock);
				program->dead_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
				msg("died!", philo, philo[i].id, 1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static void	check_if_eat_limit(t_program *program)
{
	int	i;

	i = 0;
	if (program->eat_limit == 0)
		return ;
	while (i < program->num_of_philos)
	{
		if (program->philo[i].meal_ate < program->eat_limit)
			return ;
		i++;
	}
	program->is_limit_reached = 1;
}

void	*monitor(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (check_for_death(program) == 1)
			break ;
		check_if_eat_limit(program);
		if (program->is_limit_reached == 1)
			break ;
	}
	return (NULL);
}
