#include "../include/philo.h"

static int	check_if_alive(t_program *program)
{
	pthread_mutex_lock(&program->dead_lock);
	if (program->all_alive == 0)
	{
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&program->dead_lock);
	return (0);
}

static void	think(t_philo *philo)
{
	if (check_if_alive(philo->program) == 1)
		return ;
	pthread_mutex_lock(&philo->program->print_locks);
	printf("Philosopher %d is thinking...\n", philo->id);
	pthread_mutex_unlock(&philo->program->print_locks);
}

static void eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		pthread_mutex_lock(&philo->r_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->l_fork->mutex);
	}

    // Aktualizacja czasu ostatniego posiłku przed rozpoczęciem jedzenia
    pthread_mutex_lock(&philo->program->meal_lock);
	philo->is_eating = 1;
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->program->meal_lock);

    // Informowanie o rozpoczęciu jedzenia
    pthread_mutex_lock(&philo->program->print_locks);
    printf("Philosopher %d is eating\n", philo->id);
    pthread_mutex_unlock(&philo->program->print_locks);

    // Symulacja jedzenia
    ft_usleep(philo->program->time_to_eat);
    // Zwolnienie widelców po jedzeniu
	pthread_mutex_lock(&philo->program->meal_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->program->meal_lock);
    pthread_mutex_unlock(&philo->l_fork->mutex);
    pthread_mutex_unlock(&philo->r_fork->mutex);
}

static void	do_sleep(t_philo *philo)
{
	if (check_if_alive(philo->program) == 1)
		return ;
	pthread_mutex_lock(&philo->program->print_locks);
	printf("Philosopher %d is sleeping\n", philo->id);
	ft_usleep(philo->program->time_to_sleep);
	pthread_mutex_unlock(&philo->program->print_locks);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (check_if_alive(program) == 1)	
			return 0;
		eat(philo);
		if (check_if_alive(program) == 1)	
			return 0;
		do_sleep(philo);
		if (check_if_alive(program) == 1)	
			return 0;
		think(philo);
	}
	return (NULL);
}
